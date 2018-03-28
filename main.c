#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include "DeckStuff.h"

int main(void) {
    
    int deckSize = 52; //size of the deck, initially 52
    int turn = 0; //turn tracker -> evens for players, odds for computer
    int pScore = 0; //player score
    int pHandSize = 0; //player hand size
    //int pBooks = 0; //player books
    int cScore = 0; //computer score
    int cHandSize = 0; //computer hand size
    //int cBooks = 0; //computer books
    srand(time(0)); //start time for randomizer
    card *player = NULL, *computer = NULL; //hands for computer and player
    char playername[100]; //char array for player name
    char play = 'y'; //char to indicate play again
    
    while (play == 'y') //while the player wants to keep playing
    {
        //create the deck and shuffle it
        card *deck = deckMaker();
        ShuffleCard(deck, deckSize);
        
        //get player name and flush the input
        printf("Enter your first name: ");
        scanf("%s", playername);
        flush();
        
        //print the start message
        printf("><D ><D ><D ><D ><D ><D ><D ><D ><D ><D\n");
        printf("\t%s, Let's play Go Fish!!\n", playername);
        printf("><D ><D ><D ><D ><D ><D ><D ><D ><D ><D\n\n");
        
        //deal player cards, print cards by suit
        player = dealHand(&deck);
        pScore = checkForBook(&player);
        deckSize -= 7;
        printf("%s's hand has 7 cards\n", playername);
        printf("%s's Score: %d\n", playername, pScore);
        //print out the player's deck
        PrintDeck(&player);
        
        //deal computer cards, print cards by suit
        computer = dealHand(&deck);
        cScore = checkForBook(&computer);
        deckSize -= 7;
        printf("Computer's hand has 7 cards\n");
        printf("Computer Score: %d\n\n", cScore);
        
        printf("When ready, press 'G' to go!\n");
        char ch = 'n';
        while (ch != 'g')
        {
            ch = tolower(getchar());
            flush();
        }
        
        //game goes here and runs until all books have been found
        while (pScore + cScore < 13)
        {
            //shuffle deck before every turn
            ShuffleCard(deck, deckSize);
            //player
            if (turn % 2 == 0)
            {
                printf("\n%s's Turn!\n", playername);
                printf("Your score: %d\n", pScore);
                printf("Your hand:\n");
                PrintDeck(&player);
                int tryAgain = 1;
                int num = 0; //card player asks for
                while (tryAgain == 1)
                {
                    //ask for card
                    printf("Which card (1 for A, 2-10, 11 for J, 12 for Q, or 13 for K) would you like to ask for?");
                    scanf("%d", &num);
                    flush();
                    
                    //if not valid, ask for new card
                    while (num < 1 || num > 13)
                    {
                        printf("Not a valid entry, try again please!");
                        scanf("%d", &num);
                        flush();
                    }
                    
                    //check player's hand for the card they ask
                    int exist = searchHand(&player, num);
                    //if none exist, ask if they want to try again
                    //if no, ask again, else continue
                    if (exist == 0)
                    {
                        char print = num;
                        if (num == 1)
                            print = 'A';
                        else if (num == 11)
                            print = 'J';
                        else if (num == 12)
                            print = 'Q';
                        else if (num == 13)
                            print = 'K';
                        //if not a face card
                        if (num >= 2 && num <= 10)
                        {
                            printf("%s, there are no %d's in your hand.\n", playername, num);
                            printf("Are you sure you want to ask for %d? (Y or N)", num);
                        }
                        //if it is a face card
                        else
                        {
                            printf("%s, there are no %c's in your hand.\n", playername, print);
                            printf("Are you sure you want to ask for %c? (Y or N)", print);
                        }
                        char ch = tolower(getchar());
                        flush();
                        while (ch != 'y' && ch != 'n')
                        {
                            printf("Not a valid entry, try again please!");
                            ch = getchar();
                            flush();
                        }
                        if (ch == 'y')
                            tryAgain = 0;
                    }
                    //otherwise no problem
                    else
                        tryAgain = 0;
                }
                
                int exist = searchHand(&computer, num);
                if (exist == 0) //if computer does not have the card
                {
                    //if computer does not have it, say go fish and draw a card
                    //if card is card asked for -> player goes again
                    //else -> end turn
                    printf("\n><D ><D ><D ><D ><D ><D ><D ><D ><D ><D\n");
                    printf("\t\t\t\tGo Fish\n");
                    printf("><D ><D ><D ><D ><D ><D ><D ><D ><D ><D\n\n");
                    
                    if (deckSize != 0)
                    {
                        card* draw = dealCard(&deck);
                        deckSize--;
                        draw -> next = player; //add card to list
                        player = draw; //move up pointer to hand
                        if (draw -> face != num) //if card does not match requested, computer's turn
                            turn++; //else player goes again by not increasing turn
                    }
                    else
                    {
                        printf("There are no cards left!\n");
                        turn++;
                    }
                    int bookCheck = checkForBook(&player);
                    if (bookCheck == 1)
                    {
                        bookCheck = 0;
                        pScore++;
                    }
                }
                else //computer does have the card
                {
                    //swap cards from computer to player
                    swapHands(&player, &computer, num);
                    //check cards left in computer's hand
                    cHandSize = checkSize(&computer);
                    //if they have no cards left
                    if (cHandSize == 0 && deckSize != 0)
                    {
                        //if there are more than 7 cards in the deck, deal a whole new hand
                        if (deckSize >= 7)
                        {
                            computer = dealHand(&deck);
                            deckSize -= 7;
                        }
                        //if there are between zero and 6, deal all remaining cards
                        else
                        {
                            int i;
                            card* draw;
                            for (i = 0; i < deckSize; i++)
                            {
                                if (deckSize != 0)
                                {
                                    draw = dealCard(&deck);
                                    draw -> next = computer;
                                    computer = draw;
                                    deckSize--;
                                }
                            }
                        }
                    }
                    
                    //check to see if a book was made
                    int bookCheck = checkForBook(&player);
                    if (bookCheck == 1)
                    {
                        bookCheck = 0;
                        pScore++;
                        pHandSize = checkSize(&player);
                        if (pHandSize == 0 && deckSize != 0)
                        {
                            //if there are more than 7 cards in the deck, deal a whole new hand
                            if (deckSize >= 7)
                            {
                                player = dealHand(&deck);
                                deckSize -= 7;
                            }
                            //if there are between zero and 6, deal all remaining cards
                            else
                            {
                                int i;
                                card* draw;
                                for (i = 0; i < deckSize; i++)
                                {
                                    if (deckSize != 0)
                                    {
                                        draw = dealCard(&deck);
                                        draw -> next = player;
                                        player = draw;
                                        deckSize--;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //computer
            else
            {
                printf("\nComputer's Turn!\n");
                printf("Computer score: %d\n", cScore);
                //generate random card to pick using the randomizer
                int cardToAsk = (rand() % 12) + 1;
                //get char for face cards if needed
                char print = cardToAsk;
                if (cardToAsk == 1)
                    print = 'A';
                else if (cardToAsk == 11)
                    print = 'J';
                else if (cardToAsk == 12)
                    print = 'Q';
                else if (cardToAsk == 13)
                    print = 'K';
                
                //ask player if they have that card
                if (cardToAsk >= 2 && cardToAsk <= 10)
                {
                    printf("Do you have card(s) with %d?\n", cardToAsk);
                    PrintDeck(&player);
                    printf("Enter Y or y to give cards.\n");
                    printf("Enter N or n to say 'Go Fish'\n");
                }
                //if it is a face card
                else
                {
                    printf("Do you have card(s) with %c?\n", print);
                    PrintDeck(&player);
                    printf("Enter Y or y to give cards.\n");
                    printf("Enter N or n to say 'Go Fish'\n");
                }
                char answer = tolower(getchar());
                flush();
                //if the player says no, check to make sure they are not lying
                if (answer == 'n')
                {
                    //check the player's hand
                    int exist = searchHand(&player, cardToAsk);
                    //if it does exist, change answer to y and tell the player
                    if (exist != 0)
                    {
                        if (cardToAsk >= 2 && cardToAsk <= 10)
                            printf("\nYou DO have cards with %d\n", cardToAsk);
                        else
                            printf("\nYou DO have cards with %c\n", print);
                        answer = 'y';
                    }
                    //else, the computer draws a card
                    else
                    {
                        if (deckSize != 0)
                        {
                            //draw card
                            card* draw = dealCard(&deck);
                            //maintain deck size
                            deckSize--;
                            //add new card to front of the player's hand
                            draw -> next = computer;
                            computer = draw;
                            //if the card does not match the card they asked for, add it and turn is done
                            if (draw -> face != cardToAsk)
                                //value increases, ends turn
                                turn++;
                        }
                        else
                            turn++;
                        int bookCheck = checkForBook(&computer);
                        //if book is found
                        if (bookCheck == 1)
                        {
                            bookCheck = 0;
                            //increase computer score
                            cScore++;
                            //check computer hand size
                            cHandSize = checkSize(&computer);
                            if (cHandSize == 0 && deckSize != 0)
                            {
                                //if there are more than 7 cards in the deck, deal a whole new hand
                                if (deckSize >= 7)
                                {
                                    computer = dealHand(&deck);
                                    deckSize -= 7;
                                }
                                //if there are between zero and 6, deal all remaining cards
                                else
                                {
                                    int i;
                                    card* draw;
                                    for (i = 0; i < deckSize; i++)
                                    {
                                        draw = dealCard(&deck);
                                        draw -> next = computer;
                                        computer = draw;
                                        deckSize--;
                                    }
                                }
                            }
                        }
                    }
                }
                //if answer was y or is now y, give card
                if (answer == 'y')
                {
                    //check to see if they actually have the card
                    int exist = searchHand(&player, cardToAsk);
                    //if no, print that they do not and computer draws etc
                    if (exist == 0)
                    {
                        if (cardToAsk >= 2 && cardToAsk <= 10)
                            printf("You do NOT have cards with %d\n", cardToAsk);
                        else
                            printf("You do NOT have cards with %c\n", print);
                        //draw card
                        if (deckSize != 0)
                        {
                            card* draw = dealCard(&deck);
                            //maintain deck size
                            deckSize--;
                            //add new card to front of the player's hand
                            draw -> next = computer;
                            computer = draw;
                            //if the card does not match the card they asked for, add it and turn is done
                            if (draw -> face != cardToAsk)
                            {
                                //value increases, ends turn
                                turn++;
                                //check for books
                                int bookCheck = checkForBook(&computer);
                                //if book is found
                                if (bookCheck == 1)
                                {
                                    bookCheck = 0;
                                    //increase computer score
                                    cScore++;
                                    //check computer hand size
                                    cHandSize = checkSize(&computer);
                                    if (cHandSize == 0 && deckSize != 0)
                                    {
                                        //if there are more than 7 cards in the deck, deal a whole new hand
                                        if (deckSize >= 7)
                                        {
                                            computer = dealHand(&deck);
                                            deckSize -= 7;
                                        }
                                        //if there are between zero and 6, deal all remaining cards
                                        else
                                        {
                                            int i;
                                            card* draw;
                                            for (i = 0; i < deckSize; i++)
                                            {
                                                draw = dealCard(&deck);
                                                draw -> next = computer;
                                                computer = draw;
                                                deckSize--;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        else
                            turn++;
                    }
                    //they do have the card
                    else
                    {
                        //swap the cards over
                        swapHands(&computer, &player, cardToAsk);
                        //check player hand to make sure they have cards
                        pHandSize = checkSize(&player);
                        if (pHandSize == 0 && deckSize != 0)
                        {
                            //if there are more than 7 cards in the deck, deal a whole new hand
                            if (deckSize >= 7)
                            {
                                player = dealHand(&deck);
                                deckSize -= 7;
                            }
                            //if there are between zero and 6, deal all remaining cards
                            else
                            {
                                int i;
                                card* draw;
                                for (i = 0; i < deckSize; i++)
                                {
                                    if (deckSize != 0)
                                    {
                                        draw = dealCard(&deck);
                                        draw -> next = player;
                                        player = draw;
                                        deckSize--;
                                    }
                                }
                            }
                        }
                        //check for books for computer
                        int bookCheck = checkForBook(&computer);
                        if (bookCheck == 1)
                        {
                            bookCheck = 0;
                            //increase computer score
                            cScore++;
                            //check size of computer hand
                            cHandSize = checkSize(&computer);
                            if (cHandSize == 0 && deckSize != 0)
                            {
                                //if there are more than 7 cards in the deck, deal a whole new hand
                                if (deckSize >= 7)
                                {
                                    computer = dealHand(&deck);
                                    deckSize -= 7;
                                }
                                //if there are between zero and 6, deal all remaining cards
                                else
                                {
                                    int i;
                                    card* draw;
                                    for (i = 0; i < deckSize; i++)
                                    {
                                        if (deckSize != 0)
                                        {
                                            draw = dealCard(&deck);
                                            draw -> next = computer;
                                            computer = draw;
                                            deckSize--;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        printf("All books have been found!\n\n");
        if (pScore > cScore)
            printf("%s is the winner, WELL DONE!\n\n", playername);
        else
            printf("The computer won, better luck next time!\n\n");
        
        //end of game
        int end = 0;
        while (end == 0)
        {
            printf("Do you want to continue? (Q or q to quit): ");
            play = getchar();
            flush();
            if (tolower(play) == 'y')
            {
                end = 1;
                deckSize = 52;
            }
            else if (tolower(play) != 'q')
                printf("Not a valid input, please input y or q\n");
            else
                end = 1;
        }
    }
    return 0;
}



