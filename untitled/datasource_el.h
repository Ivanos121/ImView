#ifndef DATASOURCE_EL_H
#define DATASOURCE_EL_H

#include <QWidget>
#include <QTimer>
#include "mainwindow.h"


class datasource_el : public QObject
{
    Q_OBJECT
public:
    datasource_el();
    void stop_el();

    void setMainWindow(MainWindow *_mainWindow);
    QTimer *dataTimer2;
    MainWindow *mainWindow;

public slots:
    void read_el();

signals:
    void ready_el();
};

#endif // DATASOURCE_EL_H
