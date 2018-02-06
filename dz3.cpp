#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

struct Matrix
{
    int** matrix=nullptr;
    int a;
    int b;
};

bool Create_matrix(Matrix &matrix, int argc, char* argv[])
{
    int k = 2;
    int i;
    string x,y;
    for (i = 0; (argv[1][i] != 'x') && (argv[1][i] != 'X'); i++)
        x += argv[1][i];
    for (i += 1; i < strlen(argv[1]); i++)
        y += argv[1][i];
    matrix.a = atoi(x.c_str());
    matrix.b = atoi(y.c_str());
    if (matrix.a == 0 || matrix.b == 0)
    {
        cout << "Неверный размер матрицы, повторите ввод" << endl;
        return false;
    }
    matrix.matrix = new int*[matrix.a];
    for (i = 0; i < matrix.a; i++)
        matrix.matrix[i] = new int[matrix.b];
    for (i = 0; i < matrix.a; i++)
        for (int j = 0; j < matrix.b; j++)
            matrix.matrix[i][j] = 0;
    for (i = 0; i < matrix.a; i++)
        for (int j = 0; j < matrix.b; j++, k++) {
            if (k < argc)
                matrix.matrix[i][j] = atoi(argv[k]);
        }
    return true;
}

void Menu()
{
    cout << endl;
    cout << "Выберете одну из операций:" << endl
         << endl;
    cout << "1. Вывести матрицу" << endl;
    cout << "2. Сложить матрицу" << endl;
    cout << "3. Умножить матрицу" << endl;
    cout << "4. Транспонировать матрицу" << endl;
    cout << "5. Сохранить в файл" << endl;
    cout << "6. Загрузить из файла" << endl;
    cout << "7. Сортировать матрицу " << endl;
    cout << "8. Завершить работу программы" << endl
         << endl;
}

void Show_matrix(Matrix matrix)
{
    for (int i = 0; i < matrix.a; i++) {
        for (int j = 0; j < matrix.b; j++)
            cout << setw(4) << matrix.matrix[i][j];
        cout << endl;
    }
}

void Add_matrix(Matrix &matrix)
{
    int count;
    cout << "Введите матрицу " << matrix.a << "x" << matrix.b << endl;
    for (int i = 0; i < matrix.a; i++)
        for (int j = 0; j < matrix.b; j++) {
            cin >> count;
            matrix.matrix[i][j] = matrix.matrix[i][j] + count;
        }
    cout << endl
         << "Результат:" << endl
         << endl;
    for (int i = 0; i < matrix.a; i++) {
        for (int j = 0; j < matrix.b; j++)
            cout << setw(4) << matrix.matrix[i][j];
        cout << endl;
    }
}

