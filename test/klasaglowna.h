#ifndef KLASAGLOWNA_H
#define KLASAGLOWNA_H

#include <QMainWindow>

namespace Ui {
class klasaglowna;
}

class klasaglowna : public QMainWindow
{
    Q_OBJECT

public:
    explicit klasaglowna(QWidget *parent = 0);
    ~klasaglowna();

private:
    Ui::klasaglowna *ui;
};

#endif // KLASAGLOWNA_H
