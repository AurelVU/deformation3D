#ifndef CAMERA_H
#define CAMERA_H
#include <QMatrix4x4>
#include <QPointF>
#include <QVector3D>
class Camera
{
private:
    QMatrix4x4 Transformation;
    QMatrix4x4 MatrixMove;
    QMatrix4x4 MatrixRotate;
    QMatrix4x4 MatrixScale;
public:
    float turningSpeed;
    Camera();
    void RefreshTransformation();
    void moveCamera(const QVector3D &positionChange);
    QVector3D getPointInSpace(const QVector3D &p);
    QPoint getPointOnPlaneFromSpace(const QVector3D &p);
    QPoint getPointOnPlaneFromAnCoordSyst(const QVector3D &p);
    void turnCamera(const float dx, const float dy, const float dz);
    void scaleCamera(const float scale);
};

#endif // CAMERA_H
