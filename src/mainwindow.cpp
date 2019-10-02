#include <QObject>
#include <QMessageBox>
#include <QPair>
#include <QDebug>

#include "global.h"
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

Profile* MainWindow::getProfile()
{
    return profile;
}

void MainWindow::setProfile(Profile prf)
{
    *profile = prf;
    return;
}

void MainWindow::onRadioBtnClick(bool checked)
{
    UN_USED_PARAM(checked);
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

void MainWindow::parze()
{
    QString buf = ui->src->toPlainText();
    QVector<QPair<QString, QString>> data;
    QString targetText;
    if (buf.isEmpty())
    {
        ui->target->clear();
        return;
    }

    data = profile->getOffset(Profile::ETH)->extractData(&buf);
    for (qint16 i = 0; i < data.count(); i++)
    {
        targetText += QString("%1 : %2\n").arg(data.value(i).first).arg(data.value(i).second);
    }

    ui->target->setPlainText(targetText);

    return;
}

