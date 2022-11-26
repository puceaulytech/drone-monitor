#ifndef DRONE_HPP
#define DRONE_HPP
#include <QObject>
#include <QVector3D>
class Drone {
public:
  Drone();

private:
  QString m_meshFile;
  QVector3D m_position;
  QVector3D m_speed;
  // telemetry data
public Q_SLOTS:
  void updateTelemetry();
};

#endif  // DRONE_HPP
