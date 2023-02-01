#include "mainwindow.h"
#include "./ui_mainwindow.h"
//QT includes
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>

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
#include "Xml_Consistency.h"
#include "XmlGraph.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->hide();
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
    ui->label_2->hide();
    ui->OutputText->setPlainText("");
}

//Check the consistency
void MainWindow::on_check_clicked(){
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeChecked =text.toStdString();
   bool con=IsConsistent(convert2vector(removeSpaces(textToBeChecked)));
   if(con){
       QMessageBox msgBox;
       msgBox.setText("Your file has no problem.");
       msgBox.exec();
   }
   else{
       QMessageBox msgBox;
       msgBox.setText("The file has errors please use the Correct button to know what to do!");
       msgBox.exec();
   }
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
    string s="";

    for(const auto& elem :Result )

        {
            s=to_string(elem.first);
            Resultstr=Resultstr+"At line "+s+": we should use "+elem.second+"\n";
        }
    //return to QString
    QString OutString = QString::fromStdString(Resultstr);
    //Show
    ui->OutputText->setPlainText(OutString);
}

void MainWindow::on_compress_clicked(){
   QString text = ui->OutputText->toPlainText();
   //Turn into std string
   string textToBeFormatted =text.toStdString();
   vector<int> Result= CompressXML(textToBeFormatted);

   string Resultstr="";

   for(int i=0;i<Result.size();i++)
       {
           Resultstr=Resultstr+to_string(Result[i]);
       }
   QString OutString = QString::fromStdString(Resultstr);
   //Show
   ui->OutputText->setPlainText(OutString);

}


/*void MainWindow::on_decompress_clicked(){
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    vector<int> Resint;
    //int compress=stoi(textToBeFormatted);
    for(int i=0;i<textToBeFormatted.length();i++){
        Resint.push_back(int(textToBeFormatted[i])-48);
    }
    vector<string> Result=DecompressXML(Resint);
    string Resultstr="";

    for(int i=0;i<Result.size();i++)
        {
            Resultstr=Resultstr+Result[i];
        }
    QString OutString = QString::fromStdString(Resultstr);
    //Show
    ui->OutputText->setPlainText(OutString);
} */


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

void MainWindow::on_Graph_clicked(){
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    //Put XML contents into a vector
    vector <string> XML= convert2vector(removeSpaces(textToBeFormatted));
    //Turn the vector into a tree
    Node * root = new Node();
    root->set_name(XML[1]);
    int i{2};
    //Turn into tree
    xml2tree(root, XML ,i,root);
    //Traverse the tree
    vector <Node*>Travers =Traversal(root);
    //Get the adjacency list of the graph
    vector <vector <int>> GraphList =FollowerList(Travers);
    //Represent in in a file inorder to Visualize it later
     RepresentinFile(GraphList);
    //Turn the dot file into an image
    QDir::setCurrent("C:\\Program Files\\Graphviz\\bin");
    system("dot -Tpng -O C:\\Users\\pc\\Documents\\build-DSXMLL-Desktop_Qt_6_4_1_MinGW_64_bit-Debug\\a.dot");

     ui->label_2->show();
     QPixmap mypix("C:\\Users\\pc\\Documents\\build-DSXMLL-Desktop_Qt_6_4_1_MinGW_64_bit-Debug\\a.dot.png");
     ui->label_2->setPixmap(mypix);
}

void MainWindow::on_Analysis_clicked(){
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    //Put XML contents into a vector
    vector <string> XML= convert2vector(removeSpaces(textToBeFormatted));
    //Turn the vector into a tree
    Node * root = new Node();
    root->set_name(XML[1]);
    int i{2};
    //Turn into JSON and tree
    xml2tree(root, XML ,i,root);
    //Traverse the tree
    vector <Node*>Travers =Traversal(root);
    //Get the adjacency list of the graph
    vector <vector <int>> GraphList =FollowerList(Travers);
    //Get in and out degree of the graph
    vector<int> indegree=inDegree(GraphList);
    vector<int> outdegree=outDegree(GraphList);

    //int mostFollowed=distance(inDegree.begin(),std::max_element(inDegree.begin(), inDegree.end()));
    //int mostConnected=distance(outDegree.begin(),std::max_element(outDegree.begin(), outDegree.end()));

    ui->label_3->show();
    string s="The most Followed user is the user with id equal to: "+mostFollowed+"\n and the most connected user is user: "+mostConnected;
    QString OutString = QString::fromStdString(s);
    ui->label_3->setText(OutString);

}

