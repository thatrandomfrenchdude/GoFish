#ifndef DeckStuff_h
#define DeckStuff_h

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//to make dynamic list of cards
typedef struct card_s
{
    char suit;
    int face;
    struct card_s *next;
} card;

//flush the input
void flush()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {}
}

//creates a new deck and returns a pointer to the first card
card* deckMaker()
{
    card* deck = NULL;
    int i, j; //ints for for loops
    
    for (i = 0; i < 4; i++)
    {
        //outer loop for suits, inner for faces
        for (j = 1; j <= 13; j++)
        {
            //memory for a new card in the deck
            card* newCard = (card*)malloc(sizeof(card));
            
            if (i == 0) //first loop is hearts
                newCard -> suit = 'H';
            else if (i == 1) //second loop is diamonds
                newCard -> suit = 'D';
            
            else if (i==2) //third loop is spades
                newCard -> suit = 'S';
            
            else if (i==3) //fourth loop is clubs
                newCard -> suit = 'C';
            
            //set face of the new card
            //1 for Ace
            //2 - 10 for number cards
            //11 for Jack
            //12 for Queen
            //13 for King
            newCard -> face = j;
            newCard -> next = NULL;
            
            if (deck == NULL)
                deck = newCard;
            else
            {
                //add new card to the head of the deck
                newCard -> next = deck;
                deck = newCard;
            }
        }
    }
    return deck;
}

//This function prints the deck
void PrintDeck(card** first)
{
    //int count = 0;
    int i;
    
    //loops to print out the suit
    for (i = 1; i < 14; i++)
    {
        card *temp = *first;
        while (temp != NULL) //while you dont reach the end
        {
            //print by card num
            if (temp -> face == i && temp -> suit == 'H') //hearts
            {
                if (i == 1)
                    printf("A of H\n");
                else if (i == 11)
                    printf("J of H\n");
                else if (i == 12)
                    printf("Q of H\n");
                else if (i == 13)
                    printf("K of H\n");
                else
                    printf("%d of H\n", temp -> face);
            }
            else if (temp -> face == i && temp -> suit == 'D') //diamonds
            {
                if (i == 1)
                    printf("A of D\n");
                else if (i == 11)
                    printf("J of D\n");
                else if (i == 12)
                    printf("Q of D\n");
                else if (i == 13)
                    printf("K of D\n");
                else
                    printf("%d of D\n", temp -> face);
            }
            else if (temp -> face == i && temp -> suit == 'S') //spades
            {
                if (i == 1)
                    printf("A of S\n");
                else if (i == 11)
                    printf("J of S\n");
                else if (i == 12)
                    printf("Q of S\n");
                else if (i == 13)
                    printf("K of S\n");
                else
                    printf("%d of S\n", temp -> face);
            }
            else if (temp -> face == i && temp -> suit == 'C')//clubs
            {
                if (i == 1)
                    printf("A of C\n");
                else if (i == 11)
                    printf("J of C\n");
                else if (i == 12)
                    printf("Q of C\n");
                else if (i == 13)
                    printf("K of C\n");
                else
                    printf("%d of C\n", temp -> face);
            }
            
            
//            //print by suit (for loop from 0 to 4)
//            if (i == 0) //hearts
//            {
//                if (temp -> face == 1 && temp -> suit == 'H') //ace represents the first card of each suit
//                    printf("A of %c\n", temp -> suit);
//                else if (temp -> face == 11 && temp -> suit == 'H') //jack represents the 11th card
//                    printf("J of %c\n", temp -> suit);
//                else if (temp -> face == 12 && temp -> suit == 'H') //queen represents the 12th card
//                    printf("Q of %c\n", temp -> suit);
//                else if (temp -> face == 13 && temp -> suit == 'H') //king represents the 13th (last card)
//                    printf("K of %c\n", temp -> suit);
//                else if (temp -> suit == 'H') //all the regular numbered cards
//                    printf("%d of %c\n", temp -> face, temp -> suit);
//            }
//            else if (i == 1) //diamonds
//            {
//                if (temp -> face == 1 && temp -> suit == 'D') //ace represents the first card of each suit
//                    printf("A of %c\n", temp -> suit);
//                else if (temp -> face == 11 && temp -> suit == 'D') //jack represents the 11th card
//                    printf("J of %c\n", temp -> suit);
//                else if (temp -> face == 12 && temp -> suit == 'D') //queen represents the 12th card
//                    printf("Q of %c\n", temp -> suit);
//                else if (temp -> face == 13 && temp -> suit == 'D') //king represents the 13th (last card)
//                    printf("K of %c\n", temp -> suit);
//                else if (temp -> suit == 'D') //all the regular numbered cards
//                    printf("%d of %c\n", temp -> face, temp -> suit);
//            }
//            else if (i == 2) //spades
//            {
//                if (temp -> face == 1 && temp -> suit == 'S') //ace represents the first card of each suit
//                    printf("A of %c\n", temp -> suit);
//                else if (temp -> face == 11 && temp -> suit == 'S') //jack represents the 11th card
//                    printf("J of %c\n", temp -> suit);
//                else if (temp -> face == 12 && temp -> suit == 'S') //queen represents the 12th card
//                    printf("Q of %c\n", temp -> suit);
//                else if (temp -> face == 13 && temp -> suit == 'S') //king represents the 13th (last card)
//                    printf("K of %c\n", temp -> suit);
//                else if (temp -> suit == 'S') //all the regular numbered cards
//                    printf("%d of %c\n", temp -> face, temp -> suit);
//            }
//            else //clubs
//            {
//                if (temp -> face == 1 && temp -> suit == 'C') //ace represents the first card of each suit
//                    printf("A of %c\n", temp -> suit);
//                else if (temp -> face == 11 && temp -> suit == 'C') //jack represents the 11th card
//                    printf("J of %c\n", temp -> suit);
//                else if (temp -> face == 12 && temp -> suit == 'C') //queen represents the 12th card
//                    printf("Q of %c\n", temp -> suit);
//                else if (temp -> face == 13 && temp -> suit == 'C') //king represents the 13th (last card)
//                    printf("K of %c\n", temp -> suit);
//                else if (temp -> suit == 'C') //all the regular numbered cards
//                    printf("%d of %c\n", temp -> face, temp -> suit);
//            }
            temp = temp->next; //move pointer down
            //count++; //keep a count of the cards
        }
    }
    printf("\n");
}

