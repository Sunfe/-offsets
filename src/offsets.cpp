#include <QObject>
#include <QMessageBox>
#include <QPair>
#include <QDebug>
#include "offsets.h"
#include "setting.h"
#include "ui_offsets.h"


Offsets::Offsets(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Offsets)
{
    ui->setupUi(this);
    ui->radioBtnMetaframe->setChecked(true);

    profile = new Profile(Profile::FPP_META);

}

Offsets::~Offsets()
{
    delete ui;
}

void Offsets::parse()
{
    return;
}

void Offsets::editSetting()
{
    profile->loadData(d_type);
    Setting *set = new Setting(this, profile);
    set->show();
}


void Offsets::setDataType(qint8 type)
{
    d_type = type;
}


qint8 Offsets::getDataType()
{
    return d_type;
}


void Offsets::onRadioBtnClick(bool checked)
{
   QRadioButton *snd = qobject_cast<QRadioButton *>(sender());

   QList<QPair<QString, qint8>> list;
   list.append(qMakePair(QString("radioBtnEth"), Profile::ETH));
   list.append(qMakePair(QString("radioBtnIp"), Profile::IP));
   list.append(qMakePair(QString("radioBtnUdp"), Profile::UDP));
   list.append(qMakePair(QString("radioBtnMetaframe"), Profile::FPP_META));

   for (qint8 i = 0; i < list.count(); i++)
   {
       if (snd->objectName() == list.at(i).first)
       {
           setDataType(list.at(i).second);
       }
   }

   return;
}


Profile* Offsets::getProfile()
{
    return profile;
}


void Offsets::setProfile(Profile prf)
{
   *profile = prf;
   return;
}


