#include <QPair>
#include <QVector>
#include "global.h"
#include "ethoffset.h"

#define OFFSET_POS_IP_FIELD  (3)


EthOffset::EthOffset(qint8 type)
{
    if (EthOffset::ETH_FRAME_ETH2 == type)
    {
        loadOffsetEth2();
    }
    else if(EthOffset::ETH_FRAME_8023 == type)
    {
        loadOffsetEth8023();
    }
}

EthOffset::~EthOffset()
{

}

void EthOffset::loadOffsetEth8023()
{
    /* Ethernet 802.1Q :
     * 6 byte       6 byte     2 byte      4~1500 byte  4byte
     * src mac      des mac    type        data         fcs
     *
     * tag:
     * 3bit        1bit    12bit
     * priority    cfi     vlanid
     */
    QVector<Element>* elems = getElements();
    elems->clear();

    QVector<Element> eth;
    eth.append(Element(QString("SRC MAC"),  0,  6, 0, 0));
    eth.append(Element(QString("DES MAC"),  6,  6, 0, 0));
    if (0 ==  protocal )
    {
        eth.append(Element(QString("LEN"),  12, 2, 0, 0));
        setElements(eth);
    }
    else if (GLOB_PROTOCAL_IP ==  protocal)
    {
        eth.append(Element(QString("TYPE"), 12, 2, 0, 0));
        setElements(eth);
        appendOffsetIpField();
    }
    else
    {
        /* 其他协议暂不支持 */
    }


    if (isTagged)
    {
        insertOffset8023qTag();
    }
    return;
}

void EthOffset::loadOffsetEth2()
{
    /* Ethernet II :
     * 6 byte       6 byte       2 byte      4~1500 byte  4byte
     * src mac      des mac       len          data        fcs
     */
    /*
     * tag:
     * 3bit        1bit    12bit
     * priority    cfi     vlanid
     */
    QVector<Element>* elems = getElements();
    elems->clear();

    QVector<Element> eth;
    eth.append(Element(QString("SRC MAC"),  0,  6, 0, 0));
    eth.append(Element(QString("DES MAC"),  6,  6, 0, 0));

    if (GLOB_PROTOCAL_IP ==  protocal )
    {
        eth.append(Element(QString("TYPE"), 12, 2, 0, 0));
        appendOffsetIpField();
    }
    else
    {
        /* 其他协议暂不支持 */
    }

    setElements(eth);

    if (isTagged)
    {
        insertOffset8023qTag();
    }
    return;
}


void EthOffset::appendOffsetIpField()
{
    /* IP :
     * 6 byte       6 byte        2 byte      4~1500 byte  4byte
     * src mac      des mac       0x0800      ip field     fcs
     *
     * ip field:
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
     *
     * start from 14 bytes: */
    QVector<Element> *elems = getElements();
    if (!elems)
    {
        return;
    }

    elems->append(Element(QString("Version"),              0,   1, 0, 3));
    elems->append(Element(QString("IHL"),                  0,   1, 4, 4));
    elems->append(Element(QString("Type of Service"),      1,   1, 0, 0));
    elems->append(Element(QString("Total Length"),         2,   2, 0, 0));
    elems->append(Element(QString("Identifier"),           4,   2, 0, 0));

    elems->append(Element(QString("Flags"),                6,   2, 13, 3));
    elems->append(Element(QString("Fragment Offset"),      6,   2, 0,  13));

    elems->append(Element(QString("TTL"),                  8,   1, 0, 0));
    elems->append(Element(QString("Protocol"),             9,   1, 0, 0));
    elems->append(Element(QString("Header Checksum"),      10,  2, 0, 0));
    elems->append(Element(QString("Source Address"),       12,  4, 0, 0));
    elems->append(Element(QString("Destination Address"),  16,  4, 0, 0));

    elems->append(Element(QString("Options"),              20,  4, 8, 31));
    elems->append(Element(QString("Padding"),              20,  4, 0, 7));

    qint32 start  = OFFSET_POS_IP_FIELD;
    qint32 end    = getElementCount();
    qint32 delta  = GLOB_FRAME_IP_POS;
    adjustRangeByteOffset(start, end, delta);

    return;
}

