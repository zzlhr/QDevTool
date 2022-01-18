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
};


#endif //QDEVTOOL_QCODEEXPORT_H
