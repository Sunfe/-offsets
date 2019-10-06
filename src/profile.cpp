#include <QtGlobal>
#include <QObject>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

#include "profile.h"
#include "element.h"
#include "global.h"

/* inner default profiles
 * format: param: offset.bytes */
static const char *gPrfEther =
        "src: 0/4;"
        "des: 4/4;"
        "len: 8/12";

static const char *gPrfFppMetaframe =
        "FPP Identifier:0/4;"
        "FPP Length Field:20/4";

Profile::Profile(QString *buf)
{
    d_offsets[Profile::ETH]      = new EthOffset();
    d_offsets[Profile::FPP_META] = new FppOffset();
    d_buf = buf;
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
        str.append(QString("%1 : %2").arg(*itr, -20).arg(obj.value(*itr).toString(), 10) + QString("\n"));
        itr++;
    }

    return str;
}

QString Profile::getDataStr()
{
    return jsonToStr(data[d_type]);
}

void Profile::loadData(qint8 type)
{
    QJsonObject obj;

    if (Profile::ETH == type)
        obj = strToJson(gPrfEther);
    else if (Profile::FPP_META == type)
        obj = strToJson(gPrfFppMetaframe);

    updateData(obj, type);
    return;
}

void Profile::updateData(QJsonObject dt, qint8 type)
{
    if (type > GLB_MAX_PRF_NUM)
    {
        return;
    }

    data[type] = dt;
    setType(type);

    return;
}

QJsonObject Profile::getData(qint8 type)
{
    if (type > GLB_MAX_PRF_NUM)
    {
        return  data[GLB_MAX_PRF_NUM - 1];;
    }

    return data[0];
}

qint8 Profile::getType()
{
    return d_type;
}

void Profile::setType(qint8 type)
{
    if (type > GLB_MAX_PRF_NUM)
    {
        type = FPP_META;
    }

    d_type = type;
    return;
}

void Profile::setBuf(QString *buf)
{
    this->d_buf = buf;
}

Offset* Profile::getOffset(qint16 type)
{
    if (type >= GLB_MAX_PRF_NUM)
        return nullptr;
    return d_offsets[type];
}

QVector<QPair<QString, QString>>* Profile::parze(qint8 type)
{
    if (nullptr == d_buf)
    {
        return nullptr;
    }

    if (Profile::ETH == type)
    {
        EthOffset *eth = new EthOffset();
        eth->setBuf(d_buf);
        eth->extractData();
        eth->format();
        return eth->getData();
    }
    else if (Profile::FPP_META == type)
    {
        return nullptr;
    }

    return nullptr;
}



