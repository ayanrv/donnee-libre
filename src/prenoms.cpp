#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/**
 * Programme pour analyser les prénoms donnés aux enfants
 * 1. Affiche le nombre total de naissances pour une année donnée.
 * 2. Identifie le prénom le plus donné cette année-là.
 */

// Fonction pour trouver ou ajouter un prénom dans deux tableaux parallèles
void ajouterPrenom(vector<string>& noms, vector<int>& frequences, const string& prenom, int naissances) {
    for (int i = 0; i < noms.size(); ++i) {
        if (noms[i] == prenom) {
            frequences[i] += naissances; // Ajouter les naissances à la fréquence existante
            return;
        }
    }
    // Si le prénom n'existe pas encore dans les tableaux, on l'ajoute
    noms.push_back(prenom);
    frequences.push_back(naissances);
}

int main() {
    // Chemin vers le fichier des prénoms
    string fichier = "donnees/liste_des_prenoms.txt";

    // Ouvrir le fichier
    ifstream flux_fichier(fichier);
    if (!flux_fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << fichier << endl;
        return 1;
    }

    // Demander une année à l'utilisateur
    int anneeRecherchee;
    cout << "Entrez une année entre 2004 et 2023 : ";
    cin >> anneeRecherchee;

    // Vérifier si l'année est valide
    if (anneeRecherchee < 2004 || anneeRecherchee > 2023) {
        cerr << "Erreur : Année invalide !" << endl;
        return 1;
    }

    // Variables pour analyser les données
    int totalNaissances = 0;
    vector<string> noms;        // Tableau des prénoms
    vector<int> frequences;     // Tableau des fréquences associées

    string ligne;
    while (getline(flux_fichier, ligne)) {
        stringstream flux_ligne(ligne);
        int annee, naissances;
        string genre, prenom;

        // Lire les données de la ligne
        flux_ligne >> annee >> genre >> prenom >> naissances;

        // Si la ligne correspond à l'année recherchée
        if (annee == anneeRecherchee) {
            totalNaissances += naissances; // Ajouter au total des naissances
            ajouterPrenom(noms, frequences, prenom, naissances); // Ajouter/mettre à jour le prénom
        }
    }

    flux_fichier.close();

    // Trouver le prénom le plus donné
    string prenomPlusDonne;
    int maxNaissances = 0;

    for (int i = 0; i < noms.size(); ++i) {
        if (frequences[i] > maxNaissances) {
            maxNaissances = frequences[i];
            prenomPlusDonne = noms[i];
        }
    }

    // Afficher les résultats
    cout << "En " << anneeRecherchee << ", il y a eu " << totalNaissances << " naissances" << endl;
    cout << "Le prénom le plus donné a été : " << prenomPlusDonne 
         << " (donné " << maxNaissances << " fois)" << endl;

    return 0;
}
