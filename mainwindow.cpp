#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Model model("/home/aurel/cube.obj");
    QVector<VectorN<float, N>> powerPoints;
    powerPoints.append(VectorN<float, N> (6, 10, 4));
    powerPoints.append(VectorN<float, N> (-2, -2, -2));
    QVector<QPair<int, int>> r;
    r.append(QPair<int, int>(1, 0));
    r.append(QPair<int, int>(2, 1));
    GetterProblem<N> *getter = new GetterProblemModel<N>(model, powerPoints, r, 5, 1, 1);
    Problem<N> problem(getter);
    points = getter->getPoints();
    edges = getter->getEiges();
    oldPoints = points;
    powerPoints = getter->getPowerPoints();
    r = getter->getRubbing();
    QVector<float> values;
    for (int i = 0; i < points.size(); i++)
        for (int j = 0; j < N; j++)
            values << points[i][j];

    for (int i = 0; i < edges.size(); i++)
    {
        values.append({1, 0, 0});
        values.append({0, 1, 0});
        values.append({0, 0, 1});
    }

    values = performGaussNewton(values, problem, 2);

    for (int i = 0; i < points.size(); i++)
        for (int j = 0; j < N; j++)
            model.points[i][j] = values[i * 3 + j];
    QVBoxLayout *layout = new QVBoxLayout();
    sc = new Scene(this);
    //sc->camera.turnCamera(180, 0, 0);
    sc->camera.moveCamera(QVector3D(80, 80, 40));
    sc->camera.scaleCamera(40);
    sc->models.push_back(model);
    sc->update();
    sc->camera.turningSpeed = 1;
    layout->addWidget(sc);
    ui->centralWidget->setLayout(layout);
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    //sc->camera.moveCamera(QVector3D(0, 0, 0));
    //a -= 0.00000000001;
    //sc->camera.turnCamera(1, 1, 0);
    sc->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
