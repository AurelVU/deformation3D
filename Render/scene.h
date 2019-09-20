#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QVector2D>
#include <QVector3D>
#include <QVector>
#include <QPainter>
#include <Render/model.h>
#include <Render/camera.h>
#include <QMouseEvent>
class Scene : public QWidget
{
private:
    int x;
    int y;
public:
    QVector<Model> models;
    Scene(QWidget *parent = nullptr);
    Camera camera;
    Scene(QVector<Model> &_models);
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // SCENE_H
