#ifndef OFFSETS_H
#define OFFSETS_H

#include <QMainWindow>

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

private:
    Ui::Offsets *ui;
};

#endif // OFFSETS_H
