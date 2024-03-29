#ifndef DRONE_HPP
#define DRONE_HPP
#include <Q3DSurface>
#include <QObject>
#include <QVector3D>
#include <Waypoint.hpp>

class Drone : public QCustom3DItem {
  Q_OBJECT
public:
  Drone(float resolution);
  // QVector3D getBezierPoint(QVector3D* points, int numPoints, float t);
  void computePath(int n);

  // telemetry
  QString m_meshFile;
  QVector3D m_position;
  float yaw;
  float picth;
  float roll;
  QQuaternion m_rotation;
  QVector3D m_heading;
  float m_speed;
  float height;
  QList<Waypoint> path;
  Waypoint* start;
  Waypoint* target;
  float ez;
  float m_resolution;

private:
public Q_SLOTS:
  void updateTelemetry();
};

#endif  // DRONE_HPP
