#include "teplschem.h"
#include "ui_teplschem.h"

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

void teplschem::on_checkBox_toggled(bool checked)
{
    if (checked)
    {
        ui->webEngineView->page()->runJavaScript(QString("$('#text255').show();"));
    }
    else
    {
        ui->webEngineView->page()->runJavaScript(QString("$('#text255').hide();"));
    }
}

