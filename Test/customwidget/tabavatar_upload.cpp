#include "tabavatar_upload.h"
#include "ui_tabavatar_upload.h"
#include "../servicelocator.h"

#include <QFileDialog>
#include <QFileInfo>

TabAvatar_upload::TabAvatar_upload(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::TabAvatar_upload)
{
    ui->setupUi(this);
}

TabAvatar_upload::~TabAvatar_upload()
{
    delete ui;
}

void TabAvatar_upload::on_pushButton_select_file_clicked()
{
    QFileInfo fileInfo = QFileInfo(QFileDialog::getOpenFileName(this));
    auto filePath = fileInfo.filePath();
    ui->label_path->setProperty("filePath", filePath);
    ui->label_path->setText(fileInfo.fileName());
    QImage image(filePath);
    ui->label->setPixmap(QPixmap::fromImage(image));
}


void TabAvatar_upload::on_pushButton_send_clicked()
{
    auto filePath = ui->label_path->property("filePath").toString();

    QImage image(filePath);
    int imgSize = 300;
    if (!image.isNull()) {
        // 默认以图片宽度为上传尺寸
        imgSize = image.width();
    }

    QFile file(filePath);
    file.open(QFile::ReadOnly);
    auto data = file.readAll();

    auto arg = QVariantMap{
        { "imgSize", imgSize },
        { "imgFile", QVariantMap {
                           { "name", ui->label_path->text() },
                           { "data", data }
                       }
        }
    };
    QVariantMap ret = ServiceLocator::helper().invoke("avatar_upload", arg);
    ui->textEdit_ret->setText(QJsonDocument::fromVariant(ret).toJson(QJsonDocument::Indented));
}

