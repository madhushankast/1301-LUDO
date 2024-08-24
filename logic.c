#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "type.h"
#include "logic.h"
const char *players[4] = {"Yellow", "Blue", "Red", "Green"};

// pieces
// 0 - playercolor , 1 - pircenumber , 2 - position , 3 - captured , 4 - direction(1 - clockwise,-1 - anticlockwise)
// 5 - Bhawana impact 2* or 0.5* , 6 - counterforimpacts ,7 - moved units sum
// yellow
int piecey1[PDATA] = {YELLOW, PIECE1, BASE, 0, 0, 1, 0,0};
int piecey2[PDATA] = {YELLOW, PIECE2, BASE, 0, 0, 1, 0,0};
int piecey3[PDATA] = {YELLOW, PIECE3, BASE, 0, 0, 1, 0,0};
int piecey4[PDATA] = {YELLOW, PIECE4, BASE, 0, 0, 1, 0,0};

// blue pieces
int pieceb1[PDATA] = {BLUE, PIECE1, BASE, 0, 0, 1, 0,0};
int pieceb2[PDATA] = {BLUE, PIECE2, BASE, 0, 0, 1, 0,0};
int pieceb3[PDATA] = {BLUE, PIECE3, BASE, 0, 0, 1, 0,0};
int pieceb4[PDATA] = {BLUE, PIECE4, BASE, 0, 0, 1, 0,0};

// red pieces
int piecer1[PDATA] = {RED, PIECE1, BASE, 0, 0, 1, 0,0};
int piecer2[PDATA] = {RED, PIECE2, BASE, 0, 0, 1, 0,0};
int piecer3[PDATA] = {RED, PIECE3, BASE, 0, 0, 1, 0,0};
int piecer4[PDATA] = {RED, PIECE4, BASE, 0, 0, 1, 0,0};

// green pieces
int pieceg1[PDATA] = {GREEN, PIECE1, BASE, 0, 0, 1, 0,0};
int pieceg2[PDATA] = {GREEN, PIECE2, BASE, 0, 0, 1, 0,0};
int pieceg3[PDATA] = {GREEN, PIECE3, BASE, 0, 0, 1, 0,0};
int pieceg4[PDATA] = {GREEN, PIECE4, BASE, 0, 0, 1, 0,0};

// players
player player1 = {YELLOW, 0, 0, "Yellow", 'Y', YX, YO,0, {
                                                           piecey1,
                                                           piecey2,
                                                           piecey3,
                                                           piecey4,
                                                       }};
player player2 = {BLUE, 0, 0, "Blue", 'B', BX, BO,0, {
                                                       pieceb1,
                                                       pieceb2,
                                                       pieceb3,
                                                       pieceb4,
                                                   }};
player player3 = {RED, 0, 0, "Red", 'R', RX, RO, 0,{
                                                     piecer1,
                                                     piecer2,
                                                     piecer3,
                                                     piecer4,
                                                 }};
player player4 = {GREEN, 0, 0, "Green", 'G', GX, GO,0, {
                                                         pieceg1,
                                                         pieceg2,
                                                         pieceg3,
                                                         pieceg4,
                                                     }};

// the pointer array that pints to player structure variable
player *arrayplayerlist[4] = {&player1, &player2, &player3, &player4};

int endpieces = 0;
// player *blockad[4];
short mistrycell;
short blueOrder = 0;
int playedpiece;

// function to that irretative the player loop
// void gamerun(int, int);
// int coinToss();
// int captured(player *player);
// void createBlocks(player *player, int randomplaypiece);
// void telport(player *player, int randomplaypiece, int onmistry);
// bool canBeMistry(int canmistry);
// void redcatch(int x);
// void yellowcatch(int x);
// void printround();

// check the relevant piece can come to the starting cell
// must roll 6 to come and if there any pieces in standard path move them
// char checkcometox(player *, int);

// // call four players move
// void move(int);

// // move make to random pieces
// int selectPlayPiece(player *player);

// // checking position
// int checkpos(int);

// // standard move of players after getting standard path
// int standmove(player *player, int y);

// // begining
// void printbegin();

// // rolling dice and creating random 1 -6 values
// int roll();

// // deciding the starter
// int firstroll(int i);

// // printing and ordering players
// void printvalues(int *ptr);

// // sorting and find order of value and sorting players by values in same array
// int begin();
// int sort(int *arr);
// int LUDO();

