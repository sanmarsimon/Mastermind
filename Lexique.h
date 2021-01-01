#pragma once

#ifndef LEXIQUE_H
#define LEXIQUE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>
#include <unordered_set>
using namespace std;
class Lexique {
public:
	Lexique();
	~Lexique();

	bool creerLexique(string nomFichier);
	bool chercherMot(const string& mot);
	void recolterSuggestions(const string& mot);
	void afficherSuggestions();
	vector<string> getLexique();

	vector<char> convertirString(const string& mot);
	void creerAlphabet();
	vector<char> creerAlphabet(const vector<char>& mot);
	bool verifierAlphabet(const string& mot);

private:
	vector<string> lexique_;
	vector<string> suggestions_;
	unordered_set<char> alphabet_;
};

#endif