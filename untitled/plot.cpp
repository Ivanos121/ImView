#include "plot.h"
#include <QCursor>
#include <QPainter>



Plot::Plot(QWidget *parent) : QCustomPlot(parent)
{
    setMouseTracking(true);

}

void Plot::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::CrossCursor);
        p1=e->pos();
        p2 = p1;
        leftButtonPressed = true;
    }
}

void Plot::mouseReleaseEvent(QMouseEvent *e)
{
     setCursor(Qt::ArrowCursor);

     double w = abs(p1.x()-p2.x());
     double h = abs(p1.y()-p2.y());

     if (w > 50 && h > 50) {
         if (e->button() == Qt::LeftButton)
         {

             if ((p2.x() - p1.x() < 0) &&
                 (p2.y() - p1.y() < 0))
             {
                 rescaleAxes(true);
                 replot();
             } else {
                 double deltax = 0.;
                 double deltay = 0.;
                 deltax = w/axisRect()->width();
                 deltay = h/axisRect()->height();

                 axisRect()->zoomEvent(deltax, deltay, QPoint((p1.x()+p2.x())/2.0,(p1.y()+p2.y())/2.0));
             }
         }
     }
    leftButtonPressed = false;
    repaint();
}

void Plot::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        p2 = e->pos();
        repaint();
    }
}

void Plot::paintEvent(QPaintEvent *event)
{
    QCustomPlot::paintEvent(event);
    if (leftButtonPressed)
    {
        QPainter painter(this);
        QPen pen(Qt::black, 1, Qt::DotLine);
        painter.setPen(pen);
        painter.drawRect(p1.x(),p1.y(),p2.x() - p1.x(),p2.y() - p1.y());
    }
}