//output the begining statmenet and player order
int LUDO()
{
    //seed rand function
    srand(time(0));

    //begining statements
    printbegin();

    //selecting starter by higherst dice value
    int startPlayer;
    startPlayer = firstHand();

    //passing starting player and endpieces count
    gameplay(startPlayer);
    return 1;
}

//the starting statement
void printbegin()
{
    printf("The\tYellow\tplayer has four(04) pieces named Y1,Y2,Y3 and Y4\n");
    printf("The\tBlue\tplayer has four(04) pieces named B1,B2,B3 and B4\n");
    printf("The\tRed\tplayer has four(04) pieces named R1,R2,R3 and R4\n");
    printf("The\tGreen\tplayer has four(04) pieces named G1,G2,G3 and G4\n");
}

//rolling dice to output 1 - 6 values
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

//output player and rolled value
int firstroll(int i)
{
    int x = roll();
    printf("The\t%s\tplayer rolls\t%d\n", arrayplayerlist[i]->color, x);
    return x;
}

void printvalues(int *ptr)
{
    // int* ptr = arr;
    printf("%s player has the highest roll and will begin the game\n", players[*(ptr + 3)]);
    printf("The rolled dise value order is %s, %s, %s, and %s\n", players[*(ptr + 3)], players[*(ptr + 2)], players[*(ptr + 1)], players[*(ptr)]);
}

//finding highest rolled value and player
int firstHand()
{
    int firstHandValue[4];
    //int *ptrfirst = first;
    for (int i = 0; i < 4; i++)
    {
        int x = firstroll(i);
        firstHandValue[i] = x;
    }
    //return sort(first);

    int sortplayer[4];
    for (int i = 0; i < 4; i++)
    {
        sortplayer[i] = i;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (firstHandValue[j] >= firstHandValue[j + 1])
            {
                int tmp = firstHandValue[j];
                int tmp2 = sortplayer[j];

                firstHandValue[j] = firstHandValue[j + 1];
                sortplayer[j] = sortplayer[j + 1];

                firstHandValue[j + 1] = tmp;
                sortplayer[j + 1] = tmp2;
            }
        }
    }

    printvalues(sortplayer);
    return sortplayer[3];
}

void gameplay(int starter)
{
    // creating an new array to keep order and for looping
    int play[4];
    for (int i = 0; i < 4; i++)
    {
        starter = starter % 4;
        play[i] = starter;
        starter++;
        //printf("%d\n",play[i]);
    }

    printf("Round goes to left hand side and order is %s -> %s -> %s -> %s\n",
           arrayplayerlist[0]->color,
           arrayplayerlist[1]->color,
           arrayplayerlist[2]->color,
           arrayplayerlist[3]->color);
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
                //printf("Error A\n");
                int CurrentPlayer = play[i];
                move(CurrentPlayer);
                //printf("Error A");
                // printf("\n");
            }
            // one round finished
            printf("\n");
            // endpieces++;

            if (round > 2 && (round % 4 == 0))
            {
                //need to fix error can be mistry
                int mistryIs;
                do
                {
                    mistryIs = rand() % 52;
                } while(0); //(!canBeMistry(mistryIs));

                mistrycell = mistryIs;
                //printf("mistry cell on %d\n", mistrycell);
            }
        }
        //printf("Status of player\n");
        printround();
        printf("mistry cell on %d\n", mistrycell);
    }
}

