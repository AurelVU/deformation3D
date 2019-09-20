#include "set3dpoints.h"

Set3DPoints::Set3DPoints()
{

}

void Set3DPoints::add(const QVector3D v)
{
    points.push_back(v[0]);
    points.push_back(v[1]);
    points.push_back(v[2]);
}

int Set3DPoints::size()
{
    return points.size() / 3;
}

QVector3D Set3DPoints::getPoint(const int n)
{
    return QVector3D(points[3 * n], points[3 * n + 1], points[3 * n + 2]);
}

int Set3DPoints::getPoint(const int c, const int r)
{
    return points[3 * c + r];
}
