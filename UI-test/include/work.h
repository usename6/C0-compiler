#ifndef WORK_H
#define WORK_H
#include <QDialog>
namespace Ui {
class work;
}
class work : public QDialog
{
    Q_OBJECT
public:
    explicit work(QWidget *parent = 0);
    ~work();
private slots:
    void on_pushButton_2_clicked();
private slots:
    void on_pushButton_clicked();
private:
    Ui::work *ui;
};
#endif // WORK_H
