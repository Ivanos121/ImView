#ifndef PLOT_H
#define PLOT_H

#include "qcustomplot.h"

class Plot : public QCustomPlot
{
    Q_OBJECT
public:
    Plot(QWidget *parent);

    QPoint p1,p2;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    bool leftButtonPressed = false;
};

#endif // PLOT_H
