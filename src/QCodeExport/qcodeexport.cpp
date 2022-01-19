//
// Created by liuhaoran on 2022/1/18.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QCodeExport.h" resolved

#include <QRegularExpression>
#include <QDesktopServices>
#include "qcodeexport.h"
#include "ui_QCodeExport.h"

QString slash = "/";


QCodeExport::QCodeExport(QWidget *parent) :
        QWidget(parent), ui(new Ui::QCodeExport) {
    ui->setupUi(this);
    connect(ui->pushButton_selectProject, &QPushButton::clicked, this, &QCodeExport::onSelectProjectDirHandler);
    connect(ui->pushButton_selectExport, &QPushButton::clicked, this, &QCodeExport::onSelectExportDirHandler);
    connect(ui->pushButton_export, &QPushButton::clicked, this, &QCodeExport::onExportClickHandler);

    ui->textEdit_codeFileFilter->setPlainText(getInputFilter());
    ui->textEdit_excludeDirs->setPlainText(getExcludeDirs());
    ui->label_result->setText("");

#ifdef __WINDOWS_
    slash = "\\";
#endif
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
    ui->label_result->setText("开始执行,请等待执行完成!");
    // 获取输入文件过滤
    QString codeDir = ui->label_codedir->text();
    QString exportPath = ui->label_exportPath->text();
    QString inputfilter = ui->textEdit_codeFileFilter->toPlainText();
    QString excludeDirs = ui->textEdit_excludeDirs->toPlainText();

    if (codeDir.trimmed().isEmpty() || codeDir.trimmed() == "请选择") {
        QMessageBox::warning(nullptr, "错误", "请选择项目文件夹", QMessageBox::Yes, QMessageBox::Yes);
        ui->label_result->setText("请选择项目文件夹");
        return;
    }
    if (exportPath.trimmed().isEmpty() || exportPath.trimmed() == "请选择") {
        QMessageBox::warning(nullptr, "错误", "请选择导出文件夹", QMessageBox::Yes, QMessageBox::Yes);
        ui->label_result->setText("请选择导出文件夹");
        return;
    }

    if (inputfilter.trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "错误", "请输入文件过滤", QMessageBox::Yes, QMessageBox::Yes);
        ui->label_result->setText("请输入文件过滤");
        return;
    }

    if (exportPath.trimmed().isEmpty()) {
        QMessageBox::warning(nullptr, "错误", "请输入排除文件", QMessageBox::Yes, QMessageBox::Yes);
        ui->label_result->setText("请输入排除文件");
        return;
    }

    auto *fileList = new QStringList();
    inputfilter = inputfilter.replace("*", ".*?").replace("|", "$|");
    excludeDirs = excludeDirs.replace("*", ".*?").replace("|", "$|");
    qDebug() << "inputfilter:" << inputfilter;
    qDebug() << "excludeDirs:" << excludeDirs;
    getDirFiles(codeDir, fileList, inputfilter, excludeDirs);

    qDebug() << "fileList:" << fileList->length();
    QString text;
    for (const QString &item: *fileList) {
        QFile file(item);
        if (file.open(QIODevice::ReadOnly)) {
            text += file.readAll();
        }
    }
    QFile exportFile(exportPath + slash + "out.txt");
    if (exportFile.open(QIODevice::WriteOnly)) {
        exportFile.write(text.toStdString().c_str());
        exportFile.flush();
        exportFile.close();
    }
    ui->label_result->setText("导出成功!");
    QDesktopServices::openUrl("file:" + exportPath);

}

QString QCodeExport::getInputFilter() {
    auto *configIniWrite = new QSettings("config/QCodeExport.ini", QSettings::IniFormat);
    return configIniWrite->value("/default/InputFilter").toString();
}

QString QCodeExport::getExcludeDirs() {
    auto *configIniWrite = new QSettings("config/QCodeExport.ini", QSettings::IniFormat);
    return configIniWrite->value("/default/ExcludeDirs").toString();
}

void QCodeExport::getDirFiles(const QString &path, QStringList *list, const QString &inputfilter,
                              const QString &excludeDirs) {
    QRegularExpression regExp(QRegularExpression::anchoredPattern(QLatin1String(excludeDirs.toLocal8Bit())));
    auto match = regExp.match(path);
    if (match.hasMatch()) {
        return;
    }
//    qDebug() << "path:" << path;
    QDirIterator it(path);

    while (it.hasNext()) {
        auto file = it.next();
        if (file == path + slash + "." || file == path + slash + "..") {
            continue;
        }
        if (it.fileInfo().isDir()) {
            getDirFiles(file, list, inputfilter, excludeDirs);
        } else {
            addFileToWorkList(file, list, inputfilter);
        }
    }
}

void QCodeExport::addFileToWorkList(const QString &path, QStringList *list, const QString &inputfilter) {
    QRegularExpression regExp(QRegularExpression::anchoredPattern(QLatin1String(inputfilter.toLocal8Bit())));
    auto match = regExp.match(path);
    if (match.hasMatch()) {
        list->append(path);
    }

}

