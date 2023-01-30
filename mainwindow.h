#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <sstream>
#include <QtDebug>
#include <QProcess>
#include<QMessageBox>
#include<QTextEdit>
#include <QFile>
#include <QAction>
#include <bits/stdc++.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    //void on_checkbutton_clicked();
    //void on_CompressionButton_clicked();
    void on_Save_clicked();
    void on_Clear_clicked();
    void on_format_clicked();
    void on_Browse_clicked();
    void on_minify_clicked();
   void on_JSON_clicked();
   void on_correct_clicked();
   void on_check_clicked();
  // void on_Graph_clicked();
   void on_decompress_clicked();
   void on_compress_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
