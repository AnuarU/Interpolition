#include <algorithm.h>
#include <iomanip>
#include <math.h>
// Метод Гаусса для решения СЛАУ
double * gauss(double **a, double *y, int n, double eps)
{
    double *x, max;
    int k, index;
    x = new double[n];
    k = 0;
    while (k < n)
    {
        // Поиск строки с максимальным a[i][k]
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        // Перестановка строк
        if (max < eps)
        {
            // нет ненулевых диагональных элементов
            return nullptr;
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;
        // Нормализация уравнений
        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temp;
            y[i] = y[i] / temp;
            if (i == k)  continue; // уравнение не вычитать само из себя
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }
    // обратная подстановка
    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }
    return x;
}

void Interpolition(Point* p1, int &n, Point* &p2, int &m, int lenghtMatrix) //lenghtMatrix - тип интерполяции
{
    for (int i = 0; i < m; i++)
    {
        if (p2[i].x <= p1[0].x)//Если x меньше точки сетки x[0] - пользуемся первым эл-тов p1
        {
            p2[i].x = p1[0].x;
            p2[i].y = p1[0].y;
        }
        else if (p2[i].x >= p1[n - 1].x)//Если x больше точки сетки x[n - 1] - пользуемся последним эл-том p1
        {
            p2[i].x = p1[n - 1].x;
            p2[i].y = p1[n - 1].y;
        }
        else  // Иначе x лежит между граничными точками сетки - производим бинарный поиск нужного эл-та массива
        {
            int j = 0;
            int k = n - 1;
            while (j + 1 < k)
            {
                int l = j + (k - j) / 2;
                if (p2[i].x <= p1[l].x)
                {
                    k = l;
                }
                else
                {
                    j = l;
                }
            }

            //=====================================================================================
            // В этом месте можно добавить новый тип интерполяции

            double *y = new double[lenghtMatrix];  // вектор свободных коэффициентов
            double **a = new double*[lenghtMatrix];  //матрица значений
            if (k > n - (lenghtMatrix-1))  //проверяем если значение k около границы то взять последние lenghtMatrix элементы
                k = n - (lenghtMatrix-1);
            for (int t = 0; t < lenghtMatrix; t++)  //Заполняем матрицу коэффициентов при неизвестных
            {
                a[t] = new double[lenghtMatrix];

                for (int j = 0; j < lenghtMatrix; j++)
                {
                    a[t][j] = pow(p1[k - 1 + t].x, lenghtMatrix - 1 - j);
                }
                y[t] = p1[k - 1 + t].y;
            }
            double *b = gauss(a, y, lenghtMatrix, 0.0001);  // вычисляем неизвестные коэффициенты a, b, c, d, ... с помощью метода Гаусса
            if(b != nullptr)
            {
                p2[i].y = 0;
                for (int j = 0; j < lenghtMatrix; j++)
                {
                    p2[i].y += b[j] * pow(p2[i].x, lenghtMatrix - 1 - j);   //вычисляем промежуточное значение y
                }
                for (int t = 0; t < lenghtMatrix; t++)
                {
                    delete[] a[t];
                }
            }
            delete[] a;
            delete[] y;
            delete[] b;

            //=====================================================================================
        }
    }
}
