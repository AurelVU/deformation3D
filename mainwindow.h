#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Render/scene.h>
#include <QWidget>
#include <QVBoxLayout>
#include <Problem/getterproblem.h>
#include <Problem/getterproblemmodel.h>
#include <Problem/problem.h>
#include <GaussNewton/gaussnewton.h>

const int N = 3;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Scene *sc;
    QVector<VectorN<float, N>> oldPoints;
    QVector<VectorN<float, N>> powerPoints;
    QVector<VectorN<float, N>> points;
    QVector<QPair<int, int>> edges;
    QVector<QPair<int, int>> r;
    float a = 0;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
