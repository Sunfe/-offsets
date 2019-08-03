#ifndef SETTING_H
#define SETTING_H

#include <QDialog>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

private slots:
    void addOffsetItem();
    void delOffsetItem();
private:
    Ui::Setting *ui;
};

#endif // SETTING_H
