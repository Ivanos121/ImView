#ifndef TEPLOVENT_H
#define TEPLOVENT_H

#include <QWidget>

namespace Ui {
class teplovent;
}

class teplovent : public QWidget
{
    Q_OBJECT

public:
    explicit teplovent(QWidget *parent = nullptr);
    ~teplovent();

private:
    Ui::teplovent *ui;
};

#endif // TEPLOVENT_H
