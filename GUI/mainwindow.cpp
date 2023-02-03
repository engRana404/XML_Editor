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
#include <QInputDialog>
#include <unordered_map>

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
#include "Search_post.h"
#include "JSON2XML.h"
#include "JSON_Formatter.h"+



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_2->hide();
    ui->label_3->hide();
    ui->input->hide();
    ui->input->setText("");
    ui->OutputText->setReadOnly(false);
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
    ui->OutputText->setPlainText(text);
   // ui->OutputText->setLineWrapMode(NoWrap);
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
    ui->label_3->hide();
    ui->input->hide();
    ui->input->setText("");
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
   ui->input->setText(text);
   //Turn into std string
   string textToBeFormatted =text.toStdString();
   vector<int> Result= CompressXML(textToBeFormatted);
   QString str;
       for(auto c:Result)
           str.append(QString:: fromStdString(to_string(c)));

       QString fileName = QFileDialog::getSaveFileName(this,
                                                       tr("Save Address Book"), "",
                                                       tr("COMP (*.comp);;All Files ()"));
       QFile newDoc(fileName);
       if(newDoc.open(QIODevice::WriteOnly)) {
           QTextStream out(&newDoc);
           out<<str;
           newDoc.flush();
       }
     newDoc.close();


   //Show
   ui->OutputText->setPlainText(str);

}


void MainWindow::on_decompress_clicked(){
    QString text = ui->input->text();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    vector<int> Resint=CompressXML(textToBeFormatted);

    string Result=DecompressXML(Resint);

    QString OutString = QString::fromStdString(Result);
    //Show
    ui->OutputText->setPlainText(OutString);
}


//Turn XML into JSON
void MainWindow::on_JSON_clicked(){
    QString text = ui->OutputText->toPlainText();
    ui->input->setText(text);
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
//Turn JSON into XML
void MainWindow::on_JS_clicked(){
    /* QString text =ui->OutputText->toPlainText();
    //Turn into std string
     string textToBeFormatted =text.toStdString();
     string result= JSON2XML(textToBeFormatted);*/
     //QString OutString = QString::fromStdString(result);
    //Show
    ui->OutputText->setPlainText(ui->input->text());
}

void MainWindow::on_JSONformat_clicked(){
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    string result=json_formatter(textToBeFormatted);
    ui->OutputText->setPlainText(QString::fromStdString(result));

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
    QDir::setCurrent(".\\");

     system("dot -Tpng -O a.dot");
     ui->label_2->show();
     QPixmap mypix(".\\a.dot.png");
     ui->label_2->setPixmap(mypix);

     QMessageBox msgBox;
     msgBox.setText("Your file is at"+ QDir::currentPath());
     msgBox.exec();

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
    //Turn tree
    xml2tree(root, XML ,i,root);
    //Traverse the tree
    vector <Node*>Travers =Traversal(root);
    //Get the adjacency list of the graph
    vector <vector <int>> GraphList =FollowerList(Travers);
    //Get in and out degree of the graph
    vector<int> indegree=inDegree(GraphList);
    vector<int> outdegree=outDegree(GraphList);

    int mostFollowed=maxdegree(indegree);
    int mostConnected=maxdegree(outdegree);

    ui->label_3->show();
    string s="";
    s=s+"The most Followed user is: "+to_string(mostFollowed);
    string n ="\n most connected user is : "+to_string(mostConnected);
    QString OutString = QString::fromStdString(s+n);
    ui->label_3->setText(OutString);

}

void MainWindow::on_Mutual_clicked(){
    QString text = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text.toStdString();
    //Put XML contents into a vector
    vector <string> XML= convert2vector(removeSpaces(textToBeFormatted));
    //Turn the vector into a tree
    Node * root = new Node();
    root->set_name(XML[1]);
    int i{2};
    //Turn tree
    xml2tree(root, XML ,i,root);
    //Traverse the tree
    vector <Node*>Travers =Traversal(root);
    //Get the adjacency list of the graph
    vector <vector <int>> GraphList =FollowerList(Travers);

    bool ok;
        qint8 text1 = QInputDialog::getInt(this, tr("Find Mutuals"), tr("Enter User1: "),0,-2147483647, 2147483647, 1, &ok);

        if (ok && text1){
            qint8 text2 = QInputDialog::QInputDialog::getInt(this, tr("Find Mutuals"), tr("Enter User2: "),0,-2147483647, 2147483647, 1, &ok);
            if(ok&&text2){
                string s=Mutual(text1,text2,GraphList);
                ui->label_3->show();
                //string result=to_string(s);

                 QString OutString = QString::fromStdString(s);
                ui->label_3->setText(OutString);}


        }
}

void MainWindow::on_search_clicked(){
    QString text0 = ui->OutputText->toPlainText();
    //Turn into std string
    string textToBeFormatted =text0.toStdString();
    vector <string> XML= convert2vector(removeSpaces(textToBeFormatted));
    string word;
    bool ok;
    QString text = QInputDialog::getText(this, tr("Search for Word"),
                                         tr("Enter the word: "), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty()){
        word=text.toStdString();
        string body = Search_Post(XML,word);
        QString OutString = QString::fromStdString(body);
        ui->label_3->show();
        ui->label_3->setText(OutString);


    }

}

