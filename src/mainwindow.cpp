#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QCodeExport/qcodeexport.h"
#include "QImageTool/qimagetool.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->codeExportButton, &QPushButton::clicked, this, &MainWindow::codeExportButtonClickHandler);
    connect(ui->comboBox_qss, &QComboBox::activated, this, &MainWindow::qssChangedHandler);
    connect(ui->ImageToolButton, &QPushButton::clicked, this, &MainWindow::imageToolButtonClickHandler);
    // 读取皮肤
    QString path(":/res/qss/");
    QDirIterator it(path, QDirIterator::Subdirectories);
    configIni = new QSettings("config/config.ini", QSettings::IniFormat);
    auto theme = configIni->value("/ui/theme").toString();
    while (it.hasNext()) {
//        qDebug() << "qssfile:" << it.next();
        ui->comboBox_qss->addItem(it.next().replace(path, ""));
    }
    // 读取配置文件的主题
    if (theme != "") {
        ui->comboBox_qss->setCurrentText(theme);
        qssChangedHandler(0);
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

void MainWindow::qssChangedHandler(int index) {
    QString qss = ui->comboBox_qss->currentText();
    qDebug() << "改变主题:" << qss;
    QFile file(":/res/qss/" + qss);
    if (file.open(QIODevice::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qDebug() << "qss:" << styleSheet;
        qApp->setStyleSheet(styleSheet);
        configIni->setValue("/ui/theme", qss);
        file.close();
    }

}

void MainWindow::imageToolButtonClickHandler() {
    auto *qImageTool = new QImageTool;
    qImageTool->show();
}

