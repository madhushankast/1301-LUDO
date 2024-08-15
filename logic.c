#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "type.h"


const char* players[4] = {"Yellow","Blue","Red","Green"};


//pieces
//0 - playercolor , 1 - pircenumber , 2 - position , 3 - captured , 4 - direction(1 - clockwise,-1 - anticlockwise)
//yellow pieces
int piecey1[PDATA] = {YELLOW, PIECE1, BASE,0,0};
int piecey2[PDATA] = {YELLOW, PIECE2, BASE,0,0};
int piecey3[PDATA] = {YELLOW, PIECE3, BASE,0,0};
int piecey4[PDATA] = {YELLOW, PIECE4, BASE,0,0};

//blue pieces
int pieceb1[PDATA] = {BLUE, PIECE1, BASE,0,0};
int pieceb2[PDATA] = {BLUE, PIECE2, BASE,0,0};
int pieceb3[PDATA] = {BLUE, PIECE3, BASE,0,0};
int pieceb4[PDATA] = {BLUE, PIECE4, BASE,0,0};

//red pieces
int piecer1[PDATA] = {RED, PIECE1, BASE,0,0};
int piecer2[PDATA] = {RED, PIECE2, BASE,0,0};
int piecer3[PDATA] = {RED, PIECE3, BASE,0,0};
int piecer4[PDATA] = {RED, PIECE4, BASE,0,0};

//green pieces
int pieceg1[PDATA] = {GREEN, PIECE1, BASE,0,0};
int pieceg2[PDATA] = {GREEN, PIECE2, BASE,0,0};
int pieceg3[PDATA] = {GREEN, PIECE3, BASE,0,0};
int pieceg4[PDATA] = {GREEN, PIECE4, BASE,0,0};

//players
player player1 = {YELLOW, 0, 0,"Yellow",'Y',YX,YO,{piecey1,piecey2,piecey3,piecey4,}};
player player2 = {BLUE, 0, 0,"Blue",'B',BX,BO,{pieceb1,pieceb2,pieceb3,pieceb4,}};
player player3 = {RED, 0, 0,"Red",'R',RX,RO,{piecer1,piecer2,piecer3,piecer4,}};
player player4 = {GREEN, 0, 0,"Green",'G',GX,GO,{pieceg1,pieceg2,pieceg3,pieceg4,}};

//the pointer array that pints to player structure variable
player *arrayplayerlist[4] = {&player1,&player2,&player3,&player4};

//function to that irretative the player loop 
void gamerun(int, int);
int decideDirection();

//check the relevant piece can come to the starting cell
//must roll 6 to come and if there any pieces in standard path move them 
char checkcometox(player*,int);

//call four players move
void move(int);

//move make to random pieces
int randompiece();

//checking position
int checkpos(int);

//standard move of players after getting standard path
void standmove(player* player,int x);

// begining
void printbegin();

// rolling dice and creating random 1 -6 values
int roll();

// deciding the starter
int firstroll(int i);

// printing and ordering players
void printvalues(int *ptr);

// sorting and find order of value and sorting players by values in same array
int begin();
int sort(int *arr);
int LUDO();


int LUDO()
{
    
    srand(time(0));
    printbegin();
    int starter;
    starter = begin();
    struct player player1;
    player1.playernum = 1;
    // array to find maximum value rolled

    int endpieces = 0;
    gamerun(starter, endpieces);
    return 1;
}

void printbegin()
{
    printf("The\tYellow\tplayer has four(04) pieces named Y1,Y2,Y3 and Y4\n");
    printf("The\tBlue\tplayer has four(04) pieces named B1,B2,B3 and B4\n");
    printf("The\tRed\tplayer has four(04) pieces named R1,R2,R3 and R4\n");
    printf("The\tGreen\tplayer has four(04) pieces named G1,G2,G3 and G4\n");
}

int roll()
{
    // rolling the dice
    int x = (rand() % 6);
    if (x == 0)
    {
        x = 6;
    }
    return x;
}

int firstroll(int i)
{
    int x = roll();
    printf("The\t%s\tplayer rolls\t%d\n", players[i], x);
    return x;
}

void printvalues(int *ptr)
{
    // int* ptr = arr;
    printf("%s player has the highest roll and will begin the game\n", players[*(ptr + 3)]);
    printf("The rolled dise value order is %s, %s, %s, and %s\n", players[*(ptr + 3)], players[*(ptr + 2)], players[*(ptr + 1)], players[*(ptr)]);
}

int sort(int *arr)
{
    // value -> player
    int sortplayer[4];
    int *ptr = sortplayer;
    for (int i = 0; i < 4; i++)
    {
        sortplayer[i] = i;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[j] >= arr[j + 1])
            {
                int tmp = arr[j];
                int tmp2 = sortplayer[j];

                arr[j] = arr[j + 1];
                sortplayer[j] = sortplayer[j + 1];

                arr[j + 1] = tmp;
                sortplayer[j + 1] = tmp2;
            }
        }
    }

    // for (int i = 0; i < 4; i++)
    // {
    //     printf("arr %d\t",arr[i]);
    //     printf("%d\t",sortplayer[i]);
    // }
    // printf("\n");

    printvalues(ptr);
    // printf("%d\t",sortplayer[3]);
    return sortplayer[3];
}

