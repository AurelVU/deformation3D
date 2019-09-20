#ifndef FLATTABLE_H
#define FLATTABLE_H

#include <QVector>

class FlatTable
{
    QVector<int> indices;
    QVector<int> offsets;
public:
    FlatTable();
    int size();
    QVector<int> getRow(int row);
    void add(const QVector<int> &row);
    int get(int rowInd, int collInt);
};

#endif // FLATTABLE_H
