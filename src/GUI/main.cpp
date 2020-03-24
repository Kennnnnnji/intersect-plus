#include "mainwindow.h"
#include <QApplication>
#include "stdio.h"
#include "run_lib.h"
//.lib文件中仅仅是关于其对应DLL文件中函数的定位信息


using namespace std;


int main(int argc, char *argv[])
{
    run_lib rl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    rl.run3(argc,(char**)argv);
    w.add_addr(argv[5]/*"out.txt"*/);
    return a.exec();
}
