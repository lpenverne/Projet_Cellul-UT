#pragma once

#include <string>
#include <iostream>

/*! \class AutomateException
* \brief classe gérant les erreurs
*/
class AutomateException {
public:
	/*!
     *  \brief Constructeur
     *  Constructeur de la classe AutomateException
     *  \param message : le message à afficher lors de la survenue de l'erreur
     */
    AutomateException(const std::string& message) :info(message) {}
	/*!
	 *  \brief Obtenir le message d'erreur
	 *  \return Le message d'erreur.
	*/
    std::string getInfo() const { return info; }
private:
    std::string info; /*!<Information sur l'erreur*/
};

/*! \class Voisinage
* \brief classe définissant un voisinage
*/
class Voisinage {
public:
    /*!
     *  \brief Destructeur
     *  Destructeur (par défaut) de la classe Voisinage
     */
    ~Voisinage() = default;
    /*!
     *  \brief Obtenir le nom du voisinage
     *  \return Le nom du voisinage
     */
    std::string getNomV() const {return nom;}
    /*!
     *  \brief Obtenir la prise en compte des diagonales
     *  \return true si les diagonales sont prises en compte, false sinon
     */
    bool getDiagonale() const {return diagonale;}
    /*!
     *  \brief Obtenir le rayon du voisinage
     *  \return Le rayon du voisinage
     */
    int getRayon() const {return rayon;}
private:
    friend class TabVoisinage;
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Voisinage
     *  \param n : nom du voisinage
     *  \param d : prise en compte des diagonales
     *  \param r : rayon du voisinage
     */
    Voisinage(std::string n, bool d, int r): nom(n), diagonale(d), rayon(r) {}
    std::string nom;    /*!< Nom du voisinage*/
    bool diagonale;    /*!< Prise en compte des diagonales*/
    int rayon;    /*!< Rayon du voisinage*/
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    Voisinage(const Voisinage& a) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    Voisinage& operator=(const Voisinage& a) = delete;
};


/*! \class TabVoisinage
* \brief classe contenant les différents voisinages
*/
class TabVoisinage {        //tableau contenant les voisinages
public:
    /*!
     *  \brief Obtenir le nombre de voisinages
     *  \return le nombre de voisinages contenus dans le tableau de voisinages
     */
    int getNbVoisinages() const {return nb;}
    /*!
     *  \brief Obtenir un voisinage
     *  \param i : index du tableau de voisinages
     *  \return une référence du voisinage contenu à l'index i du tableau de voisinages
     */
    const Voisinage& getVoisinage(int i) const {return *tab[i];}
    /*!
     *  \brief Ajouter un voisinage au tableau de voisinage
     *  Lance le constructeur de la classe Voisinage, et ajoute l'objet créé dans le tableau de voisinages
     *  Agrandit le tableau de voisinage s'il est déjà plein
     *  \param n : nom du voisinage
     *  \param d : prise en compte des diagonales
     *  \param r : rayon du voisinage
     */
    void ajouterUnVoisinage(std::string n, bool d, int r);
    /*!
     *  \brief Destructeur
     *  Destructeur de la classe TabVoisinage
     */
    ~TabVoisinage() {for(int i=0; i<nb; i++) delete tab[i]; delete[] tab;}
private:
    friend class Biblio;
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe TabVoisinage
     *  Met à 0 le nombre de voisinage, à 0 la taille du tableau de voisinages et à nullptr le pointeur vers le tableau de voisinages
     */
    TabVoisinage(): nb(0), taille_tab(0), tab(nullptr) {}
    int nb;    /*!<nombre de voisinages contenus dans le tableau*/
    int taille_tab;  /*!<taille réelle du tableau*/
    Voisinage** tab;    /*<tableau de pointeurs sur des voisinages*/
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    TabVoisinage(const TabVoisinage& tv) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    TabVoisinage& operator=(const TabVoisinage& tv) = delete;
};


