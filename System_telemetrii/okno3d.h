#ifndef OKNO3D_H
#define OKNO3D_H

#include "obj_load.hpp"

#include <QWidget>
#include <QString>
#include <QPoint>
#include <QMouseEvent>
#include <QMessageBox>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLShaderProgram>

class Okno3D : public QOpenGLWidget, protected QOpenGLFunctions_2_0{
    Q_OBJECT

public:
    /*konstruktor*/
    explicit Okno3D(QWidget *parent = 0); /*zabraniamy niejawnych konwersji*/
    /*destruktor*/
    ~Okno3D();

    /*wyświetlanie zmiennych x,y,z*/
    int wyswietl_x() {return _x;}
    int wyswietl_y() {return _y;}
    int wyswietl_z() {return _z;}

protected:
    /*metoda w której inicjalizujemy funkcje OpenGL*/
    void initializeGL();
    /*metoda którą rysujemy na ekranie*/
    void paintGL();
    /*obsługa zmiany rozdzielczości okna*/
    void resizeGL(int szerokosc, int wysokosc);
    /*wykrycie naciśnięcia myszy*/
    void mousePressEvent(QMouseEvent *event);
    /*wykrycie przesunięcia myszy*/
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void ustaw_rotacje_x(int kat);
    void ustaw_rotacje_y(int kat);
    void ustaw_rotacje_z(int kat);
    void ustaw_skale(float skala);
    void wczytaj_model_3D(std::string nazwa_pliku);

signals:
    void rotacja_x_zmieniona(int kat);
    void rotacja_y_zmieniona(int kat);
    void rotacja_z_zmieniona(int kat);
    void skala_zmieniona(float skala);

private:
    void rysuj_obiekt();

    QPoint _ostatnia_pozycja;
    OpenGLFormat _model_3D;
    float _skala;
    int _x,_y,_z;

};

#endif // OKNO3D_H
