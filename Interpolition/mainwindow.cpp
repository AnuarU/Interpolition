#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iNumInterp = 1;
    iNumGraph = 0;
    chart = new QChart();
    chartView = new QChartView(this);
    chartView->setGeometry(QRect(17, 15, 640, 480));
    chartView->setMinimumSize(640, 480);
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->show();
    chartView->setChart(chart);

    QWidget *widgVert = new QWidget(this);
    widgVert->setLayout(ui->verticalLayout);
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(chartView, 1, 0);
    mainLayout->addWidget(widgVert, 1, 1);
    mainLayout->setColumnStretch(1, 0);
    mainLayout->setColumnStretch(0, 1);
    ui->centralWidget->setLayout(mainLayout);
}
bool MainWindow::from_file_1(Point* &p, int &k, char *NameFile)
{
    bool b = false;
    int i = 0;
    std::fstream file(NameFile);
    if (!file)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","File not open!");
        messageBox.setFixedSize(500,200);
        return false;
    }
    else
    {
        while (!file.eof())
        {
            if (!b)
            {
                file >> k;
                p = new Point[k];
                b = true;
            }
            else
            {
                file >> p[i].x >> p[i].y;
                i++;
            }
        }
    }
    return true;
}
//==========================================================================
bool MainWindow::from_file_2(Point* &p, int &k, char *NameFile)
{
    bool b = false;
    int i = 0;
    std::ifstream file(NameFile);
    if (!file)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","File not open!");
        messageBox.setFixedSize(500,200);
        return false;
    }
    else
    {
        while (!file.eof())
        {
            if (!b)
            {
                file >> k;
                p = new Point[k];
                b = true;
            }
            else
            {
                file >> p[i].x;
                i++;
            }
        }
    }
    return true;
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int n = 0;
    int m = 0;
    Point *p1, *p2;

    if (!from_file_1(p1, n, "f1.txt")) return;  // Чтение файла f1 данных x и y в p1
    if (!from_file_2(p2, m, "f2.txt")) return;  // Чтение файла f2 данных x для которых необходимо найти y

    if (((iNumInterp == 3) && (n < 4)) || ((iNumInterp == 2) && (n < 3)) || ((iNumInterp == 1) && (n < 2))) // Для кубической интерполяции необходимо минимум 4 точки,
    {																								  //для квадратной - 3 точки, для линейной - 2 точки
        QMessageBox messageBox;
        messageBox.critical(0,"Error","An error has occured !");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        /*std::for_each(chart->series().begin(), chart->series().end(), [&](QAbstractSeries* ser){
            if(ser != nullptr)
            if(ser[0].objectName().toInt() == iNumInterp) return false;
        });*/

        for(auto ser : chart->series())
        {
            if(ser->objectName().toInt() == iNumInterp) return;
        }

        Interpolition(p1, n, p2, m, iNumInterp - 1 + 2);  //интерполяция

        QLineSeries *series = new QLineSeries();
        series->setName("Line " + QString::number(++iNumGraph));
        series->setObjectName(QString::number(iNumInterp));
        for(int i = 0; i < m; i++)
        {
            series->append(p2[i].x, p2[i].y);
        }
        for(int i = 0; i < n; i++)
        {
            series->append(p1[i].x, p1[i].y);
        }
        QVector<QPointF> points = series->pointsVector();
        std::sort(points.begin(), points.end(), [](const QPointF & qp1, const QPointF & qp2) {
            return qp1.x() > qp2.x();
        });
        series->replace(points);

        chart->legend()->hide();

        chart->addSeries(series);
        chart->createDefaultAxes();
        //chart->setTitle("Interpolation graph");
        chart->setAnimationOptions(QChart::AllAnimations);
        chart->legend()->setVisible(true);  //Надписи legend


        QValueAxis *axisX = (QValueAxis*)chart->axisX();
        axisX->setTitleText("x");

        QValueAxis *axisY = (QValueAxis*)chart->axisY();
        axisY->setTitleText("y");
    }
}

void MainWindow::on_radioButton_clicked()
{
    iNumInterp = 1;
}

void MainWindow::on_radioButton_2_clicked()
{
    iNumInterp = 2;
}

void MainWindow::on_radioButton_3_clicked()
{
    iNumInterp = 3;
}

void MainWindow::on_pushButton_2_clicked()
{

}
