#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

enum type { v, sk, pl };

struct mountain {
    char country[50];
    char name[50];
    int height;
    type tip;
};

const int SIZE = 20;


void printall(void (*func)(mountain arr[], int), mountain arr[], int size) {
    func(arr, size);
    for (int i = 0; i < size; i++) {
        const char* typeName = "";
        if (arr[i].tip == v) typeName = "Вулканическая";
        else if (arr[i].tip == sk) typeName = "Складчатая";
        else if (arr[i].tip == pl) typeName = "Платообразная";

        cout << arr[i].name << " (Страна: " << arr[i].country
            << ", Высота: " << arr[i].height
            << "м, Тип: " << typeName << ")" << endl;
    }
}

void sort(mountain arr[], int size) {
    for (int a = 0; a < size - 1; a++) {
        for (int b = size - 1; b > a; b--) {
            if (arr[b - 1].height < arr[b].height) {
                mountain t = arr[b - 1]; 
                arr[b - 1] = arr[b];
                arr[b] = t;
            }
        }
    }
}

void update(mountain arr[], int size, const char targetName[]) {
    for (int i = 0; i < size; i++) {
        if (!strcmp(arr[i].name, targetName)) {
            cout << "Вершина " << targetName << " найдена. Введите новую высоту: ";
            cin >> arr[i].height;
            cout << "Данные успешно обновлены!\n";
            return;
        }
    }
    cout << "Вершина с названием " << targetName << " не найдена.\n";
}
void read(mountain arr[], int size)
{
    ifstream fin;
    char name[50]; int height;
    fin.open("mountain.txt"); 
        if (fin.is_open()) {
            while (!fin.eof())
            {
                fin.getline(name,50,'-');
                fin >> height;
                fin.ignore();
                cout << name << height;
                for (int i = 0; i < size; i++){
                    if (!strcmp(arr[i].name, name)) {
                        arr[i].height = height;
                        break;
                    }
                }
            }
        }
    fin.close();
}
void write_bin(mountain arr[],int size)
{
    setlocale(LC_ALL, "");
    
    ofstream out("mountain_bin.txt",
        ios::binary | ios::out);
    for (unsigned i = 0; i < size; i++) {
        out.write((char*)&arr[i], sizeof(arr[i]));
        
    }
    out.close();
}
void read_bin(mountain arr[], int size)
{
    {
        
       fstream in("mountain_bin.txt",ios::binary | ios::in);
       for (int i = 0; i < size; i++) {
           in.read((char*)&arr[i], sizeof(arr[i]));
            
       }
        in.close(); 
            
    }

}

int main() {
    setlocale(LC_ALL, "Russian");
    mountain mountains[SIZE] = {
        { "Russia", "Elbrus", 5642, v },
        { "France", "Mont Blanc", 4808, sk },
        { "Tanzania", "Kilimanjaro", 5895, v },
        { "Argentina", "Aconcagua", 6962, sk },
        { "USA", "Denali", 6190, pl },
        { "Switzerland", "Matterhorn", 4478, sk },
        { "Ukraine", "Hoverla", 2061, sk },
        { "Australia", "Kosciuszko", 2228, pl },
        { "Japan", "Fuji", 3776, v },
        { "Ecuador", "Chimborazo", 6263, v },
        { "Tajikistan", "Ismoil Somoni", 7495, sk },
        { "Kyrgyzstan", "Lenin Peak", 7134, sk },
        { "Nepal", "Kangchenjunga", 8586, sk },
        { "China", "Lhotse", 8516, sk },
        { "Nepal", "Makalu", 8485, sk },
        { "Nepal", "Everest", 8848, sk },
        { "Pakistan", "K2", 8611, sk },
        { "Nepal", "Cho Oyu", 8188, sk },
        { "USA", "Mauna Kea", 4207, v },
        { "Kenya", "Mount Kenya", 5199, v }
    };
    double sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += mountains[i].height;
    }
    cout << "--- 1. Средняя высота вершин ---" << endl;
    cout << "Средняя высота: " << sum / SIZE << " метров\n\n";
    cout << "--- 2. Отсортированный список (по убыванию высоты) ---" << endl;
    printall(sort, mountains,SIZE);
    cout << "\n";
    cout << "--- 3. Страны местонахождения 4-х восьмитысячников ---" << endl;
    int count8k = 0;
    for (int i = 0; i < SIZE; i++) {
        if (mountains[i].height >= 8000) {
            cout << ++count8k << ". Страна: " << mountains[i].country << " (Вершина: " << mountains[i].name <<" ("<< mountains[i].height<< "))" << endl;
            if (count8k == 4) break;
        }
    }
    cout << "\n";
    cout << "--- 4. Изменение данных ---" << endl;
    char s[50];
    cout << "Введите название вершины для изменения ";
    cin >> s;
    update(mountains, SIZE, s);
    cout << "\n";
    printall(sort, mountains, SIZE);
    cout << "\n";
    cout << "--- 5. Поиск вершин по стране ---" << endl;
    char target[50];
    cout << "Введите страну для поиска ";
    cin >> target;
    mountain fMountains[SIZE];
    int fCount = 0;
    for (int i = 0; i < SIZE; i++) {
        if


            (!strcmp(mountains[i].country, target)) {
            fMountains[fCount] = mountains[i];
            fCount++;
        }
    }
    if (fCount > 0) {
        cout << "Найдены следующие вершины в стране " << target << ":" << endl;
        printall(sort,fMountains, fCount);
    }
    else {
        cout << "В стране " << target << " вершин не найдено.\n";
    }
    cout << "--- 6. Чтение из текстового файла ---" << endl;
    printall(read, mountains, SIZE);
    cout << "--- 7. Чтение/запись в бинарный файл ---" << endl;
    write_bin(mountains, SIZE);
    mountain mountains_new[SIZE];
    printall(read_bin,mountains_new, SIZE);
    return 0;
}