/*! \class Regle
* \brief classe définissant une règle d'une fonction de transition
*/
class Regle {
public:
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Regle
     *  \param ed : etat de départ de la cellule sur laquelle la règle va s'appliquer
     *  \param ec : etat cible de la cellule, son état final après application de la règle
     *  \param nb : nombre de voisins nécessaires pour appliquer la règle
     *  \param ev : etat des voisins à prendre en compte lors du décompte des voisins
     */
    Regle(int ed, int ec, int nb, int ev): etat_depart(ed), etat_cible(ec), nb_voisins(nb), etat_voisins(ev) {}
    /*!
     *  \brief Destructeur
     *  Destructeur de la classe Regle
     */
    ~Regle() = default;
    /*!
     *  \brief Obtenir l'état de départ
     *  \return l'état de départ de la cellule
     */
    int getEtatDepartR() const {return etat_depart;}
    /*!
     *  \brief Obtenir l'état cible
     *  \return l'état cible de la cellule
     */
    int getEtatCibleR() const {return etat_cible;}
    /*!
     *  \brief Obtenir le nombre de voisins
     *  \return le nombre de voisins nécessaires à la transition
     */
    int getNbVoisinsR() const {return nb_voisins;}
    /*!
     *  \brief Obtenir l'état des voisins
     *  \return l'état des voisins à prendre en compte
     */
    int getEtatVoisinsR() const {return etat_voisins;}

private:
    int etat_depart; /*!< etat de départ de la cellule sur laquelle la règle va s'appliquer*/
    int etat_cible; /*!< etat cible de la cellule, son état final après application de la règle*/
    int nb_voisins; /*!< nombre de voisins nécessaires pour appliquer la règle*/
    int etat_voisins; /*!< etat des voisins à prendre en compte lors du décompte des voisins*/
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    Regle(const Regle& r) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    Regle& operator=(const Regle& a) = delete;
};

/*! \class Ftransit
* \brief classe contenant les différentes règles d'une fonction de transition ainsi que certains de ses attributs
*/
class Ftransit {
public:
    /*!
     *  \brief Destructeur
     *  Destructeur de la classe Ftransit
     */
    ~Ftransit() {delete[] liste_regles;}
    /*!
     *  \brief Obtenir une règle
     *  \param i : index du tableau de règles
     *  \return une référence de la règle contenue à l'index indiqué du tableau de règles
     */
    const Regle& getRegle(int i) const {return *liste_regles[i];}
    /*!
     *  \brief Obtenir le nombre d'états autorisés par la fonction
     *  \return le nombre d'états autorisés par la fonction de transition
     */
    int getNbEtatsF() const {return nb_etats;}
    /*!
     *  \brief Obtenir le nom de la fonction
     *  \return le nom de la fonction de transition
     */
    std::string getNomF() const {return nom;}
    /*!
     *  \brief Obtenir le nombre de règles de la fonction
     *  \return le nombre de règles de la fonction de transition
     */
    int getNbReglesF() const {return nb_regles;}
private:
    friend class TabFtransit;
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Ftransit
     *  \param n : nom de la fonction de transition
     *  \param etats : le nombre d'états autorisés par la fonction
     *  \param r : tableau de pointeurs vers des règles
     *  \param nb_reg : le nombre de règles de la fonction
     */
    Ftransit(std::string n, int etats, Regle** r, int nb_reg);
    std::string nom; /*!<Nom de la fonction de transition*/
    int nb_regles;    /*!<Nombre de règles*/
    Regle** liste_regles;    /*!<Tableau de pointeurs sur des règles*/
    int nb_etats; /*!<Nombre d'etat possible pour cette fonction (ex : jeu de la vie = 2 états)*/
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    Ftransit(const Ftransit& f) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    Ftransit& operator=(const Ftransit& a) = delete;
};


