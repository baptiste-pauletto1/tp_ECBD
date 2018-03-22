#include "maFenetre.h"
#include <vector>


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
    label_predire->setGeometry(200,210,400,25);

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

    m_comFievre = new QComboBox(this);
    m_comFievre->move(225,150);

    this->initComboBox(0,m_comFievre);

    m_comDouleur = new QComboBox(this);
    m_comDouleur->move(350,150);

    this->initComboBox(1,m_comDouleur);

    m_comToux = new QComboBox(this);
    m_comToux->move(475,150);
    this->initComboBox(2,m_comToux);
}

void MaFenetre::initComboBox(int column,QComboBox* m_box){
    m_lab = new QLabel (m_vet[column].c_str(),this);
    m_lab->setFont(QFont("Verdana",12));
    QStringList tmp;
    tmp.append("NULL");
    for(unsigned i(0); i < m_mat.size();++i){
        tmp.append(m_mat[i][column].c_str());
    }
    tmp.removeDuplicates(); //On ote les doublons produits par le fichier csv
    m_box->addItems(tmp);
    m_lab->move(m_box->x()+10,m_box->y()-20);
}

void MaFenetre::predire() {

    //Test avec uniquement des NULL
    if(m_comDouleur->currentText().toStdString() == "NULL" && m_comFievre->currentText().toStdString() == "NULL" && m_comToux->currentText().toStdString() == "NULL"){
        label_predire->setText("La maladie est impossible a predire !");
        return;
    }

    QStringList maladies; // On init les maladies
    for (unsigned j = 0; j < m_mat.size(); j++)
        maladies.append(QString::fromUtf8((m_mat[j][3].c_str())));
    maladies.removeDuplicates(); //On supprime les doublons
    cout << maladies.at(0).toStdString() << maladies.at(1).toStdString() << maladies.at(2).toStdString() << maladies.at(3).toStdString() << maladies.at(4).toStdString() << endl;

    vector <float> scoresMaladies; // On init le vecteur des scores liés aux maladies.

    //Boucle qui calcule le score de chaque maladie récupérée juste avant (usage : param maladie avec determinerConf)
    for (int i = 0; i < maladies.size(); ++i){
        scoresMaladies.push_back(determinerConf(maladies.at(i).toStdString()));
    }

    float meilleurScore = 0;
    int indice = 0;
    for (unsigned i = 0; i < scoresMaladies.size() ; ++i){
        if (scoresMaladies[i] > meilleurScore){
            meilleurScore = scoresMaladies[i];
            indice = i;
        }
    }
    if (meilleurScore == 0){
        label_predire->setText("La maladie est impossible a predire !");
    } else {
        if(m_prenom->text() !="" && m_nom->text() !=""){
            label_predire->setText(m_prenom->text() + " " + m_nom->text() +" a " + maladies.at(indice) + "!");
        } else {
            label_predire->setText("Le patient a " + maladies.at(indice));
        }
    }

}

float MaFenetre::determinerConf(string maladie){ // Amélioration par ComboBox en paramètre qui serait utilisable

    float freqMaladie (0);
    float freqFievre (0);
    float freqToux (0);
    float freqDouleur (0);

    for(unsigned i (0);i<m_mat.size();i++){
        if(m_mat[i][3] == maladie)
            freqMaladie++;
    }

    if (m_comFievre->currentText().toStdString() != "NULL"){
        for (unsigned i = 0; i < m_mat.size(); i++){
                    if (m_mat[i][3] == maladie && m_mat[i][0] == m_comFievre->currentText().toStdString()){
                        freqFievre++;
               }
        }
        freqFievre = freqFievre/freqMaladie;
    } else {
        freqFievre = 1;
    }

    if (m_comDouleur->currentText().toStdString() != "NULL"){
        for (unsigned i = 0; i < m_mat.size(); i++){
                    if (m_mat[i][3] == maladie && m_mat[i][1] == m_comDouleur->currentText().toStdString()){
                        freqDouleur++;
               }
        }
        freqDouleur = freqDouleur/freqMaladie;
    } else {
        freqDouleur = 1;
    }

    if (m_comToux->currentText().toStdString() != "NULL"){
        for (unsigned i = 0; i < m_mat.size(); i++){
                    if (m_mat[i][3] == maladie && m_mat[i][2] == m_comToux->currentText().toStdString()){
                        freqToux++;
               }
        }
        freqToux = freqToux/freqMaladie;
    } else {
        freqToux = 1;
    }
    float scoreMaladie = freqFievre * freqDouleur * freqToux * (freqMaladie / m_mat.size());
    cout << "Verification du score de la maladie : " << maladie << scoreMaladie << endl;
    return (scoreMaladie);
}

void MaFenetre::setQuitter() {
    exit(0);
}

