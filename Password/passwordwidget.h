#ifndef PASSWORDWIDGET_H
#define PASSWORDWIDGET_H

#include <QDialog>

namespace Ui {
class PasswordWidget;
}

class PasswordWidget : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordWidget(QWidget *parent = nullptr);
    ~PasswordWidget();

signals:
    void confirmedPassword();

private slots:
    void on_Accept_clicked();

    void on_Password_textChanged(const QString &arg1);

private:
    Ui::PasswordWidget *ui;
};

#endif // PASSWORDWIDGET_H
