#include <QPainter>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QCodeExport/qcodeexport.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->codeExportButton, &QPushButton::clicked, this, &MainWindow::codeExportButtonClickHandler);
    connect(ui->comboBox_qss, &QComboBox::currentTextChanged, this, &MainWindow::qssChangedHandler);
    // 读取皮肤
    QString path(":/res/qss/");
    QDirIterator it(path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
//        qDebug() << "qssfile:" << it.next();
        ui->comboBox_qss->addItem(it.next().replace(path, ""));
    }
}

MainWindow::~MainWindow() {
    delete ui;


}

void MainWindow::codeExportButtonClickHandler() {
    auto *qCodeExport = new QCodeExport;
    qCodeExport->show();
//    qCodeExport->activateWindow();

}

void MainWindow::qssChangedHandler(const QString &qss) {
    qDebug() << "改变主题:" << qss;
    QFile file(":/res/qss/" + qss);
    if (file.open(QIODevice::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qDebug() << "qss:" << styleSheet;
        qApp->setStyleSheet(styleSheet);
        file.close();
    }

}

