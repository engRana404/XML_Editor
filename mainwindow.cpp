#include "mainwindow.h"
#include "./ui_mainwindow.h"
//QT includes
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QTextStream>
#include <QDir>
//For better graphics
#include <QGraphicsScene>
#include <QGraphicsView>
//Our PRoject files includes
#include "XmlToVector.h"
#include "Formatting.h"
#include "XML_Minifier.h"
#include "XmlToTree.h"
#include "CorrectErr.h"
#include "XmlToJson.h"
#include "Extras.h"
#include "Compression.h"



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

QFile mytempfile("out.txt");
QFile myfile("myfile.txt");
QString text = "";
QString s="";

//Open External File
void MainWindow::on_Browse_clicked()
{
    //ui->InputText->clear();
    ui->OutputText->clear();

    QFile input_file(QFileDialog::getOpenFileName(this,tr("Open File"),"",tr("XML File (*.xml) ;;TextFile (*.txt)")));
    s=input_file.fileName();
    input_file.open(QIODevice::ReadOnly |QIODevice::Text);
    QTextStream stream(&input_file);
    text= stream.readAll();
    myfile.remove();
    mytempfile.resize(0);
    input_file.copy("myfile.txt");
    QFile myfile("myfile.txt");
    //ui->InputText->setPlainText(text);
    //ui->InputText->setLineWrapMode(NoWrap);
    ui->OutputText->setPlainText(text);
    //ui->OutputText->setLineWrapMode(NoWrap);
    input_file.close();
}

//Save Finished File
void MainWindow::on_Save_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Address Book"), "",
                                                    tr("XML (*.xml);;TEXT (*.txt;;JSON (*.json))"));
    QFile output_file(fileName);
    output_file.open(QIODevice::ReadWrite|QIODevice::Text);
    QString text=ui->OutputText->toPlainText();
    output_file.write(text.toUtf8());
    output_file.close();
}

void MainWindow::on_Clear_clicked(){
    ui->OutputText->setPlainText("");
    //ui->InputText->setPlainText("");
}

//Formating File
void MainWindow::on_format_clicked(){
    //Get text from user
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    //Format the text
    string Result=formatting(removeSpaces(textToBeFormatted));
    //return to QString
    QString OutString = QString::fromStdString(Result);
    //Show
    ui->OutputText->setPlainText(OutString);
}

//Minifying File
void MainWindow::on_minify_clicked(){
    //Get text from user
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    //minify the text
    string Result=xml_minifier(removeSpaces(textToBeFormatted));
    //return to QString
    QString OutString = QString::fromStdString(Result);
    //Show
    ui->OutputText->setPlainText(OutString);
}

//Correct Errors
void MainWindow::on_correct_clicked(){
    //Get text from user
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    //Correct Errors
    map<int, string> Result= CorrectErr(convert2vector(removeSpaces(textToBeFormatted)));

    string Resultstr="";

    for(const auto& elem :Result )
        {
            Resultstr=Resultstr+elem.second;
        }
    //return to QString
    QString OutString = QString::fromStdString(Resultstr);
    //Show
    ui->OutputText->setPlainText(OutString);
}

//Turn into JSON
void MainWindow::on_JSON_clicked(){
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    vector <string> Result= convert2vector(removeSpaces(textToBeFormatted));
    Node * root = new Node();
    root->set_name(Result[1]);
    int i{2};
    //Turn into JSON and tree
    xml2tree(root, Result ,i,root);
    vector <string> JSON;
    xmlToJson(root, JSON);

    QString OutString = QString::fromStdString(VectorToString(JSON));
    //Show
    ui->OutputText->setPlainText(OutString);
}

/*//void on_Graph_clicked(){}
//void on_decompress_clicked(){}
void MainWindow::on_compress_clicked(){
   QString text = ui->OutputText->toPlainText();
   //Turn into std string
   string textToBeFormatted =text.toStdString();
   vector<string> Result= CompressXML(textToBeFormatted);

   string Resultstr="";

   for(int i=0;i<Result.size();i++)
       {
           Resultstr=Resultstr+Result[i];
       }
   QString OutString = QString::fromStdString(Resultstr);
   //Show
   ui->OutputText->setPlainText(OutString);

}
*/
