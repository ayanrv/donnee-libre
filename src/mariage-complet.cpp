#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

vector<string> jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

/** Construction du tableau des mariages par années **/
vector<int> litTableauAnnee(string nom_fichier) {
    vector<int> tableau(13, 0); // Tableau pour les années 2010-2022
    ifstream flux_fichier(nom_fichier);
    if (!flux_fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier " + nom_fichier);
    }

    string ligne;
    while (getline(flux_fichier, ligne)) {
        stringstream flux_ligne(ligne);
        int annee, mariages;
        string jour;

        flux_ligne >> annee >> jour >> mariages;

        if (annee >= 2010 && annee <= 2022) {
            tableau[annee - 2010] += mariages;
        }
    }
    return tableau;
}

/** Renvoie le numéro du jour correspondant à la chaîne de caractères **/
int indiceJour(string jour) {
    for (int i = 0; i < jours.size(); i++) {
        if (jour == jours[i]) {
            return i;
        }
    }
    return -1;
}

/** Construction du tableau des mariages par jour **/
vector<int> litTableauJours(string nom_fichier) {
    vector<int> tableau(7, 0); // Tableau pour les jours de la semaine
    ifstream flux_fichier(nom_fichier);
    if (!flux_fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier " + nom_fichier);
    }

    string ligne;
    while (getline(flux_fichier, ligne)) {
        stringstream flux_ligne(ligne);
        int annee, mariages;
        string jour;

        flux_ligne >> annee >> jour >> mariages;

        int index = indiceJour(jour);
        if (index != -1) {
            tableau[index] += mariages;
        }
    }
    return tableau;
}

/** Renvoie la somme d'un tableau d'entiers **/
int somme(vector<int> t) {
    int total = 0;
    for (int valeur : t) {
        total += valeur;
    }
    return total;
}

/** Renvoie la moyenne d'un tableau d'entier **/
int moyenne(vector<int> t) {
    if (t.empty()) return 0;
    return somme(t) / t.size();
}

/** Renvoie l'indice de la valeur maximale du tableau **/
int indiceMax(vector<int> t) {
    if (t.empty()) return -1;
    int maxIndex = 0;
    for (int i = 1; i < t.size(); ++i) {
        if (t[i] > t[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

/** Formate un pourcentage avec une précision de 4 décimales **/
string formatPourcentage(double valeur, int precision = 4) {
    stringstream flux;
    int puissance = 1;
    for (int i = 0; i < precision; ++i) {
        puissance *= 10;
    }
    flux << (static_cast<int>(valeur * puissance)) / static_cast<double>(puissance);
    return flux.str();
}

/** Programme principal **/
int main() {
    string fichier = "donnees/statistiques-des-jours-des-mariages.txt";

    vector<int> tableauAnnee = litTableauAnnee(fichier);
    vector<int> tableauJours = litTableauJours(fichier);

    int totalMariages = somme(tableauAnnee);
    int moyenneMariages = moyenne(tableauAnnee);

    int anneeMax = indiceMax(tableauAnnee);
    int jourMax = indiceMax(tableauJours);

    double pourcentageSamedi = (static_cast<double>(tableauJours[5]) / totalMariages) * 100;

    // Afficher les résultats
    cout << "Le nombre total de mariages célébrés entre 2010 et 2022 est de " << totalMariages << endl;
    cout << "Le nombre de mariages célébrés en moyenne par an est de " << moyenneMariages << endl;
    cout << "L'année où l'on a célébré le plus de mariages est " << (2010 + anneeMax) 
         << " avec " << tableauAnnee[anneeMax] << " mariages" << endl;
    cout << "Le jour de la semaine où l'on célèbre le plus de mariages est le " << jours[jourMax] 
         << " avec " << tableauJours[jourMax] << " mariages" << endl;
    cout << "Le pourcentage de mariages célébrés le samedi est de " 
         << formatPourcentage(pourcentageSamedi) << "%" << endl;

    return 0;
}
