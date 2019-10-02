#include <QObject>
#include <QMessageBox>
#include <QPair>
#include <QDebug>
#include "mainwindow.h"
#include "setting.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioBtnMetaframe->setChecked(true);

    profile = new Profile(nullptr);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parse()
{
    return;
}

void MainWindow::editSetting()
{
    profile->loadData(d_type);
    Setting *set = new Setting(this, profile);
    set->show();
}


void MainWindow::setDataType(qint8 type)
{
    d_type = type;
}

qint8 MainWindow::getDataType()
{
    return d_type;
}

void MainWindow::onRadioBtnClick(bool checked)
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

Profile* MainWindow::getProfile()
{
    return profile;
}

void MainWindow::setProfile(Profile prf)
{
   *profile = prf;
   return;
}