void move(int CurrentPlayer)
{
    short x;
    //to track roll count
    short rolled6;
    switch (CurrentPlayer)
    {
    case 0: //yellow
        do{

            x = roll();
            printf("Yellow player rolled %d\n", x);
            if(x==6)
            {
                if(player1.started==0)
                {
                    checkcometox(&player1, x);
                }
                else
                {
                    for(int i =0;i<4;i++)
                    {
                        if(player1.forpieces[i][3]==0 && player1.started > 0)
                        {
                            if (cancaptured(&player1,x))
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
            }
            else
            {
                if(player1.started >= 1)
                {
                    playedpiece = standmove(&player1, x);
                }
                else if(player1.started==0 )
                {
                    printf("%s must roll 6 to move pieces to X but player rolled %d\n", player1.color, x);
                }
                else
                {
                    printf("--------------------------------------------------Edge case - fix\n");
                }
            }

            //captured(&player1);

            if((captured(&player1,playedpiece)))
            {
                continue;
            }
            // avoid block catrector

            if (x == 6 && player1.sixrolled<2)
            {
                player1.sixrolled++;
                {
                    printf("Rolled 6 so player gets another roll\n");
                    //move(CurrentPlayer);
                    x = roll();
                    continue;

                }
            }
            else
            {
                player1.sixrolled=0;
                break;
            }
        } while (1);
        // check implemenmted end of each standardmove
        // captured(arrayplayerlist[0]);
        printf("\n");
        break;


    case 1: //blue
        do{
            x = roll();
            printf("Blue player rolled %d\n", x);
            if(x==6)
            {
                if (player2.started <= 4)
                {
                    checkcometox(&player2, x);
                }
            }
            else
            {
                if(player2.started>0)
                {
                    playedpiece = standmove(&player2, x);
                }
                else
                {
                    printf("Cannot move must roll 6 to start %d\n", x);
                }
            }

            if((captured(&player2,playedpiece)))
            {
                continue;
            }

            if (x == 6 && player2.sixrolled<2)
            {
                player2.sixrolled++;
                {
                    printf("Rolled 6 so player gets another roll\n");
                    //move(CurrentPlayer);
                    x = roll();
                    continue;
                }
            }
            else
            {
                player2.sixrolled=0;
                break;
            }
        } while (1);
        // captured(arrayplayerlist[1]);
        printf("Passing to Next player\n");
        printf("\n");

        break;
    case 2: //red
        do{
            x = roll();
            printf("RED player rolled %d\n", x);
            // redplayer(x);

            if (x == 6)
            {
                if (player3.started == 0)
                {
                    checkcometox(&player3, x);
                    printf("Check come to x\n");
                }
                else if (player3.started > 0 && cancaptured(&player3,x))
                {
                    redcatch(x);
                    printf("Cought\n");
                }
                else
                {
                    checkcometox(&player3, x);
                }
            }
            else
            {
                if (player3.started > 0)
                {
                    if(cancaptured(&player1,x))
                    {
                        redcatch(x);
                        printf("Cought\n");
                    }
                    else if(player3.started >= 1)
                    {
                        playedpiece = standmove(&player3, x);
                    }
                }
                else if(player3.started == 0)
                {
                    printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                    player3.color, x);
                }
                // if ((player3.started == 0) && (x != 6))
                // {
                    
                // }
            }
            // avoid block catrector
            if((captured(&player3,playedpiece)))
            {
                continue;
            }
            
            if (x == 6 && player3.sixrolled<2)
            {
                player3.sixrolled++;
                {
                        printf("Rolled 6 so player gets another roll\n");
                        //move(CurrentPlayer);
                        x = roll();
                        continue;

                }
            }
            else
            {
                player3.sixrolled=0;
                break;
            }
        } while (1);
        // check implemenmted end of each standardmove
        // captured(arrayplayerlist[0]);
        printf("Passing to Next player\n");
        printf("\n");
        break;

    case 3: //green
        do{
            x = roll();
            printf("Green player rolled %d\n", x);
            if(x==6)
            {
                if (player4.started < 4)
                {
                    checkcometox(&player4, x);
                }
                // else if(canCreateBlock)
                // {
                    
                // }
                else
                {
                    playedpiece = standmove(&player4, x);
                    //printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                    //player4.color, x);
                }
            
            }
            else
            {
                if (player4.started >= 1 )
                {
                    playedpiece = standmove(&player4, x);
                }
                else
                {
                    printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                    player4.color, x);
                }
            }

            if((captured(&player4,playedpiece)))
            {
                continue;
            }
            
            
            if (x == 6 && player4.sixrolled<2)
            {
                player4.sixrolled++;
                {
                    printf("Rolled 6 so player gets another roll\n");
                    //move(CurrentPlayer);
                    x = roll();
                    continue;

                }
            }
            else
            {
                player4.sixrolled=0;
                break;
            }
        } while (1);
        // captured(arrayplayerlist[3]);
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
        printf("\n");
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
    printf("\n");


}

int selectPlayPiece(player *player,int x)
{   
    short playpiece;
    switch(player->playernum)
    {
        case 0 :return yellowPlayPiece(&player1,x);
            break;

        case 1 :return bluePlayPiece(x);
            break;
        
        case 2 :return redPlayPiece(&player3);
                //return redPlayPiece(player);
            break;
        
        case 3 :return rand()%4;
                //return greenPlayPiece(player);
            break;
    }
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
    // if ((player->started == 0))
    // {
    //     printf("%s must roll 6 to move pieces to X but player rolled %d\n", player->color, x);
    //     return x;
    // }

    if ((player->started < 4))
    {
        for (int i = 0; i < 4; i++)
        {
            if ((player->forpieces[i][2]) == BASE)
            {
                printf("Player rolled %d and piece %c%d came to X mark in standard path\n",
                x,
                player->colorfirst,
                i + 1);
                player->started = player->started+1;
                player->forpieces[i][2] = player->x;
                // store direction in pieces array[4]
                player->forpieces[i][4] = coinToss();
                printf("player started ------------------ %d\n",player->started);
                return 'x';
                
            }
        }
    }
    // else if ((player->started < 4) && (player->started > 0))
    // {
    //     playedpiece = standmove(player, x);
    //     return x;
    // }
    else
    {
        printf("Edge Case found\n");
    }
}

int standmove(player *player, short roll)
{
    short playpiece = selectPlayPiece(player,roll);
    printf("playpiece = %d,\n" ,playpiece);

        // Bhawana impact
        if ((player->forpieces[playpiece][5] != 1) && ((player->forpieces[playpiece][6]) > 0))
        {
            roll = (player->forpieces[playpiece][5]) * roll;
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
            player->forpieces[playpiece][2] = ((player->forpieces[playpiece][2]) + roll) % 52;
            printf("to %d clockwise direction\n", player->forpieces[playpiece][2]);
            // captured(player, randomplaypiece);
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
            player->forpieces[playpiece][2] = player->forpieces[playpiece][2] - roll;
            if (player->forpieces[playpiece][2] <= 0)
            {
                player->forpieces[playpiece][2] = 51 + player->forpieces[playpiece][2];
            }
            printf("to %d anti-clockwise direction\n", player->forpieces[playpiece][2]);
            
            if (player->forpieces[playpiece][2] == (mistrycell))
            {
                telport(player, playpiece, mistrycell);
            }
            // checkblock;
            //player->forpieces[playpiece][7] += roll;
        }
        return playpiece;
    // checking player can catch another if true giving anothe chance
}

int coinToss()
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

int captured(player *player,int playedpiece)
{
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if ( // remove comparing same players pieces
                    player != arrayplayerlist[j] &&
                    //can not catch at starting position
                    player->forpieces[playedpiece][2] != YX && player->forpieces[playedpiece][2] != BX && 
                    player->forpieces[playedpiece][2] != RX && player->forpieces[playedpiece][2] != GX &&

                    //removing in base pieces
                    (player->forpieces[playedpiece][2] != BASE) &&
                    //removing oppenent pieces base pieces
                    (arrayplayerlist[playedpiece]->forpieces[k][2] != BASE) &&
                    //if they in a same block
                    (player->forpieces[playedpiece][2] == arrayplayerlist[j]->forpieces[k][2]))
                {
                    
                    player->forpieces[playedpiece][3]++;

                    printf("%s player %c%d piece captures %s player's %c%d piece at %d position\n",
                           player->color,
                           player->colorfirst,
                           playedpiece+1,
                           arrayplayerlist[j]->color,
                           arrayplayerlist[j]->colorfirst,
                           k,
                           player->forpieces[playedpiece][2]);

                    printf("%s player's %c%d piece send to BASE\n",
                           arrayplayerlist[j]->color,
                           arrayplayerlist[j]->colorfirst,
                           k);
                    
                    arrayplayerlist[j]->forpieces[k][2] = BASE;
                    arrayplayerlist[j]->forpieces[k][3] = 0;
                    player->started = player->started-1;
                    printf("Catch------------------------------------------------\n");
                           
                    return 1;
                }
            }
        }
    
    return 0;
}

