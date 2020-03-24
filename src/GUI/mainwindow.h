#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <fstream>
#include <vector>
#include "run_lib.h"
#include <qpainter.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace  std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void add_addr(const char* s);

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_fileButton_clicked();

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int x1, y1, x2, y2, type=0;
    std::string inputAddr;
    std::ifstream inFile;
    std::ofstream tempFile;
    std::ofstream outFile;
    std::vector<string> vs;
    int deletId;
    run_lib rl;
    const char * outaddr;
};
#endif // MAINWINDOW_H
