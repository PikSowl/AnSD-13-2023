#define WrongInput wcout << L"Неверная команда" << endl

#include <iostream>
#include <cmath>
#include <io.h>
#include <fcntl.h>

using std::wcin;
using std::wcout;
using std::swap;
using std::endl;

struct Dot {
    double x;
    double y;
    double z;
};

class Vector {

private:
    Dot XYZ = {0, 0, 0};

public:
    Vector(Dot a, Dot b){
        XYZ.x = b.x - a.x;
        XYZ.y = b.y - a.y;
        XYZ.z = b.z - a.z;
    }

    Vector(){}
    Vector(double i, double j, double k){
        XYZ = {i,j,k};
    }
    Vector(const Vector& other){
        XYZ = other.XYZ;
    }
    double GetX(){
        return XYZ.x;
    }
    double GetY(){
        return XYZ.y;
    }
    double GetZ(){
        return XYZ.z;
    }
    double Len(){
        double len = pow(pow(XYZ.x, 2) + pow(XYZ.y, 2) + pow(XYZ.z, 2), 0.5);
        return len;
    }

    Vector& operator = (const Vector& other){
        XYZ = other.XYZ;
        return *this;
    }
    Vector& operator += (const Vector& other)
    {
        XYZ.x += other.XYZ.x;
        XYZ.y += other.XYZ.y;
        XYZ.z += other.XYZ.z;
        return *this;
    }
    Vector operator + (const Vector& other){
        Vector temp = *this;
        temp += other;
        return temp;
    }
    Vector& operator -= (const Vector& other){
        XYZ.x -= other.XYZ.x;
        XYZ.y -= other.XYZ.y;
        XYZ.z -= other.XYZ.z;
        return *this;
    }
    Vector operator - (const Vector& other){
        Vector temp = *this;
        temp -= other;
        return temp;
    }
    Vector& operator *= (const double& k){
        XYZ.x *= k;
        XYZ.y *= k;
        XYZ.z *= k;
        return *this;
    }
    Vector operator * (const double& k){
        Vector temp = *this;
        temp *= k;
        return temp;
    }
    double operator * (const Vector& other){
        return XYZ.x * other.XYZ.x + XYZ.y * other.XYZ.y + XYZ.z * other.XYZ.z;
    }
    Vector VecProd(const Vector& other){
        Vector ans;
        ans.XYZ.x = this->XYZ.y * other.XYZ.z - this->XYZ.z * other.XYZ.y;
        ans.XYZ.y = -1 * (this->XYZ.x * other.XYZ.z - this->XYZ.z * other.XYZ.x);
        ans.XYZ.z = this->XYZ.x * other.XYZ.y - this->XYZ.y * other.XYZ.x;
        return ans;
    }
    double MixProd(const Vector& other1, const Vector& other2){
        return (*this).VecProd(other1) * other2;
    }

    bool operator > (Vector& other){
        return (*this).Len() > other.Len();
    }
    bool operator < (Vector& other){
        return (*this).Len() < other.Len();
    }
    bool operator == (Vector& other){
        return (*this).Len() == other.Len();
    }

    bool Colinear(const Vector& other){
        Vector Null;
        return ((*this).VecProd(other) == Null);
    }
    bool Complanar(const Vector& other1, const Vector& other2){
        return (*this).MixProd(other1, other2) == 0;
    }

    double Angle(Vector& other){
        return std::cos((*this * other) / ((*this).Len() * other.Len()));
    }
    Vector Norm(){
        Vector temp = *this;
        double k = (*this).Len();
        if (k != 0)
            temp *= 1/k;
        return temp;
    }

    friend std::wostream& operator << (std::wostream& out, Vector& other);
    friend std::wistream& operator >> (std::wistream& in, Vector& other);

    ~Vector() {}
};

std::wostream& operator << (std::wostream& out, Vector& other)
{
    return out << other.GetX() << " " << other.GetY() << " " << other.GetZ();
}

std::wistream& operator >> (std::wistream& in, Vector& other)
{
    double x, y, z;
    in >> x >> y >> z;
    other = { x,y,z };
    return in;
}


