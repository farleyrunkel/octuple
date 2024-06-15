// itestwidget.h
#ifndef ITESTWIDGET_H
#define ITESTWIDGET_H

#include <QWidget>
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QCamera>
#include <QHBoxLayout>

class ITestWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ITestWidget(QWidget *parent = nullptr);
    ~ITestWidget();

signals:
    void resizeSignal(const QSize);

protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void onResize(const QSize &newSize);
private:
    Qt3DExtras::Qt3DWindow *m_view;
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DRender::QCamera *m_camera;

    void setup3DWindow();
    void createLineEntity(const QVector3D &start, const QVector3D &end, Qt3DExtras::QPhongMaterial *material);
    void createZAxis();
    void setupCamera();
    void setupLayout();

    void setupConnections();
    void createGridLines(int step, int gridSize);
};

#endif // ITESTWIDGET_H