//shuffles the deck
void ShuffleCard (card *deck, int numCards) //shuffles the deck
{
    if (numCards > 1)
    {
        int rand1, rand2;
        card *pt1, *pt2;
        card *temp;
        int i, j;
        
        for (i = 0; i< 2000; i++) //swap 2000 times so that the deck is adequately shuffled. Does not affect time complexity
        {
            //both pt1 & pt2 point to the first node
            pt1 = deck;
            pt2 = deck;
            
            //two rand numbers generated are the ones to be swapped
            rand1 = rand() % numCards;
            rand2 = rand() % numCards;
            
            //if they are equal, don't waste a swap, find a new rand2
            while (rand1 == rand2)
                rand2 = rand() % numCards;
            
            //find the rand1-th card
            for (j = 0; j < rand1; j++)
                pt1 = pt1 -> next;
            
            //find the rand2-th card
            for (j = 0; j < rand2; j++)
                pt2 = pt2 -> next;
            
            //malloc space for the temporary card
            temp = (card*)malloc(sizeof(card));
            
            //swap the cards using temp to hold a value
            temp -> suit = pt1 -> suit;
            temp -> face = pt1 -> face;
            pt1 -> suit = pt2 -> suit;
            pt1 -> face = pt2 -> face;
            pt2 -> suit = temp -> suit;
            pt2 -> face = temp -> face;
            
            //free memory that was allocated
            free(temp);
        }
    }
}

//delete a card from the deck and return a pointer to that card
card* DeleteCard (card **list1)
{
    if (list1 == NULL)
        return NULL;
    else
    {
        //set deleted card to head of the list1
        card *deletedCard = *list1;
        //move list down
        *list1 = (*list1) -> next;
        //unlink deleted card
        deletedCard -> next = NULL;
        return deletedCard;
    }
}

//returns a single card from the deck
card* dealCard(card** deck)
{
    card* myCard = DeleteCard(deck);
    return myCard;
}

