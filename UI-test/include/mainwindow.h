#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QString>
#include "work.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_exit_clicked();
    void on_log_clicked();
private:
    Ui::MainWindow *ui;
    work *dialog;
};
#endif // MAINWINDOW_H
