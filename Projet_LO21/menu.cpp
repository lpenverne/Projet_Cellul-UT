#include <menu.h>
#include <vector>
#include "automatePerso.h"
#include <QDebug>
#include <random>
// Constructeur
/**
 * \brief initialisation de la bibliothèque
 */
int step=0;
Biblio& b = Biblio::getInstance();
//TabVoisinage tv;	//initialisation du tableau de voisinages (vide au départ)
//TabFtransit tf;		//initialisation du tableau de fonctions de transistion (vide au depart)

/**
 * \brief constructeur de fenetrebase pour que les classes héritent du slot menu
 */
fenetreBase::fenetreBase(QWidget* parent):QWidget(parent)
{
    QPushButton *ok = new QPushButton("&Ok");
    QPushButton *menu = new QPushButton("&Menu");
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(previous()));
}

/**
 * \brief slot menu : permet de revenir au menu en partant de n'importe quelle fenetre du programme
 */
void fenetreBase::menu(){
    class menu *m= new class menu();
    m->show();
    this->hide();
}

/**
 * \brief constructeur de fenetrebase : on donne plusieurs possibilitées à l'utilisateur : charger un automate en créer un ou créer des fonctions de transitions et des voisinnages
 */
menu::menu(QWidget* parent):QWidget(parent)
{
    personalise = new QRadioButton("Automate personnalisé");
    predefini = new QRadioButton("Automate prédéfini");
    chargepredefini = new QRadioButton("Charger un automate");
    transition = new QRadioButton("Créer une fonction de transition");
    voisinnage = new QRadioButton("Créer un voisinnage");
    ok = new QPushButton("&Fin");
    couche=new QVBoxLayout;
    couche->addWidget(personalise);
    couche->addWidget(chargepredefini);
    couche->addWidget(transition);
    couche->addWidget(voisinnage);
    couche->addWidget(predefini);
    couche->addWidget(ok);
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(predefini,SIGNAL(clicked()),this,SLOT(Openpredefini()));
    QObject::connect(voisinnage, SIGNAL(clicked()), this, SLOT(Nouveau_Voisinnage()));
    connect(chargepredefini,SIGNAL(clicked()),this,SLOT(chargerpredefini()));
    connect(personalise,SIGNAL(clicked()),this,SLOT(Openpersonalise()));
    connect(transition,SIGNAL(clicked()),this,SLOT(Openpersonalise()));
    setLayout(couche);
    if (step==0)
        enregistrerpredef();
    step++;
}

/**
 * \brief Enregistre les automates prédéfinis la première fois qu'on va sur le menu (grace a step)
 */
void menu::enregistrerpredef(){
    std::string nom="Moore 1";
    b.getTabVoisinage()->ajouterUnVoisinage(nom, true, 1);			//ajout du voisinage dans le tableau de voisinage
    Regle** r=new Regle*[10];
    int nb_regles=0;
    r[nb_regles] = new Regle(0,1,3,1);
    nb_regles++;
    r[nb_regles] = new Regle(1,0,0,1);
    nb_regles++;
    r[nb_regles] = new Regle(1,0,1,1);
    nb_regles++;
    r[nb_regles] = new Regle(1,0,4,1);
    nb_regles++;
    r[nb_regles] = new Regle(1,0,5,1);
    nb_regles++;
    r[nb_regles] = new Regle(1,0,6,1);
    nb_regles++;
    r[nb_regles] = new Regle(1,0,7,1);
    nb_regles++;
    r[nb_regles] = new Regle(1,0,8,1);
    nb_regles++;
    nom="Life";
    b.getTabFtransit()->ajouterUneFtransit(nom, 2, r, nb_regles);
    delete [] r;
    nb_regles=0;
    Regle** k=new Regle*[10];
    k[nb_regles] = new Regle(2,1,3,0);
    nb_regles++;
    k[nb_regles] = new Regle(1,0,3,0);
    nb_regles++;
    k[nb_regles] = new Regle(0,2,2,2);
    nb_regles++;
    nom="BB";
    b.getTabFtransit()->ajouterUneFtransit(nom, 3, k, nb_regles);
    delete [] k;
    Regle** w = new Regle*[4];
    w[1] = new Regle(1, 2, 1, 0);
    w[2] = new Regle(2, 3, 1, 0);
    w[3] = new Regle(3, 1, 1, 1);
    w[4] = new Regle(3, 1, 2, 1);
    nom="Wire World";
    b.getTabFtransit()->ajouterUneFtransit(nom, 4, w, 4);
    delete [] k;
    Regle** g = new Regle*[24];

    g[0] = new Regle(0, 1, 3, 1);
    g[1] = new Regle(0, 1, 4, 1);
    g[2] = new Regle(0, 1, 5, 1);
    g[3] = new Regle(0, 1, 6, 1);
    g[4] = new Regle(0, 1, 7, 1);
    g[5] = new Regle(0, 1, 8, 1);

    g[6] = new Regle(1, 2, 3, 2);
    g[7] = new Regle(1, 2, 4, 2);
    g[8] = new Regle(1, 2, 5, 2);
    g[9] = new Regle(1, 2, 6, 2);
    g[10] = new Regle(1, 2, 7, 2);
    g[11] = new Regle(1, 2, 8, 2);

    g[12] = new Regle(2, 3, 3, 3);
    g[13] = new Regle(2, 3, 4, 3);
    g[14] = new Regle(2, 3, 5, 3);
    g[15] = new Regle(2, 3, 6, 3);
    g[16] = new Regle(2, 3, 7, 3);
    g[17] = new Regle(2, 3, 8, 3);

    g[18] = new Regle(3, 0, 3, 0);
    g[19] = new Regle(3, 0, 4, 0);
    g[20] = new Regle(3, 0, 5, 0);
    g[21] = new Regle(3, 0, 6, 0);
    g[22] = new Regle(3, 0, 7, 0);
    g[23] = new Regle(3, 0, 8, 0);
    nom="Griffeath";
    b.getTabFtransit()->ajouterUneFtransit(nom, 4, g, 24);
    delete [] g;
}

