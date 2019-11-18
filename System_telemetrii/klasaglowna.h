#ifndef KLASAGLOWNA_H
#define KLASAGLOWNA_H

#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class KlasaGlowna;
}

class KlasaGlowna : public QMainWindow
{
    Q_OBJECT

public:
    explicit KlasaGlowna(QWidget *parent = 0);
    ~KlasaGlowna();

private slots:
    void on_pushButton_load_model_clicked();

private:
    Ui::KlasaGlowna *ui;
};

#endif // KLASAGLOWNA_H
