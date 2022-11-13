#pragma once

#ifndef DRONE_MONITOR_VIEW_3D_HPP
#define DRONE_MONITOR_VIEW_3D_HPP

#include <QFile>
#include <QWidget>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
class View3D : public Qt3DExtras::Qt3DWindow {
  Q_OBJECT

public:
  View3D();

  QVector<Qt3DCore::QEntity*> drawFile(const QString& path);
  Qt3DCore::QEntity* drawLine(const QVector3D& start, const QVector3D& end,
                              const QColor& color);
  void centerCamera();

private:
  void addSphere();
  Qt3DCore::QEntity* m_rootEntity;
  Qt3DRender::QCamera* m_cameraEntity;
  Qt3DCore::QEntity* m_lightEntity;
  Qt3DRender::QPointLight* m_light;
  Qt3DExtras::QOrbitCameraController* m_cameraController;
};

#endif
