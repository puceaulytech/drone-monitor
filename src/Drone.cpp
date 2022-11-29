#include <Drone.hpp>
Drone::Drone() {}
void Drone::updateTelemetry() {
  // potentiellement prendre le paquet en paramètre et en extraire toute la
  // telemetrie du drone
}
// on ne peut jamais condenser un fluide hyper critique en le comprimant a t
// constant
void Drone::computePath(int n) {
  QVector3D test = get

      QVector3D
      Drone::getBezierPoint(QVector3D * points, int numPoints, float t) {
    QVector3D* tmp = new QVector3D[numPoints];
    memcpy(tmp, points, numPoints * sizeof(QVector3D));
    int i = numPoints - 1;
    while (i > 0) {
      for (int k = 0; k < i; k++) tmp[k] = tmp[k] + t * (tmp[k + 1] - tmp[k]);
      i--;
    }
    QVector3D answer = tmp[0];
    delete[] tmp;
    return answer;
  }
}
