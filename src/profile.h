#ifndef PROFILE_H
#define PROFILE_H
#include <QString>
#include <QPair>
#include <QJsonObject>

#define GLB_MAX_OFFSETS_CNT     (128)
#define GLB_MAX_PRF_NUM         (10)


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
    void updateData(QJsonObject dt, qint8 type);
    QJsonObject getData(qint8 type);
    QString getDataStr();

    QJsonObject strToJson(QString str);
    QString jsonToStr(QJsonObject obj);

    void setType(qint8 type);
    qint8 getType();


private:
    /* profile type: 0:ethernet frmae; 1: ip frame; 2: udp frame; 3:fpp meta frame*/
    QJsonObject data[GLB_MAX_PRF_NUM];
    qint8 d_type;

};

#endif // PROFILE_H
