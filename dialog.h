#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "parcer.h"
#include <QObject>
#include <QPushButton>
#include <QMessageBox>
#include <QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent, vector< vector <string> > data, int K, Parcer P, QString path);
    void setFile();
    ~Dialog();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    vector< vector <string>> _data;
    Ui::Dialog *ui;
    int k;
    Parcer* parcer;
    QString path;
};

#endif // DIALOG_H
