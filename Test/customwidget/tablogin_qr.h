#ifndef TABLOGIN_QR_H
#define TABLOGIN_QR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class TabLogin_qr;
}
QT_END_NAMESPACE

// 二维码登录测试
class TabLogin_qr : public QWidget
{
    Q_OBJECT

public:
    explicit TabLogin_qr(QWidget *parent = nullptr);
    ~TabLogin_qr();

private:

    /**
     * @brief 反射调用API中的方法
     * @param member 函数名称
     * @param arg 参数
     * @return QVariantMap 返回的数据
     */
    QVariantMap invoke(const QString member, const QVariantMap arg);

    QImage generateQRCode(QString url, qint32 width = -1, qint32 height = -1, qint32 offset = 0);

public slots:
    void showQrCode(QString url);

private slots:
    void on_pushButton_login_qr_create_clicked();

    void on_pushButton_login_qr_check_clicked();

    void on_pushButton_login_qr_key_clicked();

private:
    Ui::TabLogin_qr *ui;
};

#endif // TABLOGIN_QR_H
