#ifndef GETTERPROBLEMFIN_H
#define GETTERPROBLEMFIN_H

#include <QVector>
#include <Eigen/Core>
#include <Eigen/LU>

namespace Eigen {
template <typename Scalar>
using Vector2 = Eigen::Matrix<Scalar, 2, 1>;

template <typename Scalar, int N>
using VectorN = Eigen::Matrix<Scalar, N, 1>;
}

using namespace Eigen;

template <int N>
class GetterProblem
{
public:
    virtual QVector<VectorN<float, N>> getPoints() = 0;
    virtual QVector<VectorN<float, N>> getPowerPoints() = 0;
    virtual QVector<QPair<int, int>> getEiges() = 0;
    virtual QVector<QPair<int, int>> getRubbing() = 0;
    virtual double getRotationMatrixWeight() = 0;
    virtual double getRubbingWeight() = 0;
    virtual double getEigesWeight() = 0;
};

#endif // GETTERPROBLEMFIN_H