//returns a hand of 7 cards from the deck
card* dealHand(card** deck)
{
    //add first of 7 cards to hand
    card* myCard = DeleteCard(deck);
    card* temp = myCard;
    int i;
    //add 6 new cards to head of hand
    for (i = 0; i < 6; i++)
    {
        temp = DeleteCard(deck);
        temp -> next = myCard;
        myCard = temp;
    }
    return myCard;
}

//returns the number of a requested card in a hand
int searchHand(card** hand, int val)
{
    int exist = 0; //number of a card in a hand, initially 0
    card* temp = *hand; //temp value for hand
    while (temp != NULL)
    {
        if (temp -> face == val)
            exist++;
        temp = temp -> next;
    }
    return exist;
}

//this function moves the card from one hand to the other
void swapHands(card** toHand, card** fromHand, int val)
{
    int flag = 0;
    card* saveHead = NULL;
    card* nextCard = NULL;
    
    //if there are three or more elements in the list
    //max number of matches possible in a swap is 3, otherwise we would have had a book
    if ((*fromHand) -> next != NULL && (*fromHand) -> next -> next != NULL)
    {
        int matches = 0;
        while (matches < 3 && (*fromHand) -> face == val)
        {
            //first card is guaranteed
            //save the initial card
            card* temp = *fromHand;
            //move fromHand down
            *fromHand = (*fromHand) -> next;
            //add temp to toHand
            temp -> next = *toHand;
            //move to toHand up
            *toHand = temp;
            matches++;
        }
        //save the value of fromHand
        saveHead = (*fromHand);
        //if we have found all three matches, we are done
        //else, set the card after fromHand to nextCard and check that from now on
        if (matches != 3)
        {
            //set the next value since we know we have at least two
            nextCard = (*fromHand) -> next;
            //run until nextCard is NULL
            while (nextCard != NULL)
            {
                //if the next card is the card we need
                if (nextCard -> face == val)
                {
                    //save nextCard
                    card* temp = nextCard;
                    //cut nextCard out of the list
                    (*fromHand) -> next = nextCard -> next;
                    //add temp to the toHand
                    temp -> next = *toHand;
                    //put toHand back
                    *toHand = temp;
                    //flag change indicating we do not move down
                    flag = 1;
                }
                //move fromHand down if there was NOT a change
                if (flag == 0)
                    *fromHand = (*fromHand) -> next;
                //set next to be the next card after current card
                nextCard = (*fromHand) -> next;
                //reset flag
                flag = 0;
            }
            *fromHand = saveHead;
        }
    }
    //else if there are two elements in the list, at least one will match
    else if ((*fromHand) -> next != NULL)
    {
        //if the first one matches
        if ((*fromHand) -> face == val)
        {
            //save the initial card
            card* temp = *fromHand;
            //move fromHand down
            *fromHand = (*fromHand) -> next;
            //add temp to toHand
            temp -> next = *toHand;
            //move to toHand up
            *toHand = temp;
            //check next node which will be the last one
            if ((*fromHand) -> face == val)
            {
                //set temp to fromHand
                card* temp = *fromHand;
                //put temp on the front of toHand
                temp -> next = *toHand;
                //mive up toHand
                *toHand = temp;
                //make the return hand empty
                *fromHand = NULL;
            }
        }
        //if the first node did not match, the second one will
        else
        {
            //save fromHand
            saveHead = (*fromHand);
            //move fromHand down
            *fromHand = (*fromHand) -> next;
            //set temp to fromHand
            card* temp = *fromHand;
            //set next of current fromHand to toHand
            temp -> next = *toHand;
            //move toHand up
            *toHand = temp;
            //cut off the rest of saveHead;
            saveHead -> next = NULL;
            //set fromHand back to what it was
            *fromHand = saveHead;
        }
    }
    //else there is only one, it will match
    else
    {
        //set temp to fromHand
        card* temp = *fromHand;
        //put temp on the front of toHand
        temp -> next = *toHand;
        //mive up toHand
        *toHand = temp;
        //make the return hand empty
        *fromHand = NULL;
    }
}

