// itestwidget.cpp
#include "itestwidget.h"
#include <Qt3DCore/QGeometry>
#include <Qt3DExtras/Qt3DExtras>
#include <Qt3DRender/QGeometryRenderer>

ITestWidget::ITestWidget(QWidget *parent) : QWidget(parent) {
    setup3DWindow();

    createGridLines(100, 10000);
    createZAxis();

    setupCamera();
    setupLayout();
    setupConnections();
}

ITestWidget::~ITestWidget() { delete m_view; }

void ITestWidget::setupConnections() {

    // Connect resize event to slot for handling resize
    connect(this, &ITestWidget::resizeSignal, this, &ITestWidget::onResize);
}

void ITestWidget::setupLayout() {
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(QWidget::createWindowContainer(m_view));
    setLayout(layout);
}

void ITestWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    emit resizeSignal(event->size()); // Emit resize signal with new size
}

void ITestWidget::onResize(const QSize &newSize) {
    qDebug() << "ITestWidget::onResize: " << newSize;
    m_view->resize(newSize); // Resize the Qt3DWindow with the new size
}

void ITestWidget::setupCamera() {

    m_camera = m_view->camera();
    m_camera->lens()->setPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f,
                                               10000.0f);
    m_camera->setPosition(QVector3D(100, -500, 100));
    m_camera->setUpVector(QVector3D(0, 0, 1));
    m_camera->setViewCenter(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController *camController =
        new Qt3DExtras::QOrbitCameraController(m_rootEntity);
    camController->setLinearSpeed(150.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(m_camera);
}

void ITestWidget::setup3DWindow() {
    m_view = new Qt3DExtras::Qt3DWindow();
    m_view->defaultFrameGraph()->setClearColor(QColor(Qt::white));

    m_rootEntity = new Qt3DCore::QEntity();

    m_view->setRootEntity(m_rootEntity);
}

void ITestWidget::createLineEntity(const QVector3D &start, const QVector3D &end,
                                   Qt3DExtras::QPhongMaterial *material) {
    Qt3DCore::QEntity *lineEntity = new Qt3DCore::QEntity(m_rootEntity);
    Qt3DCore::QGeometry *geometry = new Qt3DCore::QGeometry(lineEntity);

    QByteArray bufferArray;
    bufferArray.resize(
        2 * 3 *
        sizeof(float)); // 2 points * 3 coordinates (x, y, z) * sizeof(float)
    float *positions = reinterpret_cast<float *>(bufferArray.data());

    positions[0] = start.x();
    positions[1] = start.y();
    positions[2] = start.z();
    positions[3] = end.x();
    positions[4] = end.y();
    positions[5] = end.z();

    Qt3DCore::QBuffer *buffer = new Qt3DCore::QBuffer();
    buffer->setData(bufferArray);

    Qt3DCore::QAttribute *positionAttribute = new Qt3DCore::QAttribute();
    positionAttribute->setName(
        Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(buffer);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(2);

    geometry->addAttribute(positionAttribute);

    Qt3DRender::QGeometryRenderer *geometryRenderer =
        new Qt3DRender::QGeometryRenderer();
    geometryRenderer->setGeometry(geometry);
    geometryRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);

    lineEntity->addComponent(geometryRenderer);
    lineEntity->addComponent(material);
}

void ITestWidget::createGridLines(int step, int gridSize) {

    Qt3DExtras::QPhongMaterial *xAxisMaterial = new Qt3DExtras::QPhongMaterial();
    xAxisMaterial->setDiffuse(QColor(Qt::red));

    Qt3DExtras::QPhongMaterial *yAxisMaterial = new Qt3DExtras::QPhongMaterial();
    yAxisMaterial->setDiffuse(QColor(Qt::green));

    // Create grid lines along X and Y axes
    for (int i = -gridSize; i <= gridSize; i += step) {
        createLineEntity(QVector3D(i, -gridSize, 0.0f),
                         QVector3D(i, gridSize, 0.0f),
                         xAxisMaterial); // Parallel to Y-axis, along X-axis
        createLineEntity(QVector3D(-gridSize, i, 0.0f),
                         QVector3D(gridSize, i, 0.0f),
                         yAxisMaterial); // Parallel to X-axis, along Y-axis
    }
}

void ITestWidget::createZAxis() {

    Qt3DExtras::QPhongMaterial *zAxisMaterial = new Qt3DExtras::QPhongMaterial();
    zAxisMaterial->setDiffuse(QColor(Qt::blue));

    // Create Z-axis line
    createLineEntity(QVector3D(0, 0, -10000), QVector3D(0, 0, 10000),
                     zAxisMaterial);
}
