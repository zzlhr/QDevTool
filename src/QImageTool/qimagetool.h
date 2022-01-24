//
// Created by liuhaoran on 2022/1/24.
//

#ifndef QDEVTOOL_QIMAGETOOL_H
#define QDEVTOOL_QIMAGETOOL_H

#include <QWidget>
#include <QFileDialog>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class QImageTool; }
QT_END_NAMESPACE

class QImageTool : public QWidget {
Q_OBJECT

public:
    explicit QImageTool(QWidget *parent = nullptr);

    ~QImageTool() override;

public Q_SLOT:

    void onOpenImageBtnClicked();

    void onGrayscaleBtnClicked();

private:
    Ui::QImageTool *ui;
    cv::Mat srcImg;
    cv::Mat dstImg;
    void LabelDisplayMat(QLabel *label, cv::Mat &mat);
};


#endif //QDEVTOOL_QIMAGETOOL_H
