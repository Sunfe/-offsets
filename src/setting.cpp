#include <QLayoutItem>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>

#include "ui_setting.h"
#include "setting.h"
#include "offsets.h"

Setting::Setting(QWidget *parent, Profile *prf) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    if (prf != nullptr)
    {
        QString str = prf->getDataStr();
        ui->plainTextEdit->setPlainText(str);
    }
}


Setting::~Setting()
{
    delete ui;
}
