#include <Render/flattable.h>

int FlatTable::size()
{
    return offsets.size();
}



FlatTable::FlatTable()
{
    offsets.push_back(0);
}
void FlatTable::add(const QVector<int> &row)
{
    offsets.push_back(indices.size() + row.size());
    indices.append(row);
}
QVector<int> FlatTable::getRow(int row)
{
    int begin = offsets[row];
    int end = row + 1 < offsets.size()? offsets[row + 1] : indices.size();
    QVector<int> row_v;
    for (int i = begin; i < end; i++)
    {
        row_v.push_back(indices[i]);
    }
    return row_v;
}

int FlatTable::get(int rowInd, int collInt)
{
    return indices[offsets[rowInd] + collInt];
}
