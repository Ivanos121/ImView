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
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_toggled(bool checked);

public:
    Ui::identf *ui;
    QElapsedTimer *time;
    QElapsedTimer *time2;
    Modell *modell;
    DataSource *dataSource;

    void setMainWindow(MainWindow* wind);

private:
    QVector<QColor> dataLineColors;
    MainWindow *mainWindow;

private slots:
    void on_pushButton_clicked();
    void setcolorincell(int row, int column);
};

#endif // IDENTF_H
