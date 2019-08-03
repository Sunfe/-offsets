#include<QMessageBox>
#include "offsets.h"
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
    QMessageBox box;
    box.setText("excute");
    box.exec();
    return;
}