/**
 * \brief Ouvre directement l'interface de personnalisation de voisinnage
 */
void menu::Nouveau_Voisinnage(){
    class PersonnalisationVoisinnage *p= new class PersonnalisationVoisinnage(nullptr, 2);
    p->show();
    this->hide();
}

/**
 * \brief Ouvre le début d'une personnalisation d'automate
 */
void menu::chargerpredefini()
{
    class PersonalisationnbEtats *p= new class PersonalisationnbEtats();
    p->show();
    this->hide();
}

PersonalisationnbEtats::PersonalisationnbEtats(QWidget* parent):fenetreBase(parent){
    NumEtats=new QLabel("Nombre d'états possibles");
    nbEtats=new QSpinBox;
    nbEtats->setRange(2,10);
    nbEtats->setValue(3);
    LayoutNum=new QHBoxLayout;
    LayoutNum->addWidget(NumEtats);
    LayoutNum->addWidget(nbEtats);
    QPushButton *ok = new QPushButton("&Fin");
    QPushButton *menu = new QPushButton("&Menu");
    valider = new QPushButton("&Valider");
    couche=new QVBoxLayout;
    couche->addLayout(LayoutNum);
    couche->addWidget(valider);
    couche->addWidget(ok);
    couche->addWidget(menu);
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(charger_automate()));
    setLayout(couche);
}

/**
 * \brief Ouvre le choix de voisinnage et de transition d'un voisinnage
 */
void PersonalisationnbEtats::charger_automate()
{
    class PersonalisationDimensions *p= new class PersonalisationDimensions(nullptr,nbEtats->value());
    p->show();
    this->hide();
}

/**
 * \brief Ouvre le début d'une personnalisation d'automate
 */
void menu::Openpersonalise()
{
    class PersonnalisationEtats *p= new class PersonnalisationEtats();
    p->show();
    this->hide();
}

/**
 * \brief Ouvre le choix des 4 automates implémentés
 */
void menu::Openpredefini()
{
    class predefini *p= new class predefini();
    p->show();
    this->hide();
}

/**
 * \brief constructeur de Personalisation etats : première étape de création d'une transition : on renseigne le nom et le nombre d'états possibles
 */
PersonnalisationEtats::PersonnalisationEtats(QWidget* parent):fenetreBase(parent)
{
    nb=3;
    nom="";
    Label_2=new QLabel("Nom de la configuration :");
    Nom=new QLineEdit();
    connect(Nom,SIGNAL(textChanged(QString )),this,SLOT(changer_nom(QString )));
    LayoutNom=new QHBoxLayout;
    LayoutNom->addWidget(Label_2);
    LayoutNom->addWidget(Nom);

    Label_1=new QLabel("Interface de personnalisation");
    NumEtats=new QLabel("Nombre d'états possibles");
    nbEtats=new QSpinBox;
    nbEtats->setRange(2,10);
    nbEtats->setValue(3);
    QObject::connect(nbEtats, SIGNAL(valueChanged(int)), this, SLOT(changer(int)));
    LayoutNum=new QHBoxLayout;
    LayoutNum->addWidget(NumEtats);
    LayoutNum->addWidget(nbEtats);
    QPushButton *ok = new QPushButton("&Fin");
    QPushButton *menu = new QPushButton("&Menu");
    valider = new QPushButton("&Valider");
    couche=new QVBoxLayout;
    couche->addWidget(Label_1);
    couche->addLayout(LayoutNom);
    couche->addLayout(LayoutNum);
    couche->addWidget(valider);
    couche->addWidget(ok);
    couche->addWidget(menu);
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(validation()));
    setLayout(couche);
}

