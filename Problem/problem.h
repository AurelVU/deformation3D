#ifndef PROBLEM_H
#define PROBLEM_H

#include <Eigen/Core>
#include <Eigen/LU>
#include <QVector>
#include <QPair>
#include <QDebug>
#include <Problem/getterproblem.h>
#include <QQueue>

namespace Eigen {
template <typename Scalar>
using Vector2 = Eigen::Matrix<Scalar, 2, 1>;

template <typename Scalar, int N>
using VectorN = Eigen::Matrix<Scalar, N, 1>;

template <typename Scalar, int N>
using MatrixN = Eigen::Matrix<Scalar, N, N>;
}

using namespace Eigen;

template <int N>
class Problem
{
public:
    Problem();
    Problem(QVector<VectorN<float, N>> _Points,
               QVector<VectorN<float, N>> _PowerPoints,
               QVector<QPair<int, int>> _Eiges,
               QVector<QPair<int, int>> _Rubbing,
               double _rotationMatrixWeight,
               double _rubbingWeight,
               double _eigesWeight
            ):
        points(_Points),
        powerPoints(_PowerPoints),
        eiges(_Eiges),
        rubbing(_Rubbing),
        rotationMatrixWeight(_rotationMatrixWeight),
        rubbingWeight(_rubbingWeight),
        eigesWeight(_eigesWeight)

    {}

    double rotationMatrixWeight;
    double rubbingWeight;
    double eigesWeight;

    Problem(GetterProblem<N>* sourse):
        points(sourse->getPoints()),
        powerPoints(sourse->getPowerPoints()),
        eiges(sourse->getEiges()),
        rubbing(sourse->getRubbing()),
        rotationMatrixWeight(sourse->getRotationMatrixWeight()),
        rubbingWeight(sourse->getRubbingWeight()),
        eigesWeight(sourse->getEigesWeight())
    {}
    const int Rasmern = N;
    QVector<VectorN<float, N>> points;
    QVector<VectorN<float, N>> powerPoints;
    QVector<QPair<int, int>> eiges;
    QVector<QPair<int, int>> rubbing;

    template<typename T>
    QVector<T> getResidual(QVector<T> values);

    template<typename T>
    QVector<T> getValues();

};

template <int N>
template <typename T>
QVector<T> Problem<N>::getResidual(QVector<T> var)
{


    QVector<T> res; // Результирующий массив
    QVector<VectorN<T, N>> pointsLocal; // Приведение массива Point к типу T
    QVector<VectorN<T, N>> powerPointsLocal;// Приведение массива PowerPoint к типу T

    for (int i = 0; i < points.size(); i++) // Заполнение массива Points_local
        pointsLocal << points[i].template cast<T>();

    for (int i = 0; i < powerPoints.size(); i++) // Заполнение массива PowerPoints_local
        powerPointsLocal << powerPoints[i].template cast<T>();

    const int nVertexDimensions = N; // Размерность пространства

    QVector<VectorN<T, N>> pointsChangeable; //Массив изменяемых точек из аргумента функции
    for (int i = 0; i < points.size(); i++) {
        VectorN<T, N> a;
        for (int j = 0; j < nVertexDimensions; j++)
            a[j] = var[nVertexDimensions * i + j];

        pointsChangeable << a;
    }

    //Перегонка в матрицу поворота из var
    QVector<Matrix<T, N, N>> rotationMatrices;
    for(int indexMatrix = 0; indexMatrix < points.size(); indexMatrix++) {
        Matrix<T, N, N> rotationMatrix;
        for(int row = 0; row < N; row++)
            for(int column = 0; column < N; column++)
                rotationMatrix(row, column) =
                        var[points.size() * N +
                        indexMatrix * N * N +
                        row * N + column];
        rotationMatrices << rotationMatrix;
    }
    //Добавление невязок с силовыми точками
    for (int i = 0; i < rubbing.size(); i++) {
        const int indexPointFirst = rubbing[i].first;
        const int indexPointSecond = rubbing[i].second;
        for (int j = 0; j < nVertexDimensions; j++)
            res << T(rubbingWeight) * (pointsChangeable[indexPointFirst][j] - powerPointsLocal[indexPointSecond][j]);
    }

    //Добавление невязок для ребер
    for (int i = 0; i < eiges.size(); i++) {
        const int indexPointFirst = eiges[i].first;
        const int indexPointSecond = eiges[i].second;
        VectorN<T, N> vectorDiff = pointsChangeable[indexPointSecond] - pointsChangeable[indexPointFirst] -
                rotationMatrices[indexPointFirst] * (pointsLocal[indexPointSecond] - pointsLocal[indexPointFirst]);
        for (int j = 0; j < nVertexDimensions; j++) {
            res << T(eigesWeight) * vectorDiff[j];
        }
    }
    for (int vertexIndex = 0; vertexIndex < rotationMatrices.size(); vertexIndex++)
    {
        MatrixN<T, N> I;
        I.setIdentity();
        MatrixN<T, N> diffMatrix = rotationMatrices[vertexIndex] * rotationMatrices[vertexIndex].transpose() - I;
        //qDebug() << rotationMatrices[vertexIndex](0, 0) << ' ' << rotationMatrices[vertexIndex](0, 1) << endl
        //        << rotationMatrices[vertexIndex](1, 0) << ' ' << rotationMatrices[vertexIndex](1, 1);
        for (int row = 0; row < N; row++)
            for (int column = 0; column < N; column++)
                res << T(rotationMatrixWeight) * diffMatrix(row, column);
    }

    return  res;
}

template<int N>
template<typename T>
QVector<T> Problem<N>::getValues()
{
    QVector<VectorN<T, N>> pointsLocal;
    for (int i = 0; i < points.size(); i++)
        pointsLocal << points[i].template cast<T>();

    QVector<T> res;

    for (int i = 0; i < pointsLocal.size(); i++)
        for (int j = 0; j < pointsLocal[i].size(); j++)
            res << pointsLocal[i][j].size();

    return res;
}


#endif // PROBLEM_H
