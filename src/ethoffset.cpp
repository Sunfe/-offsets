#include <QPair>
#include <QVector>
#include "global.h"
#include "ethoffset.h"

EthOffset::EthOffset()
{
    /* Ethernet II :
     * 6 byte       6 byte        2 byte      4~1500 byte  4byte
     * src mac      des mac       type/len      data        fcs
     */
    QVector<Element> eth;
    eth.append(Element(QString("SRC MAC"),  0,  6, 0, 0));
    eth.append(Element(QString("DES MAC"),  6,  6, 0, 0));
    eth.append(Element(QString("TYPE/LEN"), 10, 2, 0, 0));
    setElements(eth);
}

EthOffset::~EthOffset()
{

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