/**
 * \brief On ouvre la personnalisation de la transition avec en paramètres le nom et le nombre d'états possibles
 */
void PersonnalisationEtats::validation(){
    class PersonnalisationTransition *p= new class PersonnalisationTransition(nullptr,nb, nom);
    p->show();
    this->hide();
}

/**
 * \brief change le nombre d'états possibles
 */
void PersonnalisationEtats::changer(int i){
    nb=i;
}

/**
 * \brief change le nom de la transition
 */
void PersonnalisationEtats::changer_nom(QString name){
    nom=name;
}

/**
 * \brief constructeur de Transition : l'utilisateur renseigne une regle et valide puis, une fois toutes les règles renséignées on passe au voisinnage
 */
PersonnalisationTransition::PersonnalisationTransition(QWidget* parent, int nombre, QString name) :fenetreBase(parent)
{
    nb_etats=nombre;
    nom=name;
    Etatdep=new QLabel("Etat de départ de la cellule");
    nbEtatdep=new QSpinBox;
    nbEtatdep->setRange(0,nombre-1);
    nbEtatdep->setValue(0);
    Etatarr=new QLabel("Etat d'arrivée de la cellule");
    nbEtatsarr=new QSpinBox;
    nbEtatsarr->setRange(0,nombre-1);
    nbEtatsarr->setValue(1);
    Layout1_1=new QHBoxLayout;
    Layout1_1->addWidget(Etatdep);
    Layout1_1->addWidget(nbEtatdep);
    Layout1_1->addWidget(Etatarr);
    Layout1_1->addWidget(nbEtatsarr);
    Etatvois=new QLabel("Etat des voisins  à prendre en compte");
    Etatsvoisp=new QSpinBox;
    Etatsvoisp->setRange(0,nombre-1);
    Etatsvoisp->setValue(0);
    nbEtatsvois=new QLabel("Nombre de voisins nécessaires au déclenchement de la transition");
    nbEtatsvoisp=new QSpinBox;
    nbEtatsvoisp->setRange(0,100);
    nbEtatsvoisp->setValue(1);
    Layout1_2=new QHBoxLayout;
    Layout1_2->addWidget(Etatvois);
    Layout1_2->addWidget(Etatsvoisp);
    Layout1_2->addWidget(nbEtatsvois);
    Layout1_2->addWidget(nbEtatsvoisp);

    Layout1=new QVBoxLayout;
    Layout1->addLayout(Layout1_1);
    Layout1->addLayout(Layout1_2);

    valider=new QPushButton("Valider et passer à une nouvelle règle");
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(ajoutRegle()));

    next=new QPushButton("Passer au voisinnage (APRES AVOIR VALIDER UNE REGLE!!)");
    QObject::connect(next, SIGNAL(clicked()), this, SLOT(passageTransition()));

    horizontalLayout_3 = new QHBoxLayout;
    horizontalLayout_3->addWidget(valider);
    horizontalLayout_3->addWidget(next);

    QPushButton *ok = new QPushButton("&Fin");
    QPushButton *menu = new QPushButton("&Menu");
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));

    couche=new QVBoxLayout;
    couche->addLayout(Layout1);
    couche->addLayout(horizontalLayout_3);
    couche->addWidget(ok);
    couche->addWidget(menu);
    setLayout(couche);
    r=new Regle*[max];
}

/**
 * \brief Enregistre une nouvelle Fonction de transition avec le nom, le nombre d'états et les règles s'appliquant. Puis ouvre la personnalisation du Voisinnage
 */
void PersonnalisationTransition::passageTransition()
{
    b.getTabFtransit()->ajouterUneFtransit(nom.toStdString(), nb_etats, r, nb_regles);
    class PersonnalisationVoisinnage *p= new class PersonnalisationVoisinnage(nullptr, nb_etats);
    p->show();
    this->hide();
}

/**
 * \brief Ajoute une règle au tableau new_tab
 */
