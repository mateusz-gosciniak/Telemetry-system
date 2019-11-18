#ifndef OBJ_LOAD_HPP
#define OBJ_LOAD_HPP

#include <fstream>
#include <vector>

/*
 * Klasa jest przystosowana do podstawowych, prostych plików typu obj:
 *
 * Wymagane:
 * [x] Triangulate Faces
 *
 * Dodatkowe:
 * [x] Include Normals
 *
 * Nie wspierane:
 * [x] Selection Only
 * [x] Animation
 * [x] Apply Modifiers
 * [x] Include Edges
 * [x] Smooth Groups
 * [x] Bitflag Smooth Groups
 * [x] Include UVs
 * [x] Write Materials
 * [x] Write Nurbs
 * [x] Polygroups
 * [x] Objects as OBJ Objects
 * [x] Objects as OBJ Groups
 * [x] Material Groups
 * [x] Keep Vertex Order
 *
 * Jeśli jakaś opcja jest wspierana to jest to przypadkowe
 * Autor nie przewidział wspierania tej opcji.
 * UWAGA ! Mogą powstać błędy !
 *
 * Opis pliku OBJ:
 * * #  - komentarz
 * * o  - oznacza nazwę obiektu
 * * v  - Wierzchołek to punkt łączący krawędzie.
 * * vt - Współrzędne tekstur
 * * vn - Normalna to wektor prostopadły do powierzchni. OpenGL wykorzystuje normalne do obliczania oświetlenia.
 * * vp - Współrzędne przestrzeni
 * * s  - off - oznacza obiekt płaski
 * * f  - Ściana, pole ograniczone krawędziami oraz wierzchołkami
 * * * formaty zapisu:
 * * * f l1 l2 l3 - ściana osadzona na wierzchołkach, którym odpowiadają liczby l1, l2 i l3
 * * * f l1/lt1 l2/lt2 l3/lt3 - do formatu dochodzą współrzędne tekstury (lt) określone po znaku /                       <<< Format nie wspierany
 * * * f l1/lt1/ln1 l2/lt2/ln1 l3/lt3/ln1 - do formatu dochodzą współrzędne normalnych (ln) określone po drugim znaku /  <<< Format nie wspierany
 * * * f l1//ln1 l2//ln1 l3//ln1 - format pomija współrzędne tekstury
 * * * indeksy zaczynają się od 1 !!
 *
 * erata:
 * wyświetlanie plików - na wyjściu może pojawić się coś takiego 1e-06, w przypadku zapisu do pliku może być różnie
 * zakładam że jest tylko jedna normalna dla danej płaszczyzny
 * brak pól prywatnych w klasach
 * brak assercji dla nie wspieranych formatów, oraz dla błędnych plików lub z błędami umieszczonymi celowo
 * komentarze z całego pliku znajdą się po jego zapisie na początku pliku
 * mimo nie wczytania pliku, można go wyświetlić
 *
 * OpenGL Format:
 * Klasa przygotowana tak by jak najłatwiej wyświetlić wczytany obiekt wykorzystując biblioteki OpenGL
 * * Jeśli plik OBJ nie zawierał normalnych to co 3 wierzchołki zaczyna się nowa ściana
 * * Jeśli plik OBJ zawierał normalne to co 3 wierzchołki znajduje się wierzchołek wyznaczający normalną dla danej ściany
 *
 * Przykład użycia klasy:
 * Wczytanie pliku OBJ następnie przetworzenie na format przyjazny OpenGl
 *
 * #include "obj_load.hpp"
 * #include <iostream>
 * int main(){
 *     ObjFormat model_import;
 *     model_import.wczytaj_plik_obj("cube.obj");
 *     std::cout << model_import << std::endl;
 *     OpenGLFormat model_export;
 *     model_export = model_import.konwertuj();
 *     std::cout << model_export << std::endl;
 *     return 0;
 * }
 *
 * Przykład wyświetlania obiektu w OpenGL:
 *
 * for(unsigned i=0;i<model_3D._x.size();i+=4){
 *     glBegin(GL_TRIANGLES);
 *     for(unsigned j=0;j<3;j++)
 *          glVertex3f(model_3D._x[i+j], model_3D._y[i+j], model_3D._z[i+j]);
 *          glNormal3f(model_3D._x[i+3], model_3D._y[i+3], model_3D._z[i+3]);
 *     glEnd();
 * }
 *
 */

struct wierzcholek{
    float _x,_y,_z;

