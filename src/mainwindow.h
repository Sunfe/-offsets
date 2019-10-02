#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "profile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDataType(qint8 type);
    qint8 getDataType();

    Profile *getProfile();
    void setProfile(Profile prf);


private slots:
    void editSetting();
    void onRadioBtnClick(bool checked);
    void parze();

private:
    Ui::MainWindow *ui;

    Profile *profile;
    qint8 d_type;
};

#endif // MAINWINDOW_H