/*! \class TabFtransit
* \brief classe contenant les différentes fonctions de transition
*/
class TabFtransit {        //tableau contenant les fonctions de transition
public:
    /*!
     *  \brief Obtenir le nombre de fonctions de transition
     *  \return le nombre de fonctions de transition contenues dans le tableau
     */
    int getNbFtransit() const {return nb;};
    /*!
     *  \brief Obtenir une fonction de transition
     *  \param i : index du tableau de fonctions de transition
     *  \return une référence de la fonction de transition contenue à l'index indiqué du tableau de fonctions
     */
    const Ftransit& getFtransit(int i) const {return *tab[i];}
    /*!
     *  \brief Ajouter une fonction de transition au tableau de fonctions
     *  Lance le constructeur de la classe Ftransit, et ajoute l'objet créé dans le tableau de fonctions de transition
     *  Agrandit le tableau de fonction de transitions s'il est déjà plein
     *  \param n : nom de la fonction de transition
     *  \param nb : nombre de fonctions de transitions contenues dans le tableau
     *  \param r : liste de règles à rattacher à la nouvelle fonction créée
     *  \param nb_regles : nombre de règles de la fonction nouvellement créée
     */
    void ajouterUneFtransit(std::string n, int nb, Regle** r, int nb_regles);
    /*!
     *  \brief Destructeur
     *  Destructeur de la classe TabFtransit
     */
    ~TabFtransit() {for(int i=0; i<nb; i++) delete tab[i]; delete[] tab;}
private:
    friend class Biblio;
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe TabFtransit
     *  Met à 0 le nombre de fonctions de transition, à 0 la taille du tableau de fonctions et à nullptr le pointeur vers le tableau de fonctions de transition
     */
    TabFtransit(): nb(0), taille_tab(0), tab(nullptr) {}
    int nb;  /*!<Nombre de fonctions de transition*/
    int taille_tab; /*!<Taille du tableau de fonctions*/
    Ftransit** tab;  /*!<Tableau de pointeurs sur des fonctions de transition*/
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    TabFtransit(const TabFtransit& tf) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    TabFtransit& operator=(const TabFtransit& tf) = delete;
};


/*! \class Etat
* \brief classe représentant l'ensemble des cellules d'un automate à un instant t
*/
class Etat {
public:
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Etat
     *  Crée une nouvele matrice de cellules, en les initialisant toutes à l'état 0
     *  \param h : hauteur de la matrice de cellules
     *  \param l : largeur de la matrice de cellules
     */
    Etat(size_t h = 0, size_t l = 0);
    /*!
     *  \brief Obtenir la hauteur de la matrice
     *  \return la hauteur de la matrice de cellules
     */
    size_t getHauteur() const { return hauteur; }
    /*!
     *  \brief Obtenir la largeur de la matrice
     *  \return la largeur de la matrice de cellules
     */
    size_t getLargeur() const { return largeur; }
    /*!
     *  \brief Obtenir une cellule
     *  \param i : ligne de la matrice contenant la cellule
     *  \param j : colonne de la matrice contenant la cellule
     *  \return la valeur de la cellule aux coordonnées i, j
     */
    int getCellule(size_t i, size_t j) const;
    /*!
     *  \brief Changer la valeur d'une cellule
     *  \param i : ligne de la matrice contenant la cellule
     *  \param j : colonne de la matrice contenant la cellule
     *  \param val : valeur de la cellule
     */
    void setCellule(size_t i, size_t j, int val);
    /*!
     *  \brief Destructeur
     *  Destructeur de la classe Etat
     */
    ~Etat() { delete[] valeur; }
    /*!
     *  \brief Constructeur par recopie de la classe Etat
     */
    Etat(const Etat& e);
    /*!
     *  \brief Constructeur par affectation de la classe Etat
     */
    Etat& operator=(const Etat& e);
private:
    size_t largeur; /*!<Largeur de la matrice*/
    size_t hauteur; /*!<Hauteur de la matrice*/
    int** valeur; /*!<La matrice contenant l'état des cellules*/
};


/*!
 *  \brief Afficher une matrice d'état de cellules
 *  \param f : flux ostream
 *  \param e : une référence de l'état à afficher
 *  \return un flux ostream affichant l'état indiqué
 */
std::ostream& operator<<(std::ostream& f, const Etat& e);

