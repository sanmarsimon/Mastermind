#include "Jeu.h"

bool optionValide(int option)
{
	if (option == 1 || option == 2 || option == 3 || option == 4) { 
		return true; 
	}
	else {
		cout << "Veuillez choisir une option valide\n";
		return false;
	}
}

int main() {

	char entree;
	int option = 0;
	bool valide = false;
	Lexique lexique;
	Jeu jeu;
	string nomFichier;
	bool initialised = false;

	do
	{
		do
		{
			cout << "Veuillez choisir une option : \n\n";
			cout << "\t1. Initialisation du jeu\n";
			cout << "\t2. Partie contre l’ordinateur\n";
			cout << "\t3. Deux joueurs\n";
			cout << "\t4. Quitter\n";
			cout << endl;
			cin >> entree;

			if (!isalpha(entree)) {
				option = (int)entree - 48;
			}

		} while (!optionValide(option));

		switch (option)
		{
		case 1:
			cout << "\nVeuillez entrer le nom du fichier : ";
			cin >> nomFichier;
			initialised = lexique.creerLexique(nomFichier);
			jeu.associerLexique(lexique);
			if(initialised)
				cout << "\n\nLe jeu est initialisé !\n\n" << endl;
			break;
		
		case 2:
			if (!initialised) {
				cout << "\nErreur : le jeu n'as pas été initialisé ! \n" << endl;
				break;
			}
			jeu.modeAuto();
			initialised = false;
			break;
		
		case 3:
			if (!initialised) {
				cout << "\nErreur : le jeu n'as pas été initialisé ! \n" << endl;
				break;
			}
			jeu.modeVersus();
			initialised = false;
			break;
		
		case 4:
			cout << "\nMerci d'avoir joué. Au revoir !" << endl;
			break;
		}

	} while (option != 4);


}