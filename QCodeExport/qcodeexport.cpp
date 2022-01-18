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
}

QCodeExport::~QCodeExport() {
    delete ui;
}

void QCodeExport::onSelectProjectDirHandler() {
    QString defaultDir;
#ifdef Q_OS_WIN
    defaultDir = "C:/";
#endif
#ifdef Q_OS_UNIX
    defaultDir = "~";
#endif

    auto dialog = QFileDialog(
            this,
            tr("选择项目文件夹"),
            defaultDir);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    if (dialog.exec() == QFileDialog::Accepted) {
        auto urls = dialog.selectedUrls()[0];
        qDebug() << "select urls:" << urls;
        ui->label_codedir->setText(urls.path());
    }
}

void QCodeExport::onSelectExportDirHandler() {
    QString defaultDir;

#ifdef Q_OS_WIN
    defaultDir = "C:/";
#endif
#ifdef Q_OS_UNIX
    defaultDir = "~";
#endif

    auto dialog = QFileDialog(
            this,
            tr("选择导出文件夹"),
            defaultDir);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    if (dialog.exec() == QFileDialog::Accepted) {
        auto urls = dialog.selectedUrls()[0];
        qDebug() << "select urls:" << urls;
        ui->label_exportPath->setText(urls.path());
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

}

