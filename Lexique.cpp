#include "Lexique.h"

int min(unsigned int a, unsigned int b) {
	return a < b ? a : b;
}

Lexique::Lexique()
{
}

Lexique::~Lexique()
{
}

bool Lexique::creerLexique(string nomFichier)
{
	ifstream fichier(nomFichier);
	string mot;

	if (fichier.fail()) {
		cout << "\nProblème lors de l'ouverture du fichier." << endl << endl;
		return false;
	}
	else {
		while (fichier.peek() != EOF) {
			getline(fichier, mot);
			lexique_.push_back(mot);
		}
		creerAlphabet();
		return true;
	}
}

bool Lexique::chercherMot(const string& mot)
{
	for (string& ref : lexique_)
	{
		if (mot == ref) { return true; }
	}
	return false;
}

void Lexique::recolterSuggestions(const string& mot)
{
	//Convertir le string en une chaîne de caractères
	vector<char> patron = convertirString(mot);

	//Définir les états
	vector<vector<char>> etats;
	for (int i = 0; i < patron.size() + 1; i++){
		vector<char> etat;
		for (int j = 0; j < i; j++) {
			etat.push_back(patron[j]);
		}
		etats.push_back(etat);
	}
	
	//Définir le vocabulaire
	vector<char> vocabulaire = creerAlphabet(patron);
	
	//Construction de la fonction de placement
	vector<vector<int>> delta;
	vector<int> echo;
	int k = 0;
	for (unsigned int i = 0; i < patron.size() + 1; i++) {
		for (unsigned int j = 0; j < vocabulaire.size(); j++) {

			//Création du mot temporaire
			vector<char> temp = etats[i];
			temp.push_back(vocabulaire[j]);
			bool same = true;
			k = min(patron.size() + 1, i + 2);
			do {
				same = true;
				k = k - 1;

				//Comparaison du préfixe avec le postfixe
				for (unsigned int l = 0; l < k; l++) {
					if (patron[l] != temp[temp.size() - (k-1) + (l-1)])
						same = false;
				}
			} while (k > 0 && !same);
			echo.push_back(k);
		}
		delta.push_back(echo);
		echo.clear();
	}

	//Afficher les suggestions
	suggestions_.clear();
	for (auto& combinaison : lexique_) {
		int state = 0;
		int caractere = 0;
		for (auto& lettre : combinaison) {
			bool valide = false;
			for (int i = 0; i < vocabulaire.size(); i++) {
				if (lettre == vocabulaire[i]) {
					valide = true;
					caractere = i;
					state = delta[state][caractere];
				}
			}
			if (!valide) {
				state = 0;
			}
			if (state == patron.size()) {
				suggestions_.push_back(combinaison);
				break;
			}
		}
	}
}

void Lexique::afficherSuggestions()
{
	for (auto& suggestion : suggestions_)
		cout << suggestion << endl;
}

vector<string> Lexique::getLexique()
{
	return lexique_;
}

vector<char> Lexique::convertirString(const string& mot)
{
	vector<char> chars(mot.c_str(), mot.c_str() + mot.size() + 1);
	chars.pop_back();
	return chars;
}

vector<char> Lexique::creerAlphabet(const vector<char>& mot)
{
	vector<char> vocabulaire;
	for (int i = 0; i < mot.size(); i++) {
		bool doublon = false;
		for (int j = 0; j < vocabulaire.size(); j++) {
			if (vocabulaire[j] == mot[i])
				doublon = true;
		}
		if (!doublon) {
			vocabulaire.push_back(mot[i]);
		}
	}
	return vocabulaire;
}

void Lexique::creerAlphabet() {
	for (int i = 0; i < lexique_.size(); i++) {
		for (int j = 0; j < lexique_[i].size(); j++) {
			alphabet_.insert(lexique_[i][j]);
		}
	}
}

bool Lexique::verifierAlphabet(const string& mot)
{
	for (int i = 0; i < mot.size(); i++) {
		if (alphabet_.find(mot[i]) == alphabet_.end())
			return false;
	}
	return true;
}

