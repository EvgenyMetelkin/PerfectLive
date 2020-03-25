#include "rewritedialog.h"
#include "ui_rewritedialog.h"

#include <QDebug>

RewriteDialog::RewriteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RewriteDialog)
{
    ui->setupUi(this);
}

RewriteDialog::~RewriteDialog()
{
    delete ui;
}
