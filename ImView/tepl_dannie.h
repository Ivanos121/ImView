#ifndef TEPL_DANNIE_H
#define TEPL_DANNIE_H

#include <QWidget>
#include "Base_tepl.h"

namespace Ui {
class Tepl_dannie;
}

class Tepl_dannie : public QWidget
{
    Q_OBJECT

public:
    explicit Tepl_dannie(QWidget *parent = nullptr);
    ~Tepl_dannie();


    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::Tepl_dannie *ui;
    Base_tepl base_tepl;
};

#endif // TEPL_DANNIE_H