    friend std::istream &operator>> (std::istream &wejscie, wierzcholek &o)
        { wejscie >> o._x >> o._y >> o._z; return wejscie; }
    friend std::ostream &operator<< (std::ostream &wyjscie, const wierzcholek &o)
        { wyjscie << o._x << " " << o._y << " " << o._z; return wyjscie; }
};

struct sciana{
    float _p1,_p2,_p3;
    unsigned _nr_normalnej; /*nie wymagane*/

    friend std::istream &operator>> (std::istream &wejscie, sciana &o)
        { wejscie >> o._p1 >> o._p2 >> o._p3; return wejscie; }
    friend std::ostream &operator<< (std::ostream &wyjscie, const sciana &o)
        { wyjscie << o._p1 << " " << o._p2 << " " << o._p3; return wyjscie; }
};

struct OpenGLFormat{
    std::vector<float> _x, _y, _z;
    bool _normalne; /*informacyjnie*/

    OpenGLFormat() : _x(), _y(), _z(), _normalne(false) {}
    ~OpenGLFormat() {}

    void dodaj_wierzcholek(const wierzcholek &nowy_wierzcholek){
        this->_x.push_back(nowy_wierzcholek._x);
        this->_y.push_back(nowy_wierzcholek._y);
        this->_z.push_back(nowy_wierzcholek._z);
    }
    friend std::istream &operator>> (std::istream &wejscie, OpenGLFormat &o){
        wierzcholek nowy_wierzcholek;
        wejscie >> nowy_wierzcholek;
        o.dodaj_wierzcholek(nowy_wierzcholek);
        return wejscie;
    }
    friend std::ostream &operator<< (std::ostream &wyjscie, const OpenGLFormat &o){
        for(unsigned i=0;i<o._x.size();i++) wyjscie << o._x[i] << " " << o._y[i] << " " << o._z[i] << "\n";
        return wyjscie;
    }
};

struct ObjFormat{
    std::string _nazwa_pliku, _nazwa_modelu, _off;
    std::vector<std::string> _wektor_komentarzy;   /* #  */
    std::vector<wierzcholek> _wektor_wierzcholkow; /* v  */
 /* std::vector<wierzcholek> _wektor_w_tekstur;    brak obsługi*/ /* vt */
    std::vector<wierzcholek> _wektor_normalnych;   /* vn */
 /* std::vector<wierzcholek> _wektor_przestrzeni;  brak obsługi*/ /* vp */
    std::vector<sciana>      _wektor_scian;        /* f  */

    ObjFormat() : _nazwa_pliku(), _nazwa_modelu(), _off(),
                  _wektor_komentarzy(), _wektor_wierzcholkow(), _wektor_normalnych(), _wektor_scian() {}
    ~ObjFormat() {}

