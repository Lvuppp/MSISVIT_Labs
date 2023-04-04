#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "variable.h"
#include<QFileDialog>
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


void MainWindow::on_pushButton_clicked()
{
    auto str = ui->plainTextEdit->toPlainText().toStdString();

    Parser pars(std::move(str));

    ui->variables->clear();
    ui->functions->clear();

    map<string,int> operators = pars.getOperators();
    map<string,int> operations = pars.getOperations();
    int i=0,j=0, amountOfOperations = 0, amountOfOperators = 0;


    for(auto v = operators.begin(); v != operators.end(); v++){
        ui->variables->addItem(QString::number(++i) + QString::fromStdString(") " + v->first)+ " count: " + QString::number(v->second));
        amountOfOperators += v->second;
    }

    qDebug() << amountOfOperators;
    for(auto v = operations.begin(); v != operations.end(); v++){
        ui->functions->addItem(QString::number(++j) + QString::fromStdString(") " + v->first)+ " count: " + QString::number(v->second));
        amountOfOperations += v->second;
    }

    qDebug() << amountOfOperations;

    ui->label_3->setText("Словарь программы: " + QString::number(i + j));
    ui->label_4->setText("Длинна программы: " + QString::number(amountOfOperations + amountOfOperators));
    ui->label_5->setText("Объём программы: " + QString::number((amountOfOperations + amountOfOperators) * log2(i + j)));
//    for(auto v : pars.getBranches()){
//        ui->branches->addItem("Branch pos:"+QString::number(v.first) + " " + ",branch deep: "+ QString::number(v.second) + "\n");
//    }


}


void MainWindow::on_pushButton_2_clicked()
{
    QString currentText;
    auto fileName=QFileDialog::getOpenFileName(0,"Выберите файл");
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);

        currentText.clear();

        string line;
        while(!stream.atEnd()){
            line=stream.readLine().toStdString();
            currentText+=QString::fromStdString(line);
            currentText+='\n';
        }
    }

    else{
        qDebug()<<"file not opened";
    }

    file.close();

    ui->plainTextEdit->setPlainText(currentText);
}

