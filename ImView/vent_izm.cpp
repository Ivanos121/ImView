#include "vent_izm.h"
#include "ui_vent_izm.h"

#include <QFileInfo>

vent_izm::vent_izm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vent_izm)
{
    ui->setupUi(this);
}

vent_izm::~vent_izm()
{
    delete ui;
}
