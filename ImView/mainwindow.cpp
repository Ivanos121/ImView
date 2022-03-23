#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QClipboard>
#include <QScreen>
#include "base.h"
#include "datas.h"
#include "ui_datas.h"
#include "identf.h"
#include "electromagn.h"
#include "kalibr.h"
#include "teplovent.h"
#include "ui_teplovent.h"
#include "ui_draw_line.h"
#include "ui_draw_poper.h"
#include "ui_teplschem.h"
#include "ui_vent_model.h"
#include "ui_vent_izm.h"
#include "ui_datas.h"

Base base;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget_2->wf=this;
    ui->widget_3->wf=this;
    ui->widget_5->wf=this;
    ui->widget_6->wf=this;
    ui->widget_5->ui->widget_4->wf=this;

    ui->widget_5->ui->widget->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ax_var/ax_var_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/rad_var/rad_var_2.html").absoluteFilePath()));
    ui->widget_6->ui->widget_2->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_tract/vent_tract.html").absoluteFilePath()));
    ui->widget_5->ui->widget_3->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/vent_tract.html").absoluteFilePath()));


    showMaximized();
    ui->action_9->setEnabled(false);
    ui->action_21->setEnabled(false);

}

void MainWindow::closeEvent (QCloseEvent *)
{
    ui->widget_3->stop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionabout_triggered()
{
    QScreen *screen = QGuiApplication::primaryScreen();
        rsc= new AboutDialog(this);
        rsc->exec();
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
ui->widget->ui->lineEdit_3->cut();
}

void MainWindow::on_actionhelp_triggered()
{
    view = new QWebEngineView;
    connect(view, &QWebEngineView::titleChanged, this, &MainWindow::titleChanged);
    view->setUrl(QUrl::fromLocalFile(QFileInfo("../help/index.html").absoluteFilePath()));
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
    if(ui->widget->ui->lineEdit_2->text().isEmpty() || ui->widget->ui->lineEdit_3->text().isEmpty()
            || ui->widget->ui->lineEdit_4->text().isEmpty() || ui->widget->ui->lineEdit_5->text().isEmpty() || ui->widget->ui->lineEdit_6->text().isEmpty()
            || ui->widget->ui->lineEdit_7->text().isEmpty() || ui->widget->ui->lineEdit_8->text().isEmpty() || ui->widget->ui->lineEdit_9->text().isEmpty())
        {
        QMessageBox::critical(this, "Ошибка!", "Заполните пустые поля");
        }
    else
        {
            ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
            ui->action_9->setEnabled(true);
            ui->widget_2->raschet_f();
        }

}

void MainWindow::on_action_9_triggered()
{
    ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start_2.svg"));
    ui->action_9->setEnabled(false);
    ui->widget_2->dataSource->stop();
}

void MainWindow::on_action_20_triggered()
{
    ui->action_20->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
    ui->action_21->setEnabled(true);
    ui->widget_5->ui->widget_4->startTeplo();
    ui->widget_3->raschet_el();
}

void MainWindow::on_action_21_triggered()
{
    ui->action_20->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-start.svg"));
    ui->action_21->setEnabled(false);
    ui->widget_5->ui->widget_4->stopTeplo();
    ui->widget_3->stop();
}

void MainWindow::on_tabWidget_currentChanged(int)
{

}

void MainWindow::on_action_22_triggered()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    kalibr=new Kalibr(this);
    kalibr->showMaximized();
    kalibr->setGeometry(
    QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    kalibr->size(),
    screen->geometry()));
}

void MainWindow::on_action_23_triggered()
{
QDir().mkdir("MyFolder");
}

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);
}

void AboutDialog::on_pushButton_clicked()
{
    close();
}

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    QListWidgetItem *item_1=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/folder.svg"), "Интерфейс");
    ui->listWidget->addItem(item_1);
    QListWidgetItem *item_2=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-axis-vertical.svg"), "Исходные данные");
    ui->listWidget->addItem(item_2);
    QListWidgetItem *item_3=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-matrix-new.svg"), "Идентификация параметров");
    ui->listWidget->addItem(item_3);
    QListWidgetItem *item_4=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-xy-interpolation-curve.svg"), "Энергетические показатели");
    ui->listWidget->addItem(item_4);
    QListWidgetItem *item_5=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/labplot-zoom-out-y.svg"), "Тепловентиляция");
    ui->listWidget->addItem(item_5);
    QListWidgetItem *item_6=new QListWidgetItem(QIcon(":/system_icons/data/img/system_icons/map-flat.svg"), "Выходные данные");
    ui->listWidget->addItem(item_6);

    QModelIndex firstRow = ui->listWidget->model()->index(0, 0);
    ui->listWidget->selectionModel()->select(firstRow,
                                   QItemSelectionModel::ClearAndSelect |
                                   QItemSelectionModel::Rows);

    ui->listWidget->setFocus();

    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &Settings::on_listWidget_itemSelectionChanged);

    ui->stackedWidget->setCurrentIndex(0);
}

void Settings::on_pushButton_clicked()
{
    close();
}

void Settings::on_pushButton_3_clicked()
{
    close();
}

void Settings::on_listWidget_itemSelectionChanged()
{
    ui->stackedWidget->setCurrentIndex(ui->listWidget->currentRow());
}

void MainWindow::on_action_15_triggered()
{
    QScreen *screen = QGuiApplication::primaryScreen();
        rsc2= new Settings(this);
        rsc2->exec();
        rsc2->setGeometry(
            QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            rsc2->size(),
            screen->geometry()));
}
