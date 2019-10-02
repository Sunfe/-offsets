#include "element.h"

Element::Element()
{

}

Element::Element(QString name, qint32 byteOffset, qint32 byteLen, qint32 bitOffset, qint32 bitLen, FMT format)
{
    this->name       = name;
    this->byteOffset = byteOffset;
    this->byteLen    = byteLen;
    this->bitOffset  = bitOffset;
    this->bitLen     = bitLen;
    this->disaplyFmt = format;
}

Element::Element(const Element &elem)
{
    name       = elem.name;
    byteOffset = elem.byteOffset;
    byteLen    = elem.byteLen;
    bitOffset  = elem.bitOffset;
    bitLen     = elem.bitLen;
    disaplyFmt = elem.disaplyFmt;
}

Element::~Element()
{

}

void Element::setName(QString n)
{
    name = n;
}

QString Element::getName()
{
    return name;
}

void Element::setByteOffset(qint32 o)
{
    byteOffset = o;
}

qint32 Element::getByteOffset()
{
    return byteOffset;
}

void Element::setByteLen(qint32 len)
{
    byteLen = len;
}

qint32 Element::getByteLen()
{
    return byteLen;
}

void Element::setBitOffset(qint32 o)
{
    bitOffset = o;
}

qint32 Element::getBitOffset()
{
    return bitOffset;
}

void Element::setBitLen(qint32 len)
{
    bitLen = len;
}

qint32 Element::getBitLen()
{
    return bitLen;
}

void Element::setDisplayFmt(FMT fmt)
{
    disaplyFmt = fmt;
}

Element::FMT Element::getDisplayFmt()
{
    return disaplyFmt;
}
