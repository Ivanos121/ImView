#include <cmath>
#include <QSettings>

#include "kalibr.h"
#include "ui_kalibr.h"

Kalibr::Kalibr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Kalibr)
{
    ui->setupUi(this);
}

Kalibr::~Kalibr()
{
    delete ui;
}

void Kalibr::showEvent(QShowEvent *)
{
    QSettings settings;

    dataSourceBVAS.IaZeroLevel = settings.value("calibration/IaZero", 0.0).toDouble();
    dataSourceBVAS.IbZeroLevel = settings.value("calibration/IbZero", 0.0).toDouble();
    dataSourceBVAS.IcZeroLevel = settings.value("calibration/IcZero", 0.0).toDouble();

    dataSourceBVAS.UaZeroLevel = settings.value("calibration/UaZero", 0.0).toDouble();
    dataSourceBVAS.UbZeroLevel = settings.value("calibration/UbZero", 0.0).toDouble();
    dataSourceBVAS.UcZeroLevel = settings.value("calibration/UcZero", 0.0).toDouble();

    dataSourceBVAS.IaCalibrationCoeff = settings.value("calibration/IaCoeff", 1.0).toDouble();
    dataSourceBVAS.IbCalibrationCoeff = settings.value("calibration/IbCoeff", 1.0).toDouble();
    dataSourceBVAS.IcCalibrationCoeff = settings.value("calibration/IcCoeff", 1.0).toDouble();

    dataSourceBVAS.UaCalibrationCoeff = settings.value("calibration/UaCoeff", 1.0).toDouble();
    dataSourceBVAS.UbCalibrationCoeff = settings.value("calibration/UbCoeff", 1.0).toDouble();
    dataSourceBVAS.UcCalibrationCoeff = settings.value("calibration/UcCoeff", 1.0).toDouble();

    ui->lineEditZeroIa->setText(QString("%1").arg(dataSourceBVAS.IaZeroLevel));
    ui->lineEditZeroIb->setText(QString("%1").arg(dataSourceBVAS.IbZeroLevel));
    ui->lineEditZeroIc->setText(QString("%1").arg(dataSourceBVAS.IcZeroLevel));

    ui->lineEditZeroUa->setText(QString("%1").arg(dataSourceBVAS.UaZeroLevel));
    ui->lineEditZeroUb->setText(QString("%1").arg(dataSourceBVAS.UbZeroLevel));
    ui->lineEditZeroUc->setText(QString("%1").arg(dataSourceBVAS.UcZeroLevel));

    dataSourceBVAS.init();
    connect(&dataSourceBVAS, &DataSourceBVAS::ready, this, &Kalibr::bvasSlot);
}

void Kalibr::bvasSlot()
{
    i_dev_a=0.0;
    i_dev_b=0.0;
    i_dev_c=0.0;
    u_dev_a=0.0;
    u_dev_b=0.0;
    u_dev_c=0.0;

    i_zero_a=0.0;
    i_zero_b=0.0;
    i_zero_c=0.0;
    u_zero_a=0.0;
    u_zero_b=0.0;
    u_zero_c=0.0;

    for (int i=0; i<BUF_SIZE; i++)
    {
        i_dev_a += pow(dataSourceBVAS.Ia[i],2);
        i_dev_b += pow(dataSourceBVAS.Ib[i],2);
        i_dev_c += pow(dataSourceBVAS.Ic[i],2);
        u_dev_a += pow(dataSourceBVAS.Ua[i],2);
        u_dev_b += pow(dataSourceBVAS.Ub[i],2);
        u_dev_c += pow(dataSourceBVAS.Uc[i],2);

        i_zero_a += dataSourceBVAS.Ia[i];
        i_zero_b += dataSourceBVAS.Ib[i];
        i_zero_c += dataSourceBVAS.Ic[i];
        u_zero_a += dataSourceBVAS.Ua[i];
        u_zero_b += dataSourceBVAS.Ub[i];
        u_zero_c += dataSourceBVAS.Uc[i];
    }

    //Расчет действующих значений токов
    i_dev_a /= BUF_SIZE;
    i_dev_a = sqrt(i_dev_a);
    i_dev_b /= BUF_SIZE;
    i_dev_b = sqrt(i_dev_b);
    i_dev_c /= BUF_SIZE;
    i_dev_c = sqrt(i_dev_c);

    //Расчет действующих значений напряжений
    u_dev_a /= BUF_SIZE;
    u_dev_a = sqrt(u_dev_a);
    u_dev_b /= BUF_SIZE;
    u_dev_b = sqrt(u_dev_b);
    u_dev_c /= BUF_SIZE;
    u_dev_c = sqrt(u_dev_c);

    i_zero_a /= BUF_SIZE;
    i_zero_b /= BUF_SIZE;
    i_zero_c /= BUF_SIZE;
    u_zero_a /= BUF_SIZE;
    u_zero_b /= BUF_SIZE;
    u_zero_c /= BUF_SIZE;

    ui->labelValueIa->setText(QString("%1").arg(i_dev_a));
    ui->labelValueIb->setText(QString("%1").arg(i_dev_b));
    ui->labelValueIc->setText(QString("%1").arg(i_dev_c));

    ui->labelValueUa->setText(QString("%1").arg(u_dev_a));
    ui->labelValueUb->setText(QString("%1").arg(u_dev_b));
    ui->labelValueUc->setText(QString("%1").arg(u_dev_c));
}

