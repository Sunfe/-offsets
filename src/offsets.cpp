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
