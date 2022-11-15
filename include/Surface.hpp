#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <Q3DSurface>
#include <QDebug>
#include <QLinearGradient>
#include <QSurface>
#include <QVector3D>
#include <QWidget>
//#include <QtMath>
class Surface : public Q3DSurface {
  Q_OBJECT

public:
  Surface();

private:
  int m_min;
  int m_max;
  QSurfaceDataArray* m_mainArray;
  QSurfaceDataArray* setupArray();
};

#endif  // SURFACE_HPP
