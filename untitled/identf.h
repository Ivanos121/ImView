#ifndef IDENTF_H
#define IDENTF_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>

#include "datasource.h"
#include "model.h"

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

    DataSource *dataSource;

private slots:
    void on_pushButton_clicked();
};

#endif // IDENTF_H
