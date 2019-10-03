#include <QPair>
#include <QVector>
#include "ethoffset.h"

EthOffset::EthOffset()
{
    /* Ethernet II :
     * 6 byte       6 byte        2 byte      4~1500 byte  4byte
     * src mac      des mac       type/len      data        fcs
     */
    QVector<Element> eth;
    eth.append(Element(QString("src mac"),  0,  6, 0, 0));
    eth.append(Element(QString("des mac"),  6,  6, 0, 0));
    eth.append(Element(QString("type/len"), 10, 2, 0, 0));
    setElements(eth);
}

EthOffset::~EthOffset()
{

}

QString EthOffset::format()
{
    QVector<QPair<QString, QString>> d_data = getData();

    if (d_data.isEmpty())
        return QString("no data");

    QString data;
    for (qint16 i = 0; i < d_data.count(); i++)
    {
        QString name     = d_data.value(i).first;
        QString origData = d_data.value(i).second;

        QString mac;
        if((name == "src mac") || (name == "des mac"))
        {
            for(qint8 j = 0; j < 6; j += 2)
            {
                mac += origData.mid(j, 2) + "-";
            }
            /* 去掉末尾多余的'-'*/
            mac.remove( QRegExp("-$"));
        }

        data += QString("%1   :   %2\n").arg(d_data.value(i).first).arg(d_data.value(i).second);
    }


    return data.toUpper();
}