bool cancaptured(player *player,int x)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if ( // remove comparing same players pieces
                    player != arrayplayerlist[j] &&
                    //can not catch at starting position
                    player->forpieces[i][2] != YX && player->forpieces[i][2] != BX && 
                    player->forpieces[i][2] != RX && player->forpieces[i][2] != GX &&

                    //removing in base pieces
                    (player->forpieces[i][2] != BASE) &&
                    //removing oppenent pieces base pieces
                    (arrayplayerlist[j]->forpieces[k][2] != BASE) &&
                    //if they in a same block
                    (player->forpieces[i][2]+x == arrayplayerlist[j]->forpieces[k][2]))
                {
                    
                    player->forpieces[i][3]++;
                    /*
                    printf("%s player %c%d piece captures %s player's %c%d piece at %d position\n",
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
                           k);
                    
                    arrayplayerlist[j]->forpieces[k][2] = BASE;
                    player->started = player->started-1;
                    printf("Catch------------------------------------------------\n");*/
                           
                    return true;
                }
            }
        }
    }
    return false;
}

int createBlocks(player *player, int randomplaypiece)
{
    int blocksize = 0;
    for (int i = 0; i < 4; i++)
    {
        if (((player->forpieces[randomplaypiece][2]) || (player->forpieces[i][2])) != BASE &&
            player->forpieces[randomplaypiece][2] == player->forpieces[i][2])
        {
            printf("%s player's %c%d piece and %c%d create a block\n",
                   player->color,
                   player->colorfirst,
                   randomplaypiece,
                   player->colorfirst,
                   i);
            blocksize++;
            return 1;
        }
    }
    printf("Blockad size %d\n", blocksize);
}

