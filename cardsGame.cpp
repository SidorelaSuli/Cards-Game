#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstdio>

using namespace std;

// The card type.
struct Card{
    int value;
    int color;
};

int Max (int a, int b) {
if (a>b){
    return a;
}
    return b;
}

// Shuffle the cards. Takes all the cards and card array size.
void shuffle ( struct Card cards[], int number ){
    srand ( time(NULL) );

    int i;
    for (i = number-1; i > 0; i--){  //number-1 because its in array.
        // Take a random index.
        int j = rand() % (i+1);
        // Swap cards
        struct Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

// Creates the deck, takes Card array and card array size.
void createDeck(struct Card cards[], int n){

    int color = 0;
    int value = 0;
    int i = 0;
    for( i = 0 ; i < n ; i++){
        if( i % 13 == 0){       // using mod for value.
            color++;
            value = 1;
        }

        cards[i].color = color;
        cards[i].value = value;
        value++;
    }
}

// used "clean up" memory for pulled cards. Takes card array and card array size (PulledCard).
void emptyCardArray(struct Card cards[], int n){

    int i;

    for(i = 0; i < n; i++){

        cards[i].value = -1;
        cards[i].color = -1;
    }
}

// Put pulled cars on screen. Takes Computer cards and player cards with their sizes.
void printCards( struct Card cards[], int n ){

    int i;
    for(i = 0 ; i < n; i++){
        if(cards[i].value != -1 && cards[i].color != -1)
            cout << "Card   value is: " << cards[i].value << " , Card color is: " << cards[i].color<< endl;
    }
}

// control if the hands are full. (pulled cards).
bool isFull(struct Card cards[], int n){

    int i = 0;

    for(i =0; i < n; i++){

        if(cards[i].value == -1 && cards[i].color == -1){
            return false;
        }
    }

    return true;

}

int main(){
    bool answer = true;
    while (answer == true){
    struct Card cards[52];  // The deck (from 0 to and 51)
    struct Card pulledCards[6]; // pulled cards for the computer and the player.

    struct Card playerCards[3];  // Player hand cards.
    struct Card computerCards[3];  // computer hand cards.

    createDeck(cards, 52);  // Create the deck.
    shuffle(cards, 52);     // Shuffle the deck.

    // Clean memory
    emptyCardArray(pulledCards, 6);
    emptyCardArray(playerCards, 3);
    emptyCardArray(computerCards, 3);

    // Variables to know how many cards we have in each hand.
    int pulledCard = 0;
    int playerCard = 0;
    int computerCard = 0;

    // Plays the game until every hand is full.
    while(!isFull(pulledCards, 6)){
        // pulls a card and then delete it from the deck (Player).
        struct Card player = cards[pulledCard];
        cards[pulledCard].value = -1;
        cards[pulledCard].color = -1;
        pulledCard++;

        // pulls a card and then delete it from the deck (computer).
        struct Card computer = cards[pulledCard];
        cards[pulledCard].value = -1;
        cards[pulledCard].color = -1;
        pulledCard++;
        // if the player pulled card and the computer pulled card has the same value then, pull again!. Otherwise continue.
        if(player.value == computer.value)
           continue; // repeats the while.

        // allocate the pulled cards in hands.
        pulledCards[playerCard +computerCard] = player;
        playerCards[playerCard] = player;
        playerCard++;
        pulledCards[playerCard +computerCard] = computer;
        computerCards[computerCard] = computer;
        computerCard++;


        cout << "Player Cards is" << endl;

        printCards(playerCards, 3);

        cout << "Computer Cards is" << endl;

        printCards(computerCards, 3);

        std::getchar();  // pause

    }
    cout << "Do you want to play again (y/n)?";
    char y_n;
    cin >> y_n;
    fflush(stdin);
    if (y_n == 'n') {
        answer = false;
    }
    }
    return 0;

}
