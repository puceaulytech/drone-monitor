#include <Surface.hpp>

Surface::Surface() {
  // setFlags(flags() ^ Qt::FramelessWindowHint);
  setAspectRatio(15);
  m_mainArray = parseFileToArray(QString(""));
  QSurface3DSeries* series = new QSurface3DSeries;
  series->setDrawMode(QSurface3DSeries::DrawSurface);
  series->dataProxy()->resetArray(m_mainArray);
  addSeries(series);
  activeTheme()->setBackgroundColor(QColor(0, 0, 0));
  activeTheme()->setWindowColor(QColor(0, 0, 0));
  QLinearGradient gr;
  gr.setColorAt(0.0, Qt::black);
  gr.setColorAt(0.33, Qt::blue);
  gr.setColorAt(0.67, Qt::red);
  gr.setColorAt(1000, Qt::yellow);
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
  initFromFileHeader(path);
  if (path == "") {
    path = QFileDialog::getOpenFileName(
        nullptr, "Open 3D Object", QDir::currentPath(), "Text files (*.asc)");
  }
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(nullptr, "File not found",
                          "Cannot find specified file");
    return data;
  }

  QTextStream in(&file);
  for (int k = 0; k < 7; k++) {
    QString line = in.readLine();
  };
  double heightMultiplier = 1;
  m_sizeX = 1000;  // 5999
  m_sizeY = 1000;
  double step =
      static_cast<double>(m_resolution) / static_cast<double>(m_sizeX);
  qInfo() << "step :" << step;
  for (int i = 0; i < m_sizeX; i++) {
    qInfo() << "done %"
            << (static_cast<float>(i) / static_cast<float>(m_sizeX)) * 100;
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
  }
  return data;
}

void Surface::initFromFileHeader(QString path) {
  if (path == "") {
    path = QFileDialog::getOpenFileName(
        nullptr, "Open 3D Object", QDir::currentPath(), "Text files (*.asc)");
  }
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
