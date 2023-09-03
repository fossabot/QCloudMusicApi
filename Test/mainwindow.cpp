﻿#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../QCloudMusicApi/module.h"
#include <QMetaMethod>
#include <QTextEdit>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = QObject().metaObject()->methodCount(); i < api.metaObject()->methodCount(); i++) {
        ui->comboBox->addItem(api.metaObject()->method(i).name());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->textEdit_2->setText(QJsonDocument::fromJson(ui->textEdit_2->toPlainText().toUtf8()).toJson(QJsonDocument::Indented));
    QByteArray ret;
    QMetaObject::invokeMethod(&api, ui->comboBox->currentText().toUtf8()
                              , Qt::DirectConnection
                              , Q_RETURN_ARG(QByteArray, ret)
                              , Q_ARG(QVariantMap, QJsonDocument::fromJson(ui->textEdit_2->toPlainText().toUtf8()).toVariant().toMap()));
    ui->textEdit->setText(ret);
}

