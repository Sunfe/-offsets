#ifndef OFFSET_H
#define OFFSET_H
#include <QtGlobal>
#include <QString>
#include <QVector>
#include "element.h"

class Offset
{
public:

    Offset(QVector<Element> elems, QString buf);

    QString extractData(Element elem);

    void setBuf(QString buf);
    QString getBuf();

    void setElements( QVector<Element> elems);
    void setElement( qint32 pos, Element elem);
    Element getElement(qint32 pos);
    qint32 getElementCount();

private:
    QVector<Element> elems;
    QString buf;

};

#endif // OFFSET_H
