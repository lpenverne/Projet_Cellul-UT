#ifndef MENU_H
#define MENU_H
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <qboxlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QModelIndex>
#include <QPushButton>
#include <QRadioButton>
#include <QApplication>
#include <QDebug>
#include <random>
#include <vector>
#include <QFile>
#include <QList>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QtMath>
#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <qboxlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QModelIndex>
#include <QPushButton>
#include <QBrush>
#include <QColor>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QIntValidator>
#include <QString>
#include <qboxlayout.h>
#include <QTableWidget>
#include <QHeaderView>
#include <QModelIndex>
#include <QPushButton>
#include <QTest>
#include <QTextEdit>
#include <QComboBox>
#include "automatePerso.h"

/**
 * \brief QWidget de base qui permet à toutes les autres fenetres d'hériter le retour au menu
 */
class fenetreBase: public QWidget{
    Q_OBJECT
public:
    // Constructeur
    explicit fenetreBase(QWidget* parent = nullptr);
private slots:
    void menu();
};

/**
 * \brief Première fenetre de l'application : l'utilisateur arrive dessus au démarrage et il choisit s'il veut charger un ancien automate ou en créé un nouveau
 */

class menu : public QWidget{
    Q_OBJECT
    QRadioButton* personalise;
    QRadioButton* chargepredefini;
    QRadioButton* transition;
    QRadioButton* voisinnage;
    QRadioButton* predefini;
    QVBoxLayout* couche;
    QPushButton *ok;
public:
    // Constructeur
    explicit menu(QWidget* parent = nullptr);
    void enregistrerpredef();
private slots:
    void Openpersonalise();
    void Openpredefini();
    void Nouveau_Voisinnage();
    void chargerpredefini();
};

/**
 * \brief permet de nommer un automate personnaliser et de choisir le nombre d'états possibles
 */
class PersonnalisationEtats : public fenetreBase{
    Q_OBJECT
    QLabel* Label_1;
    QLabel* NumEtats;
    QSpinBox *nbEtats;
    QHBoxLayout* LayoutNum;

    QLabel* Label_2;
    QLineEdit* Nom;
    QHBoxLayout* LayoutNom;

    QPushButton *valider;

    QVBoxLayout* couche;
public:
    explicit PersonnalisationEtats(QWidget* parent = nullptr);
private slots:
    void validation();
    void changer(int i);
    void changer_nom(QString nom);
private:
    int nb;
    QString nom;
};

class PersonalisationnbEtats : public fenetreBase{
    Q_OBJECT
    QLabel* NumEtats;
    QSpinBox *nbEtats;
    QHBoxLayout* LayoutNum;

    QPushButton *valider;

    QVBoxLayout* couche;
public :
    PersonalisationnbEtats(QWidget * parent =nullptr);
private slots :
    void charger_automate();
};

/**
 * \brief permet de rajouter des nouvelles regles à un automate en choisissant l'état de départ, d'arrivée, le nombre de voisin nécessaires à la transition et leur état
 */
class PersonnalisationTransition :public fenetreBase{
    Q_OBJECT
    QLabel* Etatdep;
    QSpinBox *nbEtatdep;
    QLabel* Etatarr;
    QSpinBox *nbEtatsarr;
    QLabel* Etatvois;
    QSpinBox *Etatsvoisp;
    QLabel* nbEtatsvois;
    QSpinBox *nbEtatsvoisp;
    QHBoxLayout* Layout1_1;
    QHBoxLayout* Layout1_2;
    QVBoxLayout* Layout1;

    QPushButton *valider;
    QPushButton *next;
    QHBoxLayout * horizontalLayout_3;

    QVBoxLayout* couche;
public :
   explicit PersonnalisationTransition(QWidget* parent = nullptr,int nb_e=2, QString Name="");
private slots :
    void ajoutRegle();
    void passageTransition();
private :
    int nb_etats;
    int max=10;
    int nb_regles=0;
    Regle** r;
    QString nom;
    //TabFtransit tf;
};

/**
* \brief Choix du voisinnage : du rayon d'action et de la prise en compte ou non des diagonales
 */
class PersonnalisationVoisinnage : public fenetreBase{
    Q_OBJECT
    QLabel* Nom;
    QLineEdit *NomV;
    QHBoxLayout * horizontalLayout_3;

