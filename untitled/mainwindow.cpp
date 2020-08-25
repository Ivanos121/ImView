#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QClipboard>
#include <QScreen>
#include "base.h"
#include "datas.h"
#include "identf.h"
#include "electromagn.h"
#include "kalibr.h"
#include "teplovent.h"

Base base;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_2->dataSource->setMainWindow(this);
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionabout_triggered()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    rsc=new about(this);
    rsc->show();
    rsc->setGeometry(
        QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        rsc->size(),
        screen->geometry()));
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_action_10_triggered()
{

}

void MainWindow::on_actionhelp_triggered()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &MainWindow::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("help_v1/index.html").absoluteFilePath()));
    view->setWindowIcon(QIcon::fromTheme("help-contents"));
    view->showMaximized();
}

void MainWindow::titleChanged(const QString &title)
{
    view->setWindowTitle(title);
}

void MainWindow::on_action_16_triggered()
{
    ui->widget->on_pushButton_3_clicked();
}

void MainWindow::on_action_12_triggered()
{
    ui->widget->on_pushButton_4_clicked();
}

void MainWindow::on_action_17_triggered()
{
    ui->widget->on_pushButton_6_clicked();
}

void MainWindow::on_action_19_triggered()
{
    ui->widget->on_pushButton_clicked();
}

void MainWindow::on_action_18_triggered()
{
    ui->widget->on_pushButton_2_clicked();
}

void MainWindow::on_action_5_triggered()
{
 ui->widget_2->raschet_f();
}

void MainWindow::on_action_9_triggered()
{
 ui->widget_2->dataSource->stop();
}

void MainWindow::on_action_20_triggered()
{
 ui->widget_3->raschet_el();
}

void MainWindow::on_action_21_triggered()
{
 ui->widget_3->stop();
}

void MainWindow::on_tabWidget_currentChanged(int)
{

}

void MainWindow::on_action_22_triggered()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    kalibr=new Kalibr(this);
    kalibr->show();
    kalibr->setGeometry(
    QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    kalibr->size(),
    screen->geometry()));
}