/*! \class Automate
* \brief classe rassemblant toutes les informations d'un automate,
* principalement un voisinage et une fonction de transition
*/
class Automate {
public:
    /*!
     *  \brief Appliquer la transition
     *  \param dep : état pré-transition
     *  \param dest : état post-transition
     */
    void appliquerTransition(const Etat& dep, Etat& dest) const;
    /*!
     *  \brief Renvoyer le nombre de voisins avec la valeur val
     *  \param e : une référence de l'état
     *  \param i : ligne de la matrice contenant la cellule
     *  \param j : colonne de la matrice contenant la cellule
     *  \param val : valeur de la cellule
     *  \return le nombre de voisins nb
     */
    int nombre_voisins(const Etat& e, size_t i, size_t j, int val) const;
    /*!
     *  \brief Obtenir le nom de l'automate
     *  \return le nom de l'automate
     */
    std::string getNomAuto() const {return nom;}
    /*!
     *  \brief Obtenir la fonction de transition
     *  \return la fonction de transition
     */
    const Ftransit& getFtransitA() const {return fonction;}
    /*!
     *  \brief Obtenir le voisinage
     *  \return le voisinage
     */
    const Voisinage& getVoisinageA() const {return voisinage;}
private:
    friend class Biblio;
    /*!
     *  \brief Créer l'automate et le placer dans le tableau d'automates
     *  \param v : référence du voisinage
     *  \param f : référence de la fonction de transition
     *  \param l : booléen indiquant la forme de la grille (tore ou non)
     *  \param nom : nom de l'automate
     */
    Automate(const Voisinage& v, const Ftransit& f, bool l, std::string nom): voisinage(v), fonction(f), limite(l), nom(nom) {}
    /*!
     *  \brief Destructeur
     *  Destructeur (par défaut) de la classe Automate
     */
    ~Automate() = default;
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    Automate(const Automate& a) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    Automate& operator=(const Automate& a) = delete;
    const Voisinage& voisinage;/*!<Référence du voisinage*/
    const Ftransit& fonction;/*!<Référence de la fonction de transition*/
    bool limite;/*!<Booléen indiquant la forme de la grille (tore ou non)*/
    std::string nom;/*!<Nom de l'automate*/
};


/*! \class Simulateur
* \brief classe qui gère l'éxecution des transitions entre les etats t et t+1 d'un automate
*/
class Simulateur {
public:
    /*!
     *  \brief Assigner un état comme étant un état de départ
     *  \param e : état à prendre comme état de départ
     */
    void setEtatDepart(const Etat& e);
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Simulateur
     *  \param a : une référence sur l'automate
     *  \param buffer : nombre d'états maximum
     */
    Simulateur(const Automate& a, size_t buffer = 2);
    /*!
     *  \brief Constructeur
     *  Constructeur de la classe Simulateur
     *  \param a : une référence sur l'automate
     *  \param e : une référence sur l'état de départ 
     *  \param buffer : nombre d'états maximum
     */
    Simulateur(const Automate& a, const Etat& e, size_t buffer = 2);
    /*!
     *  \brief Destructeur
     *  Destructeur de la classe Simulateur
     */
    ~Simulateur() {
        for (size_t i = 0; i < nbMaxEtats; i++)
            delete etats[i];
        delete[] etats;
    }
    /*!
     *  \brief Appliquer la transition pour passer à l'état suivant
     */
    void next();
    /*!
     *  \brief Executer n fois la transition
     *  \param nbSteps : nombre d'états à générer
     */
    void run(size_t nbSteps);
    /*!
     *  \brief Obtenir le dernier état généré
     *  \return une référence const du dernier état généré
     */
    const Etat& dernier() const;
    /*!
     *  \brief Obtenir le dernier état généré
     *  \return une référence const du dernier état généré
     */
    Etat& dernier();
    /*!
     *  \brief Obtenir le rang du dernier état généré
     *  \return le rang du dernier état généré (autrement dit le rang actuel)
     */
    size_t getRangDernier() const { return rang; }
    /*!
     *  \brief Réinitialise la simulation, remets le rang à 0
     */
    void reset() { rang = 0; }

