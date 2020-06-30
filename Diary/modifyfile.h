#ifndef MODIFYFILE_H
#define MODIFYFILE_H

#include <QWidget>
#include <QFile>
#include <QTextStream>

namespace Ui {
class ModifyFile;
}

class ModifyFile : public QWidget
{
    Q_OBJECT

public:
    explicit ModifyFile(QString &_dir, QWidget *parent = nullptr);
    ~ModifyFile();

private slots:
    void on_bSaveChanges_clicked();

    void on_ModifyFile_destroyed();

private:
    void OpenFile();
    QString DoNotReadHiddenLine(QTextStream &in);

private:
    Ui::ModifyFile *ui;
    QString m_dir;
    QFile m_file;
};

#endif // MODIFYFILE_H
