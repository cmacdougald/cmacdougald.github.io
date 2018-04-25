// MaoCardGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Card.h"
using namespace std;



int getSuiteValue(int intCard) {
	//Function to geth the suite value of the card
	return (intCard - 1) / 13;
}

string getFaceString(int intCard) {
	//Function to get the face as a string of a card
	int intFace = getFaceValue(intCard);
	string strFace = "";
	switch (intFace) {
		case 1:
			strFace = "Ace";
			break;
		case 11:
			strFace = "Jack";
			break;
		case 12:
			strFace = "Queen";
			break;
		case 13:
			strFace = "King";
			break;
		default:
			strFace += std::to_string(intFace);
	}
	return strFace;
}

string getSuiteString(int intCard) {
	//Returns the suite of the card as a string


int pickACard() {
	//Lets the user pick a random number
	int intCard = 0;
	do {
		cout << "Please enter a card number between 1 and 52: ";
		cin >> intCard;
	} while (intCard < 1 || intCard > 52);
	return intCard;
}

void printArrayOfCards(int aryDeck[], int intNumberOfCardsInArray = 52, bool boolShowIndex = false) {
	for (int intIndex = 0; intIndex < intNumberOfCardsInArray; intIndex++) {
		if (aryDeck[intIndex] != -1) {
			if (boolShowIndex) {
				cout << intIndex + 1 << ") ";
			}
			cout << getCardString(aryDeck[intIndex]) << endl;
		}
	}
}

void initializeArray(int aryArray[], int intNumberOfDecks = 1, int intValue = -1) {
	int intDeckIndex = 0;
	for (int intCurrentDeck = 1; intCurrentDeck <= intNumberOfDecks; intCurrentDeck++) {
		for (int intCurrentCard = 1; intCurrentCard <= 52; intCurrentCard++) {
			aryArray[intDeckIndex] = intValue;
			intDeckIndex++;
		}
	}
}

void createDeck(int aryDeck[], int intNumberOfDecks = 1) {
	int intDeckIndex = 0;
	for (int intCurrentDeck = 1; intCurrentDeck <= intNumberOfDecks; intCurrentDeck++) {
		for (int intCurrentCard = 1; intCurrentCard <= 52; intCurrentCard++) {
			aryDeck[intDeckIndex] = intCurrentCard;
			//cerr << getCardString(aryDeck[intDeckIndex]) << endl;
			intDeckIndex++;
		}
	}
}

void shuffleDeck(int aryDeck[], int &intDeckLocation, int intNumberOfDecks = 1) {
	int intTempCardStorage = 0;
	int intRandomCardIndex = 0;
	for (int intCardIndex = 0; intCardIndex < intNumberOfDecks * 52; intCardIndex++) {
		intRandomCardIndex = rand() % (intNumberOfDecks * 52);
		intTempCardStorage = aryDeck[intRandomCardIndex];
		aryDeck[intRandomCardIndex] = aryDeck[intCardIndex];
		aryDeck[intCardIndex] = intTempCardStorage;
	}
	intDeckLocation = 0;
}

int getCardFromDeck(int aryDeck[], int &intDeckLocation, int intNumberofDecks = 1) {
	if (intDeckLocation < intNumberofDecks * 52) {
		//cerr << "DEBUG: Deck Location = " << intDeckLocation << endl;
		return aryDeck[intDeckLocation++];
	}
	cerr << "ERROR: Invalid deck location." << endl;
	return -1;
}

int removeFromHand(int aryHand[], int intNumberOfDecks, int intRemoveIndex) {
	int intCard = aryHand[intRemoveIndex];
	while (intRemoveIndex + 1 < intNumberOfDecks * 52 - 1 &&
		aryHand[intRemoveIndex + 1] != -1) {
		cerr << "DEBUG:" << intRemoveIndex << ", "
			<< aryHand[intRemoveIndex] << ", "
			<< aryHand[intRemoveIndex + 1] << endl;
		aryHand[intRemoveIndex] = aryHand[intRemoveIndex + 1];
		intRemoveIndex++;
	}
	aryHand[intRemoveIndex] = -1;
	return intCard;
}

int getNumberOfCardsInHand(int aryHand[], int intNumberOfDecks) {
	int intNumberOfCards = 0;
	for (int intIndex = 0; intIndex < intNumberOfDecks * 52; intIndex++) {
		if (aryHand[intIndex] != -1) {
			intNumberOfCards++;
		}
	}
	return intNumberOfCards;
}

int promptForCard(int aryHand[], int intNumberOfDecks) {
	int intChoice = -1;
	int intNumberOfCards = getNumberOfCardsInHand(aryHand, intNumberOfDecks);
	cerr << "DEBUG:" << intNumberOfCards << endl;
	do {
		cout << "-1) to Pass" << endl;
		printArrayOfCards(aryHand, intNumberOfDecks * 52, true);
		cout << "Enter your choice: ";
		cin >> intChoice;
	} while (intChoice == 0 || intChoice > intNumberOfCards || intChoice < -1);
	return intChoice;
}

int addToHand(int aryHand[], int intNumberOfDecks, int intCardToAdd) {
	return 0;
}

void playerTurn(int intPlayerNumber, int aryHand[], int intNumberOfDecks) {
	cout << "Player " << intPlayerNumber << endl;
	int intRemoveCard = promptForCard(aryHand, intNumberOfDecks);
	if (intRemoveCard != -1) {
		removeFromHand(aryHand, intNumberOfDecks, intRemoveCard - 1);
	}
}


int main()
{
	srand(time(0)); //Setup the randomness at the beginning of the program
	const int INTNUMBEROFDECKS = 3;
	const int INTPLAYERHANDSIZE = 7;
	const int INTMAXPLAYERS = 6;
	int intNumberOfPlayers = 2;
	int intDeckLocation = 0;
	int intDiscardLocation = 0;
	int aryPlayerHand[INTMAXPLAYERS][52 * INTNUMBEROFDECKS];
	int aryDeck[52 * INTNUMBEROFDECKS];
	int aryDiscard[52 * INTNUMBEROFDECKS];
	int aryPlayerBets[INTMAXPLAYERS];
	createDeck(aryDeck, INTNUMBEROFDECKS);
	shuffleDeck(aryDeck, intDeckLocation, INTNUMBEROFDECKS);
	//cerr << (sizeof(aryDeck) / sizeof(aryDeck[0])) << endl;
	//printArrayOfCards(aryDeck, INTNUMBEROFDECKS * 52);

	for (int intPlayerIndex = 0; intPlayerIndex < INTMAXPLAYERS; intPlayerIndex++) {
		initializeArray(aryPlayerHand[intPlayerIndex], INTNUMBEROFDECKS);
	}
	
	//Give each player their cards.
	for (int intHandIndex = 0; intHandIndex < INTPLAYERHANDSIZE; intHandIndex++) {
		for (int intPlayerIndex = 0; intPlayerIndex < intNumberOfPlayers; intPlayerIndex++) {
			aryPlayerHand[intPlayerIndex][intHandIndex] = getCardFromDeck(aryDeck, intDeckLocation, INTNUMBEROFDECKS);
		}
	}

	for (int intPlayerIndex = 0; intPlayerIndex < intNumberOfPlayers; intPlayerIndex++) {
		playerTurn(intPlayerIndex + 1, aryPlayerHand[intPlayerIndex], INTNUMBEROFDECKS);
	}

    return 0;
}

