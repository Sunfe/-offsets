#include <QtGlobal>
#include <QMessageBox>
#include <QStringList>

#include "profile.h"

/* inner default profiles */
static const char *gPrfEther =
        "src: 0;"
        "des: 4;"
        "len: 8";

static const char *gPrfIp =
        "Transaction Identifier:0;"
        "Protocol Identifier:4;"
        "Length Field";


Profile::Profile()
{

}


Profile::~Profile()
{

}


QJsonObject Profile::strToJson(QString str)
{
    QJsonObject obj;
    QStringList list = str.split(';');

    QList<QPair<QString, int>> ol;
    for(qint16 i= 0; i < list.count(); i++)
    {
        QString s = list.at(i);
        QStringList l = s.split(':');

        if (l.count() != 2) /* key an value, must be 2 items */
        {
            return obj; /* empyt object*/
        }

        bool ok;
        QString key = l.at(0);
        int value = l.at(1).toInt(&ok);
        if (!ok)
        {
            return obj;
        }

        obj.insert(key, value);
    }

    return obj;
}


QJsonObject Profile::loadProfile(qint8 type)
{
    QJsonObject obj;

    if (Profile::ETH == type)
        obj = strToJson(gPrfEther);
    else if (Profile::IP == type)
        obj = strToJson(gPrfIp);

    return obj;
}

