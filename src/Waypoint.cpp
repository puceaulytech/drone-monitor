#include <Waypoint.hpp>
Waypoint::Waypoint(QVector3D pos, float pre) {
  position = pos;
  precision = pre;
  meshFile = "://ressources/waypoint.obj";
  QImage color = QImage(32, 32, QImage::Format_ARGB32);
  color.fill(QColor(255, 0, 0, 100));
  setMeshFile(meshFile);
  setTextureImage(color);
  setPosition(position);
  setScaling(QVector3D(0.01f, 0.01f, 0.01f));
}
Waypoint::Waypoint(){};
