#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_clicked()
{
    this->close();
    return;
}

void MainWindow::on_log_clicked()
{
    QString user = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();
    if(user.size() == 0 && password.size() ==0)
    {
            QMessageBox::warning(this, QString(tr("警告")), QString(tr("这是警告对话框")), QMessageBox::Yes|QMessageBox::No);//此时设置父对象为this,软件关闭时就delete该对象
            return;
    }
    if(user == QString(tr("usename6")))
    {
        string debug = password.toStdString();
        if(password == QString(tr("123456")))
        {
            QMessageBox::information(this,"",tr("登录成功"));
            this->close();
            dialog = new class work(this);
            dialog->setModal(false);
            dialog->show();
        }
        else
            QMessageBox::warning(this, QString(tr("error")), QString(tr("the password is wrong!")), QMessageBox::Yes|QMessageBox::No);//此时设置父对象为this,软件关闭时就delete该对象
    }
    else
        QMessageBox::warning(this, QString(tr("warning")), QString(tr("the account is not exist")), QMessageBox::Yes|QMessageBox::No);//此时设置父对象为this,软件关闭时就delete该对象
}