void VecInput(Vector& x, char name,const int & style) {
    if (style == 1){
        Dot A,Z{0,0,0};
        wcout << L"Введите компоненты вектора "<< name << endl;
        wcin >> A.x >> A.y >> A.z;
        x=Vector(Z,A);
    }
    else{
        Dot A,B;
        wcout << L"Введите координаты 1 точки вектора "<< name << endl;
        wcin >> A.x >> A.y >> A.z;
        wcout << L"Введите координаты 2 точки вектора "<< name << endl;
        wcin >> B.x >> B.y >> B.z;
        x=Vector(A,B);
    }
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin),  _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    Vector a, b, c;
    Vector temp;
    Dot A, B;
    int num, style = -1, input = 999, k = 0;
    wcout << L"Введите количество векторов" << endl;
    wcin >> num;
    if (num > 3 || num <= 0) {
        wcout << L"Недопустимое количество векторов";
        return 0;
    }
    wcout << L"Выберете способ задачи векторов" << endl << L"1) По компонентам" << endl << L"2) По 2 точкам"
          << endl
          << L"[по умолчанию 1]" << endl;
    wcin >> style;
    if (style != 2)
        style = 1;
    switch (num) {
        case (1):
            VecInput(a, 'a', style);
            break;
        case (2):
            VecInput(a, 'a', style);
            VecInput(b, 'b', style);
            break;
        case (3):
            VecInput(a, 'a', style);
            VecInput(b, 'b', style);
            VecInput(c, 'c', style);
            break;
    }
    wcout << L"Для вывода 1, 2 и 3 листов команд напишите 111, 222 и 333" << endl;
    while (input != 0) {
        wcin >> input;
        switch (input) {
            case (111):
                wcout << L"1) Сложить векторы a и b" << endl
                      << L"2) Вычесть b из a" << endl
                      << L"3) Умножить вектор а на число " << endl
                      << L"4) Скалярное произведение a и b" << endl
                      << L"5) Векторное произведение a и b" << endl
                      << L"0) Закончить исполнение команд" << endl;
                break;
            case (222):
                wcout << L"6) Смешаное произведение a, b и с" << endl
                      << L"7) Проверить a > b" << endl
                      << L"8) Проверить a < b" << endl
                      << L"9) Проверить a = b" << endl
                      << L"10) Найти угол между a и b" << endl
                      << L"0) Закончить исполнение команд" << endl;
                break;
            case (333):
                wcout << L"11) Найти длину вектора a" << endl
                      << L"12) Нормировать вектор a" << endl
                      << L"13) Колинеарны ли a и b" << endl
                      << L"14) Компланарны ли a, b и с" << endl
                      << L"0) Закончить исполнение команд" << endl;
                break;
            case (1):
                if (num == 1) {WrongInput; break;}
                temp = a + b;
                wcout << "life";
                wcout << "a + b = " << temp << endl;
                break;
            case (2):
                if (num == 1) {WrongInput; break;}
                temp = a - b;
                wcout << "a - b = " << temp << endl;
                break;
            case (3):
                wcout << L"Введите множитель k" << endl;
                wcin >> k;
                temp = a * k;
                wcout << "a * k = " << temp << endl;
                break;
            case (4):
                if (num == 1) {WrongInput; break;}
                wcout << "(a,b) = " << a * b << endl;
                break;
            case (5):
                if (num == 1) {WrongInput; break;}
                temp = a.VecProd(b);
                wcout << "[a,b] = " << temp << endl;
                break;
            case (6):
                if (num != 3) {WrongInput; break;}
                wcout << "(a,b,c) = " << a.MixProd(b, c) << endl;
                break;
            case (7):
                if (num == 1) {WrongInput; break;}
                if (a > b) wcout << L"Да, a > b" << endl;
                else wcout << L"Нет, a не > b" << endl;
                break;
            case (8):
                if (num == 1) {WrongInput; break;}
                if (a < b) wcout << L"Да, a < b" << endl;
                else wcout << L"Нет, a не < b" << endl;
                break;
            case (9):
                if (num == 1) {WrongInput; break;}
                if (a == b) wcout << L"Да, a = b" << endl;
                else wcout << L"Нет, a не = b" << endl;
                break;
            case (10):
                if (num == 1) {WrongInput; break;}
                wcout << "(a ^ b) = " << a.Angle(b) << endl;
                break;
            case (11):
                wcout << "|a| = " << a.Len() << endl;
                break;
            case (12):
                temp = a.Norm();
                wcout << L"Нормальный вектор a = " << temp << endl;
                break;
            case (13):
                if (num == 1) {WrongInput; break;}
                if (a.Colinear(b)) wcout << L"a и b колинеарны" << endl;
                else wcout << L"a и b не колинеарны" << endl;
                break;
            case (14):
                if (num == 1) {WrongInput; break;}
                if (a.Complanar(b, c)) wcout << L"a, b, c компланарны" << endl;
                else wcout << L"a, b, c не компланарны" << endl;
                break;
            case (0):
                break;
            default:
                wcout << L"Для вывода 1, 2 и 3 листов команд напишите 111, 222 и 333" << endl;
                break;
        }
    }
    return 0;
}
