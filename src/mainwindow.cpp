#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QExtrudedTextMesh>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建 3D 窗口
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setMinimumSize(QSize(800, 600));
    container->setFocusPolicy(Qt::TabFocus);

    // 创建根实体
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // 创建 3D 文字实体
    Qt3DCore::QEntity *textEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QExtrudedTextMesh *textMesh = new Qt3DExtras::QExtrudedTextMesh();
    textMesh->setText("Hello, Octuple!");
    textMesh->setDepth(0.5f);
    textMesh->setFont(QFont("Arial", 20, QFont::Bold));

    // 创建材质
    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(QRgb(0xFF0000)));

    // 创建变换
    Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
    transform->setScale(1.0f);
    transform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    // 将网格、材质和变换添加到文字实体
    textEntity->addComponent(textMesh);
    textEntity->addComponent(material);
    textEntity->addComponent(transform);

    // 设置摄像机
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 20));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // 创建相机控制器
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(camera);

    // 设置根实体
    view->setRootEntity(rootEntity);

    // 显示窗口
    container->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
