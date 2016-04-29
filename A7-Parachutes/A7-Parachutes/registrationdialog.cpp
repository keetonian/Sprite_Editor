#include "registrationdialog.h"
#include "ui_registrationDialog.h"

RegistrationDialog::RegistrationDialog(Networking *client_, QWidget *parent)
    : client(client_), QDialog(parent), ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
    ui->teacberNameLabel->setEnabled(false);
    ui->teachersName->setEnabled(false);

    connect(ui->studentRadioButton, &QRadioButton::toggled, this, &RegistrationDialog::enableTeacherName);
    connect(ui->teacherRadioButton, &QRadioButton::toggled, this, &RegistrationDialog::disableTeacherName);
    connect(ui->OKButton, &QPushButton::clicked, this, &RegistrationDialog::checkInput);
    connect(ui->cancelButton, &QPushButton::clicked, this, &RegistrationDialog::showMainwindow);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::enableTeacherName()
{
    ui->teacberNameLabel->setEnabled(true);
    ui->teachersName->setEnabled(true);
}

void RegistrationDialog::disableTeacherName()
{
    ui->teacberNameLabel->setEnabled(false);
    ui->teachersName->setEnabled(false);
}

void RegistrationDialog::showMainwindow()
{
    this->close();
}

void RegistrationDialog::checkInput()
{
    if(ui->username->text().count() > 0
            &&ui->password->text().count() > 0
            &&ui->confirmPassword->text().count() > 0)
    {
        if(ui->password->text().compare(ui->confirmPassword->text(), Qt::CaseSensitive)!= 0)
        {
               ui->warningLabel->setText("Password does not match");
        }
        else if(ui->teacherRadioButton->isChecked())
        {
            this->close();
        }
        else if(ui->studentRadioButton->isChecked()&&ui->teachersName->text().count() > 0)
        {
            this->close();
        }
        else
        {
         ui->warningLabel->setText("Select Student or Teacher and fill the blank.");
        }
    }
    else
    {
        ui->warningLabel->setText("Username or password cannot be empty");
    }
}
