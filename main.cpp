#include <iostream>
#include <cmath>
using namespace std;
class Complex {
    float im, re;
public:
    explicit Complex(float im = 0, float re = 0) {
        this -> im = im;
        this -> re = re;
    }
    Complex(Complex &nr){
        re = nr.re;
        im = nr.im;
    }

//Getter si setter pentru partea reala (generate de clion)
    float getRe() const {
        return re;
    }

    void setRe(float real) {
        re = real;
    }

//Getter si setter pentru partea imaginara (generate de clion)
    float getIm() const {
        return im;
    }
    void setIm(float imaginar) {
        im = imaginar;
    }

//Suprascriere >> si <<
    friend istream& operator>>(istream &is, Complex &nr) {
        cout<<"Introdu partea reala: ";
        is >> nr.re;
        cout<<endl;
        cout<<"Introdu partea imaginara: ";
        is >> nr.im;
        cout<<endl;
        return is;
    }
    friend ostream& operator<<(ostream &os, Complex &nr) {
        os << nr.getRe();
        if(nr.getIm() < 0)
            os << nr.im <<"i";
        else if(nr.im > 0)
            os << "+" << nr.im << "i";
        cout<<endl;
        return os;
    }
    void afisare() {
        cout << *this;
    }
    void citire() {
        cin >> *this;
    }

//Metoda pentru calculul modulului nr complex
    float modul_complex () const {
        float modul;
        modul = sqrtf(im * im + re * re);
        modul = round(modul);
        return modul;
    }

    friend Complex operator+(const Complex &a, const Complex &b)
    {
        Complex suma;
        suma.im = a.im + b.im;
        suma.re = a.re + b.re;
        return suma;
    }

//Suprascriere == si != (Generate de Clion)
    bool operator==(const Complex &rhs) const {
        return im == rhs.im &&
               re == rhs.re;
    }

    bool operator!=(const Complex &rhs) const {
        return !(rhs == *this);
    }

    Complex operator=(Complex b) {
        re = b.re;
        im = b.im;
        return b;
    }
};
//
class Matrice {
protected:
    float **v;
    int l, c;
public:
//Constructor parametrizat (valoare default 0, pentru cazul in care nu sunt introduse alte valori
    Matrice(int l = 0, int c = 0) {
            v = new float*[l];
            for(int i = 0; i < l; i++) {
                v[i] = new float[c];
            }
            this -> l = l;
            this -> c = c;
    }

//Destructor
    ~Matrice (){
        for(int i = 0; i < l; i++)
            delete[] v[i];
        delete[] v;
    }

//Suprascriere operatori << si >>
    friend ostream &operator<<(ostream &os, const Matrice &M) {
        for(int i = 0; i < M.l; i++) {
            for (int j = 0; j < M.c; j++)
                os << M.v[i][j] << " ";
            os << endl;
        }
        return os;
    }
    friend istream& operator>>(istream &is, Matrice &M){
        cout << endl << "Introduceti elementele: ";
        for(int i = 0; i < M.l; i++) {
            for (int j = 0; j < M.c; j++)
            {
                Complex nr;
                cin >> nr;
                M.v[i][j] = nr.modul_complex();
            }
        }
        return is;
    }

    void afisare() const {
        cout << *this;
    }

    void citire() {
        cin >> *this;
    }
//Getter si setter
    float getElement(int i, int j) {
        return v[i][j];
    }
    void setElement(int i, int j, float valoare) {
        v[i][j] = valoare;
    }
};
//
class Matrice_Patratica:public Matrice {
    int d;
public:
    Matrice_Patratica(int d = 0):Matrice(d,d) {this -> d = d;}
    ~Matrice_Patratica() {
        for(int i = 0; i < d; i++)
            delete[] v[i];
        delete v;
    }
    friend istream& operator>>(istream &is, Matrice_Patratica &MP) {
        cout << endl << "Introduceti elementele (partea reala si partea imaginara): " << endl;
        for (int i = 0; i < MP.d; i++) {
            for (int j = 0; j < MP.d; j++) {
                Complex nr;
                nr.citire();
                MP.v[i][j] = nr.modul_complex();
            }
        }
        return is;
    }
        friend ostream &operator<<(ostream &os, const Matrice_Patratica &MP) {
            for(int i = 0; i < MP.d; i++) {
                for (int j = 0; j < MP.d; j++)
                    os << MP.v[i][j] << " ";
                os << endl;
            }
            return os;
        }
    void afisare() const{
        cout << *this;
    }
    void citire() {
        cin >> *this;
    }
    float suma_diagprinc() {
        float suma = 0;
        for(int i = 0; i < d; i++)
            for(int j = 0; j < d; j++)
                if(i == j) suma += v[i][j];
        return suma;
    }
};
//Clasa Matrice_Oarecare
class Matrice_Oarecare:public Matrice{
    int l, c;
public:
   explicit Matrice_Oarecare(int l = 0, int c = 0):Matrice(l,c) {this -> l = l; this -> c = c;}
    ~Matrice_Oarecare() {
        for(int i = 0; i < l; i++)
            delete[] v[i];
        delete[] v;
    }
    friend ostream& operator<<(ostream &os, Matrice_Oarecare &M) {
        for (int i = 0; i < M.l; i++) {
            for (int j = 0; j < M.c; j++)
                os << M.v[i][j] << " ";
            os << "\n";
        }
        return os;
    }
    friend istream& operator>>(istream &is, Matrice_Oarecare &M) {
        cout <<endl<<"Introduceti elementele (partea reala si partea imaginara): "<<endl;
        for(int i = 0; i < M.l; i++)
            for(int j = 0; j < M.c; j++)
            {
                Complex nr;
                cin >> nr;
                M.v[i][j] = nr.modul_complex();
            }
        return is;
    }
    void citire() {
        cin >> *this;
    }
    void afisare() {
        cout << *this;
    }
    float getElement(int i, int j) {
        return v[i][j];
    }
    void setElem(int i, int j, float valoare) {
        v[i][j] = valoare;
    }
};
int main() {
}
