#include "itestwidget.h"
#include <QApplication>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QExtrudedTextMesh>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QDebug>
#include <QSurfaceFormat>

ITestWidget::ITestWidget() {

    // 设置 OpenGL 渲染
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    // 创建 3D 窗口
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view,this);
    container->setMinimumSize(QSize(800, 600));
    container->setFocusPolicy(Qt::TabFocus);

    // 创建根实体
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();
    qDebug() << "Root entity created";

    // 创建线段实体
    Qt3DCore::QEntity *lineEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DCore::QGeometry *geometry = new Qt3DCore::QGeometry(lineEntity);
    qDebug() << "Line entity and geometry created";

    QByteArray bufferArray;
    bufferArray.resize(6 * 3 * sizeof(float)); // 2 points * 3 coordinates (x, y, z) * sizeof(float)
    float *positions = reinterpret_cast<float*>(bufferArray.data());

    // 设置线段的起始和结束点
    positions[0] = 0.0f; positions[1] = 0.0f; positions[2] = 0.0f; // 起点
    positions[3] = 1.0f; positions[4] = 1.0f; positions[5] = 1.0f; // 终点

    auto* buffer = new Qt3DCore::QBuffer(geometry);
    buffer->setData(bufferArray);
    qDebug() << "Buffer set";

    auto* positionAttribute = new Qt3DCore::QAttribute(geometry);
    positionAttribute->setName(Qt3DCore::QAttribute::defaultPositionAttributeName());
    positionAttribute->setVertexBaseType(Qt3DCore::QAttribute::Float);
    positionAttribute->setVertexSize(3);
    positionAttribute->setAttributeType(Qt3DCore::QAttribute::VertexAttribute);
    positionAttribute->setBuffer(buffer);
    positionAttribute->setByteStride(3 * sizeof(float));
    positionAttribute->setCount(2);
    qDebug() << "Position attribute set";

    geometry->addAttribute(positionAttribute);

    // 创建几何体渲染器
    Qt3DRender::QGeometryRenderer *geometryRenderer = new Qt3DRender::QGeometryRenderer();
    geometryRenderer->setGeometry(geometry);
    geometryRenderer->setPrimitiveType(Qt3DRender::QGeometryRenderer::Lines);
    qDebug() << "Geometry renderer created";

    // 创建材质
    Qt3DExtras::QPhongMaterial *lineMaterial = new Qt3DExtras::QPhongMaterial();
    lineMaterial->setDiffuse(QColor(QRgb(0x00FF00))); // 绿色
    qDebug() << "Material created";

    // 将几何体和材质添加到线段实体
    lineEntity->addComponent(geometryRenderer);
    lineEntity->addComponent(lineMaterial);
    qDebug() << "Components added to line entity";

    // 设置摄像机
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 20));
    camera->setViewCenter(QVector3D(0, 0, 0));
    qDebug() << "Camera set";

    // 创建相机控制器
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(camera);
    qDebug() << "Camera controller set";

    // 设置根实体
    view->setRootEntity(rootEntity);
    qDebug() << "Root entity set in view";

    // 显示窗口
    container->show();
    qDebug() << "Container shown";
}