void PersonnalisationTransition::ajoutRegle()
{
    if(nb_regles==max){
        max +=5 ;
        Regle** new_tab = new Regle*[max];
        for(int i=0; i<nb_regles; i++)
            new_tab[i] = r[i];
        Regle** old_tab = r;
        r = new_tab;
        delete[] old_tab;
    }
    r[nb_regles] = new Regle(nbEtatdep->value(), nbEtatsarr->value(), nbEtatsvoisp->value(), Etatsvoisp->value());
    nb_regles++;
}

/**
 * \brief constructeur de Personnalisation Voisinnage : choix du rayon d'action et de la prise en compte des diagonales ou non et du nom du voisinnage
 */
PersonnalisationVoisinnage::PersonnalisationVoisinnage(QWidget* parent, int nb_e):fenetreBase(parent){

    nb_etats=nb_e;
    Nom=new QLabel("Nom de la configuration de voisinnage :");
    NomV=new QLineEdit();
    horizontalLayout_3=new QHBoxLayout;
    horizontalLayout_3->addWidget(Nom);
    horizontalLayout_3->addWidget(NomV);

    Rayon=new QLabel("Rayon du voisinnage");
    Rayonnum=new QSpinBox();
    Rayonnum->setRange(1,1000);
    Rayonnum->setValue(1);
    horizontalLayout_1=new QHBoxLayout();
    horizontalLayout_1->addWidget(Rayon);
    horizontalLayout_1->addWidget(Rayonnum);

    Diago=new QLabel("Cocher pour activer les diagonales");
    bDiago=new QRadioButton();
    connect(bDiago,SIGNAL(clicked()),this,SLOT(changer_diago()));
    horizontalLayout_2=new QHBoxLayout();
    horizontalLayout_2->addWidget(Diago);
    horizontalLayout_2->addWidget(bDiago);


    valider=new QPushButton("Valider et passer à la prochaine étape");
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(validation()));

    QPushButton *ok = new QPushButton("&Fin");
    QPushButton *menu = new QPushButton("&Menu");
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));

    couche=new QVBoxLayout;
    couche->addLayout(horizontalLayout_3);
    couche->addLayout(horizontalLayout_1);
    couche->addLayout(horizontalLayout_2);
    couche->addWidget(valider);
    couche->addWidget(ok);
    couche->addWidget(menu);
    setLayout(couche);

};

/**
 * \brief Enregistre la prise en compte des diagonales
 */
void PersonnalisationVoisinnage::changer_diago()
{
    diag=true;
}

/**
 * \brief Créé un nouveau voisinnage et envoie vers la personnalisation des dimensions
 */
void PersonnalisationVoisinnage::validation()
{
    b.getTabVoisinage()->ajouterUnVoisinage(NomV->text().toStdString(), diag, Rayonnum->value());			//ajout du voisinage dans le tableau de voisinage
    class PersonalisationDimensions *p= new class PersonalisationDimensions(nullptr,nb_etats);
    p->show();
    this->hide();
}

/**
 * \brief constructeur Personalisation Dimensions : choix de la largeur, de la longueur et de la prise en compte du tore
 */
PersonalisationDimensions::PersonalisationDimensions(QWidget* parent, int nb_e):fenetreBase(parent){
    nb_etats=nb_e;
    verticalLayout_3= new QVBoxLayout;
    horizontalLayout_5 = new QHBoxLayout;
    horizontalLayout_6 = new QHBoxLayout;
    label_8=new QLabel(("Grille"));
    label_9=new QLabel(("Nombre de cellules par lignes : "));
    cellsPerLine=new QSpinBox;
    cellsPerLine->setRange(0,10000);
    cellsPerLine->setValue(20);

    label_10=new QLabel(("Nombre de cellules par colonnes : "));
    cellsPerColumn=new QSpinBox;
    cellsPerColumn->setRange(0,10000);
    cellsPerColumn->setValue(20);
    horizontalLayout_5->addWidget(label_9);
    horizontalLayout_5->addWidget(cellsPerLine);

    horizontalLayout_6->addWidget(label_10);
    horizontalLayout_6->addWidget(cellsPerColumn);

    verticalLayout_3->addWidget(label_8);
    verticalLayout_3->addLayout(horizontalLayout_5);
    verticalLayout_3->addLayout(horizontalLayout_6);

    Limite=new QLabel("Cocher pour activer les limites");
    bLimite=new QRadioButton();
    connect(bLimite,SIGNAL(clicked()),this,SLOT(changerlimites()));
    horizontalLayout_2=new QHBoxLayout();
    horizontalLayout_2->addWidget(Limite);
    horizontalLayout_2->addWidget(bLimite);

    next=new QPushButton("Passer à l'étape suivante");
    horizontalLayout_3 = new QHBoxLayout;
    horizontalLayout_3->addWidget(next);
    QObject::connect(next, SIGNAL(clicked()), this, SLOT(PersoFini()));

    horizontalLayout_4 = new QHBoxLayout;
    menu = new QPushButton("&Menu");
    ok = new QPushButton("&Fin");
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));
    horizontalLayout_4->addWidget(menu);
    horizontalLayout_4->addWidget(ok);


    couche= new QVBoxLayout();
    couche->addLayout(verticalLayout_3);
    couche->addLayout(horizontalLayout_3);
    couche->addLayout(horizontalLayout_4);
    setLayout(couche);
}