int canCreateBlock(player *player)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if (((player->forpieces[i][2]) || (player->forpieces[j][2])) != BASE &&
            player->forpieces[i][2] == player->forpieces[j][2])
            {
                return 1;
            }
        }
    }
    return 0;
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

bool canBeMistry(int mistryis)
{
    if (isPiecelocated)
    {
        return false;
    }
    else if(mistrycell==mistryis)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool redcatch(short x)
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
                    if ( // remove comparing same players pieces
                    &player3 != arrayplayerlist[j] &&
                    //can not catch at starting position
                    player3.forpieces[playedpiece][2] != YX && player3.forpieces[playedpiece][2] != BX && 
                    player3.forpieces[playedpiece][2] != RX && player3.forpieces[playedpiece][2] != GX &&

                    //removing in base pieces
                    (player3.forpieces[playedpiece][2] != BASE) &&
                    //removing oppenent pieces base pieces
                    (arrayplayerlist[playedpiece]->forpieces[k][2] != BASE) &&
                    //if they in a same block
                    (player3.forpieces[playedpiece][2] == arrayplayerlist[j]->forpieces[k][2]))
                    {
                        if ((arrayplayerlist[j]->o - arrayplayerlist[j]->forpieces[k][2]) < min)
                        {
                            player3.started = player3.started+1;
                            player3.forpieces[i][2] = player3.forpieces[i][2] + x;
                            player3.forpieces[i][3]++;
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
                            arrayplayerlist[j]->forpieces[k][3] = 0;
                            player3.started = player3.started-1;
                            return true;
                        }
                        else
                        {
                            return false;
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

int yellowPlayPiece(player *player,int x)
{
    short unitsToHome;
    short minUnits = 60;
    short playpiece = rand()%player1.started;
    for(short i=0;i<4;i++)
    {
        if (player->forpieces[i][2] != BASE);
        {
            if(player->forpieces[i][4] == 1)
            {
                unitsToHome =  YO - player->forpieces[i][2];
                if(unitsToHome<minUnits)
                {
                    minUnits = unitsToHome;
                    playpiece = i;
                }
            }
            else if(player->forpieces[i][4] == -1)
            {
                if(player->forpieces[i][7] <= 2)
                {
                    unitsToHome = 51+(player->forpieces[i][2]);
                    if(unitsToHome<minUnits)
                    {
                        minUnits = unitsToHome;
                        playpiece = i;
                        printf("playpiece = %d,\n" ,playpiece);
                        player->forpieces[i][7] = player->forpieces[i][7]+2;
                    }
                }
                else
                {
                    unitsToHome =  player->forpieces[i][2];
                    if(unitsToHome<minUnits)
                    {
                        minUnits = unitsToHome;
                        playpiece = i;
                        printf("playpiece = %d,\n" ,playpiece);
                    }
                }
                
            }
        }
    }
    return playpiece;
}

int bluePlayPiece(int x)
{
    while(1)
    {
        if(blueOrder>3)
        {
            blueOrder = 0;
        }
        if(arrayplayerlist[1]->forpieces[blueOrder][2] != BASE)
        {
            return blueOrder;
        }
        blueOrder++;
    }    
}

int redPlayPiece()
{
    return rand()%player3.started;
}

bool isPiecelocated(int mistryis)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<4;k++)
            {
                if(arrayplayerlist[i]->forpieces[j][k] == mistryis)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//