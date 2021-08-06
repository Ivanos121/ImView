#ifndef IDENTF_H
#define IDENTF_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

#include "datasource.h"
#include "model.h"
#include "modell.h"
#include "plot.h"

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

private:
    QVector<QColor> dataLineColors;

private slots:
    void on_pushButton_clicked();
    void setcolorincell(int row, int column);
};

#endif // IDENTF_H
