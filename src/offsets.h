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

private slots:
    void parse();
    void showSetting();

private:
    Ui::Offsets *ui;
    Profile *profile;
};

#endif // OFFSETS_H
