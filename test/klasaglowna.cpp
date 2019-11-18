#include "klasaglowna.h"
#include "ui_klasaglowna.h"

klasaglowna::klasaglowna(QWidget *parent) : QMainWindow(parent), ui(new Ui::klasaglowna){
    ui->setupUi(this);
    connect(ui->horizontalSlider_rot_x,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_os_x(int)));
    connect(ui->horizontalSlider_rot_y,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_os_y(int)));
    connect(ui->horizontalSlider_rot_z,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_os_z(int)));

    connect(ui->horizontalSlider_odl_x,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_odleglosc_x(int)));
    connect(ui->horizontalSlider_odl_y,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_odleglosc_y(int)));
    connect(ui->horizontalSlider_odl_z,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_odleglosc_z(int)));

    connect(ui->horizontalSlider_kol_r,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_kolor_r(int)));
    connect(ui->horizontalSlider_kol_g,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_kolor_g(int)));
    connect(ui->horizontalSlider_kol_b,SIGNAL(valueChanged(int)),ui->openGLWidget,SLOT(ustaw_kolor_b(int)));
}

klasaglowna::~klasaglowna(){
    delete ui;
}