    /*! \class Iterator
    * \brief iterateur de la classe Simulateur, fonctionne avec des méthodes, gère les références non const de Simulateur
    */
    class Iterator {
        Simulateur& s;/*!<Simulateur sur lequel porte l'itérateur*/
        int courant;/*!<Indice de l'état courant désigné par l'itérateur*/
        /*!
         *  \brief Constructeur
         *  Constructeur de la classe Iterator
         *  \param sim : référence sur le simulateur
         */
        Iterator(Simulateur& sim) :s(sim), courant(sim.rang) {}
        friend class Simulateur;
    public:
        /*!
         *  \brief Passer à l'état précédent contenu dans le buffer
         */
        void next() {
            if (isDone())
                throw AutomateException("next sur un it�rateur en fin de s�quence");
            courant--;
        }
        /*!
         *  \brief Obtenir l'état sur lequel porte l'itérateur
         *  \return un pointeur sur l'état pointé par l'itérateur
         */
        Etat& currentItem() const {
            if (isDone())
                throw AutomateException("currentItem sur un it�rateur en fin de s�quence");
            return *s.etats[courant%s.nbMaxEtats];
        }
        /*!
         *  \brief Vérifier si l'itérateur est en fin de séquence
         *  \return un booléen indiquant si les états contenus dans le buffer ont bien été tous parcourus
         */
        bool isDone() const {
            if (s.rang < s.nbMaxEtats)
                return courant == -1;
            else
                return s.rang - courant == s.nbMaxEtats;
            
        }
    };

    /*! \class ConstIterator
    * \brief iterateur de la classe Simulateur, fonctionne avec des méthodes, gère les références const de Simulateur
    */
    class ConstIterator {
        const Simulateur& s;/*!Simulateur sur lequel porte l'itérateur*/
        int courant;/*!<Indice de l'état courant désigné par l'itérateur*/
        /*!
         *  \brief Constructeur
         *  Constructeur de la classe ConstIterator
         *  \param sim : référence sur le simulateur
         */
        ConstIterator(const Simulateur& sim) :s(sim), courant(sim.rang) {}
        friend class Simulateur;
    public:
        /*!
         *  \brief Passer à l'état précédent contenu dans le buffer
         */
        void next() {
            if (isDone())
                throw AutomateException("next sur un it�rateur en fin de s�quence");
            courant--;
        }
        /*!
         *  \brief Obtenir l'état sur lequel porte l'itérateur
         *  \return un pointeur sur l'état pointé par l'itérateur
         */
        const Etat& currentItem() const {
            if (isDone())
                throw AutomateException("currentItem sur un it�rateur en fin de s�quence");
            return *s.etats[courant%s.nbMaxEtats];
        }
        /*!
         *  \brief Vérifier si l'itérateur est en fin de séquence
         *  \return un booléen indiquant si les états contenus dans le buffer ont bien été tous parcourus
         */
        bool isDone() const {
            if (s.rang < s.nbMaxEtats)
                return courant == -1;
            else
                return s.rang - courant == s.nbMaxEtats;

        }
    };


    friend class Iterator;
    friend class ConstIterator;

    /*!
     *  \brief Initialiser un itérateur
     *  \return un itérateur Iterator pour le simulateur courant
     */
    Iterator first() { return Iterator(*this); }
    /*!
     *  \brief Initialiser un itérateur
     *  \return un itérateur ConstIterator pour le simulateur courant
     */
    ConstIterator first() const { return ConstIterator(*this); }

    /*! \class iterator
    * \brief iterateur de la classe Simulateur, fonctionne avec des surcharges d'opérateurs, gère les références non const de Simulateur
    */
    class iterator {
        Simulateur& s;/*!Simulateur sur lequel porte l'itérateur*/
        int courant;/*!Indice de l'état courant désigné par l'itérateur*/
        /*!
         *  \brief Constructeur
         *  Constructeur de la classe iterator
         *  \param sim : référence sur le simulateur
         */
        iterator(Simulateur& sim) :s(sim), courant(sim.rang) {}
        friend class Simulateur;
        /*!
         *  \brief Vérifier si l'itérateur est en fin de séquence
         *  \return un booléen indiquant si les états contenus dans le buffer ont bien été tous parcourus
         */
        bool isDone() const {
            if (s.rang < s.nbMaxEtats)
                return courant == -1;
            else
                return s.rang - courant == s.nbMaxEtats;

        }
    
