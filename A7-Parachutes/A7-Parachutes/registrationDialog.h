#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QEvent>
#include <QDialog>
namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = 0);

    ~RegistrationDialog();

private slots:
    void enableTeacherName();
    void disableTeacherName();
    void showMainwindow();
    void checkInput();
private:
    Ui::RegistrationDialog *ui;


};

#endif // REGISTRATIONDIALOG_H
