#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QDirIterator>
#include <QCheckBox>
#include <QApplication>
#include <QPainter>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QSettings *configIni;


public Q_SLOTS:

    static void codeExportButtonClickHandler();

    void qssChangedHandler(int index);

};

#endif // MAINWINDOW_H
