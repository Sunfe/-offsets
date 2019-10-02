#include <QtGlobal>
#include <QObject>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>

#include "profile.h"
#include "element.h"

/* inner default profiles
 * format: param: offset.bytes */
static const char *gPrfEther =
        "src: 0/4;"
        "des: 4/4;"
        "len: 8/12";

static const char *gPrfIp =
        "Transaction Identifier:0/4;"
        "Protocol Identifier:4/8;"
        "Length Field:20/4";

static const char *gPrfFppMetaframe =
        "FPP Identifier:0/4;"
        "FPP Length Field:20/4";

Profile::Profile(QString *buf)
{
#if 0
    QVector<Element> fppFrame;
    fppFrame.append(Element(QString("src"),  0, 4, 0, 0));
    fppFrame.append(Element(QString("des"),  0, 4, 0, 0));
    fppFrame.append(Element(QString("type"), 0, 4, 0, 0));
#endif

    /* Ethernet II :
     * 6 byte       6 byte        2 byte      4~1500 byte  4byte
     * src mac      des mac       type/len      data        fcs
     */
    QVector<Element> eth;
    eth.append(Element(QString("src"),  0,  6, 0, 0));
    eth.append(Element(QString("des"),  6,  6, 0, 0));
    eth.append(Element(QString("type"), 10, 2, 0, 0));

  #if 0

    /* IP :
     * 6 byte       6 byte        2 byte      4~1500 byte  4byte
     * src mac      des mac       0x0800      data          fcs
     *
     * data field:
     *    0                   1                   2                   3
     *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |Version|  IHL  |Type of Service|          Total Length         |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |         Identification        |Flags|      Fragment Offset    |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |  Time to Live |    Protocol   |         Header Checksum       |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |                       Source Address                          |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |                    Destination Address                        |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     * |                    Options                    |    Padding    |
     * +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     */
    QVector<Element> ipFrame;
    ipFrame.append(Element(QString("src"), 0, 4, 0, 0));
    ipFrame.append(Element(QString("des"), 0, 4, 0, 0));
    ipFrame.append(Element(QString("type"), 0, 4, 0, 0));


    QVector<Element> udpFrame;
    udpFrame.append(Element(QString("src"), 0, 4, 0, 0));
    udpFrame.append(Element(QString("des"), 0, 4, 0, 0));
    udpFrame.append(Element(QString("type"), 0, 4, 0, 0));

#endif
    Offset offset(eth);
    d_offsets[Profile::ETH] = offset;
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
    else if (Profile::IP == type)
        obj = strToJson(gPrfIp);
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

