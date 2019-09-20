#include "camera.h"

Camera::Camera()
{
    Transformation.setToIdentity();
    MatrixMove.setToIdentity();
    MatrixScale.setToIdentity();
    MatrixRotate.setToIdentity();
    turningSpeed = 0.1;
}

void Camera::RefreshTransformation()
{
    Transformation = MatrixMove * MatrixRotate * MatrixScale;
}

void Camera::moveCamera(const QVector3D &positionChange)
{
    MatrixMove.translate(positionChange);
    RefreshTransformation();
}

QVector3D Camera::getPointInSpace(const QVector3D &p)
{
    QVector4D p1 = QVector4D(p, 1);
    auto result =  QVector3D(Transformation * p1);
    return result;
}

QPoint Camera::getPointOnPlaneFromSpace(const QVector3D &p)
{
    QPoint p1(p.x(), p.y());
    return p1;
}

QPoint Camera::getPointOnPlaneFromAnCoordSyst(const QVector3D &p)
{
    return getPointOnPlaneFromSpace(getPointInSpace(p));
}

void Camera::turnCamera(const float dx, const float dy, const float dz)
{
    MatrixRotate.rotate(turningSpeed, dx, dy, dz);
    RefreshTransformation();
}

void Camera::scaleCamera(const float scale)
{
    MatrixScale.scale(scale);
    RefreshTransformation();
}
