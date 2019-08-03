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

    Profile();
    ~Profile();

    QJsonObject loadProfile(qint8 type);
    void updateProfile();

    QJsonObject StrToJson(QString str);


private:
    /* profile type: 0:ethernet frmae; 1: ip frame; 2: udp frame; 3:fpp meta frame*/
    QPair<QString, qint16> offset[GLB_MAX_OFFSETS_CNT];

};

#endif // PROFILE_H
