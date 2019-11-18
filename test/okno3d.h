#ifndef OKNO3D_H
#define OKNO3D_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_0>

class okno3d : public QOpenGLWidget,
               protected QOpenGLFunctions_3_0{
    Q_OBJECT /// makro do slotów i sygnałów

public:
    explicit okno3d(QWidget *parent = 0);
    ~okno3d();

public slots:
    void ustaw_os_x(int kat);
    void ustaw_os_y(int kat);
    void ustaw_os_z(int kat);
    void ustaw_odleglosc_x(int odl);
    void ustaw_odleglosc_y(int odl);
    void ustaw_odleglosc_z(int odl);
    void ustaw_kolor_r(int r);
    void ustaw_kolor_g(int g);
    void ustaw_kolor_b(int b);

protected: /// funkcje z OpenGL
    void initializeGL();
    void paintGL();
    void resizeGL(int szerokosc, int wysokosc);

private:
    GLfloat _rot_x, _rot_y, _rot_z;
    GLfloat _odl_x, _odl_y, _odl_z;
    GLfloat _kol_r, _kol_g, _kol_b;

};

#endif // OKNO3D_H
