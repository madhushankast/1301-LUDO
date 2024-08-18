#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "type.h"

const char *players[4] = {"Yellow", "Blue", "Red", "Green"};

// pieces
// 0 - playercolor , 1 - pircenumber , 2 - position , 3 - captured , 4 - direction(1 - clockwise,-1 - anticlockwise)
// 5 - Bhawana impact 2* or 0.5* , 6 - countforimpacts
// yellow
int piecey1[PDATA] = {YELLOW, PIECE1, BASE, 0, 0, 1, 0};
int piecey2[PDATA] = {YELLOW, PIECE2, BASE, 0, 0, 1, 0};
int piecey3[PDATA] = {YELLOW, PIECE3, BASE, 0, 0, 1, 0};
int piecey4[PDATA] = {YELLOW, PIECE4, BASE, 0, 0, 1, 0};

// blue pieces
int pieceb1[PDATA] = {BLUE, PIECE1, BASE, 0, 0, 1, 0};
int pieceb2[PDATA] = {BLUE, PIECE2, BASE, 0, 0, 1, 0};
int pieceb3[PDATA] = {BLUE, PIECE3, BASE, 0, 0, 1, 0};
int pieceb4[PDATA] = {BLUE, PIECE4, BASE, 0, 0, 1, 0};

// red pieces
int piecer1[PDATA] = {RED, PIECE1, BASE, 0, 0, 1, 0};
int piecer2[PDATA] = {RED, PIECE2, BASE, 0, 0, 1, 0};
int piecer3[PDATA] = {RED, PIECE3, BASE, 0, 0, 1, 0};
int piecer4[PDATA] = {RED, PIECE4, BASE, 0, 0, 1, 0};

// green pieces
int pieceg1[PDATA] = {GREEN, PIECE1, BASE, 0, 0, 1, 0};
int pieceg2[PDATA] = {GREEN, PIECE2, BASE, 0, 0, 1, 0};
int pieceg3[PDATA] = {GREEN, PIECE3, BASE, 0, 0, 1, 0};
int pieceg4[PDATA] = {GREEN, PIECE4, BASE, 0, 0, 1, 0};

// players
player player1 = {YELLOW, 0, 0, "Yellow", 'Y', YX, YO, {
                                                           piecey1,
                                                           piecey2,
                                                           piecey3,
                                                           piecey4,
                                                       }};
player player2 = {BLUE, 0, 0, "Blue", 'B', BX, BO, {
                                                       pieceb1,
                                                       pieceb2,
                                                       pieceb3,
                                                       pieceb4,
                                                   }};
player player3 = {RED, 0, 0, "Red", 'R', RX, RO, {
                                                     piecer1,
                                                     piecer2,
                                                     piecer3,
                                                     piecer4,
                                                 }};
player player4 = {GREEN, 0, 0, "Green", 'G', GX, GO, {
                                                         pieceg1,
                                                         pieceg2,
                                                         pieceg3,
                                                         pieceg4,
                                                     }};

// the pointer array that pints to player structure variable
player *arrayplayerlist[4] = {&player1, &player2, &player3, &player4};

// player *blockad[4];

int mistrycell;

// function to that irretative the player loop
void gamerun(int, int);
int decideDirection();
int checkcatch(player *player);
void createBlocks(player *player, int randomplaypiece);
void telport(player *player, int randomplaypiece, int onmistry);
bool isMistry(int canmistry);
void redcatch(int x);
void yellowcatch(int x);
void printround();

// check the relevant piece can come to the starting cell
// must roll 6 to come and if there any pieces in standard path move them
char checkcometox(player *, int);

// call four players move
void move(int);

// move make to random pieces
int randompiece();

// checking position
int checkpos(int);

// standard move of players after getting standard path
int standmove(player *player, int y, int playpiece);

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
        // printf("game run %d\n",starter);
        starter++;
        // printf("%d\n",play[i]);
    }
    printf("Round goes to left hand side and order is %s -> %s -> %s -> %s\n",
           players[play[0]],
           players[play[1]],
           players[play[2]],
           players[play[3]]);
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

            if (round > 2 && (round % 4 == 0))
            {
                int canmistry;
                do
                {
                    canmistry = rand() % 52;
                } while (isMistry(canmistry));
                mistrycell = canmistry;
                printf("mistry cell on %d\n", mistrycell);
            }
        }
        printf("Status of player\n");
        printround();
    }
}