/**
 * \brief Change la prise en compte du tore
 */
void PersonalisationDimensions::changerlimites(){
    limitebis=true;
}

/**
 * \brief Ouvre l'interface de choix final où l'on choisit Fonction de transition et Voissinage et l'on nomme l'automate
 */
void PersonalisationDimensions::PersoFini(){
    class PersoFinition *p= new class PersoFinition(nullptr, cellsPerLine->value(),cellsPerColumn->value(), nb_etats, limitebis);
    p->show();
    this->hide();
}

/**
 * \brief Interface de choix final où l'on choisit Fonction de transition et Voissinage et l'on nomme l'automate
 */
PersoFinition::PersoFinition(QWidget* parent,int l, int h, int nb_e, bool limites) : fenetreBase(parent){
    longueur=l;
    largeur=h;
    nb_etats=nb_e;
    priselimites=limites;

    NomAutomate=new QLabel("Donnez un nom à l'automate :");
    nom=new QLineEdit;
    horizontalLayout_1=new QHBoxLayout;
    horizontalLayout_1->addWidget(NomAutomate);
    horizontalLayout_1->addWidget(nom);

    Vois= new QLabel("Selectionnez la fonction de Voisinnage :");
    nomvois=new QComboBox;
    for(int i=0; i<b.getTabVoisinage()->getNbVoisinages(); i++){
        QString nom=QString::fromStdString(b.getTabVoisinage()->getVoisinage(i).getNomV());
        nomvois->insertItem(i, nom);
    }
    horizontalLayout_2= new QHBoxLayout;
    horizontalLayout_2->addWidget(Vois);
    horizontalLayout_2->addWidget(nomvois);

    Ftrans= new QLabel("Selectionnez la fonction de Transition :");
    nomFtrans=new QComboBox;
    for(int i=0; i<b.getTabFtransit()->getNbFtransit(); i++){
        if(b.getTabFtransit()->getFtransit(i).getNbEtatsF() == nb_etats){
            //affichage des f du tableau de f correspondant au nombre d'états possibles sélectionné
            QString nom=QString::fromStdString(b.getTabFtransit()->getFtransit(i).getNomF());
            nomFtrans->insertItem(i, nom);
        }
    }
    horizontalLayout_3= new QHBoxLayout;
    horizontalLayout_3->addWidget(Ftrans);
    horizontalLayout_3->addWidget(nomFtrans);

    valider=new QPushButton("Valider");
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(passerAautomate()));

    horizontalLayout_4 = new QHBoxLayout;
    menu = new QPushButton("&Menu");
    ok = new QPushButton("&Fin");
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));
    horizontalLayout_4->addWidget(menu);
    horizontalLayout_4->addWidget(ok);

    couche=new QVBoxLayout;
    couche->addLayout(horizontalLayout_1);
    couche->addLayout(horizontalLayout_2);
    couche->addLayout(horizontalLayout_3);
    couche->addWidget(valider);
    couche->addLayout(horizontalLayout_4);
    setLayout(couche);
}

/**
 * \brief passage à l'automate
 */
void PersoFinition::passerAautomate(){
    class Personnalise *p= new class Personnalise(nullptr, longueur,largeur, nomvois->currentIndex(),
                                                  nomFtrans->currentIndex(), nom->text().toStdString(),
                                                  priselimites,nb_etats);
    p->show();
    this->hide();
}

/**
 * \brief constructeur de l'automate personnalisé avec des états aléatoires pour chaque cellules
 */
