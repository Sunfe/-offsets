#include <QPair>
#include "offset.h"


Offset::Offset()
{

}

Offset::Offset(QVector<Element> elems)
{
    this->elems = elems;
}

Offset::~Offset()
{

}

QString Offset::extractElemData(QString *buf, Element elem)
{
    if (buf->isEmpty())
        return QString("%1").arg(0); /* 异常返回0值*/

    qint32 byOffset = elem.getByteOffset();
    qint32 byLen    = elem.getByteLen();
    qint32 biOffset = elem.getBitOffset();
    qint32 biLen    = elem.getBitLen();

    if (0 == byLen)
    {
        return QString("%1").arg(0); /* 异常返回0值*/
    }

    QString dtStr = buf->remove(QRegExp("\\s")).mid(byOffset * 2, byLen * 2); /* 2个字符一个byte */
    /* 常见情况1：没有比特偏移的情况,直接取出 */
    if ((0 == biOffset) && (0 == biLen))
    {
        return formatData(dtStr);
    }
    else if (0 != biLen)
    {
        int val = 0;
        bool ok = false;

        if (byLen <= 4)
        {
            val = dtStr.toInt(&ok, 16);
        }
        else if (byLen <= 8)
        {
            val = dtStr.toInt(&ok, 16);
        }

        if (ok)
        {
            qint32 upperShiftNum = byLen * 8 - (biOffset + biLen);
            val <<= upperShiftNum;
            val >>= byLen * 8 - biLen;
            return QString("%1").arg(val, 0, 16);
        }
    }

    /* 其他情况均认为异常 */
    return QString("%1").arg(0);
}

void Offset::extractData(QString *buf)
{
    QString de;
    QVector<QPair<QString, QString>> dv;
    QPair<QString, QString> pair;

    for(qint16 i = 0; i < elems.count(); i++)
    {
        de = extractElemData(buf, elems.at(i));
        dv.append(qMakePair(elems.value(i).getName(), de));
    }

    d_data = dv;
    return;
}

void Offset::setElements( QVector<Element> elems)
{
    this->elems = elems;
    return;
}

void Offset::setElement( qint32 pos, Element elem)
{
    if (0 == pos)
        return;

    elems[pos] = elem;
    return;
}

Element Offset::getElement(qint32 pos)
{
    if (pos > elems.count())
    {
        return  Element(QString(""));
    }
    return elems[pos];
}

void Offset::appendElement(Element elem)
{
    return elems.append(elem);
}

qint32 Offset::getElementCount()
{
    return elems.count();
}

QVector<QPair<QString, QString>> Offset::getData()
{
    return d_data;
}

QString Offset::formatData(QString in)
{

    return in.toUpper();
}

QString Offset::format()
{
    if (d_data.isEmpty())
        return QString("no data");

    QString data;
    for (qint16 i = 0; i < d_data.count(); i++)
    {
        data += QString("%1   :   %2\n").arg(d_data.value(i).first).arg(d_data.value(i).second);
    }

    return data.toUpper();
}

