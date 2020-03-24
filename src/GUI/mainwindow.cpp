#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "run_lib.h"
#include <string>
#include <qdir.h>
#include <QPainter>

const int xoff = 761/2;
const int yoff = 200;

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    x1 = arg1.toInt();
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    y1 = arg1.toInt();
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    x2 = arg1.toInt();
}

void MainWindow::on_lineEdit_4_textChanged(const QString &arg1)
{
    y2 = arg1.toInt();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    type = index;
}

void MainWindow::on_lineEdit_5_textChanged(const QString &arg1)
{
    inputAddr = arg1.toStdString();
}

void myDrawLine(QPainter &p,int  x1,int  y1, int  x2, int y2){
    p.drawLine(x1 + xoff, -y1 + yoff, x2 + xoff, -y2 + yoff);
}

void myDrawCircle(QPainter &p, int x, int y, int r) {
    p.drawEllipse(x-r + xoff, -(y - r) + yoff, x + r + xoff, -(y + r) + yoff);
}

void MainWindow::on_pushButton_2_clicked()
{

    tempFile.open("temp.txt");
    tempFile << vs.size() <<endl;
    for(int i = 0; i< (int)vs.size();i++) tempFile << vs.at(i) <<endl;
    tempFile.close();
    string s("-i");
    const char *s2[5];
    s2[1] = s.c_str();
    string s3("temp.txt");
    s2[2] = s3.c_str();
    string s4("-o");
    s2[3] = s4.c_str();
    s2[4] = outaddr;
    rl.run3(5,(char **)s2);

    inFile.open("points.txt");
    string buf;
    string text;
    while(getline(inFile, buf)) {
        text += buf+"\n";
    }
    inFile.close();
    ui->textBrowser->setText(text.c_str());
    QPainter painter(ui->openGLWidget);
    painter.setPen(QPen(Qt::white,1));
    painter.drawLine(xoff, -100000, xoff, 100000);
    painter.drawLine(-100000, yoff, 100000, yoff);
    vector<string> inString;
    for(int i = 0; i < (int)vs.size();i++) {
        split(vs[i],inString, ' ');
        switch (inString[0][0]) {
        case 'C': myDrawCircle(painter, stoi(inString[1]), stoi(inString[2]), stoi(inString[3]));
            break;
        case 'S': myDrawLine(painter, stoi(inString[1]), stoi(inString[2]), stoi(inString[3]),stoi(inString[4]));
            break;
        case 'L': {
            int x1 = stoi(inString[1]);
            int y1 = stoi(inString[2]);
            int x2 = stoi(inString[3]);
            int y2 = stoi(inString[4]);
            if(x1 == x2) {
                myDrawLine(painter, x1, 200, x2, -200);
            } else {
                double k = ((double)y2- y1)/ ((double)x2-x1);
                double b = (double)y1 - (double)k * (double)x1;
                double yr = xoff * k + b;
                double yl = -xoff * k + b;
                myDrawLine(painter,-xoff, yl, xoff, yr);

            }
            break;
        }
        case 'R': {
            int x1 = stoi(inString[1]);
            int y1 = stoi(inString[2]);
            int x2 = stoi(inString[3]);
            int y2 = stoi(inString[4]);
            if(x1 == x2) {
                if(y1 > y2) {
                    myDrawLine(painter, x1, y1, x2, -200);
                } else {
                    myDrawLine(painter, x1, y1, x2, 200);
                }
            } else {
                double k = ((double)y2- y1)/ ((double)x2-x1);
                double b = (double)y1 - (double)k * (double)x1;
                double yr = xoff * k + b;
                double yl = -xoff * k + b;
                double x1in, x2in, y1in, y2in;
                x1in = x1;
                x2in = x1;
                y1in = y1;
                y2in = y1;
                int vx = x2 - x1;
                int vy = y2 - y1;
                if (vx * xoff + vy * yr > 0) {
                    x1in = xoff;
                    y1in = yr;
                }
                if(vx * -xoff + vy * yl > 0) {
                    x2in = -xoff;
                    y2in = yl;
                }
                myDrawLine(painter, x1in, y1in, x2in, y2in);
            }
            break;
        }
        }
    }
}

void MainWindow::on_fileButton_clicked()
{
    vs.clear();
    string buff;
    inFile.open(inputAddr);
    getline(inFile, buff);
    while(getline(inFile, buff)) {
        vs.push_back(string(buff));
    }
}

void MainWindow::on_lineEdit_6_textChanged(const QString &arg1)
{
    deletId = arg1.toInt();
}

void MainWindow::on_pushButton_3_clicked()
{
    vs.erase(vs.begin()+deletId);
}

void MainWindow::on_pushButton_clicked()
{
    string s;
    switch(type) {
    case 0: s = *new string("L " + to_string(x1) + " " + to_string(y1) + " " + to_string(x2) + " " + to_string(y2));
        break;
    case 1: s =  *new string("S " + to_string(x1) + " " + to_string(y1) + " " + to_string(x2) + " " + to_string(y2));
        break;
    case 2: s =  *new string("R " + to_string(x1) + " " + to_string(y1) + " " + to_string(x2) + " " + to_string(y2));
        break;
    case 3: s =  *new string("C " + to_string(x1) + " " + to_string(y1) + " " + to_string(x2));
        break;
    }
    vs.push_back(s);
}

void MainWindow::add_addr(const char *s) {
    outaddr = s;
}