Personnalise::Personnalise(QWidget* parent, int l,int h, int indexV, int indexF, std::string nom, bool limites, int nb_e):fenetreBase(parent){
    longueur=l;
    largeur=h;
    step=true;
    nb_etats=nb_e;
    int taille=25;
    bool lance=false;
    iV=indexV;
    iF=indexF;
    nomAuto=nom;
    lim=limites;
    couche=new QVBoxLayout;
    etats=new QTableWidget(longueur,largeur);
    etats->setFixedSize(1.56*longueur*taille,largeur*taille);
    etats->horizontalHeader()->setVisible(false);
    etats->verticalHeader()->setVisible(false);
    etats->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    etats->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int i=0;i<longueur;i++)//Initialisation de la grille
    {
        etats->setColumnWidth(i,taille);
        etats->setRowHeight(i,taille);
        for (int j=0;j<largeur;j++)
        {
            etats->setItem(i,j, new QTableWidgetItem(""));
            int r=rand()%nb_etats;
            switch (r) {
            case 0:
                etats->item(i,j)->setBackground(Qt::black);
                break;
            case 1:
                etats->item(i,j)->setBackground(Qt::white);
                break;
            case 2:
                etats->item(i,j)->setBackground(Qt::blue);
                break;
            case 3:
                etats->item(i,j)->setBackground(Qt::green);
                break;
            case 4:
                etats->item(i,j)->setBackground(Qt::yellow);
                break;
            case 5:
                etats->item(i,j)->setBackground(Qt::red);
                break;
            case 6:
                etats->item(i,j)->setBackground(Qt::cyan);
                break;
            case 7:
                etats->item(i,j)->setBackground(Qt::magenta);
                break;
            case 8:
                etats->item(i,j)->setBackground(Qt::gray);
                break;
            case 9:
                etats->item(i,j)->setBackground(Qt::darkGreen);
                break;
            default:
                etats->item(i,j)->setBackground(Qt::black);
                break;
            }
        }
    }
    connect(etats,SIGNAL(doubleClicked(const QModelIndex&)),this,SLOT(cellActivation(const QModelIndex&)));

    const Automate& a = Biblio::getInstance().createAutomate(b.getTabVoisinage()->getVoisinage(iV),
                                                             b.getTabFtransit()->getFtransit(iF),
                                                             lim, nomAuto); //création de l'automate, ajout dans la liste des automates de AutomateManager

    horizontalLayout_3=new QHBoxLayout;
    nextButton= new QPushButton("Prochain");
    QObject::connect(nextButton, SIGNAL(clicked()), this, SLOT(faire_step()));
    horizontalLayout_3->addWidget(nextButton);


    Tab= new QPushButton("Tableau noir");
    QObject::connect(Tab, SIGNAL(clicked()), this, SLOT(tableaunoir()));
    horizontalLayout_3->addWidget(Tab);

    horizontalLayout_1=new QHBoxLayout;
    pauseButton= new QPushButton("Pause");
    reprendreButton=new QPushButton("Reprendre");
    QObject::connect(reprendreButton, SIGNAL(clicked()), this, SLOT(on_reprendre()));
    QObject::connect(pauseButton, SIGNAL(clicked()), this, SLOT(on_pause()));
    horizontalLayout_1->addWidget(pauseButton);
    horizontalLayout_1->addWidget(reprendreButton);

    horizontalLayout_2 =new QHBoxLayout;
    menu = new QPushButton("&Menu");
    ok = new QPushButton("&Fin");
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));
    //rajouter liberer instances
    horizontalLayout_2->addWidget(menu);
    horizontalLayout_2->addWidget(ok);

    couche->addWidget(etats);
    couche->addLayout(horizontalLayout_3);
    couche->addLayout(horizontalLayout_1);
    couche->addLayout(horizontalLayout_2);
    setLayout(couche);
}

void Personnalise::tableaunoir() {
    for (int i=0;i<longueur;i++)//Initialisation de la grille
    {
        for (int j=0;j<largeur;j++)
        {
            etats->item(i,j)->setBackground(Qt::black);
        }
    }
}
/**
 * \brief fonction d'itération en continu : on regarde la couleur des cellules pour initialiser les états de l'automate, puis on construit l'automate et on fait les steps, à chaque step on contrôle que l'utilisateur n'a pas demandé un arrêt de la simulation puis on actualise l'interface graphique
 */
