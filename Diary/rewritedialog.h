#ifndef REWRITEDIALOG_H
#define REWRITEDIALOG_H

#include <QDialog>

namespace Ui {
class RewriteDialog;
}

class RewriteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RewriteDialog(QWidget *parent = nullptr);
    ~RewriteDialog();

private:
    Ui::RewriteDialog *ui;
};

#endif // REWRITEDIALOG_H
