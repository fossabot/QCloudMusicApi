#include "index.h"

// #include <QRandomGenerator>
#include <QtMath>

using namespace QCloudMusicApi;

bool Index::toBoolean(const QVariant &val) {
    if (val.userType() == QMetaType::Bool) return val.toBool();
    if (val == "") return val.toBool();
    return val == "true" || val == "1";
}

QVariantMap Index::cookieToJson(const QString &cookie) {
    if (cookie.isEmpty()) return QVariantMap();
    auto cookieArr = cookie.split(";");
    QVariantMap obj;
    for (const QString &i : cookieArr) {
        QStringList arr = i.trimmed().split("=");
        // 如果子串的个数不等于2，跳过这个元素
        if (arr.size() != 2) continue;
        obj.insert(arr[0], arr[1]);
    }
    return obj;
}

QString Index::cookieObjToString(const QVariantMap &cookie) {
    QString string;
    for(auto i = cookie.begin(); i != cookie.end(); ++i) {
        string.append(i.key() + "=" + i.value().toString() + "; ");
    }
    return string;
}

int Index::getRandom(int num) {
    int random;/* = QRandomGenerator::global()->bounded(1, 9) + 1;
    random += QRandomGenerator::global()->generate();
    random *= qPow(10, num - 1);*/
    return random;
}

QString Index::generateRandomChineseIP() {
    QStringList chinaIPPrefixes { "116.25", "116.76", "116.77", "116.78" };
    QString randomPrefix/* = chinaIPPrefixes.at(QRandomGenerator::global()->bounded(chinaIPPrefixes.size()))*/;
    return QString("%1.%2.%3").arg(randomPrefix).arg(generateIPSegment()).arg(generateIPSegment());
}

// 生成一个随机整数
int Index::getRandomInt(int min, int max) {
    return 0/*QRandomGenerator::global()->bounded(min, max + 1)*/;
}

// 生成一个随机IP地址段
int Index::generateIPSegment() {
    return getRandomInt(1, 255);
}

QVariantMap Index::mergeMap(const QVariantMap &map0, const QVariantMap &map1)
{
    QVariantMap result = map0; //复制第一个map
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    for (auto i = map1.constBegin(); i != map1.constEnd(); ++i) {
        result.insert(i.key(), i.value()); //插入或覆盖第二个map的键值对
    }
#else
    result.insert(map1);
#endif
    return result;
}
