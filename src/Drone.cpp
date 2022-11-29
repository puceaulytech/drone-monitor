#include <Drone.hpp>
Drone::Drone() {
  setMeshFile("C:/Users/robin/Desktop/test.obj");
  setPosition(QVector3D(7.143647f, 300.0f, 43.4651584f));
  setScaling(QVector3D(0.005f, 0.005f, 0.005f));
  QImage color = QImage(2, 2, QImage::Format_RGB32);
  color.fill(Qt::red);
  setTextureImage(color);
}
void Drone::updateTelemetry() {
  setPosition(
      QVector3D(position().x(), position().y(), position().z() + 0.001));
  qInfo() << "MOVED";
  setRotationAxisAndAngle(QVector3D(0, 1, 0), 180);
  // potentiellement prendre le paquet en paramètre et en extraire toute la
  // telemetrie du drone
}
// on ne peut jamais condenser un fluide hyper critique en le comprimant a t
// constant
void Drone::computePath(int n) {}
