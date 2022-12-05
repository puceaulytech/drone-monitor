#include <Surface.hpp>

Surface::Surface(float degX, float degY, float around) {
  // setFlags(flags() ^ Qt::FramelessWindowHint);
  m_degX = degX;
  m_degY = degY;
  m_around = around;
  // axisZ()->setReversed(true);
  shower = new QProgressDialog;
  shower->setMinimum(0);
  shower->setMaximum(5998);
  shower->setModal(true);
  shower->setValue(shower->minimum());
  shower->setLabelText("Processing very complex equations...");
  connect(this, &Surface::update, this, &Surface::updateValue);
  setAspectRatio(10);  // 15 50
  m_mainArray = parseFileToArray(QString(""));
  QSurface3DSeries* series = new QSurface3DSeries;
  series->setDrawMode(QSurface3DSeries::DrawSurface);
  // series->setFlatShadingEnabled(false);
  series->dataProxy()->resetArray(m_mainArray);
  addSeries(series);
  activeTheme()->setBackgroundColor(QColor(0, 0, 0));
  activeTheme()->setWindowColor(QColor(0, 0, 0));
  QLinearGradient gr;
  gr.setColorAt(0.0, Qt::darkBlue);
  gr.setColorAt(0.01, Qt::blue);
  gr.setColorAt(0.015, Qt::green);
  gr.setColorAt(0.5, Qt::yellow);
  gr.setColorAt(1, Qt::red);
  seriesList().at(0)->setBaseGradient(gr);
  seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
  scene()->activeCamera()->setMaxZoomLevel(5000.0f);
  setMeasureFps(true);
  qInfo() << currentFps();
  // axisY()->setRange(-5, 5000);
  QImage color = QImage(2, 2, QImage::Format_RGB32);
  color.fill(Qt::red);
  QCustom3DItem* plane = new QCustom3DItem;
  //"C:\Users\robin\Desktop\Mig_29_obj.obj"
  plane->setMeshFile("://ressources/mig29.obj");
  // 43.56515844128664, 7.133647658036022
  plane->setPosition(QVector3D(7.133647f, 300.0f, 43.5651584f));
  plane->setScaling(QVector3D(0.005f, 0.005f, 0.005f));
  // plane->setRotationAxisAndAngle ( QQuaternion::fromAxisAndAngle(0.0f, 1.0f,
  // 0.0f, 45.0f));
  plane->setTextureImage(color);
  // plane->setVisible(true);
  // 43.618497136583315, 7.065778601779528
  Waypoint* coucou =
      new Waypoint(QVector3D(7.065778f, 350.0f, 43.618497f), 10.0);
  addCustomItem(coucou);
  addCustomItem(plane);

  // Drone* ez = new Drone();
  drone = new Drone(m_resolution);
  addCustomItem(drone);
}
QSurfaceDataArray* Surface::setupArray() {
  int sizeX = 100;
  int sizeY = 100;
  auto* data = new QSurfaceDataArray;
  for (int i = 0; i < sizeX; i++) {
    auto* row = new QSurfaceDataRow(sizeY);
    for (int j = 0; j < sizeY; j++) {
      (*row)[j].setPosition(QVector3D(j, qSin(0.1 * (i - j)), i));
    }
    *data << row;
  }
  return data;
}

QSurfaceDataArray* Surface::parseFileToArray(QString path) {
  auto* data = new QSurfaceDataArray;

  if (path == "") {
    path = QFileDialog::getOpenFileName(
        nullptr, "Open 3D Object", QDir::currentPath(), "Text files (*.asc)");
  }
  initFromFileHeader(path);
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(nullptr, "File not found",
                          "Cannot find specified file");
    return data;
  }
  // alors ca c'est un point de methode : bien observer le domaine
  // d'integrabilité et combien d'integrales il faut considerer
  QTextStream in(&file);
  for (int k = 0; k < 7; k++) {
    in.readLine();
  };
  /*
    QList<QList<int>> coucou;
    for (int i = 0; i < 6000; i++) {
      emit update(i);
      QString line = in.readLine();
      QStringList fields = line.split(" ");
      QList<int> ez;
      for (int j = 0; j < 6000; j++) {
        ez.append(fields[j].toInt());
      }
      coucou.append(ez);
    }
  */
  m_sizeX = 5999;  // 5999
  m_sizeY = 5999;
  double step =
      static_cast<double>(m_resolution) / static_cast<double>(m_sizeX);
  int lowX = (m_degX - m_around - m_xll) * (1 / step);
  int upX = (m_degX + m_around - m_xll) / step;
  int lowY = (m_degY - m_around - m_yll) / step;
  int upY = (m_degY + m_around - m_yll) / step;

  qInfo() << lowX * m_cellsize << upX * m_cellsize;
  qInfo() << lowY * m_cellsize << upY * m_cellsize;
  // le cycle de carnot a un rendement plus important par rapport a tout les
  // autres cycles moteurs
  m_resolution = qFloor((static_cast<float>(m_sizeX) * m_cellsize) + 0.5);

  qInfo() << "step :" << step;
  double z;
  double x;
  qInfo() << "drawing from " << m_xll + lowX * m_cellsize << "to"
          << m_xll + upX * m_cellsize;
  for (int i = 0; i < m_sizeY; i++) {
    emit update(i);
    // if on est entre xmin et xmax de la surface qu'on veut dessiner

    QString line = in.readLine();
    QStringList fields = line.split(" ");

    z = m_yll + i * step;

    if (i >= lowY /*- 2000* marche bien wtf */ && i < upY /*- 2000*/) {
      auto* row = new QSurfaceDataRow(upX - lowX);
      int index = 0;
      for (int j = lowX; j < upX; j++) {
        // if same mais y

        x = m_xll + j * step;
        double y;
        if (fields[j].toDouble() == m_undefined) {
          y = 0;
        } else {
          y = fields[j].toDouble();
        }
        (*row)[index].setPosition(QVector3D(x, y, z));

        index++;
      }
      // 43 - 1
      // 42 + z

      *data << row;
      // data->prepend(row);
      //   free(row);
    }
  }
  file.close();
  return data;
}

void Surface::initFromFileHeader(QString path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(nullptr, "File not found",
                          "Cannot find specified file");
    return;
  }

  QTextStream in(&file);
  QString line = in.readLine();
  QStringList fields = line.split(" ");
  for (int i = 0; i < fields.length(); i++) {}
  m_sizeX = fields[9].toInt();

  line = in.readLine();
  fields = line.split(" ");
  m_sizeY = fields[9].toInt();

  line = in.readLine();
  fields = line.split(" ");
  m_xll = fields[5].toInt();

  line = in.readLine();
  fields = line.split(" ");
  m_yll = fields[5].toInt();
  line = in.readLine();
  fields = line.split(" ");

  m_cellsize = fields[6].toFloat();
  m_resolution = qFloor((static_cast<float>(m_sizeX) * m_cellsize) + 0.5);
  line = in.readLine();
  fields = line.split(" ");
  m_undefined = fields[2].toInt();
  qInfo() << m_xll << m_yll;
  file.close();
}
void Surface::updateValue(int i) {
  shower->setValue(i);
  // qInfo() << shower->value();
}
void Surface::initDrone(Drone drone) {
  // faut mettre le code pour initialiser le QCustom3DObject mais la il est
  // 1h37 j'ai la flemme de ctrl c ctrl v comme un bourain donc je vais plutot
  // bosser sur Drone.cpp
}
