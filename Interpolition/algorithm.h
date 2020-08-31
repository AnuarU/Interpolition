#ifndef ALGORITHM_H
#define ALGORITHM_H
struct Point
{
    double x;
    double y;
};
double * gauss(double **a, double *y, int n, double eps);
void Interpolition(Point* p1, int &n, Point* &p2, int &m, int lenghtMatrix); //lenghtMatrix - тип интерполяции
#endif // ALGORITHM_H
