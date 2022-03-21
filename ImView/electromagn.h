#ifndef ELECTROMAGN_H
#define ELECTROMAGN_H

#include <QWidget>
#include <QTimer>
#include <QElapsedTimer>
#include "nabludatel.h"
#include "nabludatel_part.h"
#include "datasource_file.h"
#include "datasourcebvas.h"
#include "datasource.h"
#include "plot.h"

namespace Ui {
class electromagn;
}

class electromagn : public QWidget
{
    Q_OBJECT

public:
    explicit electromagn(QWidget *parent = nullptr);
    ~electromagn();
    double key;
    int count = 0;
    MainWindow *wf;

    void stop();

public slots:
    void realtimeDataSlot();
    void raschet_el(); 

private slots:
    void on_pushButton_clicked();
    void setcolorincell(int row, int column);

    void on_pushButton_2_clicked();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_4_clicked();

    void on_radioButton_3_clicked();

    void bvasFailureSlot();

private:
    Ui::electromagn *ui;
    QElapsedTimer *time;
    Nabludatel nabludatel;
    Nabludatel_part nabludatel_part;
    DataSource* dataSource;
    QComboBox* combo = new QComboBox();
    QComboBox* combo2 = new QComboBox();
    QVector<QColor> dataLineColors;

    void addDataLines();

};

#endif // ELECTROMAGN_H
