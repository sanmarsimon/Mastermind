#pragma once

#ifndef JEU_H
#define JEU_H
#include "Lexique.h"
#include <memory>


using namespace std;
class Jeu {
public:
	Jeu();

	void associerLexique(const Lexique& lexique);
	int creerVerif(string proposition);
	void modeAuto();
	void modeVersus();

	void selectionnerCode();
	void genererCode();

	void devinerCode();

private:
	Lexique lexique_;
	string codeSecret_;
	int nbTentatives_;
};
#endif 
