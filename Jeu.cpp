#include "Jeu.h"

const int NB_TENTATIVES_MAX = 15;

Jeu::Jeu() : nbTentatives_(0)
{
}

void Jeu::associerLexique(const Lexique& lexique)
{
	lexique_ = lexique;
}

int Jeu::creerVerif(string proposition)
{
	int nbErreurs = 0;

	for (int i = 0; i < codeSecret_.size(); i++) {
		if (proposition[i] != codeSecret_[i])
			nbErreurs++;
	}
	
	return nbErreurs;
}

void Jeu::modeAuto()
{
	//Génération du code aléatoire
	genererCode();
	//Seconde phase de la partie
	devinerCode();
}

void Jeu::modeVersus()
{
	//Sélection du code par l'utilisateur
	selectionnerCode();
	//Seconde phase de la partie
	devinerCode();
}

void Jeu::selectionnerCode()
{
	bool selection = false;
	string reponse;

	do
	{
		//L'utilisateur entre son mot
		cout << "> Quel code ?" << endl;
		cout << "Réponse : ";
		cin >> reponse;
		cout << endl;

		//Le système vérifie l'existence du mot
		if (!lexique_.chercherMot(reponse)) {
			cout << "Ce mot n'existe pas dans le lexique" << endl << endl;

			//Le système affiche des suggestions
			cout << "Sugestions(s)" << endl;
			lexique_.recolterSuggestions(reponse);
			lexique_.afficherSuggestions();
		}
		else {
			//Le système affiche des suggestions
			cout << "Sugestions(s)" << endl;
			lexique_.recolterSuggestions(reponse);
			lexique_.afficherSuggestions();

			//Le système demande la confirmation de l'utilisateur
			cout << "Voulez-vous sélectionner ce code? (1:oui/0:non) " << endl;
			cout << "Réponse : ";
			cin >> selection;
			cout << endl;
		}

	} while (!selection);

	//Le système sauvegarde la réponse
	codeSecret_ = reponse;
	cout << "Le code sélectionné est : " << codeSecret_ << endl << endl
		<< "Début de la seconde partie..." << endl;

}

void Jeu::genererCode()
{
	//Le système génère un indice aléatoire
	int it = rand() % lexique_.getLexique().size();

	//On sauvegarde le code situé à l'emplacement de l'indice
	codeSecret_ =  lexique_.getLexique().at(it);

}

void Jeu::devinerCode()
{
	int nbErreur = 0;
	do
	{
		//Affichage du nombre de lettre
		cout << "Le mot contient " << codeSecret_.size() << " lettres." << endl << endl;
		cout << "Votre réponse : ";
		string reponse;
		cin >> reponse;
		nbErreur = reponse.size();
		//Vérification de la longueur et de l'alphabet de la réponse
		if (!(reponse.size() == codeSecret_.size()) || !lexique_.verifierAlphabet(reponse)) {
			cout << "La proposition est invalide. Veuillez recommencer." << endl << endl;
		}
		else {
			/*Insérer la méthode creerVerif()*/
			nbErreur = creerVerif(reponse);
			if (nbErreur == 0) {
				cout << endl << "FELICITATION ! Vous avez bien trouvé le code secret" << endl;
				break;
			}
			else {
				cout << "Votre proposition comporte " << nbErreur << " erreurs " << endl;
			}
		}
		nbTentatives_++;
		cout << endl << "Il vous reste " << NB_TENTATIVES_MAX - nbTentatives_ << " tentatives" << endl;
	} while (nbErreur!=0 && nbTentatives_ < NB_TENTATIVES_MAX );
	
	if (nbTentatives_ == NB_TENTATIVES_MAX)
		cout << "Vous avez perdu " << endl;
	cout << "Le code secret était : " << codeSecret_ << endl << endl;
	nbTentatives_ = 0;

}
