#ifndef TREND_H
#define TREND_H

#include <QWidget>
#include <QGraphicsTextItem>
#include <QDomDocument>
#include <QTimer>
#include <QTimer>
#include <QElapsedTimer>
#include "plot.h"
#include "mainwindow.h"

namespace Ui {
class trend;
}

class trend : public QWidget
{
    Q_OBJECT

public:
    explicit trend(QWidget *parent = nullptr);
    ~trend();

    MainWindow *mw;
    MainWindow *wwwf;
    MainWindow *wwff;

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_timerTimeout();
    void setcolorincell(int row, int column);


private:
    Ui::trend *ui;
    QDomDocument doc,doc3,doc4;
    QTimer timer;
    double t;
    QVector<QColor> dataLineColors;

    double maxY2;
    double minY2;

    double count;
    double max;



};

#endif // TREND_H