    public:
        /*!
         *  \brief Surcharge de l'operateur ++ pour la classe iterator
         *  Passe à l'état précédent contenu dans le buffer
         */
        void operator++() {
            if (isDone())
                throw AutomateException("next sur un it�rateur en fin de s�quence");
            courant--;
        }
        /*!
         *  \brief Surcharge de l'operateur * pour la classe iterator
         *  Obtenir l'état sur lequel porte l'itérateur
         *  \return un pointeur sur l'état pointé par l'itérateur
         */
        Etat& operator*() const {
            if (isDone())
                throw AutomateException("currentItem sur un it�rateur en fin de s�quence");
            return *s.etats[courant%s.nbMaxEtats];
        }
        /*!
         *  \brief Condition d'arrêt pour l'itérateur
         *  \return un booléen indiquant si les deux itérateurs pointe sur le même état courant
         */
        bool operator!=(iterator it) const{
            return courant == it.courant;
        }
        
    };
    
    /*!
     *  \brief Initialiser un itérateur
     *  \return un itérateur iterator pour le simulateur courant
     */
    iterator begin() {    return iterator(*this); }
    /*!
     *  \brief Constuire un itérateur condition d'arrêt
     *  \return l'itérateur construit
     */
    iterator end() {
        iterator it(*this);
        // il faut construire un it�rateur d�j� fini
        if (rang < nbMaxEtats) it.courant = -1;
        else it.courant= rang - nbMaxEtats;
        return it;
    }

    /*! \class const_iterator
    * \brief iterateur de la classe Simulateur, fonctionne avec des surcharges d'opérateurs, gère les références non const de Simulateur
    */
    class const_iterator {
        const Simulateur& s;/*!Simulateur sur lequel porte l'itérateur*/
        int courant;/*!Indice de l'état courant désigné par l'itérateur*/
        /*!
         *  \brief Constructeur
         *  Constructeur de la classe const_iterator
         *  \param sim : référence sur le simulateur
         */
        const_iterator(const Simulateur& sim) :s(sim), courant(sim.rang) {}
        friend class Simulateur;
        /*!
         *  \brief Vérifier si l'itérateur est en fin de séquence
         *  \return un booléen indiquant si les états contenus dans le buffer ont bien été tous parcourus
         */
        bool isDone() const {
            if (s.rang < s.nbMaxEtats)
                return courant == -1;
            else
                return s.rang - courant == s.nbMaxEtats;

        }

    public:
        /*!
         *  \brief Surcharge de l'operateur ++ pour la classe iterator
         *  Passe à l'état précédent contenu dans le buffer
         */
        void operator++() {
            if (isDone())
                throw AutomateException("next sur un it�rateur en fin de s�quence");
            courant--;
        }
        /*!
         *  \brief Surcharge de l'operateur * pour la classe iterator
         *  Obtenir l'état sur lequel porte l'itérateur
         *  \return un pointeur sur l'état pointé par l'itérateur
         */
        const Etat& operator*() const {
            if (isDone())
                throw AutomateException("currentItem sur un it�rateur en fin de s�quence");
            return *s.etats[courant%s.nbMaxEtats];
        }
        /*!
         *  \brief Condition d'arrêt pour l'itérateur
         *  \return un booléen indiquant si les deux itérateurs pointe sur le même état courant
         */
        bool operator!=(const_iterator it) const {
            return courant == it.courant;
        }

    };
    /*!
     *  \brief Initialiser un itérateur
     *  \return un itérateur const_iterator pour le simulateur courant
     */
    const_iterator begin() const { return const_iterator(*this); }
    /*!
     *  \brief Constuire un itérateur condition d'arrêt
     *  \return l'itérateur construit
     */
    const_iterator end() const {
        const_iterator it(*this);
        // il faut construire un it�rateur d�j� fini
        if (rang < nbMaxEtats) it.courant = -1;
        else it.courant = rang - nbMaxEtats;
        return it;
    }
    /*!
     *  \brief Initialiser un itérateur
     *  \return un itérateur const_iterator pour le simulateur courant
     */
    const_iterator cbegin() const { return begin(); }
    /*!
     *  \brief Constuire un itérateur condition d'arrêt
     *  \return l'itérateur construit
     */
    const_iterator cend() const { return end(); }


private:
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    Simulateur(const Simulateur&) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    Simulateur& operator=(const Simulateur&) = delete;

