#ifndef MODEL_H
#define MODEL_H

#include <Render/flattable.h>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QVector3D>
#include <QVector2D>
#include <Render/set3dpoints.h>

class Model
{
public:
    Model() = default;
    Model(const QString file);
    Model(QTextStream &stream);
    QVector<QVector3D> points;
    QVector<QVector2D> texturePoint;
    FlatTable polygons;
    FlatTable texture_points_polygons;
    Set3DPoints triang();


private:

    friend class Tests;
    bool ReadFromStream(QTextStream &streamInput);
    bool isComment(const QString &str);
    static bool readGeometricVertex(const QStringList &vstr, QVector3D &vector);
    bool ReadTextureCoordinates(const QStringList &vstr, QVector2D &vector);
    bool ReadPolygonalFace(const QStringList &vstr, FlatTable &polygons,  FlatTable &texture_points_polygons);
};

#endif // MODEL_H
