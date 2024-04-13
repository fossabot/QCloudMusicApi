#include "apihelper.h"
#include "util/index.h"

#include <QMetaMethod>

using namespace QCloudMusicApiNS;
ApiHelper::ApiHelper(QObject *parent)
    : NeteaseCloudMusicApi{parent}
{}

void ApiHelper::beforeInvoke(QVariantMap& arg)
{
    //Api只能处理map类型的cookie
    if(arg.contains("cookie")) {
        //如果传入新的cookie，替换原有的cookie
        if(arg["cookie"].userType() == QMetaType::QVariantMap) {
            set_cookie(arg["cookie"].toMap());
        }
        else if(arg["cookie"].userType() == QMetaType::QString) {
            set_cookie(arg["cookie"].toString());
        }
    }
    else {
        //使用存储的cookie
        arg["cookie"] = cookie();
    }
}

void ApiHelper::afterInvoke(QVariantMap& ret)
{
    auto newCookie = Index::stringToMap(ret["cookie"].toString());
    if (!newCookie.isEmpty()) {
        set_cookie(Index::mergeMap(cookie(), newCookie));
    }
    auto token = ret["body"].toMap()["token"].toString();
    if (!token.isEmpty()) {
        m_cookie["MUSIC_A"] = token;
    }
}

QVariantMap ApiHelper::invoke(QString member, QVariantMap arg, callbackType callback)
{
    beforeInvoke(arg);

    QVariantMap ret;
    QMetaObject::invokeMethod(this, member.toUtf8()
                              , Qt::DirectConnection
                              , Q_RETURN_ARG(QVariantMap, ret)
                              , Q_ARG(QVariantMap, arg)
                              , Q_ARG(callbackType, callback));

    afterInvoke(ret);

    return ret;
}

QVariantMap ApiHelper::invoke(QVariantMap (NeteaseCloudMusicApi::*member)(QVariantMap, callbackType), QVariantMap arg, callbackType callback)
{
    beforeInvoke(arg);

    // auto bind = std::bind(member, &api, arg);
    // QVariantMap ret = bind();
    QVariantMap ret = (this->*member)(arg, callback);

    afterInvoke(ret);

    return ret;
}

QStringList ApiHelper::memberList()
{
    QStringList memberList;
    NeteaseCloudMusicApi api;
    for(int i = QObject().metaObject()->methodCount(); i < api.metaObject()->methodCount(); i++) {
        memberList.push_back(api.metaObject()->method(i).name());
    }
    return memberList;
}

void ApiHelper::set_cookie(QString cookie)
{
    set_cookie(Index::stringToMap(cookie));
}
