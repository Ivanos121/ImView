#ifndef TEPLSCHEM_H
#define TEPLSCHEM_H

#include <QWidget>
#include <QList>
#include <QGraphicsTextItem>
#include <QDomDocument>
#include <QTimer>

namespace Ui {
class teplschem;
}

class teplschem : public QWidget
{
    Q_OBJECT

public:
    explicit teplschem(QWidget *parent = nullptr);
    ~teplschem();

    void retrievElements(QDomElement root, QString tag, QString att);

public slots:
    void on_checkBox_clicked();


private slots:
    void on_radioButton_5_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_4_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

public:
    Ui::teplschem *ui;
    QDomDocument doc;
    QTimer timer;
};

#endif // TEPLSCHEM_H
