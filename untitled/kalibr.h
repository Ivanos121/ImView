#ifndef KALIBR_H
#define KALIBR_H

#include <QDialog>

#include "datasourcebvas.h"

namespace Ui {
class Kalibr;
}

class Kalibr : public QDialog
{
    Q_OBJECT

public:
    explicit Kalibr(QWidget *parent = nullptr);
    ~Kalibr();

private slots:
    void bvasSlot();
    void on_pushButtonZeroApplyIa_clicked();
    void on_pushButtonZeroApplyIb_clicked();
    void on_pushButtonZeroApplyIc_clicked();
    void on_pushButtonZeroApplyUa_clicked();
    void on_pushButtonZeroApplyUb_clicked();
    void on_pushButtonZeroApplyUc_clicked();

    void on_pushButtonValueApplyIa_clicked();
    void on_pushButtonValueApplyIb_clicked();
    void on_pushButtonValueApplyIc_clicked();
    void on_pushButtonValueApplyUa_clicked();
    void on_pushButtonValueApplyUb_clicked();
    void on_pushButtonValueApplyUc_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButtonAccept_clicked();

protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *e);

private:
    Ui::Kalibr *ui;
    DataSourceBVAS dataSourceBVAS;

    double i_dev_a;
    double i_dev_b;
    double i_dev_c;
    double u_dev_a;
    double u_dev_b;
    double u_dev_c;

    double i_zero_a;
    double i_zero_b;
    double i_zero_c;
    double u_zero_a;
    double u_zero_b;
    double u_zero_c;
};

#endif // KALIBR_H
