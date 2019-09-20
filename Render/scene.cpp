#include "scene.h"

#include <QDebug>

Scene::Scene(QWidget *parent):
    QWidget(parent)
{
    this->y = 0;
    this->x = 0;
    setMouseTracking(true);
}

Scene::Scene(QVector<Model> &_models)
{
    this->y = 0;
    this->x = 0;
    models = _models;
    setMouseTracking(true);
}

void Scene::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    qDebug() << "Scene::paintEvent";
    /*QPoint p1(3, 3);
    QPoint p2(140, 140);
    QPoint p3(340, 50);
    QPolygon pol;
    pol << p1 << p2 << p3;
    p.drawPolygon(pol);*/
    //camera.moveCamera(QVector3D(-40, -40, 0));

    //camera.scaleCamera(3);
    for (int i = 0; i < models.size(); i++)
    {
        Set3DPoints table = models[i].triang();
        for (int j = 0; j < table.size(); j++)
        {
            QPolygon pol;
            QVector3D pt = table.getPoint(j);
            for (int k = 0; k < 3; k++)
            {
                pol << camera.getPointOnPlaneFromAnCoordSyst(models[i].points[pt[k] - 1]);
            }
            p.drawPolygon(pol);
        }
    }
}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QVector3D turn = QVector3D(event->x() - this->x, event->y() - this->y, 0);
        this->y = event->y();
        this->x = event->x();
        this->camera.turnCamera(turn.x(), turn.y(), turn.z());
    } else if (event->button() == Qt::MidButton)
    {
        QVector3D move = camera.getPointInSpace(QVector3D(event->x() - this->x, event->y() - this->y, 0));
        this->y = event->y();
        this->x = event->x();
        this->camera.moveCamera(move);
    }

}
