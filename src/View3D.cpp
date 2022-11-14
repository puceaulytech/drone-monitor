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
  drawLine({-20, 0, 0}, {20, 0, 0}, Qt::red);
  drawLine({0, -20, 0}, {0, 20, 0}, Qt::green);
  drawLine({0, 0, -20}, {0, 0, 20}, Qt::blue);
/*  PROTO CUSTOM MESH
   Qt3DCore::QEntity* sphereEntity = new Qt3DCore::QEntity(m_rootEntity);
  auto* sphereMesh = new Qt3DRender::QMesh();
  sphereMesh->setSource(QUrl::fromLocalFile(
      "C:/Users/robin/Desktop/VRAC/uploads_files_2582308_Venator+2k/Venator "
      "2k/Venator.obj"));
  Qt3DRender::QMaterial* material =
      new Qt3DExtras::QPhongMaterial(m_rootEntity);
  Qt3DCore::QTransform* sphereTransform = new Qt3DCore::QTransform;
  sphereEntity->addComponent(sphereMesh);
  sphereEntity->addComponent(sphereTransform);
  sphereEntity->addComponent(material);*/
}

Qt3DCore::QEntity* View3D::drawLine(const QVector3D& start,
                                    const QVector3D& end, const QColor& color) {
  auto* geometry = new Qt3DCore::QGeometry(m_rootEntity);

  QByteArray bufferBytes;
  bufferBytes.resize(3 * 2 * sizeof(float));
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

  geometry->addAttribute(positionAttribute);

  QByteArray indexBytes;
  indexBytes.resize(2 * sizeof(unsigned int));
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

  geometry->addAttribute(indexAttribute);

  auto* line = new Qt3DRender::QGeometryRenderer(m_rootEntity);
  line->setGeometry(geometry);
  line->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
  auto* material = new Qt3DExtras::QPhongMaterial(m_rootEntity);
  material->setAmbient(color);

  auto* lineEntity = new Qt3DCore::QEntity(m_rootEntity);
  lineEntity->addComponent(line);
  lineEntity->addComponent(material);

  return lineEntity;
}

void View3D::centerCamera() {
  m_cameraEntity->setViewCenter(QVector3D(0, 0, 0));
  m_cameraEntity->setUpVector(QVector3D(0, 1, 0));
}

QVector<Qt3DCore::QEntity*> View3D::drawFile(const QString& path) {
  QVector<Qt3DCore::QEntity*> entities;
  QFile toDraw(path);
  if (!toDraw.open(QIODevice::ReadOnly)) {
    QMessageBox::critical(nullptr, "File not found",
                          "Cannot find specified file");
    return entities;
  }
  int index = 0;
  QTextStream in(&toDraw);
  QStringList old;

  while (!in.atEnd()) {
    QString line = in.readLine();
    QStringList fields = line.split(" ");

    if (index != 0) {
      auto currentEntity = drawLine(
          QVector3D(old[0].toFloat(), old[1].toFloat(), old[2].toFloat()),
          QVector3D(fields[0].toFloat(), fields[1].toFloat(),
                    fields[2].toFloat()),
          QColor(abs(old[2].toFloat()) * 255, 255, 255));
      entities.append(currentEntity);
    }
    old = fields;
    index++;
  }

  toDraw.close();

  return entities;
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