void EthOffset::adjustRangeByteOffset(qint32 start, qint32 end, qint32 deltaOffset)
{
    qint32 cnt = getElementCount();
    if (start >= cnt)
    {
        return;
    }

    QVector<Element>* elems = getElements();
    for (qint32 i = start; (i < end) && (i < cnt); i++)
    {
        Element elem =elems->at(i);
        elem.setByteOffset(elem.getByteOffset() + deltaOffset);
        elems->replace(i, elem);
    }
    return;
}

void EthOffset::insertOffset8023qTag()
{
    QVector<Element>* elems = getElements();
    if (!elems)
    {
        return;
    }

    /* 在原有基础上挪动2个自己给802.1q字段，即byteOffset参数增加2字节, 并插入TPID,TCI字段 */
    for (qint32 i = 0; i < elems->count(); i++)
    {
        Element elem =elems->at(i);
        elem.setByteOffset(elem.getByteOffset() + 2);
        elems->replace(i, elem);
    }

    qint32 start = 2; /*从 TYPE/LEN 字段开始*/
    qint32 end = getElementCount();
    qint32 delta = 2;
    adjustRangeByteOffset(start, end, delta);

    elems->insert(2, Element(QString("TPID"),      12, 2, 0,  0));
    /* TCI : PRIORITY, CFI, VLANID */
    elems->insert(3, Element(QString("VLANID"),    14, 2, 0,  12));
    elems->insert(4, Element(QString("CFI"),       14, 2, 12, 1));
    elems->insert(5, Element(QString("PRIORITY"),  14, 2, 13, 3));
    return;
}

QString EthOffset::format()
{
    QVector<QPair<QString, QString>> *d_data = getData();

    if (d_data->isEmpty())
        return QString("no-data");

    QString data;
    for (qint16 i = 0; i < d_data->count(); i++)
    {
        QString name     = d_data->value(i).first;
        QString origData = d_data->value(i).second;

        if((name.toLower() == "src mac") || (name.toLower() == "des mac"))
        {
            QString mac = formatMacAddress(origData);
            d_data->replace(i, qMakePair(name, mac));
        }
        else if ((name.toLower() == "source address") || (name.toLower() == "destination address"))
        {
            QString ip = formatIpAddress(origData);
            d_data->replace(i, qMakePair(name, ip));
        }
    }

    return data.toUpper();
}


QString EthOffset::formatMacAddress(QString src)
{
    QString mac;
    /* 每个Byte两个字母 */
    for(qint8 i = 0; i < GLB_MAC_BYTE_LEN * 2; i += 2)
    {
        mac += src.mid(i, 2) + "-";
    }
    /* 去掉末尾多余的'-'*/
    mac.remove( QRegExp("-$"));
    return mac;
}

QString EthOffset::formatIpAddress(QString src)
{
    QString ip;
    /* 每个Byte两个16进制字母 */
    for(qint8 i = 0; i < GLB_IP_ADDR_BYTE_LEN * 2; i += 2)
    {
        QString dtStr  = src.mid(i, 2);
        if (dtStr.isEmpty())
            continue;

        bool ok = false;
        qint32 decimal = dtStr.toInt(&ok, 16);
        ip += QString::number(decimal, 10) + ".";
    }
    /* 去掉末尾多余的'.'*/
    ip.remove( QRegExp(".$"));
    return ip;
}

void EthOffset::extractData()
{
    Element *elem = new Element(QString("TAG"),  12, 2, 0, 0);
    if (!elem)
    {
       return;
    }

    if (getElemDataStr(elem) == "8100")
    {
        isTagged = true;

        Element *elem = new Element(QString("TYPE/LEN"), 16, 2, 0, 0);
        QString tlStr = getElemDataStr(elem);

        bool ok;
        qint32 val = tlStr.toInt(&ok, 16);
        protocal = (val > GLOB_FRAME_MAX_LEN)? val : 0;
    }
    else
    {
        isTagged = false;
        Element *elem = new Element(QString("TYPE/LEN"), 12, 2, 0, 0);
        QString tlStr = getElemDataStr(elem);

        bool ok;
        qint32 val = tlStr.toInt(&ok, 16);
        protocal = (val > GLOB_FRAME_MAX_LEN)? val : 0;
    }

    loadOffsetEth8023();
    Offset::extractData();
    return;
}


