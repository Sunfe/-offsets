#ifndef SHIFT_H
#define OFFSET_H
#include <QtGlobal>

class Offset
{
public:
    enum DISPLAY{
        FTM_HEX,                  /* 16进制格式显示 */
        FTM_DEC                   /* 10进制格式显示 */
    };

	Offset();

private:
    qint32 byteOffset;
    qint32 byteLen;
    qint32 bitOffset;
    qint32 bitLen;
    qint8  displayFtm;

};

#endif // OFFSET_H
