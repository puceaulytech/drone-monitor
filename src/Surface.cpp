#include <Surface.hpp>

Surface::Surface() {
  // setFlags(flags() ^ Qt::FramelessWindowHint);
  m_mainArray = setupArray();
  QSurface3DSeries* series = new QSurface3DSeries;
  series->dataProxy()->resetArray(m_mainArray);
  addSeries(series);

  QLinearGradient gr;
  gr.setColorAt(0.0, Qt::black);
  gr.setColorAt(0.33, Qt::blue);
  gr.setColorAt(0.67, Qt::red);
  gr.setColorAt(1.0, Qt::yellow);
  seriesList().at(0)->setBaseGradient(gr);
  seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
  axisX()->setRange(0, 100);
  axisZ()->setRange(0, 100);
}

QSurfaceDataArray* Surface::setupArray() {
  int sizeX = 100;
  int sizeY = 100;
  auto* data = new QSurfaceDataArray;
  for (int i = 0; i < sizeX; i++) {
    auto* row = new QSurfaceDataRow(sizeY);
    for (int j = 0; j < sizeY; j++) {
      qInfo() << i << "   " << j;
      (*row)[j].setPosition(QVector3D(i, i + j + qSin(j + i), j));
    }
    *data << row;
  }

  return data;
}
