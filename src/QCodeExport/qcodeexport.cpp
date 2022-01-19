//
// Created by liuhaoran on 2022/1/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QCodeExport.h" resolved

#include "qcodeexport.h"
#include "ui_QCodeExport.h"


QCodeExport::QCodeExport(QWidget *parent) :
        QWidget(parent), ui(new Ui::QCodeExport) {
    ui->setupUi(this);
    connect(ui->pushButton_selectProject, &QPushButton::clicked, this, &QCodeExport::onSelectProjectDirHandler);
    connect(ui->pushButton_selectExport, &QPushButton::clicked, this, &QCodeExport::onSelectExportDirHandler);
    connect(ui->pushButton_export, &QPushButton::clicked, this, &QCodeExport::onExportClickHandler);

    ui->textEdit_codeFileFilter->setPlainText(getInputFilter());
    ui->textEdit_excludeDirs->setPlainText(getExcludeDirs());
}

QCodeExport::~QCodeExport() {
    delete ui;
}

void QCodeExport::onSelectProjectDirHandler() {

    auto *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("选择项目文件夹");
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::FileMode::Directory);

    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        if (fileNames.length() > 0) {
            ui->label_codedir->setText(fileNames[0]);
        }
    }
}

void QCodeExport::onSelectExportDirHandler() {

    auto *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("选择导出文件夹");
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::FileMode::Directory);
    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        if (fileNames.length() > 0) {
            ui->label_exportPath->setText(fileNames[0]);
        }
    }


}

void QCodeExport::onExportClickHandler() {
    // 获取输入文件过滤
    QString inputfilter = ui->textEdit_codeFileFilter->placeholderText();
    QString excludeDirs = ui->textEdit_excludeDirs->placeholderText();
    QStringList ifs = inputfilter.split("|");
    QStringList eds = excludeDirs.split("|");

    QDirIterator it(ui->label_codedir->text());
    while (it.hasNext()) {
        qDebug() << "it:" << it.next();
    }
    qDebug() << "getInputFilter:" << getInputFilter();
    qDebug() << "getExcludeDirs:" << getExcludeDirs();

}

QString QCodeExport::getInputFilter() {
    auto *configIniWrite = new QSettings("config/QCodeExport.ini", QSettings::IniFormat);
    return configIniWrite->value("/default/InputFilter").toString();
}

QString QCodeExport::getExcludeDirs() {
    auto *configIniWrite = new QSettings("config/QCodeExport.ini", QSettings::IniFormat);
    return configIniWrite->value("/default/ExcludeDirs").toString();
}

