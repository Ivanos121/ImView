#ifndef IDENTF_H
#define IDENTF_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

#include "datasource.h"
#include "datasource_file.h"
#include "datasource_el.h"
#include "model.h"
#include "modell.h"
#include "plot.h"
#include "mainwindow.h"

#include <QButtonGroup>

namespace Ui {
class identf;
}

class identf : public QWidget
{
    Q_OBJECT

public:
    explicit identf(QWidget *parent = nullptr);
    ~identf();

public slots:
    void realtimeDataSlot();
    void raschet_f();

public:
    Ui::identf *ui;
    QElapsedTimer *time;
    QElapsedTimer *time2;
    Modell *modell;
    DataSource *dataSource;
    MainWindow *wf;
    QString dataSourceFilename;
};

#endif // IDENTF_H
