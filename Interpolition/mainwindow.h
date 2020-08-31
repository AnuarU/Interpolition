#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "algorithm.h"
#include <QtCharts/QtCharts>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int iNumInterp;
    int iNumGraph;

    QChart *chart;      // Создаём представление графика
    QChartView *chartView;
    QGridLayout *mainLayout;

    explicit MainWindow(QWidget *parent = nullptr);
    bool from_file_1(Point* &p, int &k, char *NameFile);
    bool from_file_2(Point* &p, int &k, char *NameFile);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
