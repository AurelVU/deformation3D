#ifndef GETTERPROBLEMMODEL_H
#define GETTERPROBLEMMODEL_H

#include <Problem/getterproblem.h>
#include <Render/model.h>

template <int N>
class GetterProblemModel : public GetterProblem<N>
{
public:
    GetterProblemModel(Model model, QVector<VectorN<float, N>> powerPoints, QVector<QPair<int, int>> r,
                       double rotationMatrixWeight, double rubbingWeight, double eigesWeight);
    QVector<VectorN<float, N>> getPoints() override;
    Model model;
    double rotationMatrixWeight;
    double rubbingWeight;
    double eigesWeight;
    QVector<VectorN<float, N>> powerPoints;
    QVector<QPair<int, int>> r;
    QVector<VectorN<float, N>> getPowerPoints() override;
    QVector<QPair<int, int>> getEiges() override;
    QVector<QPair<int, int>> getRubbing() override;
    virtual double getRotationMatrixWeight() override;
    virtual double getRubbingWeight() override;
    virtual double getEigesWeight() override;

};

template<int N>
double GetterProblemModel<N>::getRotationMatrixWeight()
{
    return this->rotationMatrixWeight;
}

template<int N>
double GetterProblemModel<N>::getRubbingWeight()
{
    return this->rubbingWeight;
};

template<int N>
double GetterProblemModel<N>::getEigesWeight()
{
    return this->eigesWeight;
};

template<int N>
QVector<VectorN<float, N>> GetterProblemModel<N>::getPoints()
{
    QVector<VectorN<float, N>> res;

    for (int i = 0; i < this->model.points.size(); i++) {
        VectorN<float, N> a;
        for (int j = 0; j < N; ++j) {
            a[j] = this->model.points[i][j];
        }
        res << a;
    }

    return res;
}

template<int N>
QVector<VectorN<float, N>> GetterProblemModel<N>::getPowerPoints()
{
    return this->powerPoints;
}

template<int N>
QVector<QPair<int, int>> GetterProblemModel<N>::getEiges()
{
    QVector<QPair<int, int>> res;

    for (int i = 0; i < this->model.polygons.size(); i++)
    {
        QVector<int> a = this->model.polygons.getRow(i);
        for (int j = 0; j < a.size(); j++)
        res.append(QPair<int, int>(a[j] - 1, a[(j + 1) % a.size()] - 1)); //проблемное место
    }

    return res;
}

template<int N>
QVector<QPair<int, int>> GetterProblemModel<N>::getRubbing()
{
    return this->r;
}



template<int N>
GetterProblemModel<N>::GetterProblemModel(Model _model, QVector<VectorN<float, N>> _powerPoints, QVector<QPair<int, int>> _r,
                                          double _rotationMatrixWeight, double _rubbingWeight, double _eigesWeight) :
    model(_model),
    powerPoints(_powerPoints),
    r(_r),
    rotationMatrixWeight(_rotationMatrixWeight),
    rubbingWeight(_rubbingWeight),
    eigesWeight(_eigesWeight)
{}

#endif // GETTERPROBLEMMODEL_H
