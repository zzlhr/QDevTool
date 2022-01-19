//
// Created by liuhaoran on 2022/1/18.
//

#ifndef QDEVTOOL_QCODEEXPORT_H
#define QDEVTOOL_QCODEEXPORT_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDirIterator>
#include <QDebug>
#include <QStandardPaths>
#include <QSettings>
#include <QRegExp>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class QCodeExport; }
QT_END_NAMESPACE

class QCodeExport : public QWidget {
Q_OBJECT

public:
    explicit QCodeExport(QWidget *parent = nullptr);

    ~QCodeExport() override;

private:
    Ui::QCodeExport *ui;

    void onSelectProjectDirHandler();

    void onSelectExportDirHandler();

    void onExportClickHandler();

    QString getInputFilter();

    QString getExcludeDirs();

    void getDirFiles(const QString &path, QStringList *list, const QString &inputfilter, const QString &excludeDirs);

    void addFileToWorkList(const QString &path, QStringList *list, const QString &inputfilter);

};


#endif //QDEVTOOL_QCODEEXPORT_H
