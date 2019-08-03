#include<QMessageBox>
#include "offsets.h"
#include "setting.h"
#include "ui_offsets.h"

Offsets::Offsets(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Offsets)
{
    ui->setupUi(this);

}

Offsets::~Offsets()
{
    delete ui;
}

void Offsets::parse()
{
    return;
}


void Offsets::showSetting()
{
    Setting *set = new Setting(this);
    set->show();
}
