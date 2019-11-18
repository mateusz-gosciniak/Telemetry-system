#include "okno3d.h"

okno3d::okno3d(QWidget *parent) : QOpenGLWidget(parent),
    _rot_x(2880), _rot_y(2880), _rot_z(2880),
    _odl_x(0), _odl_y(0), _odl_z(-100),
    _kol_r(2), _kol_g(4), _kol_b(6) {


}

okno3d::~okno3d(){

}

/*inicjalizacja okna OpenGL*/
void okno3d::initializeGL(){
    initializeOpenGLFunctions(); /*załadowanie opcji opengl z qt*/
    glClearColor(0.2,0.2,0.2,1); /*wypełnienie tła*/
    glEnable(GL_DEPTH_TEST); /*testowanie głębi*/
    glEnable(GL_CULL_FACE); /*wyłączenie wyświetlania wielokątów skierowanych tyłem do patrzącego*/
    glShadeModel(GL_SMOOTH); /*miękkie cieniowanie*/
    glEnable(GL_LIGHTING); /*włączenie światła*/
    glEnable(GL_LIGHT0); /*ustawienie światła nr 0*/
    glEnable(GL_COLOR_MATERIAL); /*śledzenie kolorów*/
    /*ustawienie właściwości źródła światła*/
    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

/*obsługa zmiany rozdzielczości okna*/
void okno3d::resizeGL(int szerokosc, int wysokosc){
    /*wybieramy mniejszą krawędź*/
    int bok = qMin(szerokosc, wysokosc);
    /*Ustalenie obszaru widzenia*/
    glViewport((szerokosc - bok) / 2, (wysokosc - bok) / 2, bok, bok);
    /*Wybieramy stos macierzy - rzutowania*/
    glMatrixMode(GL_PROJECTION);
    /*Tworzymy macierz jednostkową*/
    glLoadIdentity();
    /*rzutowanie równoległe*/
    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
    /*Wybieramy stos macierzy - widok modelu*/
    glMatrixMode(GL_MODELVIEW);
}

/*rysowanie bezpośrednio na ekranie*/
void okno3d::paintGL(){
    /*czyszczenie buforów ekranu i głębokości*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*Reset widoku*/
    glLoadIdentity();

    /*Kolor obiektu*/
    glColor3f(_kol_r/10,_kol_g/10,_kol_b/10);
    /*Przesunięcie*/
    glTranslatef(_odl_x/10,_odl_y/10,_odl_z/10);
    /*Rotacja*/
    glRotatef(_rot_x/16,1,0,0);
    glRotatef(_rot_y/16,0,1,0);
    glRotatef(_rot_z/16,0,0,1);

    /*FIGURA*/
    glBegin(GL_TRIANGLES);
        glVertex3f( 0, 1, 0);
        glVertex3f(-1,-1, 1);
        glVertex3f( 1,-1, 1);
        glVertex3f( 0, 1, 0);
        glVertex3f( 1,-1, 1);
        glVertex3f( 1,-1,-1);
        glVertex3f( 0, 1, 0);
        glVertex3f( 1,-1,-1);
        glVertex3f(-1,-1,-1);
        glVertex3f( 0, 1, 0);
        glVertex3f(-1,-1,-1);
        glVertex3f(-1,-1, 1);
    glEnd();

    update();
}

void okno3d::ustaw_os_x(int kat){ _rot_x = kat; }
void okno3d::ustaw_os_y(int kat){ _rot_y = kat; }
void okno3d::ustaw_os_z(int kat){ _rot_z = kat; }
void okno3d::ustaw_odleglosc_x(int odl){ _odl_x = odl; }
void okno3d::ustaw_odleglosc_y(int odl){ _odl_y = odl; }
void okno3d::ustaw_odleglosc_z(int odl){ _odl_z = odl; }
void okno3d::ustaw_kolor_r(int r){ _kol_r = r; }
void okno3d::ustaw_kolor_g(int g){ _kol_g = g; }
void okno3d::ustaw_kolor_b(int b){ _kol_b = b; }