void move(int pl)
{
    int x = 0;
    // to track roll count
    int rolled6 = 0;
    switch (pl)
    {
    case 0:
        do
        {
            x = roll();
            printf("Yellow player rolled %d\n", x);
            if(player1.started==0)
            {
                checkcometox(&player1, x);
            }
            else if (player1.started < 4 && x==6)
            {
                for(int i =0;i<4;i++)
                {
                    if(player1.forpieces[i][3]==0 && player1.started > 0)
                    {
                        if ((checkcatch(&player1)))
                        {
                            yellowcatch(x);
                        }
                        else
                        {
                            checkcometox(&player1, x);
                        }      
                    }
                } 
            }
            else if (player1.started >= 1)
            {
                standmove(&player1, x, rand() % player1.started);
            }
            else
            {
                printf("Not implemented else if\n");
            }
            // avoid block catrector

            if (x == 6)
            {
                if (rolled6 < 2)
                {
                    printf("Rolled 6 so player gets another roll\n");
                    rolled6++;
                }
                else
                {
                    printf("Rolled 6 3 times rolle canceled\n");
                    rolled6 = 0;
                    break;
                }
            }
            else
            {
                rolled6 = 0;
                break;
            }
        } while (1);
        // check implemenmted end of each standardmove
        // checkcatch(arrayplayerlist[0]);
        
        printf("\n");
        break;
    case 1:
        do
        {
            x = roll();
            printf("Blue player rolled %d\n", x);
            if (player2.started < 5)
            {
                checkcometox(&player2, x);
            }
            else if (player2.started == 4 && player2.finished < 4)
            {
                standmove(&player2, x, rand() % player2.started);
            }

            if (x == 6)
            {
                if (rolled6 < 2)
                {
                    printf("Rolled 6 so player gets another roll\n");
                    rolled6++;
                }
                else
                {
                    printf("Rolled 6 3 times rolle canceled\n");
                    rolled6 = 0;
                    break;
                }
            }
            else
            {
                rolled6 = 0;
                break;
            }
        } while (1);
        // checkcatch(arrayplayerlist[1]);
        printf("Passing to Next player\n");
        printf("\n");

        break;
    case 2:
        do
        {
            x = roll();
            printf("RED player rolled %d\n", x);
            // redplayer(x);

            if (x == 6 && player3.started < 4)
            {
                if (player3.started < 1)
                {
                    checkcometox(&player3, x);
                }
                else if (player3.started > 0 && (checkcatch(&player3)))
                {
                    redcatch(x);
                }
                else
                {
                    checkcometox(&player3, x);
                }
            }
            else if (player3.started > 0 && (checkcatch(&player3)))
            {
                redcatch(x);
            }
            
            else if (player3.started >= 1)
            {

                standmove(&player3, x, rand() % player3.started);
            }

            if ((player3.started == 0) && (x != 6))
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                       player3.color, x);
            }
            // avoid block catrector

            if (x == 6)
            {
                if (rolled6 < 2)
                {
                    printf("Rolled 6 so player gets another roll\n");
                    rolled6++;
                }
                else
                {
                    printf("Rolled 6 3 times rolle canceled\n");
                    rolled6 = 0;
                    break;
                }
            }
            else
            {
                rolled6 = 0;
                break;
            }
        } while (1);
        // check implemenmted end of each standardmove
        // checkcatch(arrayplayerlist[0]);
        printf("Passing to Next player\n");
        printf("\n");
        break;
    case 3:
        do
        {
            x = roll();
            printf("Green player rolled %d\n", x);
            if (player4.started < 4 && player4.finished < 4)
            {
                checkcometox(&player4, x);
            }
            else if (player4.started == 4 && player1.finished < 4)
            {
                standmove(&player4, x, rand() % player4.started);
            }
            if (x == 6)
            {
                if (rolled6 < 2)
                {
                    printf("Rolled 6 so player gets another roll\n");
                    rolled6++;
                }
                else
                {
                    printf("Rolled 6 3 times rolle canceled\n");
                    rolled6 = 0;
                    break;
                }
            }
            else
            {
                rolled6 = 0;
                break;
            }
        } while (1);
        // checkcatch(arrayplayerlist[3]);
        printf("Passing to Next player\n");
        printf("\n");

        break;
    }

    //[Color X] player now has [Number]/4 on pieces on the board and [Number]/4 pieces on the base.
}

