#include "okno3d.h"

/*konstruktor*/
Okno3D::Okno3D(QWidget *parent) : QOpenGLWidget(parent),_skala(1),_x(2880),_y(2880),_z(2880) {}

/*destruktor*/
Okno3D::~Okno3D() {}

/*inicjalizacja okna OpenGL*/
void Okno3D::initializeGL(){
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
void Okno3D::resizeGL(int szerokosc, int wysokosc){
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
void Okno3D::paintGL(){
    /*czyszczenie buforów ekranu i głębokości*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /*Reset widoku*/
    glLoadIdentity();
    /*Kolor obiektu*/
    glColor3f(1,0.6,0); /*odcień żółtego*/
    /*Przesunięcie*/
    glTranslatef(0.0, 0.0, -10.0);
    /*Rotacja*/
    glRotatef(_x/16.0, 1.0, 0.0, 0.0);
    glRotatef(_y/16.0, 0.0, 1.0, 0.0);
    glRotatef(_z/16.0, 0.0, 0.0, 1.0);
    /*Skalowanie*/
    glScalef(_skala,_skala,_skala);
    /*FIGURA 3D*/
    rysuj_obiekt();
}

/*metoda rysująca obiekt*/
void Okno3D::rysuj_obiekt(){
    for(unsigned i=0;i<_model_3D._x.size();i+=4){
        glBegin(GL_TRIANGLES); /*początek rysowania trójkąta*/
        for(unsigned j=0;j<3;j++)
/*wierzchołek*/glVertex3f(_model_3D._x[i+j], _model_3D._y[i+j], _model_3D._z[i+j]);
   /*normalna*/glNormal3f(_model_3D._x[i+3], _model_3D._y[i+3], _model_3D._z[i+3]);
        glEnd(); /*koniec rysowania*/
    }
}

/*Wczytywanie obiektu*/
void Okno3D::wczytaj_model_3D(std::string nazwa_pliku){
    ObjFormat model_obj;
    if(!model_obj.wczytaj_plik_obj(nazwa_pliku))
        /*Komunikat z błędem*/
        QMessageBox::information(0, "error", "Błąd wczytania pliku OBJ !");
    _model_3D = model_obj.konwertuj();
    /*Odświerzenie ekranu*/
    update();
}

/*Obsługa rotacji*/
static void Normalizacja_katow(int &kat){
    while (kat < 0)   kat += 360 * 16;
    while (kat > 5760) kat -= 360 * 16;
}

/*Skalowanie obiektu*/
void Okno3D::ustaw_skale(float skala){
    /*wprowadzenie skali obiektu*/
    _skala = skala/10;
    /*wywołanie (emitacja) sygnału*/
    emit skala_zmieniona(skala);
    /*odświerzenie ekranu*/
    update();
}

/*Rotacja w osi x*/
void Okno3D::ustaw_rotacje_x(int kat){
    /*Obsługujemy odpowiednią strone rotacji*/
    Normalizacja_katow(kat);
    /*Jeśli trzeba to aktualizujemy kąt*/
    if (kat != _x) {
        /*aktualizacja kąta*/
        _x = kat;
        /*wywołanie (emitacja) sygnału*/
        emit rotacja_x_zmieniona(kat);
        /*odświerzenie ekranu*/
        update();
    }
}

/*Rotacja w osi y*/
void Okno3D::ustaw_rotacje_y(int kat){
    /*Obsługujemy odpowiednią strone rotacji*/
    Normalizacja_katow(kat);
    /*Jeśli trzeba to aktualizujemy kąt*/
    if (kat != _y) {
        /*aktualizacja kąta*/
        _y = kat;
        /*wywołanie (emitacja) sygnału*/
        emit rotacja_y_zmieniona(kat);
        /*odświerzenie ekranu*/
        update();
    }
}

/*Rotacja w osi z*/
void Okno3D::ustaw_rotacje_z(int kat){
    /*Obsługujemy odpowiednią strone rotacji*/
    Normalizacja_katow(kat);
    /*Jeśli trzeba to aktualizujemy kąt*/
    if (kat != _z) {
        /*aktualizacja kąta*/
        _z = kat;
        /*wywołanie (emitacja) sygnału*/
        emit rotacja_z_zmieniona(kat);
        /*odświerzenie ekranu*/
        update();
    }
}

/*wykrycie naciśnięcia myszy*/
void Okno3D::mousePressEvent(QMouseEvent *event){
    /*zapamiętujemy pozycję kursora w chwili naciśnięcia przycisku myszy*/
    _ostatnia_pozycja = event->pos();
}

/*wykrycie przesunięcia myszy*/
void Okno3D::mouseMoveEvent(QMouseEvent *event){
    /*Obliczamy różnicę pomiędzy aktualną pozycją kursora, a zapamiętaną*/
    int dx = event->x() - _ostatnia_pozycja.x();
    int dy = event->y() - _ostatnia_pozycja.y();

    /*Jeśli kliknięcie lewym przyciskiem myszy*/
    if(event->buttons() & Qt::LeftButton){
        /*obracamy układ*/
        ustaw_rotacje_x(_x + 8 * dy);
        ustaw_rotacje_y(_y + 8 * dx);
    }
    /*Jeśli kliknięcie prawym przyciskiem myszy*/
    else if(event->buttons() & Qt::RightButton){
        /*obracamy układ*/
        ustaw_rotacje_y(_y + 8 * dy);
        ustaw_rotacje_z(_z + 8 * dx);
    }

    /*Zapamiętujemy położenie kursora*/
    _ostatnia_pozycja = event->pos();
}
