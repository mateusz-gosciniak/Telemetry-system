#include "klasaglowna.h"
#include "ui_klasaglowna.h"

KlasaGlowna::KlasaGlowna(QWidget *parent) : QMainWindow(parent), ui(new Ui::KlasaGlowna){
    ui->setupUi(this);

    connect(ui->openGLWidget_okno3d,SIGNAL(rotacja_x_zmieniona(int)),ui->verticalSlider_x,SLOT(setValue(int)));
    connect(ui->verticalSlider_x,SIGNAL(valueChanged(int)),ui->openGLWidget_okno3d,SLOT(ustaw_rotacje_x(int)));
    connect(ui->openGLWidget_okno3d,SIGNAL(rotacja_y_zmieniona(int)),ui->verticalSlider_y,SLOT(setValue(int)));
    connect(ui->verticalSlider_y,SIGNAL(valueChanged(int)),ui->openGLWidget_okno3d,SLOT(ustaw_rotacje_y(int)));
    connect(ui->openGLWidget_okno3d,SIGNAL(rotacja_z_zmieniona(int)),ui->verticalSlider_z,SLOT(setValue(int)));
    connect(ui->verticalSlider_z,SIGNAL(valueChanged(int)),ui->openGLWidget_okno3d,SLOT(ustaw_rotacje_z(int)));

    connect(ui->verticalSlider_x,SIGNAL(valueChanged(int)),ui->graphicsView,SLOT(obrot_x(int)));
    connect(ui->verticalSlider_y,SIGNAL(valueChanged(int)),ui->graphicsView,SLOT(obrot_y(int)));
    connect(ui->verticalSlider_z,SIGNAL(valueChanged(int)),ui->graphicsView,SLOT(obrot_z(int)));
}

KlasaGlowna::~KlasaGlowna(){
    delete ui;
}

void KlasaGlowna::on_pushButton_load_model_clicked()
{
    /*Pobranie ścieżki do pliku za pomocą obiektu klasy QFileDialog*/
    QString nazwa_pliku = QFileDialog::getOpenFileName(this,tr("Otwórz plik"),"","Pliki OBJ (*.obj);;Wszystkie pliki (*.*)");
    /*Wyświetlenie komunikatu informacyjnego co odczytano*/
    QMessageBox::information(this,tr("Nazwa pliku: "),nazwa_pliku);
    /*Wczytanie modelu - przekazanie ścieżki do funkcji wczytującej*/
    ui->openGLWidget_okno3d->wczytaj_model_3D(nazwa_pliku.toStdString());
}
