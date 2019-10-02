#ifndef OFFSET_H
#define OFFSET_H
#include <QtGlobal>
#include <QString>
#include <QVector>
#include "element.h"

class Offset
{
public:

    Offset();
    Offset(QVector<Element> elems);
    ~Offset();

    /* 从一块缓冲区中解析出某个元素的数据 */
    QString extractData(QString buf, Element elem);

    void setBuf(QString buf);
    QString getBuf();

    void setElements( QVector<Element> elems);
    void setElement( qint32 pos, Element elem);
    Element getElement(qint32 pos);
    void appendElement(Element elem);
    qint32 getElementCount();

private:
    QVector<Element> elems;
    QString buf;

};

#endif // OFFSET_H
