#include <View3D.hpp>

View3D::View3D() {
  defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

  m_rootEntity = new Qt3DCore::QEntity;
  m_cameraEntity = camera();

  m_cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f,
                                                   1000.0f);
  m_cameraEntity->setPosition(QVector3D(0, 0, 20.0f));
  m_cameraEntity->setUpVector(QVector3D(0, 1, 0));
  m_cameraEntity->setViewCenter(QVector3D(0, 0, 0));

  m_lightEntity = new Qt3DCore::QEntity(m_rootEntity);
  m_light = new Qt3DRender::QPointLight(m_lightEntity);
  m_light->setColor("white");
  m_light->setIntensity(1);
  m_lightEntity->addComponent(m_light);
  auto* lightTransform = new Qt3DCore::QTransform(m_lightEntity);
  lightTransform->setTranslation(m_cameraEntity->position());
  m_lightEntity->addComponent(lightTransform);

  m_cameraController =
      new Qt3DExtras::QFirstPersonCameraController(m_rootEntity);
  m_cameraController->addComponent(lightTransform);

  setRootEntity(m_rootEntity);

  addSphere();
}

void View3D::addSphere() {
  auto* sphereMesh = new Qt3DExtras::QSphereMesh;
  sphereMesh->setRings(20);
  sphereMesh->setSlices(20);
  sphereMesh->setRadius(2);

  auto* sphereTransform = new Qt3DCore::QTransform;
  sphereTransform->setScale(1.3f);
  sphereTransform->setTranslation(QVector3D(-5.0f, -4.0f, 0.0f));

  auto* sphereMaterial = new Qt3DExtras::QPhongMaterial();
  sphereMaterial->setDiffuse(QColor(QRgb(0xa69929)));

  auto* sphere = new Qt3DCore::QEntity(m_rootEntity);
  sphere->addComponent(sphereMesh);
  sphere->addComponent(sphereMaterial);
  sphere->addComponent(sphereTransform);
}
