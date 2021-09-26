#include "automatePerso.h"
int Etat::getCellule(size_t i, size_t j) const {
    //if (i >= hauteur || j >= largeur) throw
        //AutomateException("tentative d'acces a un etat non existant");
    return valeur[i][j];
}

void Etat::setCellule(size_t i, size_t j, int val) {
    if (i >= hauteur || j >= largeur) throw
        AutomateException("tentative d'acces a un etat non existant");
    valeur[i][j] = val;
}

Etat::Etat(size_t h, size_t l): hauteur(h), largeur(l) {
    valeur = new int* [hauteur];
    for (size_t i = 0; i < hauteur; i++){
        valeur[i] = new int [largeur];
        for (size_t j = 0; j < largeur; j++)
            valeur[i][j] = 0;
    }
}


Etat::Etat(const Etat& e): hauteur(e.hauteur), largeur(e.largeur) {
    valeur = new int* [hauteur];
    for (size_t i = 0; i < hauteur; i++){
        valeur[i] = new int [largeur];
        for (size_t j = 0; j < largeur; j++)
            valeur[i][j] = e.valeur[i][j];
    }
}

Etat& Etat::operator=(const Etat& e) {
    if (this == &e) // autoaffectation
        return *this;
    if (hauteur != e.hauteur || largeur != e.largeur) {
        // cr�er un nouveau tableau
        auto old = valeur;
        auto newtab = new int*[e.hauteur];
        for (size_t i = 0; i < hauteur; i++){
            valeur[i] = new int[e.largeur];
            for (size_t j = 0; j < largeur; j++)
                newtab[i][j] = e.valeur[i][j];
        }
        valeur = newtab;
        hauteur = e.hauteur;
        largeur = e.largeur;
        delete[] old; // d�truire l'ancien tableau
    }
    else {
        // valeur pointe sur un tableau de la bonne taille
        for (size_t i = 0; i < hauteur; i++)
            for (size_t j = 0; j < largeur; j++)
                valeur[i][j] = e.valeur[i][j];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& f, const Etat& e) {
    for (size_t i = 0; i < e.getHauteur(); i++){
        for (size_t j = 0; j < e.getLargeur(); j++)
            f << e.getCellule(i, j);
        f << "\n";
    }
    f << "---------------------------------------\n";
    return f;
}


int Automate::nombre_voisins(const Etat& e, size_t i, size_t j, int val) const{		//calcul le nombre de voisins ayant la valeur val
    int test=-1, r1, r2, r3, r4;
    size_t h = e.getHauteur();
    size_t l = e.getLargeur();
    int nb = 0;
    const Voisinage& v = voisinage;
    for(size_t k=1; k<=v.getRayon(); k++){
        if(limite){	//grille classique, pas tore
            r1 = i-k;
            r2 = j-k;
            r3 = i+k;
            r4 = j+k;
            if (v.getDiagonale() && r1 >= 0 && r2 >= 0 && e.getCellule(i - k, j - k) == val) //diag
                nb++;
            if (r1 >= 0 && e.getCellule(i - k, j) == val)
                nb++;
            if (v.getDiagonale() && r1 >= 0 && r4 <= l-1 && e.getCellule(i - k, j + k) == val) //diag
                nb++;
            if (r2 >= 0 && e.getCellule(i, j - k) == val)
                nb++;
            if (v.getDiagonale() && r3 <= h-1 && r2 >= 0 && e.getCellule(i + k, j - k) == val) //diag
                nb++;
            if (v.getDiagonale() && r3 <= h-1 && r4 <= l-1 && e.getCellule(i + k, j + k) == val) //diag
                nb++;
            if (r3 <= h-1 && e.getCellule(i + k, j) == val)
                nb++;
            if (r4 <= l-1 && e.getCellule(i, j + k) == val)
                nb++;
        }
        else{	//tore
            if (v.getDiagonale() && e.getCellule((i + h - k) % h, (j + l - k) % l) == val) //diag
                nb++;
            if (e.getCellule((i + h - k) % h, j % l) == val)
                nb++;
            if (v.getDiagonale() && e.getCellule((i + h - k) % h, (j + k) % l) == val) //diag
                nb++;
            if (e.getCellule(i % h, (j + l - k) % l) == val)
                nb++;
            if (v.getDiagonale() && e.getCellule((i + k) % h, (j + l - k) % l) == val) //diag
                nb++;
            if (v.getDiagonale() && e.getCellule((i + k) % h, (j + k) % l) == val) //diag
                nb++;
            if (e.getCellule((i + k) % h, j  % l) == val)
                nb++;
            if (e.getCellule(i % h, (j + k)  % l) == val)
                nb++;
        }
    }
    return nb;
}

void Automate::appliquerTransition(const Etat& dep, Etat& dest) const {
    dest = dep;

    int voisins = 0;

    for (size_t i = 0; i < dep.getHauteur(); i++){
        for(size_t j = 0; j < dep.getLargeur(); j++){
            for(size_t k = 0; k < fonction.getNbReglesF(); k++){		//on applique une à une les règles de la fonction
                int val = fonction.getRegle(k).getEtatVoisinsR();
                voisins = nombre_voisins(dep, i, j, val);			//calcul le nomre de voisins à prendre en compte
                if (dep.getCellule(i, j) == fonction.getRegle(k).getEtatDepartR() && voisins == fonction.getRegle(k).getNbVoisinsR()){  //si la règle est respectée
                    dest.setCellule(i, j, fonction.getRegle(k).getEtatCibleR());		//alors la cellule est changée comme l'indique la règle
                }
            }
        }
    }
}


void Simulateur::setEtatDepart(const Etat& e) {
    depart = &e;
    if (etats[0] == nullptr)
        etats[0] = new Etat(e); // construction par recopie
    else *etats[0] = e; // affectation
    rang = 0;
}

Simulateur::Simulateur(const Automate& a, size_t buffer):
    automate(a),nbMaxEtats(buffer),etats(new Etat* [buffer])
{
    // au d�but nous n'avons allou� aucun �tat :
    for (size_t i = 0; i < nbMaxEtats; i++)
        etats[i] = nullptr;
}

Simulateur::Simulateur(const Automate& a, const Etat& e, size_t buffer) :
    automate(a), nbMaxEtats(buffer), depart(&e),etats(new Etat*[buffer])
{
    etats[0] = new Etat(e);
    // au d�but nous n'avons allou� aucun �tat :
    for (size_t i = 1; i < nbMaxEtats; i++)
        etats[i] = nullptr;

}

void Simulateur::next() {
    if (depart == nullptr)
        throw AutomateException("etat de depart non defini");
    size_t prec = rang % nbMaxEtats;
    rang++;
    size_t current= rang % nbMaxEtats;
    if (etats[current] == nullptr)
        etats[current] = new Etat(etats[prec]->getHauteur(), etats[prec]->getLargeur());
    automate.appliquerTransition(*etats[prec], *etats[current]);
}

void Simulateur::run(size_t nbSteps) {
    for (size_t i = 0; i < nbSteps; i++) next();
}

const Etat& Simulateur::dernier() const {
    if (depart == nullptr)
        throw AutomateException("etat de depart non defini");
    return *etats[rang%nbMaxEtats];
}

Etat& Simulateur::dernier() {
    if (depart == nullptr)
        throw AutomateException("etat de depart non defini");
    return *etats[rang%nbMaxEtats];
}


const Automate& Biblio::createAutomate(const Voisinage& v, const Ftransit& f, bool l, std::string nom) { //on crée l'automate et on le place dans le tableau d'automate
    if (nb_automates == taille_tab){
        taille_tab += 5;
        Automate** new_tab = new Automate*[taille_tab];
        for(int i=0; i<nb_automates; i++){
            new_tab[i] = tab[i];
            delete tab[i];
        }
        Automate** old_tab = tab;
        tab = new_tab;
        delete[] old_tab;
    }
    tab[nb_automates] = new Automate(v, f, l, nom);
    nb_automates ++;
    return *tab[nb_automates-1];		//on retourne l'automate qui vient d'être créé
}

Biblio::~Biblio() {
    for(size_t i=0; i<nb_automates; i++) delete tab[i];
    delete[] tab;
}


// un attribut static doit �tre d�fini et initialis� dans un fichier source :
//Biblio* Biblio::instance=nullptr; // pointeur sur l'unique instance

Biblio::Handler Biblio::handler;

Biblio& Biblio::getInstance() {
    if (handler.instance == nullptr)
        handler.instance = new Biblio;
    return *handler.instance;
}

void Biblio::libererInstance() {
    delete handler.instance;
    handler.instance = nullptr;
}


void TabVoisinage::ajouterUnVoisinage(std::string n, bool d, int r){
    if (nb == taille_tab){
        taille_tab += 5;
        Voisinage** new_tab = new Voisinage*[taille_tab];
        for(int i=0; i<nb; i++)
            new_tab[i] = tab[i];
        Voisinage** old_tab = tab;
        tab = new_tab;
        delete[] old_tab;
    }
    tab[nb] = new Voisinage(n, d, r);
    nb++;
}


void TabFtransit::ajouterUneFtransit(std::string n, int etats, Regle** r, int nb_reg){
    if (nb == taille_tab){
        taille_tab += 5;
        Ftransit** new_tab = new Ftransit*[taille_tab];
        for(int i=0; i<nb; i++)
            new_tab[i] = tab[i];
        Ftransit** old_tab = tab;
        tab = new_tab;
        delete[] old_tab;
    }
    tab[nb] = new Ftransit(n, etats, r, nb_reg);
    nb++;
}


Ftransit::Ftransit(std::string n, int etats, Regle** r, int nb_reg): nom(n), nb_regles(nb_reg), liste_regles(nullptr), nb_etats(etats) {
        liste_regles = new Regle*[nb_regles];
        for(int i=0; i<nb_regles; i++)
            liste_regles[i] = r[i];
        delete[] r;
    }
/*Ftransit::Ftransit(const Ftransit& f) :
    nom(f.nom),
    nb_regles(f.nb_regles),
    nb_etats(f.nb_etats),
    liste_regles(new Regle*[f.nb_regles])
{
    for(int i = 0 ; i < nb_regles ; i++)
        liste_regles[i] = f.liste_regles[i] ;
}*/

/*
using namespace std ;

using time_point = chrono::system_clock::time_point ;
string serializeTimePoint(const time_point& time, const std::string& format) {
    time_t tt = chrono::system_clock::to_time_t(time) ;
    std::tm tm = *std::gmtime(&tt) ;
    std::stringstream ss ;
    ss << std::put_time(&tm, format.c_str()) ;
    return ss.str() ;
}

void Voisinage::save(string id) const {
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_voisinages.txt" ;
    ofstream monFlux (filepath, ios::app) ;
    if (monFlux) {
        monFlux << id << "|" << nom << "|" << rayon << "|" << (diagonale ? "True" : "False") << endl ;
    } else throw "ERREUR : Impossible d'ouvrir le fichier." ;
}

void Regle::save(string id) const {
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_regles.txt" ;
    ofstream monFlux (filepath, ios::app) ;
    if (monFlux) {
        monFlux << id << "|" << etat_depart << "|" << etat_cible << "|" << nb_voisins << "|" << etat_voisins << endl ;
    } else throw "ERREUR : Impossible d'ouvrir le fichier." ;
}

void Ftransit::save(string id) const {
    for (unsigned int i = 0 ; i < nb_regles ; i++) liste_regles[i]->save(id) ;
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_ftransit.txt" ;
    ofstream monFlux (filepath, ios::app) ;
    if (monFlux) {
        monFlux << id << "|" << nom << "|" << nb_regles << "|" << nb_etats << endl ;
    } else throw "ERREUR : Impossible d'ouvrir le fichier." ;
}

void Automate::save() const {
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_automates.txt" ;
    time_point input = chrono::system_clock::now() ;
    string id = serializeTimePoint(input, "%Y%m%d%H%M%S") ;
    voisinage.save(id) ;
    fonction.save(id) ;
    cout << filepath << endl ; // test
    ofstream monFlux (filepath, ios::app) ;
    if (monFlux) {
        monFlux << id << "|" << nom << "|" << (limite ? "True" : "False") << endl ;
    } else throw "ERREUR : Impossible d'ouvrir le fichier." ;
}

Automate& load_automate(std::string nomDeLAutomate) {
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_automates.txt" ;
    ifstream monFlux (filepath) ;
    stringstream file_content ;
    string line, id, nom ;
    bool limite, found = false ;
    const string delimiter = "|" ;
    size_t pos = 0 ;

    while (getline(monFlux, line)) {
        // id
        pos = line.find(delimiter) ;
        id = line.substr(0, pos) ;
        line.erase(0, pos + delimiter.length());
        // nom
        pos = line.find(delimiter) ;
        nom = line.substr(0, pos) ;
        line.erase(0, pos + delimiter.length()) ;
        // limite
        limite = ((line == "True") ? true : false) ;
        if (nom == nomDeLAutomate) {
            found = true ;
            break ;
    }}
    if (!found) throw AutomateException("Automaton not found !\n") ;
    else {
        // cout << "ID : " << id << " NOM : " << nom << " LIMITE : " << (limite ? "True" : "False") << endl ;
        const Voisinage& v = load_voisinage(id) ;
        const Ftransit& f = load_ftransit(id) ;
        Automate* automate_ptr = new Automate(v, f, limite, nom) ;
        return *automate_ptr ;
    }
}

Voisinage load_voisinage(std::string id) {
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_voisinages.txt" ;
    ifstream monFlux (filepath) ;
    stringstream file_content ;
    string line, nom, id_intoFile ;
    int rayon ;
    bool diagonale, found = false ;
    const string delimiter = "|" ;
    size_t pos = 0 ;

    while (getline(monFlux, line)) {
        // id
        pos = line.find(delimiter) ;
        id_intoFile = line.substr(0, pos) ;
        line.erase(0, pos + delimiter.length());
        // nom
        pos = line.find(delimiter) ;
        nom = line.substr(0, pos) ;
        line.erase(0, pos + delimiter.length()) ;
        // rayon
        pos = line.find(delimiter) ;
        rayon = stoi(line.substr(0, pos)) ;
        line.erase(0, pos + delimiter.length()) ;
        // diagonale
        diagonale = ((line == "True") ? true : false) ;
        if (id_intoFile == id) {
            found = true ;
            break ;
    }}
    if (!found) throw AutomateException("Automaton not found !\n") ;
    else {
        Voisinage v = Voisinage(nom, diagonale, rayon) ;
        return v ;
    }
}

Regle** load_regles(std::string id) {
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_regles.txt" ;
    ifstream monFlux (filepath) ;
    stringstream file_content ;
    string line, id_intoFile ;
    int etat_depart, etat_cible, nb_voisins, etat_voisins ;
    bool found = false ;
    vector<Regle> temp_vector ;
    const string delimiter = "|" ;
    size_t pos = 0 ;

    while (getline(monFlux, line)) {
        // id
        pos = line.find(delimiter) ;
        id_intoFile = line.substr(0, pos) ;
        line.erase(0, pos + delimiter.length());
        // etat_depart
        pos = line.find(delimiter) ;
        etat_depart = stoi(line.substr(0, pos)) ;
        line.erase(0, pos + delimiter.length()) ;
        // etat_cible
        pos = line.find(delimiter) ;
        etat_cible = stoi(line.substr(0, pos)) ;
        line.erase(0, pos + delimiter.length()) ;
        // nb_voisins
        pos = line.find(delimiter) ;
        nb_voisins = stoi(line.substr(0, pos)) ;
        line.erase(0, pos + delimiter.length()) ;
        // etat_voisins
        etat_voisins = stoi(line) ;
        if (id_intoFile == id) {
            found = true ;
            temp_vector.push_back(Regle(etat_depart, etat_cible, nb_voisins, etat_voisins)) ;
        }
    }
    if (!found) throw AutomateException("Automaton not found !\n") ;
    else {
        Regle** tabRegle = new Regle*[temp_vector.size()] ;
        for (unsigned int i = 0 ; i < temp_vector.size() ; i++) {
            tabRegle[i] = new Regle(temp_vector[i].getEtatDepartR(), temp_vector[i].getEtatCibleR(), temp_vector[i].getNbVoisinsR(), temp_vector[i].getEtatVoisinsR()) ;
        }
        return tabRegle ;
    }
}

Ftransit load_ftransit(std::string id) {
    string filepath = std::filesystem::current_path().string() + "/sauvegarde_ftransit.txt" ;
    ifstream monFlux (filepath) ;
    stringstream file_content ;
    string line, nom, id_intoFile ;
    int nb_regles, nb_etats ;
    bool found = false ;
    const string delimiter = "|" ;
    size_t pos = 0 ;
    while (getline(monFlux, line)) {
        // id
        pos = line.find(delimiter) ;
        id_intoFile = line.substr(0, pos) ;
        line.erase(0, pos + delimiter.length());
        // nom
        pos = line.find(delimiter) ;
        nom = line.substr(0, pos) ;
        line.erase(0, pos + delimiter.length()) ;
        // nb_regles
        pos = line.find(delimiter) ;
        nb_regles = stoi(line.substr(0, pos)) ;
        line.erase(0, pos + delimiter.length()) ;
        // nb_etats
        nb_etats = stoi(line) ;
        if (id_intoFile == id) {
            found = true ;
            break ;
    }}
    if (!found) throw AutomateException("Automaton not found !\n") ;
    else  {
        Ftransit ftransit(nom, nb_etats, load_regles(id), nb_regles) ;
        return ftransit ;
    }
}*/