    const Automate& automate;/*!<Référence sur l'automate*/
    const Etat* depart = nullptr;/*!<Pointeur sur l'état de départ*/
    size_t nbMaxEtats;/*!<Nombre maximal d'états*/
    Etat** etats;/*!<Tableau d'états*/
    size_t rang = 0;/*!<Rang initialisé à 0*/
};


/*! \class Biblio
* \brief classe contenant les différents automates, gère également la création d'automate
*/
class Biblio {
public:
    /*!
     *  \brief Créer l'automate et le placer dans le tableau d'automates
     *  On agrandit le tableau d'automates s'il est plein
     *  \param v : référence sur le voisinage
     *  \param f : référence sur la fonction de transition
     *  \param l : booléen indiquant la forme de la grille
     *  \param nom : nom de l'automate
     *  \return l'automate qui vient d'être créé
     */
    const Automate& createAutomate(const Voisinage& v, const Ftransit& f, bool l, std::string nom);
    /*!
     *  \brief Obtenir un automate
     *  \param i : indice de l'automate
     *  \return une référence de l'automate d'indice i correspondant
     */
    const Automate& getAutomate(int i) const {return *tab[i];}
    /*!
     *  \brief Obtenir le nombre d'automates
     *  \return le nombre d'automates contenus dans le tableau d'automates
     */
    int getNbAutomates() const {return nb_automates;}
    /*!
     *  \brief Obtenir le tableau de fonctions de transition
     *  \return le tableau de fonctions de transition
     */
    TabFtransit* getTabFtransit() const {return tf;}
    /*!
     *  \brief Obtenir le tableau de voisinages
     *  \return le tableau de voisinages
     */
    TabVoisinage* getTabVoisinage() const {return tv;}
    
    struct Handler {
        Biblio* instance=nullptr; /*!<Pointeur sur l'unique instance de Biblio*/
        ~Handler() { delete instance; } /*!<Destructeur de la structure Handler*/
    };

    static Handler handler;/*!<Objet static de type Handler */

    /*!
     *  \brief Obtenir le pointeur sur l'unique instance
     *  \return le pointeur sur l'unique instance
     */
    static Biblio& getInstance();
    /*!
     *  \brief Supprimer l'unique instance
     */
    static void libererInstance();

private:
    /*!
     * \brief Constructeur
     *  Constructeur de la classe Biblio
     *  Initialise le nombre d'automates à 0, la taille du tableau à 0, le pointeur sur le tableau d'automates au pointeur nul, et crée un nouveau tableau de fonctions de transition et un nouveau tableau de voisinages
     */
    Biblio(): nb_automates(0), taille_tab(0), tab(nullptr), tf(new TabFtransit), tv(new TabVoisinage) {};
    /*!
     *  \brief Destructeur
     *  Destructeur (par défaut) de la classe Biblio
     */
    ~Biblio();
    /*!
     *  \brief Constructeur par recopie
     *  Annulé (=delete)
     */
    Biblio(const Biblio& a) = delete;
    /*!
     *  \brief Constructeur par affectation
     *  Annulé (=delete)
     */
    Biblio& operator=(const Biblio& a) = delete;
    
    mutable Automate** tab;/*!<Tableau de pointeurs sur des automates*/
    int nb_automates;/*!<Nombre d'automates*/
    int taille_tab;/*!<Taille de tableau*/
    TabFtransit* tf;/*!<Tableau de fonctions de transition*/
    TabVoisinage* tv;/*!<Tableau de voisinages*/

};
