#include <QMessageBox>
#include <View3D.hpp>

View3D::View3D() {
  defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));

  m_rootEntity = new Qt3DCore::QEntity;
  m_cameraEntity = camera();

  m_cameraEntity->lens()->setPerspectiveProjection(90.0f, 16.0f / 9.0f, 0.01f,
                                                   10000.0f);
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

  m_cameraController = new Qt3DExtras::QOrbitCameraController(m_rootEntity);
  m_cameraController->addComponent(lightTransform);
  m_cameraController->setCamera(m_cameraEntity);
  setRootEntity(m_rootEntity);

  // addSphere();
  drawLine({0, 0, 0}, {20, 0, 0}, Qt::red, m_rootEntity);    // X
  drawLine({0, 0, 0}, {0, 20, 0}, Qt::green, m_rootEntity);  // Y
  drawLine({0, 0, 0}, {0, 0, 20}, Qt::blue, m_rootEntity);   // Z))

  // TODO: trouver le chemin relatif de ce ptn de truc pck wallah jvais cabler a
  // force de ctrl c ctrl v le path du truc
}
void View3D::drawLine(const QVector3D& start, const QVector3D& end,
                      const QColor& color, Qt3DCore::QEntity* _rootEntity) {
  auto* geometry = new Qt3DCore::QGeometry(_rootEntity);

  // position vertices (start and end)
  QByteArray bufferBytes;
  bufferBytes.resize(
      3 * 2 *
      sizeof(float));  // start.x, start.y, start.end + end.x, end.y, end.z
  float* positions = reinterpret_cast<float*>(bufferBytes.data());
  *positions++ = start.x();
  *positions++ = start.y();
  *positions++ = start.z();
  *positions++ = end.x();
  *positions++ = end.y();
  *positions++ = end.z();

  auto* buf = new Qt3DCore::QBuffer(geometry);
  buf->setData(bufferBytes);

  auto* positionAttribute = new Qt3DCore::QAttribute(geometry);
  positionAttribute->setName(
      Qt3DCore::QAttribute::defaultPositionAttributeName());
  positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
  positionAttribute->setVertexSize(3);
  positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
  positionAttribute->setBuffer(buf);
  positionAttribute->setByteStride(3 * sizeof(float));
  positionAttribute->setCount(2);
  geometry->addAttribute(
      positionAttribute);  // We add the vertices in the geometry

  // connectivity between vertices
  QByteArray indexBytes;
  indexBytes.resize(2 * sizeof(unsigned int));  // start to end
  unsigned int* indices = reinterpret_cast<unsigned int*>(indexBytes.data());
  *indices++ = 0;
  *indices++ = 1;

  auto* indexBuffer = new Qt3DCore::QBuffer(geometry);
  indexBuffer->setData(indexBytes);

  auto* indexAttribute = new Qt3DCore::QAttribute(geometry);
  indexAttribute->setVertexBaseType(Qt3DCore::QAttribute::UnsignedInt);
  indexAttribute->setAttributeType(Qt3DCore::QAttribute::IndexAttribute);
  indexAttribute->setBuffer(indexBuffer);
  indexAttribute->setCount(2);
  geometry->addAttribute(
      indexAttribute);  // We add the indices linking the points in the geometry

  // mesh
  auto* line = new Qt3DRender::QGeometryRenderer(_rootEntity);
  line->setGeometry(geometry);
  line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
  auto* material = new Qt3DExtras::QPhongMaterial(_rootEntity);
  material->setAmbient(color);

  // entity
  auto* lineEntity = new Qt3DCore::QEntity(_rootEntity);
  lineEntity->addComponent(line);
  lineEntity->addComponent(material);
}

void View3D::drawFile(const QString& path) {
  QFile toDraw(path);
  if (!toDraw.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(nullptr, "File not found",
                          "Cannot find specified file");
    return;
  }
  int index = 0;
  QTextStream in(&toDraw);
  QStringList old;

  while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList fields = line.split(" ");

    if (index != 0) {
      drawLine(QVector3D(old[0].toFloat(), old[1].toFloat(), old[2].toFloat()),
               QVector3D(fields[0].toFloat(), fields[1].toFloat(),
                         fields[2].toFloat()),
               QColor(abs(old[2].toFloat ())*255,255,255), m_rootEntity);
    }
    old = fields;
    index++;
  }

  toDraw.close();
}

void View3D::addSphere() {
  auto* sphereMesh = new Qt3DExtras::QSphereMesh;
  sphereMesh->setRings(20);
  sphereMesh->setSlices(20);
  sphereMesh->setRadius(2);

  auto* sphereTransform = new Qt3DCore::QTransform;
  sphereTransform->setScale(1.0f);
  sphereTransform->setTranslation(QVector3D(0.0f, 0.0f, 1.0f));

  auto* sphereMaterial = new Qt3DExtras::QPhongMaterial();
  sphereMaterial->setDiffuse(QColor(QRgb(0x00ffff)));

  auto* sphere = new Qt3DCore::QEntity(m_rootEntity);
  sphere->addComponent(sphereMesh);
  sphere->addComponent(sphereMaterial);
  sphere->addComponent(sphereTransform);
}
