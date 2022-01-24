//
// Created by liuhaoran on 2022/1/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QImageTool.h" resolved

#include "qimagetool.h"
#include "ui_QImageTool.h"


QImageTool::QImageTool(QWidget *parent) :
        QWidget(parent), ui(new Ui::QImageTool) {
    ui->setupUi(this);
    connect(ui->open_img_btn, &QPushButton::clicked,
            this, &QImageTool::onOpenImageBtnClicked);
    connect(ui->grayscaleBtn, &QPushButton::clicked,
            this, &QImageTool::onGrayscaleBtnClicked);
}

QImageTool::~QImageTool() {
    delete ui;
}

void QImageTool::LabelDisplayMat(QLabel *label, cv::Mat &mat) {
    cv::Mat Rgb;
    QImage Img;
    if (mat.channels() == 3)//RGB Img
    {
        cv::cvtColor(mat, Rgb, cv::COLOR_BGR2RGB);//颜色空间转换
        Img = QImage((const uchar *) (Rgb.data), Rgb.cols, Rgb.rows, Rgb.cols * Rgb.channels(), QImage::Format_RGB888);
    } else//Gray Img
    {
        Img = QImage((const uchar *) (mat.data), mat.cols, mat.rows, mat.cols * mat.channels(),
                     QImage::Format_Indexed8);
    }
    label->setPixmap(QPixmap::fromImage(Img));
    label->setScaledContents(true);
}

void QImageTool::onOpenImageBtnClicked() {
    auto *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle("选择图片");
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::FileMode::ExistingFile);
    QStringList fileNames;
    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
        if (fileNames.length() > 0) {
            cv::Mat image = cv::imread(fileNames[0].toStdString());
            srcImg = image;
            LabelDisplayMat(ui->img_src, image);
        }
    }
}

void QImageTool::onGrayscaleBtnClicked() {
    cv::cvtColor(srcImg, dstImg, cv::COLOR_RGB2GRAY);
    LabelDisplayMat(ui->img_des, dstImg);
}



