#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QLineEdit>
#include <QTableWidget>
#include "charger_csv.h"

class MaFenetre : public QMainWindow
{
    Q_OBJECT //Macro Obligatoire

public slots :
    void setQuitter();
    void predire();

private:
     QLabel *m_lab, *m_res, *label_prenom, *label_nom, *label_table, *label_predire;
     QPushButton *m_bou, *predict_button;
     QComboBox *m_com1, *m_com2, *m_com3;
     QLineEdit *m_nom,*m_prenom;
     QTableWidget *m_informations;

     CVString m_vet; // Vecteur d'entete
     CMatString m_mat;

public:
    MaFenetre(QWidget *parent = 0);
    void initComboBox(int i, QComboBox* m_box);
    int determinerFreq(string maladie);
    int determinerConf(string maladie);
};



#endif // MAFENETRE_H
