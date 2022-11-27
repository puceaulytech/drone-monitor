#ifndef WAYPOINT_HPP
#define WAYPOINT_HPP
#include <QVector3D>
class Waypoint {
public:
  Waypoint(QVector3D position, float precision /* precision en metre  */);
  QVector3D m_position;
  float m_precision;
};

#endif  // WAYPOINT_HPP
