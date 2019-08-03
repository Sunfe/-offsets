#include <QtGlobal>
#include <QObject>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

#include "profile.h"

/* inner default profiles
 * format: param: offset.bytes */
static const char *gPrfEther =
        "src: 0.4;"
        "des: 4.4;"
        "len: 8.12";

static const char *gPrfIp =
        "Transaction Identifier:0.4;"
        "Protocol Identifier:4.8;"
        "Length Field:20.4";

static const char *gPrfFppMetaframe =
        "FPP Identifier:0.4;"
        "FPP Length Field:20.4";

Profile::Profile(qint8 type)
{
    qDebug() << type;
   loadData(type);
}


Profile::~Profile()
{

}


QJsonObject Profile::strToJson(QString str)
{
    QJsonObject obj;
    QStringList list = str.split(';');

    QList<QPair<QString, QString>> ol;
    for(qint16 i= 0; i < list.count(); i++)
    {
        QString s = list.at(i);
        QStringList l = s.split(':');
        if (l.count() != 2) /* key an value, must be 2 items */
        {
            return obj; /* empyt object*/
        }

        QString key   = l.at(0);
        QString value = l.at(1);
        obj.insert(key, value);
    }

    return obj;
}

QString Profile::jsonToStr(QJsonObject obj)
{
    QString str;
    QStringList keys = obj.keys();
    QStringList::iterator itr = keys.begin();
    while(itr != keys.end())
    {
        str.append(QString("%1:%2").arg(*itr, -30).arg(obj.value(*itr).toString()) + QString("\n"));
        itr++;
    }

    return str;
}


QString Profile::getDataStr()
{
    return jsonToStr(data);
}


void Profile::loadData(qint8 type)
{
    QJsonObject obj;

    if (Profile::ETH == type)
        obj = strToJson(gPrfEther);
    else if (Profile::IP == type)
        obj = strToJson(gPrfIp);
    else if (Profile::FPP_META == type)
        obj = strToJson(gPrfFppMetaframe);

    qDebug()<<type;
    updateData(obj);
    return;
}

void Profile::updateData(QJsonObject dt)
{
    data = dt;
    return;
}


QJsonObject Profile::getData()
{
    return data;
}