    OpenGLFormat konwertuj(){
        OpenGLFormat opengl_model;

        if(_wektor_normalnych.size()){
            opengl_model._normalne = true;
            for(unsigned i=0;i<_wektor_scian.size();i++){
                opengl_model.dodaj_wierzcholek(_wektor_wierzcholkow[(_wektor_scian[i]._p1-1)]);
                opengl_model.dodaj_wierzcholek(_wektor_wierzcholkow[(_wektor_scian[i]._p2-1)]);
                opengl_model.dodaj_wierzcholek(_wektor_wierzcholkow[(_wektor_scian[i]._p3-1)]);
                /*normalna*/
                opengl_model.dodaj_wierzcholek(_wektor_normalnych[(_wektor_scian[i]._nr_normalnej-1)]);
            }
        } else {
            opengl_model._normalne = false;
            for(unsigned i=0;i<_wektor_scian.size();i++){
                opengl_model.dodaj_wierzcholek(_wektor_wierzcholkow[(_wektor_scian[i]._p1-1)]);
                opengl_model.dodaj_wierzcholek(_wektor_wierzcholkow[(_wektor_scian[i]._p2-1)]);
                opengl_model.dodaj_wierzcholek(_wektor_wierzcholkow[(_wektor_scian[i]._p3-1)]);
            }
        }

        return opengl_model;
    };
    bool wczytaj_plik_obj(const std::string &nazwa_pliku){
        _nazwa_pliku = nazwa_pliku;
        std::ifstream Plik(_nazwa_pliku.c_str());
        if(!Plik.good()){
            printf("BRAK PLIKU OBJ !!\n");
            return false;
        }
        Plik >> *this;
        return true;
    }
    bool zapisz_plik_obj(const std::string &nazwa_pliku){
        std::fstream plik(nazwa_pliku.c_str(), std::ios::out);
        if(plik.good())
        {
            plik << *this;
            plik.close();
            return true;
        }
        return false;
    }
    friend std::istream &operator>> (std::istream &wejscie, ObjFormat &o){
        if(o._nazwa_pliku.size() == 0)
            getline( wejscie, o._nazwa_pliku );

        std::string znak;
        while(!wejscie.eof())
        {
            wejscie >> znak;
            if(znak == "#") /*Obsługa komentarzy*/
            {
                std::string tmp;
                getline( wejscie, tmp );
                o._wektor_komentarzy.push_back(tmp);
            }
            else  if(znak == "o") /*Obsługa nazw*/
            {
                wejscie >> o._nazwa_modelu;
            }
            else if(znak == "v") /*Obsługa wierzchołków*/
            {
                wierzcholek tmp;
                wejscie >> tmp;
                o._wektor_wierzcholkow.push_back(tmp);
            }
            else if(znak == "vt") /*Obsługa tekstury*/
            {
                wierzcholek tmp;
                wejscie >> tmp;
                o._wektor_normalnych.push_back(tmp);
            }
            else if(znak == "vn") /*Obsługa normalnych*/
            {
                wierzcholek tmp;
                wejscie >> tmp;
                o._wektor_normalnych.push_back(tmp);
            }
            else if(znak == "vp") /*Obsługa przestrzeni*/
            {
                wierzcholek tmp;
                wejscie >> tmp;
                o._wektor_normalnych.push_back(tmp);
            }
            else if(znak == "s") /*s off*/
            {
                wejscie >> o._off;
            }
            else if(znak == "g") /*Obsługa grup*/
            {
                wejscie >> o._off;
            }
            else if(znak == "f") /*Obsługa ścian*/
            {
                if(wejscie.eof()) break;

                char pomocnik, smiec;
                unsigned  l1 = 0, l2  = 0, l3  = 0,
                         lt1 = 0, lt2 = 0, lt3 = 0,
                         ln1 = 0, ln2 = 0, ln3 = 0;

                wejscie >> l1;
                pomocnik = wejscie.get();
                if(pomocnik != '/'){
                    wejscie.putback(pomocnik);
                    wejscie >> l2 >> l3;
                } else{
                    pomocnik = wejscie.get();
                    if(pomocnik != '/'){
                        wejscie.putback(pomocnik);
                        wejscie >> lt1;

                        pomocnik = wejscie.get();
                        if(pomocnik == '/'){
                            wejscie >> ln1 >> l2 >> smiec >> lt2 >> smiec >> ln2 >> l3 >> smiec >> lt3 >> smiec >> ln3;
                        } else{
                            wejscie.putback(pomocnik);
                            wejscie >> l2 >> smiec >> lt2 >> l3 >> smiec >> lt3;
                        }
                    }
                    wejscie >> ln1 >> l2 >> smiec >> smiec >> ln2 >> l3 >> smiec >> smiec >> ln3;
                }

                sciana tmp;
                tmp._p1 = l1; tmp._p2 = l2; tmp._p3 = l3;
                tmp._nr_normalnej = ln1 = ln2 = ln3;
                o._wektor_scian.push_back(tmp);
            }
        }
        return wejscie;
    }
    friend std::ostream &operator<< (std::ostream &wyjscie, const ObjFormat &o){
        wyjscie << "# " << o._nazwa_pliku << "\n";
        for(unsigned i=0;i<o._wektor_komentarzy.size();i++)
            wyjscie << "# " << o._wektor_komentarzy[i] << "\n";
        wyjscie << "o " << o._nazwa_modelu << "\n";
        for(unsigned i=0;i<o._wektor_wierzcholkow.size();i++)
            wyjscie << "v " << o._wektor_wierzcholkow[i] << "\n";
        for(unsigned i=0;i<o._wektor_normalnych.size();i++)
            wyjscie << "v " << o._wektor_normalnych[i] << "\n";
        wyjscie << "s " << o._off << "\n";

        if(o._wektor_normalnych.size())
        {
            for(unsigned i=0;i<o._wektor_scian.size();i++)
            {
                wyjscie << "f ";
                wyjscie << o._wektor_scian[i]._p1 << "//" << o._wektor_scian[i]._nr_normalnej << " ";
                wyjscie << o._wektor_scian[i]._p2 << "//" << o._wektor_scian[i]._nr_normalnej << " ";
                wyjscie << o._wektor_scian[i]._p3 << "//" << o._wektor_scian[i]._nr_normalnej << " ";
                wyjscie << "\n";
            }
        }else {
            for(unsigned i=0;i<o._wektor_scian.size();i++)
                wyjscie << "f " << o._wektor_scian[i] << "\n";
        }

        return wyjscie;
    }
};

#endif /*OBJ_LOAD_HPP*/
