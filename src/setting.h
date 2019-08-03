#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "profile.h"

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr, Profile *prf=nullptr);
    ~Setting();

private slots:

private:
    Ui::Setting *ui;
    Profile *profile;
};

#endif // SETTING_H