//returns a book if found
//function also deletes cards when a book is made to avoid memory leaks
int checkForBook(card** hand)
{
    //declarations
    card* head = *hand;
    card* temp = head;
    card* toFree = NULL;
    //card* saveHand = NULL;
    int books = 0;
    int val = 0;
    int ace = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int seven = 0;
    int eight = 0;
    int nine = 0;
    int ten = 0;
    int jack = 0;
    int queen = 0;
    int king = 0;
    
    //loop through all cards looking for a book
    //when a book is completed, save which card has a completed book
    //set temp to null to end the while loop
    while (temp != NULL)
    {
        if (temp -> face == 1)
        {
            ace++;
            if (ace == 4)
            {
                books++;
                val = 1;
                temp = NULL;
            }
        }
        else if (temp -> face == 2)
        {
            two++;
            if (two == 4)
            {
                books++;
                val = 2;
                temp = NULL;
            }
        }
        else if (temp -> face == 3)
        {
            three++;
            if (three == 4)
            {
                books++;
                val = 3;
                temp = NULL;
            }
        }
        else if (temp -> face == 4)
        {
            four++;
            if (four == 4)
            {
                books++;
                val = 4;
                temp = NULL;
            }
        }
        else if (temp -> face == 5)
        {
            five++;
            if (five == 4)
            {
                books++;
                val = 5;
                temp = NULL;
            }
        }
        else if (temp -> face == 6)
        {
            six++;
            if (six == 4)
            {
                books++;
                val = 6;
                temp = NULL;
            }
        }
        else if (temp -> face == 7)
        {
            seven++;
            if (seven == 4)
            {
                books++;
                val = 7;
                temp = NULL;
            }
        }
        else if (temp -> face == 8)
        {
            eight++;
            if (eight == 4)
            {
                books++;
                val = 8;
                temp = NULL;
            }
        }
        else if (temp -> face == 9)
        {
            nine++;
            if (nine == 4)
            {
                books++;
                val = 9;
                temp = NULL;
            }
        }
        else if (temp -> face == 10)
        {
            ten++;
            if (ten == 4)
            {
                books++;
                val = 10;
                temp = NULL;
            }
        }
        else if (temp -> face == 11)
        {
            jack++;
            if (jack == 4)
            {
                books++;
                val = 11;
                temp = NULL;
            }
        }
        else if (temp -> face == 12)
        {
            queen++;
            if (queen == 4)
            {
                books++;
                val = 12;
                temp = NULL;
            }
        }
        else //if temp -> face == 13
        {
            king++;
            if (king == 4)
            {
                books++;
                val = 13;
                temp = NULL;
            }
        }
        if (temp != NULL)
            temp = temp -> next;
    }
    temp = head;
    //if book is found, loop again and free cards from book
    if (books != 0)
    {
        printf("\nBook found!\n");
        //loop through deck
        while (temp != NULL)
        {
            //if the first card in the list needs to be freed
            if (temp -> face == val)
            {
                //set toFree to temp
                toFree = temp;
                //move temp down
                temp = temp -> next;
                //cut off toFree
                toFree -> next = NULL;
                //set toFree to NULL
                toFree = NULL;
                //free the memory
                free(toFree);
                head = temp;
            }
            //if we are on the last card in the list
            else if (temp -> next == NULL)
            {
                //if it matches
                if (temp -> face == val)
                {
                    //we can fee temp directly since we are on the last node
                    //set temp to NULL
                    temp = NULL;
                    //free temp
                    free(temp);
                }
                else
                    temp = temp -> next;
            }
            //else if it is not the first
            else if (temp -> next -> face == val)
            {
                //set toFree to temp -> next
                toFree = temp -> next;
                //remove it from the list
                temp -> next = temp -> next -> next;
                //DO NOT MOVE TEMP DOWN
                //cut off toFree
                toFree -> next = NULL;
                //set toFree to NULL
                toFree = NULL;
                //free toFree
                free(toFree);
            }
            else
                temp = temp -> next;
        }
    }
    //return numbers of books, should be 0 or 1
    *hand = head;
    return books;
}

//checks the size of a hand
int checkSize(card** hand)
{
    card* temp = *hand;
    int size = 0;
    while (temp != NULL)
    {
        size++;
        temp = temp -> next;
    }
    return size;
}

#endif /* DeckStuff_h */
