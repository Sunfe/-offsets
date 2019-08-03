#include <QLayoutItem>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QGridLayout>

#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}

#define GLB_MAX_OFFSET_ITEM  (5)
void Setting::addOffsetItem()
{
#if 0
    QGridLayout *offsetGroup = ui->layoutOffsetGroup;
    QLabel *offsetLabel = new QLabel("Type");
    QLineEdit *lineEdit = new QLineEdit(this);


    int row = offsetGroup->rowCount() + 1;
    if (row > GLB_MAX_OFFSET_ITEM)
    {
        QMessageBox *msg = new QMessageBox();
        int i = GLB_MAX_OFFSET_ITEM;
        msg->setText(QString("only supported to %1 items").arg(i));
        msg->exec();
        return;
    }

    offsetGroup->addWidget(offsetLabel,row,0);
    offsetGroup->addWidget(lineEdit, row,1);
#endif

    return;
}

void Setting::delOffsetItem()
{
    return;
}
