#ifndef ELEMENT_H
#define ELEMENT_H
#include<QtGlobal>
#include<QString>

class Element
{
public:
    enum FMT{
        HEX,                  /* 16进制格式显示 */
        DEC,                  /* 10进制格式显示 */
        TEXT
    };

    Element();
    Element(QString n, qint32 byteOffset=0, qint32 byteLen=0, qint32 bitOffset=0, qint32 bitLen=0, FMT fmt=HEX);
    Element(const Element &elem);
    ~Element();

    void setName(QString n);
    QString getName();

    void setByteOffset(qint32 o);
    qint32 getByteOffset();
    void setByteLen(qint32 len);
    qint32 getByteLen();

    void setBitOffset(qint32 o);
    qint32 getBitOffset();
    void setBitLen(qint32 len);
    qint32 getBitLen();

    void setDisplayFmt(FMT fmt);
    FMT getDisplayFmt();

private:
    QString name;
    qint32 byteOffset;
    qint32 byteLen;
    qint32 bitOffset;
    qint32 bitLen;
    FMT disaplyFmt;
};

#endif // ELEMENT_H
