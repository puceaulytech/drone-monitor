#ifndef DRONE_HPP
#define DRONE_HPP
#include <QObject>
#include <QVector3D>
#include <Waypoint.hpp>
class Drone {
public:
  Drone();
  void addWaypoint(Waypoint add);
  Waypoint getWaypoint(int index);
  // bezier

private:
  QString m_meshFile;
  QVector3D m_position;
  QVector3D m_heading;
  float m_speed;
  QList<Waypoint> path;

  // path
  //  telemetry data
public Q_SLOTS:
  void updateTelemetry();
};

#endif  // DRONE_HPP
