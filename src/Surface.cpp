#include <Surface.hpp>

Surface::Surface() {
  // setFlags(flags() ^ Qt::FramelessWindowHint);
  shower = new QProgressDialog;
  shower->setMinimum(0);
  shower->setMaximum(5998);
  shower->setModal(true);
  shower->setValue(shower->minimum());
  connect(this, &Surface::update, this, &Surface::updateValue);
  setAspectRatio(50);
  m_mainArray = parseFileToArray(QString(""));
  QSurface3DSeries* series = new QSurface3DSeries;
  series->setDrawMode(QSurface3DSeries::DrawSurface);
  series->dataProxy()->resetArray(m_mainArray);
  addSeries(series);
  activeTheme()->setBackgroundColor(QColor(0, 0, 0));
  activeTheme()->setWindowColor(QColor(0, 0, 0));
  QLinearGradient gr;
  gr.setColorAt(0.002, Qt::black);
  gr.setColorAt(0.01, Qt::green);
  gr.setColorAt(0.5, Qt::yellow);
  gr.setColorAt(1, Qt::red);
  seriesList().at(0)->setBaseGradient(gr);
  seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
  scene()->activeCamera()->setMaxZoomLevel(5000.0f);
  setMeasureFps(true);
  qInfo() << currentFps();
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
    QString line = in.readLine();
  };
  double heightMultiplier = 1;
  m_sizeX = 5999;  // 5999
  m_sizeY = 5999;

  double step =
      static_cast<double>(m_resolution) / static_cast<double>(m_sizeX);
  qInfo() << "step :" << step;
  for (int i = 0; i < m_sizeX; i++) {
    emit update(i);
    QString line = in.readLine();
    QStringList fields = line.split(" ");
    double x = i * step;
    auto* row = new QSurfaceDataRow(m_sizeY);
    for (int j = 0; j < m_sizeY; j++) {
      double z = j * step;
      int y;
      if (fields[j].toDouble() == m_undefined) {
        y = 0;
      } else {
        y = fields[j].toDouble();
      }
      (*row)[j].setPosition(QVector3D(z, heightMultiplier * y, x));
    }
    *data << row;
    // free(row);
  }
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
  for (int i = 0; i < fields.length(); i++) {
    qInfo() << i << "   " << fields[i];
  }
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
  double cellsize;
  cellsize = fields[6].toFloat();
  m_resolution = qFloor((m_sizeX * cellsize) + 0.5);
  line = in.readLine();
  fields = line.split(" ");
  m_undefined = fields[2].toInt();
  qInfo() << m_sizeX << m_sizeY << m_xll << m_yll << m_resolution
          << m_undefined;
  file.close();
}
void Surface::updateValue(int i) {
  shower->setValue(i);
  qInfo() << shower->value();
}
