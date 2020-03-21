#include "diarywidget.h"
#include "ui_diarywidget.h"

#include <QDebug>
#include <QFileDialog>


DiaryWidget::DiaryWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DiaryWidget)
{
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);

    connect(this, &DiaryWidget::showOpenOldFileWidget, &openOldFileWidget, &OpenOldFileWidget::onShowOpenOldFileWidget);
    connect(&openOldFileWidget, &OpenOldFileWidget::signalOpenFile, this, &DiaryWidget::onOpenFile);

    ui->setupUi(this);

    dir = settings.value(SETTINGS_DIR, QDir::currentPath() + "/data").toString();
    if (!dir.exists()) {
        dir.mkpath(dir.absolutePath());
    }

    ui->Date->setDate(QDate::currentDate());
}

DiaryWidget::~DiaryWidget()
{
    foreach (auto modifyFile, listModifyFiles) { // !? память освобождается только при закрытии приложения
        delete modifyFile;
    }
    delete ui;
}


void DiaryWidget::onOpenFile(QString &path)
{
    ModifyFile *modifyFile = new ModifyFile(path);
    listModifyFiles.append(modifyFile);
    openOldFileWidget.hide();
}

void DiaryWidget::on_Save_clicked()
{
    QString fileName = dir.absolutePath() + "/" + ui->Date->text() + ".png";

    if(QFile::exists(fileName)) {
        ui->Info->setText("Error: the file " + fileName + " is not unique...");
        ui->Info->setStyleSheet("background-color: #ff7a5c");
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << ui->Text->toPlainText();

    file.close();

    ui->Info->setText("File: " + fileName + " saved.");
    ui->Info->setStyleSheet("background-color: #75ffb8");
}

void DiaryWidget::on_setBasePath_triggered()
{
    dir = QDir::currentPath() + "/data";
    if (!dir.exists()) {
        dir.mkpath(dir.absolutePath());
    }
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(SETTINGS_DIR, dir.absolutePath());
    settings.sync();
}

void DiaryWidget::on_changPath_triggered()
{
    dir = QFileDialog::getExistingDirectory(nullptr, "ChangePath", dir.absolutePath());
    QSettings settings(ORGANIZATION_NAME, APPLICATION_NAME);
    settings.setValue(SETTINGS_DIR, dir.absolutePath());
    settings.sync();
}


void DiaryWidget::on_openOldFile_clicked()
{
    emit showOpenOldFileWidget(dir);
}