    QLabel* Rayon;
    QSpinBox *Rayonnum;
    QHBoxLayout * horizontalLayout_1;
    QLabel* Diago;
    QRadioButton *bDiago;
    QHBoxLayout * horizontalLayout_2;
    QPushButton *valider;

    QVBoxLayout* couche;
public :
   explicit PersonnalisationVoisinnage(QWidget* parent = nullptr,int nb_e=2);
private slots :
    void validation();
    void changer_diago();
private :
    bool diag=false;
    int nb_etats;
};

/**
* \brief choix des dimensions (hauteur, longueur) de l'automate et de la prise en compte du tore ou non
 */
class PersonalisationDimensions : public fenetreBase{
    Q_OBJECT
    QLabel *Label;

    QVBoxLayout *verticalLayout_3;
    QHBoxLayout * horizontalLayout_5;
    QHBoxLayout * horizontalLayout_6;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *cellsPerLine;
    QLabel *label_10;
    QSpinBox *cellsPerColumn;

    QLabel* Limite;
    QRadioButton* bLimite;
    QHBoxLayout* horizontalLayout_2;

    QPushButton* next;
    QHBoxLayout * horizontalLayout_3;

    QPushButton *menu;
    QPushButton *ok;
    QHBoxLayout * horizontalLayout_4;

    QVBoxLayout* couche;
public:
    // Constructeur
    explicit PersonalisationDimensions(QWidget* parent = nullptr, int nb_e=2);
private slots:
    void changerlimites();
    void PersoFini();
private :
    int nb_etats;
    bool limitebis=false;
};

/**
*  \brief Met en commun le voisinnage et la transition du futur automate et lui donne un nom
*/
class PersoFinition : public fenetreBase{
    Q_OBJECT
    QLabel* NomAutomate;
    QLineEdit* nom;
    QHBoxLayout * horizontalLayout_1;

    QLabel* Vois;
    QComboBox* nomvois;
    QHBoxLayout * horizontalLayout_2;

    QLabel* Ftrans;
    QComboBox* nomFtrans;
    QHBoxLayout * horizontalLayout_3;

    QPushButton *menu;
    QPushButton *ok;
    QHBoxLayout * horizontalLayout_4;

    QPushButton *valider;

    QVBoxLayout* couche;

public :
    explicit PersoFinition(QWidget* parent = nullptr,int l=20, int h=20, int nb_e=2, bool limites=false);
private slots :
    void passerAautomate();
private :
    int longueur,largeur,nb_etats;
    bool priselimites;

};

/**
 * \brief Affichage d'un automate avec la possibilité de le lancer en continu ou itération par itération
 */
class Personnalise : public fenetreBase{
    Q_OBJECT
    QTableWidget* etats;

    QHBoxLayout * horizontalLayout_1;
    QPushButton *pauseButton;
    QPushButton *reprendreButton;

    QHBoxLayout * horizontalLayout_3;
    QPushButton *nextButton;
     QPushButton *Tab;

    QHBoxLayout * horizontalLayout_2;
    QPushButton *menu;
    QPushButton *ok;

    QVBoxLayout* couche;
public :
    explicit Personnalise(QWidget* parent = nullptr, int l=20,int h=20, int indexV=0, int indexF=0, std::string nom="", bool limites=false, int nb_e=2);
private slots:
    void on_pause(); //mettre la simulation en pause
    void on_reprendre(); //reprendre la simulation
    void faire_step(); //faire une itération
    void cellActivation(const QModelIndex& index); //changer la couleur des cellules
    void tableaunoir(); //change la couleur du tableau
private :
    bool checkstep(); //utilisé pour interrompre si l'utilisateur a cliqué sur pause
    int longueur;
    int largeur;
    int nb_etats;
    int iV;
    int iF;
    std::string nomAuto;
    bool lim;
    bool step;
    bool lance;
    //const Automate& a;
};

/**
 * \brief permet de choisir un automate prédéfini et de le lancer
 */
class predefini : public fenetreBase{
    Q_OBJECT
    QRadioButton* Life;
    QRadioButton* Brain;
    QRadioButton* Loop;
    QRadioButton* Griffeath;
    QVBoxLayout* couche;
public:
    // Constructeur
    explicit predefini(QWidget* parent = nullptr);
private slots:
    void SetupLife();
    void SetupBB();
    void SetupLoop();
    void SetupGriffeath();

};

#endif // MENU_H