void printround()
{
    for(int j=0;j<4;j++)
    {
        printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base\n",
            arrayplayerlist[j]->color,
            arrayplayerlist[j]->started,
            (4 - arrayplayerlist[j]->started));
    printf("=====================================================================================\n");
    printf("Locations of pieces of %s player\n",arrayplayerlist[j]->color);
    for(int i=0;i<4;i++)
    {
        if(arrayplayerlist[j]->forpieces[i][2]==-1)
        {
            printf("%c%d -> Base\t\t",arrayplayerlist[j]->colorfirst,arrayplayerlist[j]->forpieces[i][1]);
        }
        else
        {
            printf("%c%d is at L%d\t\t",arrayplayerlist[j]->colorfirst,arrayplayerlist[j]->forpieces[i][1],arrayplayerlist[j]->forpieces[i][2]);

        }
    }
    printf("\n");
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

// firstly to come to x if all in standard area then move
char checkcometox(player *player, int x)
{
    if ((player->started == 0) && (x != 6))
    {
        printf("%s must roll 6 to move pieces to X but player rolled %d\n", player->color, x);
        return x;
    }

    else if ((player->started < 4) && (x == 6))
    {
        for (int i = 0; i < 4; i++)
        {
            if ((player->forpieces[i][2]) == BASE)
            {
                printf("Player rolled %d and piece %c%d came to X mark in standard path\n",
                x,
                player->colorfirst,
                i + 1);
                (player->started)++;
                player->forpieces[i][2] = player->x;
                // store direction in pieces array[4]
                player->forpieces[i][4] = decideDirection();
                return 'x';
            }
        }
    }
    else if ((player->started < 4) && (player->started > 0))
    {
        standmove(player, x, rand() % player->started);
        return x;
    }
    else
    {
        printf("Else part Player can move by %d\n", x);
    }
}

int standmove(player *player, int y, int playpiece)
{
    int x = y;
    // selecting random piece just for run code later has to implement player AI
    //  A:
    //  int randomplaypiece = randompiece();
    //  if (randomplaypiece >= player->started)
    //  {
    //      goto A;
    //  }

    do
    {
        // Bhawana impact
        if ((player->forpieces[playpiece][5] != 1) && ((player->forpieces[playpiece][6]) > 0))
        {
            x = (player->forpieces[playpiece][5]) * y;
            player->forpieces[playpiece][6]--;
        }
        // Kotuwa Impact
        if (player->forpieces[playpiece][6] > 0 && player->forpieces[playpiece][2] == KOTUWA)
        {
            printf("%s %c%d in KOTUWA cant move for next %d rounds\n",
                   player->color,
                   player->colorfirst,
                   player->forpieces[playpiece][1],
                   player->forpieces[playpiece][6]--);
            break;
        }

        // selecting player randomplt has to implement player AIs
        if (player->forpieces[playpiece][4] == 1)
        {
            printf("%s -> %c%d moved from %d",
                   player->color,
                   player->colorfirst,
                   playpiece,
                   player->forpieces[playpiece][2]);
            // player->forpieces[randomplayer][2] = player->forpieces[randomplayer][2]+x;
            player->forpieces[playpiece][2] = ((player->forpieces[playpiece][2]) + x) % 52;
            printf("to %d clockwise direction\n", player->forpieces[playpiece][2]);
            // checkcatch(player, randomplaypiece);
        }

        else if (player->forpieces[playpiece][4] == -1)
        {
            printf("%s -> %c%d moved from %d ",
                   player->color,
                   player->colorfirst,
                   playpiece,
                   player->forpieces[playpiece][2]);
            // player->forpieces[randomplayer][2] = player->forpieces[randomplayer][2]+x;
            // int temp;
            // temp = (temp - x) % 52;
            player->forpieces[playpiece][2] = player->forpieces[playpiece][2] - x;
            if (player->forpieces[playpiece][2] <= 0)
            {
                player->forpieces[playpiece][2] = 51 + player->forpieces[playpiece][2];
            }
            printf("to %d anti-clockwise direction\n", player->forpieces[playpiece][2]);
            // if (checkcatch (player, randomplaypiece))
            // {
            //     goto A;
            // }

            if (player->forpieces[playpiece][2] == (mistrycell))
            {
                telport(player, playpiece, mistrycell);
            }
            // checkblock;
        }
    } while (checkcatch(player));
    // checking player can catch another if true giving anothe chance
}

int decideDirection()
{
    int x = (rand() % 2);
    if (x == 0)
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

int checkcatch(player *player)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if ( // cheking possibles pieces catches when a move was make
                    player != arrayplayerlist[j] &&
                    player->forpieces[i][2] != (YX || BX || RX || GX) &&
                    (player->forpieces[i][2] != BASE) &&
                    ((arrayplayerlist[j])->forpieces[j][k] != BASE) &&
                    (player->forpieces[i][2] == arrayplayerlist[j]->forpieces[j][k]))
                {
                    player->forpieces[i][3]++;

                    /*printf("%s player %c%d piece captures %s player's %c%d piece at %d position\n",
                           player->color,
                           player->colorfirst,
                           i+1,
                           arrayplayerlist[j]->color,
                           arrayplayerlist[j]->colorfirst,
                           k,
                           player->forpieces[i][2]);

                    printf("%s player's %c%d piece send to BASE\n",
                           arrayplayerlist[j]->color,
                           arrayplayerlist[j]->colorfirst,
                           k);*/
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }
    }
}

