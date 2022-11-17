#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <Q3DSurface>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QLinearGradient>
#include <QMessageBox>
#include <QProgressDialog>
#include <QSurface>
#include <QVector3D>
#include <QWidget>
//#include <QtMath>
class Surface : public Q3DSurface {
  Q_OBJECT

public:
  Surface(float degX, float degY, float around);
  QSurfaceDataArray* parseFileToArray(QString path);

private:
  float m_degX;
  float m_degY;
  float m_around;
  int m_sizeX;
  int m_sizeY;
  int m_undefined;
  int m_xll;
  float m_cellsize;
  int m_yll;
  int m_value;
  int m_resolution;
  QProgressDialog* shower;
  void initFromFileHeader(QString path);
  QSurfaceDataArray* m_mainArray;
  QSurfaceDataArray* setupArray();

Q_SIGNALS:
  void update(int i);
public Q_SLOTS:
  void updateValue(int i);
};

#endif  // SURFACE_HPP