int begin()
{
    int first[4];
    int *ptrfirst = first;
    for (int i = 0; i < 4; i++)
    {
        int x = firstroll(i);
        first[i] = x;
    }
    return sort(ptrfirst);
}

void gamerun(int starter, int endpieces)
{
    // creating an new array to keep order and for looping
    int play[4];
    for (int i = 0; i < 4; i++)
    {
        starter = starter % 4;
        play[i] = starter;
        //printf("game run %d\n",starter);
        starter++;
        // printf("%d\n",play[i]);
    }
    printf("Round goes to left hand side and order is %s -> %s -> %s -> %s\n", players[play[0]], players[play[1]], players[play[2]], players[play[3]]);
    printf("\n");
    char ch;
    endpieces = 0;
    int round = 1;
    while (endpieces <= 16)
    {
        ch = getchar();
        if (ch = '\n')
        {
            printf("This is round %d\n", round++);
            // repeating the players order
            for (int i = 0; i < 4; i++)
            {
                int pl = play[i];
                // printf("%s\n",players[pl]);
                move(pl);
                // printf("\n");
            }
            // one round finished
            printf("\n");
            // endpieces++;
        }
    }
}

void move(int pl)
{
    int x = 0;
    switch (pl)
    {
    case 0  :   x = roll();
                printf("Yellow player rolled %d\n", x);
                // if(x==6)
                // {
                //     //checksix();
                // }
                if(player1.started<4 && player1.finished<4)
                {
                    checkcometox(&player1,x);
                }
                else if(player1.started==4 && player1.finished<4)
                {
                    standmove(&player1,x);
                }
                
        break;
    case 1:     x = roll();
                printf("Blue player rolled %d\n", x);
                if(player2.started<4 && player2.finished<4)
                {
                    checkcometox(&player2,x);
                }
                else if(player2.started==4 && player1.finished<4)
                {
                    standmove(&player2,x);
                }
                
        break;
    case 2:     x = roll();
                printf("Red player rolled %d\n", x);
                if(player3.started<4 && player3.finished<4)
                {
                    checkcometox(&player3,x);
                }
                else if(player3.started==4 && player1.finished<4)
                {
                    standmove(&player3,x);
                }
                
        break;
    case 3:     x = roll();
                printf("Green player rolled %d\n", x);
                if(player4.started<4 && player4.finished<4)
                {
                    checkcometox(&player4,x);
                }
                else if(player4.started==4 && player1.finished<4)
                {
                    standmove(&player4,x);
                }
                
        break;
    }
}

int randompiece()
{
    return (rand() % 4);
}

int checkpos(int pos)
{
    if (pos > 51)
    {
        pos = pos % 52;
    }
    return pos;
}

//firstly to come to x if all in standard area then move
char checkcometox(player* player,int x)
{
    if((player->started==0) && (x!=6))
   {
        printf("%s must roll 6 to move pieces to X but player rolled %d\n",player->color, x);
        printf("Passing to Next player\n");
        return x;
    }
    
    else if((player->started<4) && (x ==6))
    {   
            for(int i = 0;i<4;i++)
            {
                if((player->forpieces[i][2]) == BASE)
                {
                    printf("Player rolled %d and piece %c%d came to X mark in standard path\n", x,player->colorfirst,i+1);
                    (player->started)++;
                    player->forpieces[i][2] = player->x;
                    //store direction in pieces array[4]
                    player->forpieces[i][4] = decideDirection();
                    printf("Passing to Next player\n");
                    return 'x';
                }
            }
    }
    else if((player->started<4) && (player->started>0))
    {
        standmove(player,x);
        printf("Passing to Next player\n");
        return x;
    }
    else
    {
         printf("Else part Player can move by %d\n",x);
    }
}

void standmove(player* player,int x)
{
    A:
    int randomplayer = randompiece();
    if(randomplayer>=player->started)
    {
        goto A;
    }
    if(player->forpieces[randomplayer][4]==1)
    {
        printf("%s -> %c%d moved from %d",player->color,player->colorfirst,randomplayer,player->forpieces[randomplayer][2]);
        //player->forpieces[randomplayer][2] = player->forpieces[randomplayer][2]+x;
        //if(player->forpieces[randomplayer][2]>51)
        //{
            player->forpieces[randomplayer][2]=((player->forpieces[randomplayer][2])+x)%52;
        //}
        printf("to %d clockwise direction\n",player->forpieces[randomplayer][2]);
    }
    else if(player->forpieces[randomplayer][4]==-1)
    {
        printf("%s -> %c%d moved from %d",player->color,player->colorfirst,randomplayer,player->forpieces[randomplayer][2]);
        //player->forpieces[randomplayer][2] = player->forpieces[randomplayer][2]+x;

        player->forpieces[randomplayer][2]= 52 - (((player->forpieces[randomplayer][2])+x)%52);
        printf("to %d anti-clockwise direction\n",player->forpieces[randomplayer][2]);

    }


}

int decideDirection()
{
    int x = (rand()%2);
    if(x==0)
    {
        printf("A coin is tossed, landed HEAD\n");
        printf("Piese is moving clockwise direction\n");
        return 1;
    }
    else
    {
        printf("A coin is tossed, landed TAIL\n");
        printf("Piese is rolling Anti-clockwise direction\n");
        return -1;
    }
}
//int main()
// {
//    LUDO();
//}