void createBlocks(player *player, int randomplaypiece)
{
    int blocksize = 0;
    for (int i = 0; i < 4; i++)
    {
        if (((player->forpieces[randomplaypiece][2]) || (player->forpieces[i][2])) != 0 &&
            player->forpieces[randomplaypiece][2] == player->forpieces[i][2])
        {
            printf("%s player's %c%d piece and %c%d create a block\n",
                   player->color,
                   player->colorfirst,
                   randomplaypiece,
                   player->colorfirst,
                   i);
            blocksize++;
        }
    }
    printf("Blockad size %d\n", blocksize);
}

void telport(player *player, int randomplaypiece, int onmistry)
{
    switch (rand() % 6)
    {
    case 0:
        printf("Teleported to Bhawana\n");
        player->forpieces[randomplaypiece][2] = BHAWANA;
        player->forpieces[randomplaypiece][6] = FORROUND;
        if (rand() % 2 == 0)
        {
            player->forpieces[randomplaypiece][5] = ENERGIZE;
        }
        else
        {
            player->forpieces[randomplaypiece][5] = SICK;
        }
        break;
    case 1:
        printf("Teleported to Kotuwa\n");
        player->forpieces[randomplaypiece][2] = KOTUWA;
        player->forpieces[randomplaypiece][6] = FORROUND;

        break;
    case 2:
        printf("Teleported to Pita-Kotuwa\n");
        if (player->forpieces[randomplaypiece][4] == 1)
        {
            player->forpieces[randomplaypiece][4] = -1;
        }
        else
        {
            printf("Teleported to Kotuwa\n");
            player->forpieces[randomplaypiece][2] = KOTUWA;
            player->forpieces[randomplaypiece][6] = FORROUND;
        }
        break;
    case 3:
        printf("Teleported to Base\n");
        player->forpieces[randomplaypiece][2] = BASE;
        break;
    case 4:
        printf("Teleported to X of itself\n");
        player->forpieces[randomplaypiece][2] = player->x;
        break;
    case 5:
        printf("Teleported to Approach of\n");
        player->forpieces[randomplaypiece][2] = player->o;
        break;
    }
}

bool isMistry(int canmistry)
{
    if ((mistrycell) == (canmistry))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void redcatch(int x)
{
    int min = 52;
    for (int i = 0; i < 4; i++)
    {
        if (player3.forpieces[i][2] != BASE)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (&player3 != arrayplayerlist[j] &&
                        player3.forpieces[i][2] + x == arrayplayerlist[j]->forpieces[k][2])
                    {
                        if ((arrayplayerlist[j]->o - arrayplayerlist[j]->forpieces[k][2]) < min)
                        {
                            player3.forpieces[i][2] = player3.forpieces[i][2] + x;
                            printf("%s player %c%d piece captures %s player's %c%d piece at %d position\n",
                                   player3.color,
                                   player3.colorfirst,
                                   i + 1,
                                   arrayplayerlist[j]->color,
                                   arrayplayerlist[j]->colorfirst,
                                   k + 1,
                                   player3.forpieces[i][2]);

                            printf("%s player's %c%d piece send to BASE\n",
                                   arrayplayerlist[j]->color,
                                   arrayplayerlist[j]->colorfirst,
                                   k + 1);
                            arrayplayerlist[j]->forpieces[k][2] = BASE;
                        }
                    }
                }
            }
        }
    }
}

void yellowcatch(int x)
{
    for(int i=0;i<4;i++)
    {
        if(player1.forpieces[i][3]>0)
        {
            continue;
        }
        else
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (&player1 != arrayplayerlist[j] &&
                        player1.forpieces[i][2] + x == arrayplayerlist[j]->forpieces[k][2])
                    {
                        player1.forpieces[i][2] = player1.forpieces[i][2]+x;
                        printf("%s player %c%d piece captures %s player's %c%d piece at %d position\n",
                                   player1.color,
                                   player1.colorfirst,
                                   i + 1,
                                   arrayplayerlist[j]->color,
                                   arrayplayerlist[j]->colorfirst,
                                   k + 1,
                                   player1.forpieces[i][2]);

                            printf("%s player's %c%d piece send to BASE\n",
                                   arrayplayerlist[j]->color,
                                   arrayplayerlist[j]->colorfirst,
                                   k + 1);
                            arrayplayerlist[j]->forpieces[k][2] = BASE;
                    }
            
                
                }
            }
        }
    }
    
}