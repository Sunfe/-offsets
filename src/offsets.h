#ifndef OFFSETS_H
#define OFFSETS_H

#include <QMainWindow>
#include "profile.h"

namespace Ui {
class Offsets;
}

class Offsets : public QMainWindow
{
    Q_OBJECT

public:
    explicit Offsets(QWidget *parent = nullptr);
    ~Offsets();

    void setDataType(qint8 type);
    qint8 getDataType();

private slots:
    void parse();
    void showSetting();
    void onRadioBtnClick(bool checked);

private:
    Ui::Offsets *ui;

    Profile *profile;
    qint8 d_type;
};

#endif // OFFSETS_H
