#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(int type,QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::Dialog *ui;
    QSqlRelationalTableModel *tablemodel;        //数据库模型
};

#endif // DIALOG_H
