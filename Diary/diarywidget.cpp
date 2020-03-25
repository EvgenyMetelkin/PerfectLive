#include "diarywidget.h"
#include "ui_diarywidget.h"
#include "Global/settings.h"

#include <QDebug>
#include <QFileDialog>


DiaryWidget::DiaryWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiaryWidget)
{
    connect(this, &DiaryWidget::ShowOpenOldFileWidget, &m_openOldFileWidget, &OpenOldFileWidget::OnShowOpenOldFileWidget);
    connect(&m_openOldFileWidget, &OpenOldFileWidget::SignalOpenFile, this, &DiaryWidget::OnOpenFile);

    connect(&m_rewriteDialog, &RewriteDialog::accepted, this, &DiaryWidget::SaveFile);

    ui->setupUi(this);
    m_rewriteDialog.hide();

    m_dir = Settings::get(Settings::DiaryPath, Settings::General).toString();
    if(m_dir.absolutePath() == "") {
        on_setBasePath_triggered();
        m_dir = Settings::get(Settings::DiaryPath, Settings::General).toString();
    }

    ui->Date->setDate(QDate::currentDate());
}

DiaryWidget::~DiaryWidget()
{
    foreach (auto modifyFile, m_listModifyFiles) { // !! память освобождается только при закрытии приложения
        delete modifyFile;
    }
    delete ui;
}


void DiaryWidget::OnOpenFile(QString &path)
{
    ModifyFile *modifyFile = new ModifyFile(path);
    m_listModifyFiles.append(modifyFile);
    m_openOldFileWidget.hide();
}

void DiaryWidget::SaveFile()
{
    qDebug() << Q_FUNC_INFO;
    QString fileName = m_dir.absolutePath() + "/" + ui->Date->text() + ".png";

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->Text->toPlainText();

    file.close();

    ui->Info->setText("File: " + fileName + " saved.");
    ui->Info->setStyleSheet("background-color: #75ffb8");
}

void DiaryWidget::on_Save_clicked()
{
    QString fileName = m_dir.absolutePath() + "/" + ui->Date->text() + ".png";

    if(QFile::exists(fileName)) {
        ui->Info->setText("Error: the file " + fileName + " is not unique...");
        ui->Info->setStyleSheet("background-color: #ff7a5c");
        m_rewriteDialog.show();
        return;
    }

    SaveFile();
}

void DiaryWidget::on_setBasePath_triggered()
{
    m_dir = QDir::currentPath() + "/data";
    if (!m_dir.exists()) {
        m_dir.mkpath(m_dir.absolutePath());
    }
    Settings::set(Settings::DiaryPath, Settings::General) = m_dir.absolutePath();
}

void DiaryWidget::on_changPath_triggered()
{
    m_dir = QFileDialog::getExistingDirectory(nullptr, "ChangePath", m_dir.absolutePath());
    Settings::set(Settings::DiaryPath, Settings::General) = m_dir.absolutePath();
}


void DiaryWidget::on_openOldFile_clicked()
{
    emit ShowOpenOldFileWidget(m_dir);
}
