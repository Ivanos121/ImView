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
#include "vent_model.h"
#include "ui_vent_model.h"
#include "ui_vent_tract.h"
#include "gridlinedelegate.h"

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
    ui->widget->wf=this;

    ui->widget_5->ui->widget->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/ax_var/ax_var_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/rad_var/rad_var_2.html").absoluteFilePath()));
    ui->widget_6->ui->widget_2->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/vent_tract/vent_tract.html").absoluteFilePath()));
    ui->widget_5->ui->widget_3->ui->webEngineView->setUrl(QUrl::fromLocalFile(QFileInfo("../data/tepl_schen_zam/vent_tract.html").absoluteFilePath()));

    ui->widget_5->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_5->ui->widget_5->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));
    ui->widget_6->ui->widget->ui->webEngineView_2->setUrl(QUrl::fromLocalFile(QFileInfo("../data/grad_line/grad_line_2.html").absoluteFilePath()));


    showMaximized();
    ui->action_9->setEnabled(false);
    ui->action_21->setEnabled(false);

    ui->treeWidget->setColumnCount(2);
    QStringList name;
    name << "Параметр" << "Свойство";
    ui->treeWidget->setHeaderLabels(name);

    ui->treeWidget->header()->setVisible(1);
    ui->treeWidget->header()->setStretchLastSection(false);
    ui->treeWidget->header()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->treeWidget->header()->setSectionResizeMode(1, QHeaderView::Interactive);
   // ui->treeWidget->setStyleSheet("QTreeWidget::item { border-bottom: 1px solid black;}");

    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->treeWidget);
    treeItem->setText(0,"Настройки проекта");
    //treeItem->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem);

    QTreeWidgetItem *child= new QTreeWidgetItem();
    child->setText(0,"Название проекта");
    child->setText(1,"Описание");
    treeItem->addChild(child);

    QTreeWidgetItem *child2= new QTreeWidgetItem();
    child2->setText(0,"Расположение проекта");
    child2->setText(1,"Описание");
    QPushButton *pushbutton=new QPushButton();
    ui->treeWidget->setItemWidget(child2, 1, pushbutton);
    treeItem->addChild(child2);

    QTreeWidgetItem *treeItem2 = new QTreeWidgetItem(ui->treeWidget);
    treeItem2->setText(0,"Исходные данные");
    treeItem2->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem2);

    QTreeWidgetItem *child3= new QTreeWidgetItem();
    child3->setText(0,"Исходные данные");
    child3->setText(1,"Описание");
    treeItem2->addChild(child3);

    QTreeWidgetItem *treeItem3 = new QTreeWidgetItem(ui->treeWidget);
    treeItem3->setText(0,"Идентификация параметров схемы замещения");
    treeItem3->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem3);

    QTreeWidgetItem *child4= new QTreeWidgetItem();
    child4->setText(0,"Исходные данные");
    child4->setText(1,"Описание");
    treeItem3->addChild(child4);

    QTreeWidgetItem *treeItem4 = new QTreeWidgetItem(ui->treeWidget);
    treeItem4->setText(0,"Электромагнитные процессы");
    treeItem4->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem4);

    QTreeWidgetItem *treeItem5 = new QTreeWidgetItem(ui->treeWidget);
    treeItem5->setText(0,"Тепловые процессы");
    treeItem5->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem5);

    QTreeWidgetItem *treeItem6 = new QTreeWidgetItem(ui->treeWidget);
    treeItem6->setText(0,"Вентиляционные процессы");
    treeItem6->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem6);

    QTreeWidgetItem *treeItem7 = new QTreeWidgetItem(ui->treeWidget);
    treeItem7->setText(0,"Энергетика");
    treeItem7->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem7);

    QTreeWidgetItem *treeItem8 = new QTreeWidgetItem(ui->treeWidget);
    treeItem8->setText(0,"Выходные данные");
    treeItem8->setText(1,"Описание");
    ui->treeWidget->addTopLevelItem(treeItem8);

    GridLineDelegate* gridlinedelegate = new GridLineDelegate(this); //создание делегата для создания комбобоксов
    ui->treeWidget->setItemDelegateForColumn(0, gridlinedelegate);
    ui->treeWidget->setItemDelegateForColumn(1, gridlinedelegate);

    ui->treeWidget->header()->setVisible(1);

    QPalette p99=ui->treeWidget->palette();
    p99.setColor(QPalette::Base, QColor(255, 255, 222));
    p99.setColor(QPalette::AlternateBase, QColor(255, 255, 191));
    ui->treeWidget->setPalette(p99);
    //ui->treeWidget->hide();


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
    ui->widget->on_enterDannie_clicked();
}

void MainWindow::on_action_12_triggered()
{

}

void MainWindow::on_action_17_triggered()
{
    ui->widget->on_deleteDannie_clicked();
}

void MainWindow::on_action_19_triggered()
{

}

void MainWindow::on_action_5_triggered()
{
    QModelIndex myIndex, myIndex2, myIndex3,myIndex4,myIndex5,myIndex6,myIndex7;
    myIndex = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 2, QModelIndex());
    base.P_nom=ui->widget->ui->tableView->model()->data(myIndex).toDouble();
    myIndex2 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 3, QModelIndex());
    base.n_nom=ui->widget->ui->tableView->model()->data(myIndex2).toDouble();
    myIndex3 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 4, QModelIndex());
    base.U_fnom=ui->widget->ui->tableView->model()->data(myIndex3).toDouble();
    myIndex4 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 5, QModelIndex());
    base.cosf_nom=ui->widget->ui->tableView->model()->data(myIndex4).toDouble();
    myIndex5 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 6, QModelIndex());
    base.kpd_nom=ui->widget->ui->tableView->model()->data(myIndex5).toDouble();
    myIndex6 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 7, QModelIndex());
    base.muk=ui->widget->ui->tableView->model()->data(myIndex6).toDouble();
    myIndex7 = ui->widget->ui->tableView->model()->index(ui->widget->ui->tableView->currentIndex().row(), 8, QModelIndex());
    base.n_0=ui->widget->ui->tableView->model()->data(myIndex7).toDouble();
//qDebug() << QString("%1").arg(base.P_nom);

    ui->action_5->setIcon(QIcon(":/system_icons/data/img/system_icons/media-playback-paused.svg"));
    ui->action_9->setEnabled(true);
    ui->widget_2->raschet_f();
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
