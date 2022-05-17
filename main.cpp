#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
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

    float getRe() const {
        return re;
    }

    void setRe(float real) {
        re = real;
    }

    float getIm() const {
        return im;
    }
    void setIm(float imaginar) {
        im = imaginar;
    }

    friend istream& operator>>(istream &is, Complex &nr) {
        cout<<"Introdu partea reala: ";
        is >> nr.re;
        cout << "Introdu partea imaginara: ";
        is >> nr.im;
        cout << endl;
        return is;
    }
    friend ostream& operator<<(ostream &os, Complex &nr) {
        os << nr.getRe();
        if(nr.getIm() < 0)
            os << nr.im <<"i";
        else if(nr.im > 0)
            os << "+" << nr.im << "i";
        cout << " ";
        return os;
    }
    void afisare() {
        cout << *this;
    }
    void citire() {
        cin >> *this;
    }

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

class Matrice {
protected:
    Complex **v;
public:
    explicit Matrice(int nrl = 0, int nrc = 0) {
        v = new Complex *[nrl];
        for (int i = 0; i < nrl; i++) {
            v[i] = new Complex[nrc];
        }
    }
    ~Matrice() {
        delete[] v;
    }
    virtual void citire() = 0;
    virtual void afisare() = 0;
};

class Matrice_Oarecare: public Matrice {
    int nrl, nrc;
public:
    explicit Matrice_Oarecare(int nrl = 0, int nrc = 0):Matrice(nrl, nrc) {this -> nrl = nrl; this -> nrc = nrc;};
    Matrice_Oarecare(Matrice_Oarecare &MO) {
        this -> nrl = MO.nrl;
        this -> nrc = MO.nrc;
        this -> v = new Complex*[this -> nrl];
        for (int i = 0; i < this -> nrl; i++){
            v[i] = new Complex[this -> nrc];
            for (int j = 0; j < this -> nrc; j++)
                this -> v[i][j] = MO.v[i][j];
        }
    }
    ~Matrice_Oarecare() {
        for (int i = 0; i < nrl; i++) {
            delete[] v[i];
        }
    }
    void citire() override {
        for (int i = 0; i < this -> nrl; i++)
            for (int j = 0; j < this -> nrc; j++) {
                cin >> v[i][j];
            }

    }
    void afisare() override {
        for (int i = 0; i < this -> nrl; i++) {
            for (int j = 0; j < this -> nrc; j++)
                cout << this -> v[i][j];
            cout << "\n";
        }
    }
    friend istream& operator>>(istream &is, Matrice_Oarecare &MO) {
        MO.citire();
        return is;
    }
    friend ostream& operator<<(ostream &os, Matrice_Oarecare &MO) {
        MO.afisare();
        return os;
    }
    Complex getElement(int i, int j) {
        return v[i][j];
    }
    Matrice_Oarecare& operator=(const Matrice_Oarecare &MO) {
        if(this -> nrl != 0 || this -> nrc != 0) {
            for (int i = 0; i < this -> nrl; i++)
                delete[] this -> v[i];
            delete[] this -> v;
        }
        this -> nrl = MO.nrl;
        this -> nrc = MO.nrc;
        this -> v = new Complex*[MO.nrl];
        for (int i = 0; i <  MO.nrl; i++) {
            this -> v[i] = new Complex[MO.nrc];
        }
        for (int i = 0; i < MO.nrl; i++) {
            for (int j = 0; j < MO.nrc; j++)
                this -> v[i][j] = MO.v[i][j];
        }
    }
};

class Matrice_Patratica: public Matrice {
    int dim;
public:
    explicit Matrice_Patratica(int dim = 0):Matrice(dim, dim) {this -> dim = dim;};
    Matrice_Patratica(Matrice_Patratica &MP) {
        this -> dim = MP.dim;
        this -> v = new Complex*[this -> dim];
        for (int i = 0; i < this -> dim; i++){
            v[i] = new Complex[this -> dim];
            for (int j = 0; j < this -> dim; j++)
                this -> v[i][j] = MP.v[i][j];
        }
    }
    ~Matrice_Patratica() {
        for (int i = 0; i < dim; i++) {
            delete[] v[i];
        }
    }
    void citire() override {
        for (int i = 0; i < this -> dim; i++)
            for (int j = 0; j < this -> dim; j++)
                cin >> v[i][j];
    }
    void afisare() override {
        for (int i = 0; i < this -> dim; i++) {
            for (int j = 0; j < this -> dim; j++)
                cout << this -> v[i][j];
            cout << "\n";
        }
    }
    friend istream& operator>>(istream &is, Matrice_Patratica &MP) {
        MP.citire();
        return is;
    }
    friend ostream &operator<<(ostream &os, Matrice_Patratica &MP) {
        MP.afisare();
        return os;
    }
    Complex getElement(int i, int j) {
        if(i > this -> dim || j > this -> dim)
            throw "Depaseste limita boss";
        else
            return v[i][j];
    }
    Matrice_Patratica& operator=(const Matrice_Patratica &MP) {
        if(this -> dim != 0) {
            for (int i = 0; i < this -> dim; i++)
                delete[] this -> v[i];
            delete[] this -> v;
        }
        this -> dim = MP.dim;
        this -> v = new Complex*[MP.dim];
        for (int i = 0; i <  MP.dim; i++) {
            this -> v[i] = new Complex[MP.dim];
        }
        for (int i = 0; i < MP.dim; i++) {
            for (int j = 0; j < MP.dim; j++)
                this -> v[i][j] = MP.v[i][j];
        }
    }
    int operator==(const Matrice_Patratica &MP)  {
        if (this -> dim != MP.dim) {
            cout << "Nu sunt egale! \n";
            return 0;
        }
        for (int i = 0; i < MP.dim; i++) {
            for (int j = 0; j < MP.dim; j++)
                if (this -> v[i][j] != MP.v[i][j]) {
                    cout << "Nu sunt egale! \n";
                    return 0;
                }
        }
        cout << "Sunt egale! \n";
        return 1;
    }

};

int main() {
//    Matrice_Patratica MP1(1);
//    MP1.citire();
//    MP1.afisare();
//
//    Matrice_Patratica MP2(MP1);
//    MP2.afisare();
//
//    Matrice_Patratica MP3(1);
//    MP3.citire();
//
//    MP2 = MP3;
//    cout << MP3;
//
//    MP1 == MP3;
//    Matrice_Oarecare MO1(1, 2);
//    MO1.citire();
//    MO1.afisare();
//
//    Matrice_Oarecare MO2(MO1);
//    MO2.afisare();

//    Matrice_Oarecare MO3(2, 2);
//    cout << MO3;
//
//    cout << endl;
//    MO3 = MO1;
//    MO3.afisare();
//    vector< shared_ptr <Matrice>> Matrix;
//    Matrix.push_back(make_shared<Matrice_Oarecare>(MO3));
//    cout << Matrix[0].get();
//    Matrice_Patratica MP(1);
//    MP.citire();
//    cout << MP;
//    try {
//        MP.getElement(2, 3);
//    }
//    catch (const char *txtEception) {
//        cout << "Exception: " << txtEception << endl;
//    }
    return 0;
}
