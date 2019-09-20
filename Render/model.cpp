#include <Render/model.h>

Model::Model(const QString fileName)
{
    QFile file(fileName);
    bool flag1 = file.open(QFile::ReadOnly);
    QTextStream fileInput(&file);
    ReadFromStream(fileInput);
}

Model::Model(QTextStream &stream)
{
    ReadFromStream(stream);
}

Set3DPoints Model::triang()
{
    Set3DPoints set;
    int size_t = polygons.size();
    for (int i = 0; i < size_t; i++)
    {
        QVector<int> a = polygons.getRow(i);
        if (polygons.size() > 3)
        {
            for (int j = 2; j < a.size(); j++)
            {
                QVector3D b;
                b[0] = a[0];
                b[1] = a[j - 1];
                b[2] = a[j];
                set.add(b);
            }
        } else
        {
            set.add(QVector3D(a[0], a[1], a[2]));
        }
    }
    return set;
}

bool Model::readGeometricVertex(const QStringList &vstr, QVector3D &vector)
{
    if (vstr.size() != 3) return false;
    double x, y, z;
    bool ok = true;
    x = vstr[0].toDouble(&ok);
    y = vstr[1].toDouble(&ok);
    z = vstr[2].toDouble(&ok);
    if (!ok) return false;
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    return ok;
}


bool Model::ReadTextureCoordinates(const QStringList &vstr, QVector2D &vector)
{
    if (vstr.size() != 2) return false;
    double u, v;
    u = vstr[0].toDouble();
    v = vstr[1].toDouble();
    vector[0] = u;
    vector[1] = v;
    return true;
}

bool Model::ReadPolygonalFace(const QStringList &vstr, FlatTable &polygons, FlatTable &texture_points_polygons)
{
    QVector<int> vector;
    QVector<int> vector_t_point;
    for (int i = 0; i < vstr.size(); i++) {
        QStringList lstr = vstr[i].split('/', QString::KeepEmptyParts);
        int number = lstr[0].toInt();
        if (lstr.size() > 1 && lstr[1] != "")
        {
            vector_t_point.push_back(lstr[1].toInt());
        }
        if (number > -1) {
            vector.push_back(number);
        } else if (number == -1)  {
            vector.push_back(points.size() - 1);
        }
    }
    texture_points_polygons.add(vector_t_point);
    polygons.add(vector);
    return true;
}

bool Model::ReadFromStream(QTextStream &streamInput)
{
    QString str;

    while(!streamInput.atEnd()) {
        str = streamInput.readLine();
        if (isComment(str)){
            continue;
        }
        QStringList vstr;
        vstr = str.split(' ', QString::SkipEmptyParts);
        if (vstr.size() == 0) continue;
        if (vstr[0] == "v") {
            QVector3D vector;
            vstr.pop_front();
            bool flag = readGeometricVertex(vstr, vector);
            points.push_back(vector);
        } else if (vstr[0] == "vt") {
            QVector2D vector;
            vstr.pop_front();
            ReadTextureCoordinates(vstr, vector);
            texturePoint.push_back(vector);
        } else if (vstr[0] == "f")  {
            vstr.pop_front();
            ReadPolygonalFace(vstr, polygons, texture_points_polygons);
        }
    }
}


bool Model::isComment(const QString &str)
{
    bool flag = false;
    for (int i = 0; i < str.size() && str[i] != ' ' && str[i] != '#'; i++) {
        if (str[i] == "#"){
            flag = true;
            break;
        }
    }
    return flag;
}

