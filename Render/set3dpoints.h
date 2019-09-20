#ifndef SET3DPOINTS_H
#define SET3DPOINTS_H

#include <QVector>
#include <QVector3D>

class Set3DPoints
{
private:
    QVector<int> points;
public:
    Set3DPoints();
    void add(const QVector3D v);
    int size();
    QVector3D getPoint(const int n);
    int getPoint(const int c, const int r);
};

#endif // SET3DPOINTS_H
