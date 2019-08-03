#ifndef PROFILE_H
#define PROFILE_H
#include <QString>
#include <QPair>
#include <QJsonObject>

#define GLB_MAX_OFFSETS_CNT     128


class Profile
{
public:
    enum PROFILE_TYPE {
        ETH,
        IP,
        UDP,
        FPP_META
    };

    Profile(qint8 type = Profile::FPP_META);
    ~Profile();

    void loadData(qint8 type);
    void updateData(QJsonObject dt);
    QJsonObject getData();
    QString getDataStr();

    QJsonObject strToJson(QString str);
    QString jsonToStr(QJsonObject obj);


private:
    /* profile type: 0:ethernet frmae; 1: ip frame; 2: udp frame; 3:fpp meta frame*/
    QJsonObject data;

};

#endif // PROFILE_H
