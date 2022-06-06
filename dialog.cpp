#include "dialog.h"

#include "ui_dialog.h"
#include <QObject>
#include <QPushButton>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent, vector< vector <string> > d, int K, Parcer Par, QString _path): QDialog(parent), ui(new Ui::Dialog){

        ui->setupUi(this);
        _data = d;
        k = K;
        parcer = &Par;
        path = _path;

        ui->tableWidget->setColumnCount(_data[0].size());
        ui->tableWidget->setRowCount(_data.size());

        for(int i = 0; i < _data.size(); i++) {
            for(int j = 0; j < _data[0].size(); j++) {
                ui-> tableWidget ->setItem(i, j, new QTableWidgetItem(QString::fromStdString(_data[i][j])));

            }
        }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_buttonBox_accepted()
{

   for(int i = 0; i < _data.size(); i++) {
        for(int j = 0; j < _data[0].size(); j++) {
            _data[i][j] = ui->tableWidget->item(i, j)->text().toStdString();
        }
    }

   switch (k){
       case 0: {
           std::ofstream fout(path.toStdString() + "/Caffe-and-cinema.csv");
           for (size_t i = 0; i < _data.size(); i++) {
               for (size_t j = 0; j < _data[i].size(); j++ ) {
                   fout << _data[i][j] <<  (j + 1 == _data[i].size() ? "\n" : ",");
               }
           }
       }
       case 1: {
            std::ofstream fout(path.toStdString() + "/Institute.csv");
            for ( size_t i = 0; i < _data.size(); i++) {
                for (size_t j = 0; j < _data[i].size(); j++) {
                    fout << _data[i][j] << (j + 1 == _data[i].size() ? "\n" : ",");
                }
            }
       }
       case 2:{
           std::ofstream fout(path.toStdString() + "/Costs.csv");
           for ( size_t i = 0; i < _data.size(); i++) {
               for (size_t j = 0; j < _data[i].size(); j++) {
                   fout << _data[i][j] << (j + 1 == _data[i].size() ? "\n" : ",");
               }
           }
       }
       case 3:{
           std::ofstream fout(path.toStdString() + "/Transport.csv");
           for ( size_t i = 0; i < _data.size(); i++) {
               for (size_t j = 0; j < _data[i].size(); j++) {
                   fout << _data[i][j] << (j + 1 == _data[i].size() ? "\n" : ",");
               }
           }
       }
   }

}


void Dialog::on_buttonBox_rejected()
{
    close();
}

