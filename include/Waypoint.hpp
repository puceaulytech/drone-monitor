#ifndef WAYPOINT_HPP
#define WAYPOINT_HPP
#include <QCustom3DItem>
#include <QVector3D>
class Waypoint : public QCustom3DItem {
  Q_OBJECT
public:
  Waypoint();
  Waypoint(QVector3D position, float precision /* precision en metre  */);
  QVector3D position;
  float precision;
  QString meshFile;
};

#endif  // WAYPOINT_HPP