void Personnalise::on_reprendre(){
    step=true;
    Etat e(longueur,largeur);
    for (int i=0;i<longueur;i++)
    {
        for (int j=0;j<largeur;j++)
        {
            auto * current= etats->item(i,j);
            if (current->background()==Qt::black)
                e.setCellule(i,j,0);
            else if (etats->item(i,j)->background()==Qt::white)
                e.setCellule(i,j,1);
            else if (etats->item(i,j)->background()==Qt::blue)
                e.setCellule(i,j,2);
            else if (etats->item(i,j)->background()==Qt::green)
                e.setCellule(i,j,3);
            else if (etats->item(i,j)->background()==Qt::yellow)
                e.setCellule(i,j,4);
            else if (etats->item(i,j)->background()==Qt::red)
                e.setCellule(i,j,5);
            else if (etats->item(i,j)->background()==Qt::cyan)
                e.setCellule(i,j,6);
            else if (etats->item(i,j)->background()==Qt::magenta)
                e.setCellule(i,j,7);
            else if (etats->item(i,j)->background()==Qt::gray)
                e.setCellule(i,j,8);
            else if (etats->item(i,j)->background()==Qt::darkGreen)
                e.setCellule(i,j,9);
        }
    }
    int instance;
    for (size_t i;i<b.getNbAutomates();i++){
        if (b.getAutomate(i).getNomAuto()==nomAuto)
            instance=i;
    }
    const Automate& a=b.getAutomate(instance);
    Simulateur S(a,e,1);
    while(step){
        S.next();
        auto check=checkstep();
        if (!check) break;
        const Etat& d=S.dernier();
        for (int i=0;i<longueur;i++)
        {
            for (int j=0;j<largeur;j++)
            {
                if(d.getCellule(i,j)==0) etats->item(i,j)->setBackground(Qt::black);
                if(d.getCellule(i,j)==1) etats->item(i,j)->setBackground(Qt::white);
                if(d.getCellule(i,j)==2) etats->item(i,j)->setBackground(Qt::blue);
                if(d.getCellule(i,j)==3) etats->item(i,j)->setBackground(Qt::green);
                if(d.getCellule(i,j)==4) etats->item(i,j)->setBackground(Qt::yellow);
                if(d.getCellule(i,j)==5) etats->item(i,j)->setBackground(Qt::red);
                if(d.getCellule(i,j)==6) etats->item(i,j)->setBackground(Qt::cyan);
                if(d.getCellule(i,j)==7) etats->item(i,j)->setBackground(Qt::magenta);
                if(d.getCellule(i,j)==8) etats->item(i,j)->setBackground(Qt::gray);
                if(d.getCellule(i,j)==9) etats->item(i,j)->setBackground(Qt::darkGreen);
            }
        }
        QTest::qWait(125);
    }
}

/**
 * \brief fonction qui programme l'arrêt de la simulation en continue
 */
void Personnalise::on_pause(){
    step=false;
}

/**
 * \brief fonction qui contrôle l'arrêt de la simulation en continue
 */
bool Personnalise::checkstep(){
    return step;
}

/**
 * \brief fonction qui permet de changer la couleur des cellules, et donc leur état entre chaque itérations : on doit contrôler combien d'états l'automate possède pour savoir quel couleur doit être remplacée par le noir (équivalent de l'état 0)
 */
void Personnalise::cellActivation(const QModelIndex& index)
{
    if (etats->item(index.row(),index.column())->background()==Qt::black)
        etats->item(index.row(),index.column())->setBackground(Qt::white);
    else if (etats->item(index.row(),index.column())->background()==Qt::white)
        if (nb_etats>2)
            etats->item(index.row(),index.column())->setBackground(Qt::blue);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::blue)
        if (nb_etats>3)
            etats->item(index.row(),index.column())->setBackground(Qt::green);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::green)
        if (nb_etats>4)
            etats->item(index.row(),index.column())->setBackground(Qt::yellow);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::yellow)
        if (nb_etats>5)
            etats->item(index.row(),index.column())->setBackground(Qt::red);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::red)
        if (nb_etats>6)
            etats->item(index.row(),index.column())->setBackground(Qt::cyan);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::cyan)
        if (nb_etats>7)
            etats->item(index.row(),index.column())->setBackground(Qt::magenta);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::magenta)
        if (nb_etats>8)
            etats->item(index.row(),index.column())->setBackground(Qt::gray);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::gray)
        if (nb_etats>9)
            etats->item(index.row(),index.column())->setBackground(Qt::darkGreen);
        else
            etats->item(index.row(),index.column())->setBackground(Qt::black);
    else if (etats->item(index.row(),index.column())->background()==Qt::darkGreen)
        etats->item(index.row(),index.column())->setBackground(Qt::black);
}

/**
 * \brief fonction faisant une itération : comportement similaire à on_reprendre() : on regarde la couleur des cellules pour initialiser les états de l'automate, puis on construit l'automate et on fait une itération, puis on actualise l'interface graphique
 */
