#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <limits>

using namespace std;

int values[5];

void printRules() {
	cout << "Zasady gry w kości \n";
	cout << "Każdy z graczy ma do dyspozycji 5 6-ściennych kości do gry. Po każdym rzucie, gracz może wybrać jedną kość, którą chce rzucić jeszcze raz. \n";
	cout << "Celem gry jest uzyskanie jak najwyższego układu oraz zwycięstwo w dwóch rundach na trzy możliwe. \n\n\n";
	cout << "Starszeństwo układów kości - od najniższego do najwyższego:\n";
	cout << "Nic – pięć nie tworzących żadnego układu oczek\n";
	cout << "Para – dwie kości o tej samej liczbie oczek\n";
	cout << "Dwie Pary – dwie pary kości, o tej samej liczbie oczek\n";
	cout << "Trójka – trzy kości o tej samej liczbie oczek\n";
	cout << "Mały Strit – kości pokazujące wartości od 1 do 5, po kolei\n";
	cout << "Duży Strit – kości pokazujące wartości od 2 do 6, po kolei\n";
	cout << "Full – jedna para i trójka\n";
	cout << "Kareta – cztery kości o tej samej liczbie oczek\n";
	cout << "Poker – pięć kości o tej samej liczbie oczek\n";
}

void throwing(int tab[], int strength) {
	srand(time(NULL));
	for (int i = 0; i < 5; i++) { //zapis wyrzuconych kości do tablicy
		for (int j = 1; j <= strength; j++)
		tab[i] = (rand() % 6) + 1;
	}
}

void display(int tab[]) {
	cout << "Wyrzuciłeś: "; //wyświetlenie wyrzuconych oczek
	for (int j = 0; j < 5; j++) {
		cout << tab[j] << "   ";
	}
	cout << endl;
}

void submit(int &score, int playerThrow[5]) {//obliczanie wynikow rzutow

	for (int i = 0; i < 5; i++) {//sortowanie babelkowe (żeby sprawdzić strita)
		for (int j = 1; j < 5 - i; j++) { //pętla wewnętrzna
			if (playerThrow[j - 1] > playerThrow[j]) {
				swap(playerThrow[j - 1], playerThrow[j]);
			}
		}
	}

	if (playerThrow[0] == 1) { //mały strit
		if (playerThrow[0] < playerThrow[1] && playerThrow[1] < playerThrow[2] && playerThrow[2] < playerThrow[3] && playerThrow[3] < playerThrow[4] && playerThrow[4] < playerThrow[5]) {
			score += 6;
		}
		else if (playerThrow[0] == 2) { //duży strit
			if (playerThrow[0] < playerThrow[1] && playerThrow[1] < playerThrow[2] && playerThrow[2] < playerThrow[3] && playerThrow[3] < playerThrow[4] && playerThrow[4] < playerThrow[5]) {
				score += 6.5;
			}
		}
	}

	for (int i = 1; i <= 6; i++) {
		values[i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		values[playerThrow[i]]++;
	}


	for (int i = 1; i <= 6; i++) {
		if (values[i] == 2) { //para
			score += 2;
		}
		else if (values[i] == 3) { //trójka
			score += 5;
		}
		else if (values[i] == 4) { //kareta
			score += 8;
		}
		else if (values[i] == 5) { //poker
			score += 10;
		}
	}

	switch (score) { // wypisanie wyrzuconych kombinacji zaleznie od score
	case 2:
		cout << "Wyrzuciłeś parę" << endl;
		break;
	case 4:
		cout << "Wyrzuciłeś 2 pary" << endl;
		break;
	case 5:
		cout << "Wyrzuciłeś trójkę" << endl;
		break;
	case 6:
		cout << "Wyrzuciłeś strita" << endl;
		break;
	case 7:
		cout << "Wyrzuciłeś fulla" << endl;
		break;
	case 8:
		cout << "Wyrzuciłeś karetę" << endl;
		break;
	case 10:
		cout << "Wyrzuciłeś pokera!" << endl;
		break;
	default:
		cout << "Nie wyrzuciłeś żadnego układu :(" << endl;
		break;
	}
}

void errorNum(int &value) { //walidacja bledow
	cin >> value;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Podałeś błędny znak! Podaj nowy!";
		cin >> value;
	}
}

