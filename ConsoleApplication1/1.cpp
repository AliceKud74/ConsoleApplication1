#include <iostream>
#include <cmath>
#include <algorithm> 
#include <Windows.h>
using namespace std;



class d_2vector {
protected:
    double i;
    double j;
public:
    static double max_length; 

    virtual double length() {
        return i * i + j * j; 
    }

    d_2vector(double i_in = 0, double j_in = 0) {
        i = i_in;
        j = j_in;
        max_length = max(sqrt(this->length()), max_length);
    }

    virtual void info() {
        cout << "(" << i << ", " << j << ") [Длина: " << sqrt(length()) << "]";
    }

    bool operator==(const d_2vector& other) const {
        return (i == other.i && j == other.j);
    }

    friend ostream& operator<<(ostream& os, d_2vector& v) {
        v.info();
        return os;
    }
};
double d_2vector::max_length = 0;

class d_3vector : public d_2vector {
    double k;
public:
    double length()  {
        return i * i + j * j + k * k;
    }

    d_3vector(double i_in = 0, double j_in = 0, double k_in = 0) : d_2vector(i_in, j_in) {
        k = k_in;
 
        max_length = max(sqrt(this->length()), max_length);
    }

    void info()  {
        cout << "(" << i << ", " << j << ", " << k << ") [Длина: " << sqrt(length()) << "]";
    }

    bool operator==(const d_3vector& other) const {
        return (i == other.i && j == other.j && k == other.k);
    }

    friend ostream& operator<<(ostream& os, d_3vector& v) {
        v.info();
        return os;
    }
};




template <typename T>
class array_adt {
private:
    int cnt;  
    T* arr;  
public:
    array_adt(int size=0, const T* initial_arr={}) {
        cnt = size;
        if (cnt > 0 && initial_arr != nullptr) {
            arr = new T[cnt];
            for (int i = 0; i < cnt; i++) {
                arr[i] = initial_arr[i];
            }
        }
        else {
            arr = nullptr;
        }
    }
    ~array_adt() {
        delete[] arr;
    }
    array_adt(const array_adt& other) {
        cnt = other.cnt;
        if (cnt > 0) {
            arr = new T[cnt];
            for (int i = 0; i < cnt; i++) {
                arr[i] = other.arr[i];
            }
        }
        else {
            arr = nullptr;
        }
    }

   
    array_adt& operator=(const array_adt& other) {
        if (this == &other) return *this;

        delete[] arr; 

        cnt = other.cnt;
        if (cnt > 0) {
            arr = new T[cnt];
            for (int i = 0; i < cnt; i++) {
                arr[i] = other.arr[i];
            }
        }
        else {
            arr = nullptr;
        }
        return *this;
    }

    void add(T item) {
        T* temp = new T[cnt + 1];
        for (int i = 0; i < cnt; i++) {
            temp[i] = arr[i];
        }
        temp[cnt] = item;

        delete[] arr;
        arr = temp;
        cnt++;
    }

    T& operator[](int index) {
        if (index < 0 || index >= cnt) {
            throw out_of_range("Индекс за пределами массива!");
        }
        return arr[index];
    }

    bool operator==(const array_adt& other) const {
        if (cnt != other.cnt) return false;
        for (int i = 0; i < cnt; i++) {
            if (!(arr[i] == other.arr[i])) return false;
        }
        return true;
    }

  
    bool operator!=(const array_adt& other) const {
        return !(*this == other);
    }

    void info_arr() {
        cout << "{ \n";
        for (int c = 0; c < cnt; c++) {
            cout << "  [" << c << "]: " << arr[c] << "\n";
        }
        cout << "}\n";
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << "=== РАБОТА С МАССИВОМ ЦЕЛЫХ ЧИСЕЛ ===" << endl;
    array_adt<int> int_arr;
    int_arr.add(10);
    int_arr.add(20);
    int_arr.add(30);

    cout << "Массив чисел: ";
    int_arr.info_arr();

    cout << "Элемент по индексу [1]: " << int_arr[1] << endl;
    int_arr[1] = 50; 
    cout << "После изменения [1] на 50: " << int_arr[1] << endl;
    int source[] = { 10,50,30 };
    array_adt<int> int_arr2(3, source);
    cout << "Массив 1 == Массив 2? " << (int_arr == int_arr2 ? "Да" : "Нет") << endl;
    int_arr2.add(99);
    cout << "Массив 1 != Массив 2 (после изменения)? " << (int_arr != int_arr2 ? "Да" : "Нет") << endl;

    cout << endl;

   
    cout << "=== РАБОТА С МАССИВОМ ВЕКТОРОВ ===" << endl;

    array_adt<d_2vector> vec2d_arr;
    vec2d_arr.add(d_2vector(3, 4));   
    vec2d_arr.add(d_2vector(1, 1));   

    cout << "Массив 2D векторов:" << endl;
    vec2d_arr.info_arr();

    array_adt<d_3vector> vec3d_arr;
    vec3d_arr.add(d_3vector(0, 0, 0));
    vec3d_arr.add(d_3vector(2, 3, 6)); 

    cout << "Массив 3D векторов:" << endl;
    vec3d_arr.info_arr();

    
    cout << "Максимальная длина среди всех созданных векторов: " << d_2vector::max_length << endl;

    return 0;
}
