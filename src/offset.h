#ifndef OFFSET_H
#define OFFSET_H
#include <QtGlobal>
#include <QString>
#include <QVector>
#include <QPair>

#include "element.h"

class Offset
{
public:

    Offset();
    Offset(QVector<Element> elems);
    ~Offset();

    /* 从一块缓冲区中解析出某个元素的数据 */
    void extractData();
    QString extractElemData(QString *buf, Element elem);

    void setElements( QVector<Element> elems);
    void setElement( qint32 pos, Element elem);
    QVector<Element> *getElements();
    Element getElement(qint32 pos);
    void appendElement(Element elem);
    qint32 getElementCount();
    bool isEmpty();

    QString formatData(QString in);
    virtual QString format();

    QString* getBuf();
    void setBuf(QString *buf);

    QVector<QPair<QString, QString>>* getData();

private:
    QVector<Element> elems;
    QString *d_buf;
    QVector<QPair<QString, QString>> d_data;

};

#endif // OFFSET_H