void Kalibr::on_pushButtonZeroApplyIa_clicked()
{
    ui->lineEditZeroIa->setText(QString("%1").arg(i_zero_a + dataSourceBVAS.IaZeroLevel));
    dataSourceBVAS.IaZeroLevel += i_zero_a;
}

void Kalibr::on_pushButtonZeroApplyIb_clicked()
{
    ui->lineEditZeroIb->setText(QString("%1").arg(i_zero_b + dataSourceBVAS.IbZeroLevel));
    dataSourceBVAS.IbZeroLevel += i_zero_b;
}

void Kalibr::on_pushButtonZeroApplyIc_clicked()
{
    ui->lineEditZeroIc->setText(QString("%1").arg(i_zero_c + dataSourceBVAS.IcZeroLevel));
    dataSourceBVAS.IcZeroLevel += i_zero_c;
}

void Kalibr::on_pushButtonZeroApplyUa_clicked()
{
    ui->lineEditZeroUa->setText(QString("%1").arg(u_zero_a + dataSourceBVAS.UaZeroLevel));
    dataSourceBVAS.UaZeroLevel += u_zero_a;
}

void Kalibr::on_pushButtonZeroApplyUb_clicked()
{
    ui->lineEditZeroUb->setText(QString("%1").arg(u_zero_b + dataSourceBVAS.UbZeroLevel));
    dataSourceBVAS.UbZeroLevel += u_zero_b;
}

void Kalibr::on_pushButtonZeroApplyUc_clicked()
{
    ui->lineEditZeroUc->setText(QString("%1").arg(u_zero_c + dataSourceBVAS.UcZeroLevel));
    dataSourceBVAS.UcZeroLevel += u_zero_c;
}

void Kalibr::on_pushButtonValueApplyIa_clicked()
{
    dataSourceBVAS.IaCalibrationCoeff *= ui->lineEditValueIa->text().toDouble() / i_dev_a;
}

void Kalibr::on_pushButtonValueApplyIb_clicked()
{
    dataSourceBVAS.IbCalibrationCoeff *= ui->lineEditValueIb->text().toDouble() / i_dev_b;
}

void Kalibr::on_pushButtonValueApplyIc_clicked()
{
    dataSourceBVAS.IcCalibrationCoeff *= ui->lineEditValueIc->text().toDouble() / i_dev_c;
}

void Kalibr::on_pushButtonValueApplyUa_clicked()
{
    dataSourceBVAS.UaCalibrationCoeff *= ui->lineEditValueUa->text().toDouble() / u_dev_a;
}

void Kalibr::on_pushButtonValueApplyUb_clicked()
{
    dataSourceBVAS.UbCalibrationCoeff *= ui->lineEditValueUb->text().toDouble() / u_dev_b;
}

void Kalibr::on_pushButtonValueApplyUc_clicked()
{
    dataSourceBVAS.UcCalibrationCoeff *= ui->lineEditValueUc->text().toDouble() / u_dev_c;
}

void Kalibr::on_pushButtonClose_clicked()
{
    close();
}

void Kalibr::closeEvent(QCloseEvent *)
{
    dataSourceBVAS.stop();
}

void Kalibr::on_pushButtonAccept_clicked()
{
    QSettings settings;
    settings.setValue("calibration/IaZero", dataSourceBVAS.IaZeroLevel);
    settings.setValue("calibration/IbZero", dataSourceBVAS.IbZeroLevel);
    settings.setValue("calibration/IcZero", dataSourceBVAS.IcZeroLevel);

    settings.setValue("calibration/UaZero", dataSourceBVAS.UaZeroLevel);
    settings.setValue("calibration/UbZero", dataSourceBVAS.UbZeroLevel);
    settings.setValue("calibration/UcZero", dataSourceBVAS.UcZeroLevel);

    settings.setValue("calibration/IaCoeff", dataSourceBVAS.IaCalibrationCoeff);
    settings.setValue("calibration/IbCoeff", dataSourceBVAS.IbCalibrationCoeff);
    settings.setValue("calibration/IcCoeff", dataSourceBVAS.IcCalibrationCoeff);

    settings.setValue("calibration/UaCoeff", dataSourceBVAS.UaCalibrationCoeff);
    settings.setValue("calibration/UbCoeff", dataSourceBVAS.UbCalibrationCoeff);
    settings.setValue("calibration/UcCoeff", dataSourceBVAS.UcCalibrationCoeff);
}
