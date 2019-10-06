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
    else if (GLOB_PROTOCAL_IP ==  protocal )
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
    if (cnt >= start)
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

    elems->insert(2, Element(QString("TPID"),      12, 1, 0,  0));
    /* TCI : PRIORITY, CFI, VLANID */
    elems->insert(3, Element(QString("PRIORITY"),  13, 1, 13, 3));
    elems->insert(3, Element(QString("CFI"),       13, 1, 12, 1));
    elems->insert(3, Element(QString("VLANID"),    13, 1, 0,  12));
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
            QString mac;
            /* 每个Byte两个字母 */
            for(qint8 j = 0; j < GLB_MAC_BYTE_LEN * 2; j += 2)
            {
                mac += origData.mid(j, 2) + "-";
            }
            /* 去掉末尾多余的'-'*/
            mac.remove( QRegExp("-$"));
            d_data->replace(i, qMakePair(name, mac));
        }
        else
        {
            d_data->replace(i, qMakePair(name, origData.insert(0,"0x")));
        }
    }

    return data.toUpper();
}

void EthOffset::extractData()
{
    QString *buf = getBuf();
    QString typeStr = buf->mid(GLOB_FRAME_TYPE_POS, GLOB_FRAME_TYPE_LEN);

    bool ok;
    qint32 type = typeStr.toInt(&ok, 16);


    if (type > GLOB_FRAME_MAX_LEN)
    {
        if (type == 0x8100)
        {
            isTagged = true;
            protocal = 0;
        }
        else
        {
            isTagged = false;
            protocal = type;
        }
    }

    Offset::extractData();
    return;
}


