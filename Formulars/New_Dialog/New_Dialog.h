#ifndef NEW_DIALOG_H
#define NEW_DIALOG_H

#include <QWidget>

namespace Ui {
class New_Dialog;
}

class New_Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit New_Dialog(QWidget *parent = 0);
    ~New_Dialog();

private:
    Ui::New_Dialog *ui;
};

#endif // NEW_DIALOG_H
