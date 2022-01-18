#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QDirIterator>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static QApplication *qDevToolApp = nullptr;

static void setQDevToolApp(QApplication *app) {
    qDevToolApp = qDevToolApp;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private:
    Ui::MainWindow *ui;

public Q_SLOTS:
    void codeExportButtonClickHandler();

    void qssChangedHandler(const QString &qss);
};

#endif // MAINWINDOW_H
