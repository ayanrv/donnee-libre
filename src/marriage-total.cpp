#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/** 
 * Programme pour calculer et afficher :
 * 1. Le nombre total de mariages célébrés entre 2010 et 2022.
 * 2. Le nombre de mariages célébrés un samedi sur la même période.
 */
int main() {
    // Chemin vers le fichier contenant les données
    string fichier = "donnees/statistiques-des-jours-des-mariages.txt";

    // Ouvrir le fichier
    ifstream flux_fichier(fichier);
    if (!flux_fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << fichier << endl;
        return 1;
    }

    // Variables pour les statistiques
    int totalMariages = 0;         // Nombre total de mariages
    int mariagesSamedi = 0;        // Nombre de mariages le samedi
    string ligne;

    // Lire et traiter chaque ligne du fichier
    while (getline(flux_fichier, ligne)) {
        stringstream flux_ligne(ligne);
        string annee, jourDeLaSemaine;
        int mariages;

        // Analyse de la ligne (format attendu : année jourDeLaSemaine mariages)
        flux_ligne >> annee >> jourDeLaSemaine >> mariages;

        // Ajouter au total des mariages
        totalMariages += mariages;

        // Si le jour est "Samedi", ajouter au total des samedis
        if (jourDeLaSemaine == "Samedi") {
            mariagesSamedi += mariages;
        }
    }

    // Fermer le fichier après traitement
    flux_fichier.close();

    // Afficher les résultats
    cout << "Nombre total de mariages (2010-2022) : " << totalMariages << endl;
    cout << "Nombre de mariages le samedi (2010-2022) : " << mariagesSamedi << endl;

    return 0;
}
