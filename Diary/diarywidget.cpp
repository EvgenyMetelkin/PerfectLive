#include <QDebug>
#include <QFileDialog>

#include "diarywidget.h"
#include "ui_diarywidget.h"
#include "Global/settings.h"
#include "dbhistorydiary.h"
#include "WiseLine/wiselineparser.h"

#define SIZE_SMALL 700
#define SIZE_MEDIUM 1250
#define SIZE_LARGE 1800

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

    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
    connect(&m_timerWiseLine, &QTimer::timeout, this, &DiaryWidget::NextWiseLine);
    m_timerWiseLine.start(100000);
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
    AddInfoBonus(out);

    file.close();

    ui->Info->setText("File: " + fileName + " saved.");

    switch(AddHistoryInDB()) {
    case 1:
        ui->Info->setStyleSheet("background-color: #a7d984");
        break;
    case 2:
        ui->Info->setStyleSheet("background-color: #5da130");
        break;
    case 3:
        ui->Info->setStyleSheet("background-color: #F6A625");
        break;
    case 4:
        ui->Info->setStyleSheet("background-color: #BF593E");
        break;
    case 0:
    default:
        ui->Info->setStyleSheet("background-color: #ff7a5c");
    }
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

int DiaryWidget::GetBonus()
{
    int sumBonus = 0;
    if(ui->chbImportantChoice->isChecked()) {
        qDebug() << "Add bonus ImportantChoice +1000";
        sumBonus += 1000;
    }
    if(ui->chbImportantDay->isChecked()) {
        qDebug() << "Add bonus ImportantDay +200";
        sumBonus += 200;
    }
    if(ui->chbIncreaseKarma->isChecked()) {
        qDebug() << "Add bonus IncreaseKarma +100";
        sumBonus += 100;
    }
    if(ui->chbDoneGoal->isChecked()) {
        qDebug() << "Add bonus DoneGoal +1000";
        sumBonus += 1000;
    }
    if(ui->chbReadBook->isChecked()) {
        qDebug() << "Add bonus ReadBook +200";
        sumBonus += 200;
    }
    if(ui->chbLearnInglish->isChecked()) {
        qDebug() << "Add bonus LearnInglish +200";
        sumBonus += 200;
    }
    if(ui->chbTriedSomethingNew->isChecked()) {
        qDebug() << "Add bonus TriedSomethingNew +200";
        sumBonus += 200;
    }
    if(ui->chbVisiteCoolPlace->isChecked()) {
        qDebug() << "Add bonus VisiteCoolPlace +100";
        sumBonus += 100;
    }
    if(ui->chbCallMomAndDad->isChecked()) {
        qDebug() << "Add bonus CallMomAndDad +200";
        sumBonus += 200;
    }
    if(ui->chbDoNotAfraidTry->isChecked()) {
        qDebug() << "Add bonus DoNotAfraidTry +400";
        sumBonus += 400;
    }

    return  sumBonus;
}

void DiaryWidget::AddInfoBonus(QTextStream &out)
{
    out << endl << endl;
    if(ui->chbImportantChoice->isChecked()) {
        out << "Принял очень значимое в жизни решение           +1000";
    }
    if(ui->chbImportantDay->isChecked()) {
        out << "Незабываемый день                               +200";
    }
    if(ui->chbIncreaseKarma->isChecked()) {
        out << "Повысил карму                                   +100";
    }
    if(ui->chbDoneGoal->isChecked()) {
        out << "Исполнил мечту                                  +1000";
    }
    if(ui->chbReadBook->isChecked()) {
        out << "Прочитано 20+ страниц                           +200";
    }
    if(ui->chbLearnInglish->isChecked()) {
        out << "Выучил 10 англ. слов или прокачал английский    +200";
    }
    if(ui->chbTriedSomethingNew->isChecked()) {
        out << "AПопробовал что-то новое                        +200";
    }
    if(ui->chbVisiteCoolPlace->isChecked()) {
        out << "Побывал в крутом месте                          +100";
    }
    if(ui->chbCallMomAndDad->isChecked()) {
        out << "Позвонил родителям                              +200";
    }
    if(ui->chbDoNotAfraidTry->isChecked()) {
        out << "Не побоялся попробовать                         +400";
    }
}

int DiaryWidget::AddHistoryInDB()
{
    int sizeText = ui->Text->toPlainText().size();
    qDebug() << Q_FUNC_INFO << "Size text: " << sizeText << "";
    int sizeTextAndBonus = sizeText + GetBonus();
    int coefficientTextSizeAndBonus = 0;
    if(sizeTextAndBonus == 0) { return 0; }
    else if(sizeTextAndBonus < SIZE_SMALL) coefficientTextSizeAndBonus = 1;
    else if(sizeTextAndBonus < SIZE_MEDIUM) coefficientTextSizeAndBonus = 2;
    else if(sizeTextAndBonus < SIZE_LARGE) coefficientTextSizeAndBonus = 3;
    else if(sizeTextAndBonus > SIZE_LARGE) coefficientTextSizeAndBonus = 4;

    DBHistoryDiary db;
    db.InsertHistoryDiary(coefficientTextSizeAndBonus);

    return coefficientTextSizeAndBonus;
}

void DiaryWidget::on_Text_textChanged() // ! возможна потеря производительности
{
    if(!ui->Text->toPlainText().isEmpty())
        ui->Save->setEnabled(true);
    else
        ui->Save->setEnabled(false);
}

void DiaryWidget::NextWiseLine()
{
    ui->lWiseLine->setText(WiseLineParser::GetWiseLine());
}
