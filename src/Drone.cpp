#include <Drone.hpp>
Drone::Drone(float resolution) {
  setMeshFile("C:/Users/robin/Desktop/test.obj");
  setPosition(QVector3D(7.123647f, 300.0f, 43.5651584f));
  setScaling(QVector3D(0.005f, 0.005f, 0.005f));
  QImage color = QImage(2, 2, QImage::Format_RGB32);
  color.fill(Qt::red);
  ez = 0;
  setTextureImage(color);
  m_position = QVector3D(position());
  start = new Waypoint();
  m_resolution = resolution;
}
void Drone::updateTelemetry() {
  setPosition(m_position);  // qSin(ez) / 10.0));
  QVector3D merde(7.065778f, 350.0f, 43.618497f);
  ez += 0.0001;
  m_position = QVector3D(7.123647f, 300.0f, 43.5651584f + ez);
  // setRotation(QQuaternion::fromEulerAngles(50, 0, 20));
  QVector3D delta = (m_position - merde);
  delta.setX(delta.x() * m_resolution);
  delta.setZ(delta.z() * m_resolution);
  delta.setY(delta.y() / 10);
  delta.setY(0);
  QQuaternion caca = QQuaternion::rotationTo(QVector3D(0, 0, -1), delta);

  setRotation(caca.inverted());
  qInfo() << delta;
  // setRotationAxisAndAngle(QVector3D(0, 1, 0), 180);
  //  potentiellement prendre le paquet en paramètre et en extraire toute la
  //  telemetrie du drone
}
// on ne peut jamais condenser un fluide hyper critique en le comprimant a t
// constant
void Drone::computePath(int n) {}
