#include "maFenetre.h"


MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent) {
    setFixedSize(800,600);

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(600,200,80,40);

    predict_button = new QPushButton("Predire", this);
    predict_button->setGeometry(100,200,80,40);

    label_prenom = new QLabel ("Prenom : ",this);
    label_prenom->setFont(QFont("Arial", 12, QFont::Bold, true));
    label_prenom->move(500, 40);

    m_prenom = new QLineEdit("",this);
    m_prenom->setGeometry(600,40,180,30);

    label_nom = new QLabel ("Nom : ",this);
    label_nom->setFont(QFont("Arial", 12, QFont::Bold, true));
    label_nom->move(500, 80);

    m_nom = new QLineEdit("",this);
    m_nom->setGeometry(600,80,180,30);

    label_predire = new QLabel ("",this);
    label_predire->setFont(QFont("Arial", 12, QFont::Bold, true));
    label_predire->move(200, 200);
    label_predire->setGeometry(200,210,200,25);

    read_csv(m_mat,m_vet, "/home/p16005334/build-td_projet_ecbd-Desktop-Debug/data.csv");

    label_table = new QLabel ("Table d'apprentissage : ",this);
    label_table->setFont(QFont("Arial", 12, QFont::Normal, true));
    label_table->move(175, 325);
    label_table->setGeometry(175,310,200,25);

    m_informations = new QTableWidget(this);
    m_informations->setGeometry(175,350,450,200);
    m_informations->setRowCount(m_mat.size());
    m_informations->setColumnCount(m_vet.size());

    QStringList tableHeaderRow;
    for(unsigned i=0;i<m_vet.size();i++)
        tableHeaderRow.append(QString::fromUtf8(m_vet[i].c_str()));
    m_informations->setHorizontalHeaderLabels(tableHeaderRow);

    for(unsigned i=0;i<m_mat.size();i++){
        for(unsigned j=0;j<m_mat[i].size();j++){
            m_informations->setItem(i,j, new QTableWidgetItem(QString::fromUtf8((m_mat[i][j].c_str()))));
        }
    }

    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(predict_button, SIGNAL(clicked()), this, SLOT(predire()));

    m_com1 = new QComboBox(this);
    m_com1->move(225,150);

    this->initComboBox(0,m_com1);

    m_com2 = new QComboBox(this);
    m_com2->move(350,150);

    this->initComboBox(1,m_com2);

    m_com3 = new QComboBox(this);
    m_com3->move(475,150);
    this->initComboBox(2,m_com3);
}


void MaFenetre::initComboBox(int column,QComboBox* m_box){
    m_lab = new QLabel (m_vet[column].c_str(),this);
    m_lab->setFont(QFont("Verdana",12));
    QStringList tmp;
    tmp.append("NULL");
    for(unsigned i(0); i < m_mat.size();++i){
        tmp.append(m_mat[i][column].c_str());
    }
    tmp.removeDuplicates();
    m_box->addItems(tmp);
    m_lab->move(m_box->x()+10,m_box->y()-20);

}
void MaFenetre::setQuitter() {
    exit(0);
}

void MaFenetre::predire() {

    label_predire->setText(m_prenom->text() + " " + m_nom->text() +" a le cancer !");
}

int MaFenetre::determinerConf(string maladie) {
    return 0;
}

int MaFenetre::determinerFreq(string maladie) {
    return 0;
}