void Personnalise::faire_step(){
    Etat e(longueur,largeur);
    for (int i=0;i<longueur;i++)
    {
        for (int j=0;j<largeur;j++)
        {
            auto * current= etats->item(i,j);
            if (current->background()==Qt::black)
                e.setCellule(i,j,0);
            else if (etats->item(i,j)->background()==Qt::white)
                e.setCellule(i,j,1);
            else if (etats->item(i,j)->background()==Qt::blue)
                e.setCellule(i,j,2);
            else if (etats->item(i,j)->background()==Qt::green)
                e.setCellule(i,j,3);
            else if (etats->item(i,j)->background()==Qt::yellow)
                e.setCellule(i,j,4);
            else if (etats->item(i,j)->background()==Qt::red)
                e.setCellule(i,j,5);
            else if (etats->item(i,j)->background()==Qt::cyan)
                e.setCellule(i,j,6);
            else if (etats->item(i,j)->background()==Qt::magenta)
                e.setCellule(i,j,7);
            else if (etats->item(i,j)->background()==Qt::gray)
                e.setCellule(i,j,8);
            else if (etats->item(i,j)->background()==Qt::darkGreen)
                e.setCellule(i,j,9);
        }
    }
    int instance;
    for (size_t i;i<b.getNbAutomates();i++){
        if (b.getAutomate(i).getNomAuto()==nomAuto)
            instance=i;
    }
    const Automate& a=b.getAutomate(instance);
    Simulateur S(a,e,1);
    S.next();
    const Etat& d=S.dernier();
    for (int i=0;i<longueur;i++)
    {
        for (int j=0;j<largeur;j++)
        {
            if(d.getCellule(i,j)==0) etats->item(i,j)->setBackground(Qt::black);
            if(d.getCellule(i,j)==1) etats->item(i,j)->setBackground(Qt::white);
            if(d.getCellule(i,j)==2) etats->item(i,j)->setBackground(Qt::blue);
            if(d.getCellule(i,j)==3) etats->item(i,j)->setBackground(Qt::green);
            if(d.getCellule(i,j)==4) etats->item(i,j)->setBackground(Qt::yellow);
            if(d.getCellule(i,j)==5) etats->item(i,j)->setBackground(Qt::red);
            if(d.getCellule(i,j)==6) etats->item(i,j)->setBackground(Qt::cyan);
            if(d.getCellule(i,j)==7) etats->item(i,j)->setBackground(Qt::magenta);
            if(d.getCellule(i,j)==8) etats->item(i,j)->setBackground(Qt::gray);
            if(d.getCellule(i,j)==9) etats->item(i,j)->setBackground(Qt::darkGreen);
        }
    }
}

/**
 * \brief constructeur de predefini : choix des automates déjà implémentés
 */
predefini::predefini(QWidget* parent):fenetreBase(parent)
{
    Life= new QRadioButton("Life's Game de Conway", this);;
    Brain= new QRadioButton("Brian's brain", this);;
    Loop= new QRadioButton("Wire's world", this);;
    Griffeath= new QRadioButton("L'automate circulaire de Griffeath", this);;
    QPushButton *ok = new QPushButton("&Fin");
    QPushButton *menu = new QPushButton("&Menu");
    couche=new QVBoxLayout;
    couche->addWidget(Life);
    couche->addWidget(Brain);
    couche->addWidget(Loop);
    couche->addWidget(Griffeath);
    couche->addWidget(ok);
    couche->addWidget(menu);
    QObject::connect(ok, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(menu, SIGNAL(clicked()), this, SLOT(menu()));
    connect(Life,SIGNAL(clicked()),this,SLOT(SetupLife()));
    connect(Brain,SIGNAL(clicked()),this,SLOT(SetupBB()));
    connect(Loop,SIGNAL(clicked()),this,SLOT(SetupLoop()));
    connect(Griffeath,SIGNAL(clicked()),this,SLOT(SetupGriffeath()));
    setLayout(couche);
}


void predefini::SetupLife()
{
    class PersonalisationDimensions *p= new class PersonalisationDimensions(nullptr,2);
    p->show();
    this->hide();
}
void predefini::SetupBB()
{
    class PersonalisationDimensions *p= new class PersonalisationDimensions(nullptr,3);
    p->show();
    this->hide();
}
void predefini::SetupLoop()
{
    class PersonalisationDimensions *p= new class PersonalisationDimensions(nullptr,4);
    p->show();
    this->hide();
}
void predefini::SetupGriffeath()
{
    class PersonalisationDimensions *p= new class PersonalisationDimensions(nullptr,4);
    p->show();
    this->hide();
}
