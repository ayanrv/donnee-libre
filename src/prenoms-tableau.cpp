#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

/** Lit un fichier et le charge dans un tableau 2D **/
vector<vector<string>> litTableau(string nom_fichier) {
    vector<vector<string>> tableau;
    ifstream flux_fichier(nom_fichier);
    if (!flux_fichier.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier " + nom_fichier);
    }

    string ligne;
    while (getline(flux_fichier, ligne)) {
        stringstream flux_ligne(ligne);
        vector<string> row;
        string valeur;
        while (flux_ligne >> valeur) {
            row.push_back(valeur);
        }
        tableau.push_back(row);
    }

    return tableau;
}

/** Affiche un tableau 2D **/
void afficheTableau(const vector<vector<string>>& tableau) {
    for (const auto& row : tableau) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

/** Filtre les lignes du tableau en fonction d'une colonne spécifique et d'une valeur **/
vector<vector<string>> selectLignes(const vector<vector<string>>& tableau, int colIndex, const string& valeur) {
    vector<vector<string>> result;
    for (const auto& row : tableau) {
        if (colIndex < row.size() && row[colIndex] == valeur) {
            result.push_back(row);
        }
    }
    return result;
}

/** Retourne les valeurs d'une colonne spécifique **/
vector<string> colonne(const vector<vector<string>>& tableau, int colIndex) {
    vector<string> col;
    for (const auto& row : tableau) {
        if (colIndex < row.size()) {
            col.push_back(row[colIndex]);
        }
    }
    return col;
}

/** Calcule la somme des valeurs d'une colonne numérique **/
int somme(const vector<int>& t) {
    int total = 0;
    for (int val : t) {
        total += val;
    }
    return total;
}

/** Renvoie l'indice de la valeur maximale dans un tableau **/
int indiceMax(const vector<int>& t) {
    if (t.empty()) return -1;
    int maxIndex = 0;
    for (int i = 1; i < t.size(); ++i) {
        if (t[i] > t[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

/** Formate un double avec une précision limitée en chaîne de caractères **/
string formatPourcentage(double valeur, int precision = 4) {
    stringstream flux;
    flux << static_cast<int>(valeur * 10000) / 10000.0; // Limite à 4 décimales
    return flux.str();
}

/** Programme principal **/
int main() {
    string fichier = "donnees/liste_des_prenoms.txt";

    // Charger le fichier dans un tableau 2D
    vector<vector<string>> tableau = litTableau(fichier);

    // Afficher le tableau pour vérification (optionnel)
    cout << "Contenu du tableau chargé : " << endl;
    afficheTableau(tableau);

    // Afficher le nombre total de naissances
    vector<string> naissanceStr = colonne(tableau, 3); // Colonne des naissances
    vector<int> naissances;
    for (const auto& n : naissanceStr) {
        naissances.push_back(stoi(n));
    }

    int totalNaissances = somme(naissances);
    cout << "Nombre total de naissances : " << totalNaissances << endl;

    // Demander un prénom à l'utilisateur
    string prenomRecherche;
    cout << "Choisissez un prénom : ";
    cin >> prenomRecherche;

    // Filtrer les lignes correspondant au prénom
    vector<vector<string>> lignesPrenom = selectLignes(tableau, 2, prenomRecherche);

    // Calculer les statistiques pour ce prénom
    int totalGarcons = 0, totalFilles = 0;
    string anneeMax;
    int maxOccurrences = 0;

    for (const auto& ligne : lignesPrenom) {
        int annee = stoi(ligne[0]);
        string genre = ligne[1];
        int naissances = stoi(ligne[3]);

        if (genre == "M") {
            totalGarcons += naissances;
        } else if (genre == "F") {
            totalFilles += naissances;
        }

        if (naissances > maxOccurrences) {
            maxOccurrences = naissances;
            anneeMax = ligne[0];
        }
    }

    // Afficher les résultats
    cout << "Le prénom " << prenomRecherche << " a été donné à " << totalGarcons
         << " garçons entre 2006 et 2023" << endl;
    cout << "Le prénom " << prenomRecherche << " a été donné à " << totalFilles
         << " filles entre 2006 et 2023" << endl;
    cout << "L'année où le prénom a été le plus donné est " << anneeMax
         << " avec " << maxOccurrences << " occurrences" << endl;

    // Calculer le pourcentage pour le prénom
    double pourcentage = (static_cast<double>(totalGarcons + totalFilles) / totalNaissances) * 100;
    cout << "Le pourcentage du prénom " << prenomRecherche << " est de " << formatPourcentage(pourcentage) << "%" << endl;

    return 0;
}