void Multiplication_matrix(Matrix &matrix)
{
    int i, n, m;
    string x;
    string str1,str2;
    cout << "Введите размер матрицы:" << endl
         << endl;
    cin >> x;
    for (i = 0; (x[i] != 'x') && (x[i] != 'X'); i++)
        str1 += x[i];
    for (i += 1; i < x.length(); i++)
        str2 += x[i];
    n = atoi(str1.c_str());
    m = atoi(str2.c_str());
    if (matrix.b == n) {
        cout << endl;
        cout << "Введите элементы матрицы:" << endl
             << endl;
        int** subsidiary_matrix;
        subsidiary_matrix = new int*[matrix.a];
        for (i = 0; i < n; i++)
            subsidiary_matrix[i] = new int[m];
        for (i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> subsidiary_matrix[i][j];
        int** final_matrix;
        final_matrix = new int*[matrix.a];
        for (i = 0; i < matrix.a; i++)
            final_matrix[i] = new int[m];
        for (i = 0; i < matrix.a; i++)
            for (int j = 0; j < m; j++)
                final_matrix[i][j] = 0;
        for (i = 0; i < matrix.a; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < n; k++)
                    final_matrix[i][j] += matrix.matrix[i][k] * subsidiary_matrix[k][j];
        cout << "Результат:" << endl
             << endl;
        matrix.b = m;
        for (i = 0; i < n; i++)
            delete[] subsidiary_matrix[i];
        delete[] subsidiary_matrix;
        for (i = 0; i < matrix.a; i++)
            delete[] matrix.matrix[i];
        delete[] matrix.matrix;
        matrix.matrix = final_matrix;
        Show_matrix(matrix);
    }
    else
        cout << "Неверный размер";
}

void Transpose_matrix(Matrix &matrix)
{
    int** subsidiary_matrix = nullptr;
    subsidiary_matrix = new int*[matrix.b];
    for (int i = 0; i < matrix.b; i++)
        subsidiary_matrix[i] = new int[matrix.a];
    for (int i = 0; i < matrix.b; i++)
        for (int j = 0; j < matrix.a; j++)
            subsidiary_matrix[i][j] = matrix.matrix[j][i];
    for (int i = 0; i < matrix.a; i++)
        delete[] matrix.matrix[i];
    delete[] matrix.matrix;
    matrix.matrix = subsidiary_matrix;
    swap(matrix.a, matrix.b);
}

void Save_in_file(Matrix matrix)
{
    ofstream fout("file.txt");
    fout << setw(4) << matrix.a << " " << setw(4) << matrix.b << "\r\n";
    for (int i = 0; i < matrix.a; i++) {
        for (int j = 0; j < matrix.b; j++)
            fout << setw(4) << matrix.matrix[i][j];
        fout << "\r\n";
    }
    fout.close();
}

void Load_from_file(Matrix &matrix)
{
    ifstream fin("file.txt");
    if (fin.is_open()) {
        fin >> matrix.a >> matrix.b;
        matrix.matrix = new int*[matrix.a];
        for (int i = 0; i < matrix.a; i++)
            matrix.matrix[i] = new int[matrix.b];
        for (int i = 0; i < matrix.a; i++)
            for (int j = 0; j < matrix.b; j++)
                fin >> matrix.matrix[i][j];
        fin.close();
    }
    else
        cout << "Файл не найден";
}

void Sorting_matrix(Matrix &matrix) {
    int k = 0;
    int i, j;
    cout << endl << "Введите порядок сортировки:" << endl << endl;
    cout << "1.Сортировка змейкой" << endl;
    cout << "2.Сортировка улиткой" << endl;
    cout << "3.Сортировка муравейчиком" << endl;
    int *array = new int[matrix.a * matrix.b];
    for (i = 0; i < matrix.a; i++)
        for (j = 0; j < matrix.b; j++, k++)
            array[k] = matrix.matrix[i][j];
    for (i = 0; i < matrix.a * matrix.b; i++)
        for (j = 0; j < matrix.a * matrix.b; j++)
            if (array[i] < array[j])
                swap(array[i], array[j]);
    int choise;
    cin >> choise;
    switch (choise) {
        case 1:
        {
            i=j=0;
            for( k=0; k < matrix.a*matrix.b; k++)
                switch(j%2)
                {
                    case 0:
                    {
                        matrix.matrix[i][j]=array[k];
                        if(i!=matrix.a-1)
                            i++;
                        else
                            j++;
                        break;
                    }
                    case 1:
                    {
                        matrix.matrix[i][j]=array[k];
                        if(i!=0)
                            i--;
                        else
                            j++;
                        break;
                    }
                }
            Show_matrix(matrix);
            break;
        }
        case 2:
        {
            i=j=0;
            int t=0;
            for( k=0; k < matrix.a*matrix.b; k++) {
                if (i == t && j != matrix.b - 1 - t) {
                    matrix.matrix[i][j] = array[k];
                    j++;
                    continue;
                }
                if (i == t && j == matrix.b - 1 - t) {
                    matrix.matrix[i][j] = array[k];
                    i++;
                    continue;
                }
                if (j == matrix.b - 1 - t && i != matrix.a - 1 - t) {
                    matrix.matrix[i][j] = array[k];
                    i++;
                    continue;
                }
                if (j == matrix.b - 1 - t && i == matrix.a - 1 - t) {
                    matrix.matrix[i][j] = array[k];
                    j--;
                    continue;
                }
                if (i == matrix.a - 1 - t && j != t) {
                    matrix.matrix[i][j] = array[k];
                    j--;
                    continue;
                }
                if (i == matrix.a - 1 - t && j == t) {
                    matrix.matrix[i][j] = array[k];
                    i--;
                    continue;
                }
                if (j == t && i != t + 1) {
                    matrix.matrix[i][j] = array[k];
                    i--;
                    continue;
                }
                if (j == t && i == t + 1) {
                    matrix.matrix[i][j] = array[k];
                    j++;
                    t++;
                    continue;
                }
            }
            Show_matrix(matrix);
            break;
        }
        case 3:
        {
            k = 0;
                for (i = 0; i < matrix.a; i++)
                    for (j = 0; j < matrix.b; j++, k++)
                        matrix.matrix[i][j] = array[k];
            Show_matrix(matrix);
            break;
        }
        default:
            return;
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "RUS");
    Matrix matrix;
    if (argc == 1) {
        cout << "Матрица пустая" << endl;
        return 0;
    }
    bool a = Create_matrix(matrix, argc, argv);
    if (!a)
        return 0;
    int choise;
    while (true) {
        Menu();
        cin >> choise;
        switch (choise) {
            case 1:
                Show_matrix(matrix);
                break;
            case 2:
                Add_matrix(matrix);
                break;
            case 3:
                Multiplication_matrix(matrix);
                break;
            case 4:
                Transpose_matrix(matrix);
                break;
            case 5:
                Save_in_file(matrix);
                break;
            case 6:
                Load_from_file(matrix);
                break;
            case 7:
                Sorting_matrix(matrix);
                break;
            case 8:
                delete[] matrix.matrix;
                return 0;
            default:
                cout << "Неверная команда" << endl;
        }
    }
}
