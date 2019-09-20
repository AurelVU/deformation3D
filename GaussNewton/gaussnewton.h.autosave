#ifndef GAUSS_NEWTON_H
#define GAUSS_NEWTON_H
#include <QDebug>
#include <GaussNewton/variable.h>
#include <Eigen/Core>
#include <Eigen/LU>
#include <Problem/problem.h>
#include <Eigen/Eigenvalues>

using namespace Eigen;

typedef Variable<Variable<float>> Variable2;
typedef Variable<float> Variablef;



template <typename Problem>
inline
MatrixXf calculeteJr(const QVector<float> &values, Problem &problem)
{
    QVector<Variable<float>> value_v;

    for (int j = 0; j < values.size(); j++)
        value_v << Variable<float>(values[j]);


    QVector<Variable<float>> s = problem.template getResidual<Variable<float>>(value_v);

    MatrixXf res(s.size(), values.size());

    for (int i = 0; i < values.size(); i++) {
        value_v[i].derivative = 1;
        QVector<Variable<float>> s = problem.template getResidual<Variable<float>>(value_v);
        value_v[i].derivative = 0;
        for (int j = 0; j < s.size(); j++)
            res(j, i) = s[j].derivative;
    }
    return res;
}

template <typename Problem>
inline
VectorXf computeGradientGH(const MatrixXf &Jr, const QVector<float> &values, Problem &problem)
{
    QVector<float> r_v = problem.template getResidual<float>(values);
    VectorXf r(r_v.size());
    for (int i = 0; i < r_v.size(); i++)
        r[i] = r_v[i];

    VectorXf res = Jr.transpose() * r;
    return res;
}

template <typename Problem>
inline
QVector<float> performGaussNewton(const QVector<float> &values, Problem &problem, int countIteration)
{
    auto localValues = values;
    MatrixXf J = calculeteJr(localValues, problem);
    VectorXf V = computeGradientGH(J, localValues, problem);
    float dumpingFactor = 0.1;
    MatrixXf I(values.size(), values.size());
    I.setIdentity();
    MatrixXf H = J.transpose() * J + I * dumpingFactor;
    VectorXcf ev = H.eigenvalues();
    VectorXf dt = H.partialPivLu().solve(-V);

    for (int i = 0; i < countIteration; i++) {
        for (int j = 0; j < dt.size(); j++)
            localValues[j] += dt[j];
        J = calculeteJr(localValues, problem);

        MatrixXf H = J.transpose() * J + I * dumpingFactor;

        V = computeGradientGH(J, localValues, problem);
        dt = H.partialPivLu().solve(-V);
    }
    return localValues;
}


#endif // GAUSS_NEWTON_H