void game() { //cala gra
	int strength, playerOne[5], playerTwo[5], whichOne, playerOneScore = 0, playerTwoScore = 0, counter = 1, playerOneRound = 0, playerTwoRound = 0;
	char choice;
	string player1, player2;

	cout << "Wprowadź imię gracza 1: ";
	cin >> player1;
	cout << "Wprowadź imię gracza 2: ";
	cin >> player2;

	while (counter <= 3) { //ilość rund (po 3 to koniec gry)


		// RZUCA GRACZ PIERWSZY


		cout << "RUNDA " << counter << " !" << endl;

		cout << "Teraz rzuca " << player1 << endl; //rzut pierwszego gracza
		cout << "Wybierz siłę rzutu (1-3): ";
		errorNum(strength);
		throwing(playerOne, strength); //rzucanie koścmi

		display(playerOne); //wyświetlanie wyrzuconych wartoœci

		cout << "Czy chcesz rzucić jeszcze raz? (T/N): "; //pytanie o ponowienie rzutu
		cin >> choice;

		if (choice == 'T' || choice == 't') { //drugi rzut
			cout << "Które kości chcesz przerzucić? ";
			cin >> whichOne;

			srand(time(NULL));
			playerOne[whichOne - 1] = (rand() % 6) + 1;

			display(playerOne); //wyświetlanie wyrzuconych wartości
		}

		submit(playerOneScore, playerOne);




		// RZUCA GRACZ DRUGI

		cout << "Teraz rzuca " << player2 << endl;
		cout << "Wybierz siłę rzutu (1-3): "; //rzut drugiego gracza
		errorNum(strength);

		throwing(playerTwo, strength); //rzucanie koścmi

		display(playerTwo); //wyświetlanie wyrzuconych wartości

		cout << "Czy chcesz rzucić jeszcze raz? (T/N): "; //pytanie o ponowienie rzutu
		cin >> choice;


		if (choice == 'T' || choice == 't') { //drugi rzut

			cout << "Które kości chcesz przerzucić? ";
			cin >> whichOne;

			srand(time(NULL));
			playerTwo[whichOne - 1] = (rand() % 6) + 1;

			display(playerTwo);
		}

		submit(playerTwoScore, playerTwo);

		if (playerOneScore > playerTwoScore) {
			cout << "Rundę " << counter << " wygrał(a) " << player1 << endl;
			playerOneRound++;
		}
		else if (playerTwoScore > playerOneScore) {
			cout << "Rundę " << counter << " wygrał(a) " << player2 << endl;
			playerTwoRound++;
		}
		else if (playerOneScore == playerTwoScore) {
			cout << "Remis!" << endl;
		}

		counter++;

		playerOneScore = 0;
		playerTwoScore = 0;


	} if (playerOneScore > playerOneScore) {
		cout << "Wygrywa " << player1 << " w stosunku: " << playerOneRound << ":" << playerTwoRound;
	} else {
		cout << "Wygrywa " << player2 << " w stosunku: " << playerTwoRound << ":" << playerOneRound;
	}

	system("pause");

}

void menuPanel() { // panel menu

	int menuChoicePanel;
	cin >> menuChoicePanel;
	switch (menuChoicePanel) {
	case 1:
		game();
		break;
	case 2:
		printRules();
		menuPanel();
		break;
	case 3:
		cout << "KONIEC";
		break;
	default:
		cout << "Zły parametr!";
		menuPanel();
		break;

	}

}


int main()
{
	int values[5];
	setlocale(LC_ALL, "");

	cout << endl << "				GRA W KOŚCI			" << endl << endl;
	cout << "************************************************************************" << endl << endl;
	cout << "		Autorzy: Szymon Ignaszak, Grzegorz Ratajczak" << endl << endl;;
	cout << "************************************************************************" << endl << endl;

	cout << "MENU: " << endl;
	cout << "1. Rozpocznij grę. " << endl;
	cout << "2. Pokaż instrukcje. " << endl;
	cout << "3. Wyjdź z gry. " << endl;
	cout << endl;
	menuPanel();

	return 0;
}
