#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QCodeExport/qcodeexport.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->codeExportButton, &QPushButton::clicked, this, &MainWindow::codeExportButtonClickHandler);
    connect(ui->comboBox_qss, &QComboBox::currentTextChanged, this, &MainWindow::qssChangedHandler);
    // 读取皮肤
    QDirIterator it(":/res/qss/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        ui->comboBox_qss->addItem(it.next().replace(":/res/qss/", ""));
    }
}

MainWindow::~MainWindow() {
    delete ui;


}

void MainWindow::codeExportButtonClickHandler() {
    auto *qCodeExport = new QCodeExport;
    qCodeExport->show();
    qCodeExport->activateWindow();

}

void MainWindow::qssChangedHandler(const QString &qss) {
    qDebug() << "改变主题:" << qss;
    QFile file(":/res/qss/" + qss);
    if (file.open(QIODevice::ReadWrite)) {
        QString styleSheet = QLatin1String(file.readAll());
        qDevToolApp->setStyleSheet(styleSheet);
    }

}

