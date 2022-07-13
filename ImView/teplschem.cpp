#include "teplschem.h"
#include "ui_teplovent.h"
#include "ui_teplschem.h"
#include "ui_mainwindow.h"

#include <QtSvg>
#include <QSvgWidget>
#include <QGraphicsPixmapItem>

teplschem::teplschem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::teplschem)
{
    ui->setupUi(this);
}

teplschem::~teplschem()
{
    delete ui;
}

//void teplschem::on_radioButton_toggled(bool checked)
//{
//    if (checked)
//    {
//        ui->webEngineView->page()->runJavaScript(QString("$('#text4878').text('%1 °C');").arg(100.00, 0, 'f', 2));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text255').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text205').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text345').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text241').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text517').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text249').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text327').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text237').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text261').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text209').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text435').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text245').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text499').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text233').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text267').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text213').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text285').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text217').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text293').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text221').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text299').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text225').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text307').show();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text229').show();"));
//    }
//    else
//    {
//        ui->webEngineView->page()->runJavaScript(QString("$('#text255').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text205').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text345').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text241').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text517').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text249').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text327').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text237').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text261').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text209').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text435').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text245').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text499').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text233').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text267').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text213').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text285').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text217').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text293').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text221').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text299').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text225').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text307').hide();"));
//        ui->webEngineView->page()->runJavaScript(QString("$('#text229').hide();"));
//    }

//}

//void teplschem::on_radioButton_2_toggled(bool checked)
//{
//    if (checked)
//    {
//        ui->webEngineView->page()->runJavaScript(QString("$('#text4878').text('%1 °C');").arg(100.00, 0, 'f', 2));
//    }
//    else
//    {

//    }
//}

//void teplschem::on_radioButton_3_toggled(bool checked)
//{
//    if (checked)
//    {
//        ui->webEngineView->page()->runJavaScript(QString("$('#text4878').text('%1 Дж');").arg(2000.00, 0, 'f', 2));
//    }
//    else
//    {

//    }
//}

//void teplschem::on_radioButton_4_toggled(bool checked)
//{
//    if (checked)
//    {
//        ui->webEngineView->page()->runJavaScript(QString("$('#text4878').text('%1 Вт');").arg(300.00, 0, 'f', 2));
//    }
//    else
//    {

//    }
//}

