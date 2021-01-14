#include "work.h"
#include "ui_work.h"
#include "main.h"
#include <QMessageBox>
string inputfile;
string outputfile;
work::work(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::work)
{
    ui->setupUi(this);
}

work::~work()
{
    delete ui;
}

void work::on_pushButton_clicked()
{
    this->close();
    return;
}

void work::on_pushButton_2_clicked()
{
    QString input = ui->lineEdit->text();
    QString output = ui->lineEdit_2->text();
    string inputfile = input.toStdString();
    string outputfile = output.toStdString();
    start(inputfile,outputfile);
    QMessageBox::information(this,"",tr("compile finsh"));
}
