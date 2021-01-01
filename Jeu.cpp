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
	//G�n�ration du code al�atoire
	genererCode();
	//Seconde phase de la partie
	devinerCode();
}

void Jeu::modeVersus()
{
	//S�lection du code par l'utilisateur
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
		cout << "R�ponse : ";
		cin >> reponse;
		cout << endl;

		//Le syst�me v�rifie l'existence du mot
		if (!lexique_.chercherMot(reponse)) {
			cout << "Ce mot n'existe pas dans le lexique" << endl << endl;

			//Le syst�me affiche des suggestions
			cout << "Sugestions(s)" << endl;
			lexique_.recolterSuggestions(reponse);
			lexique_.afficherSuggestions();
		}
		else {
			//Le syst�me affiche des suggestions
			cout << "Sugestions(s)" << endl;
			lexique_.recolterSuggestions(reponse);
			lexique_.afficherSuggestions();

			//Le syst�me demande la confirmation de l'utilisateur
			cout << "Voulez-vous s�lectionner ce code? (1:oui/0:non) " << endl;
			cout << "R�ponse : ";
			cin >> selection;
			cout << endl;
		}

	} while (!selection);

	//Le syst�me sauvegarde la r�ponse
	codeSecret_ = reponse;
	cout << "Le code s�lectionn� est : " << codeSecret_ << endl << endl
		<< "D�but de la seconde partie..." << endl;

}

void Jeu::genererCode()
{
	//Le syst�me g�n�re un indice al�atoire
	int it = rand() % lexique_.getLexique().size();

	//On sauvegarde le code situ� � l'emplacement de l'indice
	codeSecret_ =  lexique_.getLexique().at(it);

}

void Jeu::devinerCode()
{
	int nbErreur = 0;
	do
	{
		//Affichage du nombre de lettre
		cout << "Le mot contient " << codeSecret_.size() << " lettres." << endl << endl;
		cout << "Votre r�ponse : ";
		string reponse;
		cin >> reponse;
		nbErreur = reponse.size();
		//V�rification de la longueur et de l'alphabet de la r�ponse
		if (!(reponse.size() == codeSecret_.size()) || !lexique_.verifierAlphabet(reponse)) {
			cout << "La proposition est invalide. Veuillez recommencer." << endl << endl;
		}
		else {
			/*Ins�rer la m�thode creerVerif()*/
			nbErreur = creerVerif(reponse);
			if (nbErreur == 0) {
				cout << endl << "FELICITATION ! Vous avez bien trouv� le code secret" << endl;
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
	cout << "Le code secret �tait : " << codeSecret_ << endl << endl;
	nbTentatives_ = 0;

}
