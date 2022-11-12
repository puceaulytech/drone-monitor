#pragma once

#ifndef DRONE_MONITOR_VIEW_3D_HPP
#define DRONE_MONITOR_VIEW_3D_HPP

#include <QWidget>
#include <Qt3DExtras>

class View3D : public Qt3DExtras::Qt3DWindow {
public:
  View3D();

private:
  void addSphere();

  Qt3DCore::QEntity* m_rootEntity;
  Qt3DRender::QCamera* m_cameraEntity;
  Qt3DCore::QEntity* m_lightEntity;
  Qt3DRender::QPointLight* m_light;
  Qt3DExtras::QFirstPersonCameraController* m_cameraController;
};

#endif
