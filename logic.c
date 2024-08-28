#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "type.h"
#include "logic.h"

const char *players[4] = {"Yellow", "Blue", "Red", "Green"};

// pieces
// 0 - playercolor , 1 - pircenumber , 2 - position , 3 - captured , 4 - direction(1 - clockwise,-1 - anticlockwise)
// 5 - Bhawana impact 2* or 0.5* , 6 - counterforimpacts ,7 - travelled , 8 - (not home 0 ,home 1)
// 9 - homepath value 10 - finneshed the play
// yellow
int piecey1[PDATA] = {YELLOW, PIECE1, BASE, 0, 0, 1, 0, 0,0,0};
int piecey2[PDATA] = {YELLOW, PIECE2, BASE, 0, 0, 1, 0, 0,0,0};
int piecey3[PDATA] = {YELLOW, PIECE3, BASE, 0, 0, 1, 0, 0,0,0};
int piecey4[PDATA] = {YELLOW, PIECE4, BASE, 0, 0, 1, 0, 0,0,0};

// blue pieces
int pieceb1[PDATA] = {BLUE, PIECE1, BASE, 0, 0, 1, 0, 0,0,0};
int pieceb2[PDATA] = {BLUE, PIECE2, BASE, 0, 0, 1, 0, 0,0,0};
int pieceb3[PDATA] = {BLUE, PIECE3, BASE, 0, 0, 1, 0, 0,0,0};
int pieceb4[PDATA] = {BLUE, PIECE4, BASE, 0, 0, 1, 0, 0,0,0};

// red pieces
int piecer1[PDATA] = {RED, PIECE1, BASE, 0, 0, 1, 0, 0,0,0};
int piecer2[PDATA] = {RED, PIECE2, BASE, 0, 0, 1, 0, 0,0,0};
int piecer3[PDATA] = {RED, PIECE3, BASE, 0, 0, 1, 0, 0,0,0};
int piecer4[PDATA] = {RED, PIECE4, BASE, 0, 0, 1, 0, 0,0,0};

// green pieces
int pieceg1[PDATA] = {GREEN, PIECE1, BASE, 0, 0, 1, 0, 0,0,0};
int pieceg2[PDATA] = {GREEN, PIECE2, BASE, 0, 0, 1, 0, 0,0,0};
int pieceg3[PDATA] = {GREEN, PIECE3, BASE, 0, 0, 1, 0, 0,0,0};
int pieceg4[PDATA] = {GREEN, PIECE4, BASE, 0, 0, 1, 0, 0,0,0};

// players
player player1 = {YELLOW, 4, 0, 0, "Yellow", 'Y', YX, YO, 0, {
                                                                 piecey1,
                                                                 piecey2,
                                                                 piecey3,
                                                                 piecey4,
                                                             }};
player player2 = {BLUE, 4, 0, 0, "Blue", 'B', BX, BO, 0, {
                                                             pieceb1,
                                                             pieceb2,
                                                             pieceb3,
                                                             pieceb4,
                                                         }};
player player3 = {RED, 4, 0, 0, "Red", 'R', RX, RO, 0, {
                                                           piecer1,
                                                           piecer2,
                                                           piecer3,
                                                           piecer4,
                                                       }};
player player4 = {GREEN, 4, 0, 0, "Green", 'G', GX, GO, 0, {
                                                               pieceg1,
                                                               pieceg2,
                                                               pieceg3,
                                                               pieceg4,
                                                           }};

// the pointer array that pints to player structure variable
player *arrayplayerlist[4] = {&player1, &player2, &player3, &player4};
// capturer color , piece captured color, piece,location
int captureData[5];
int diceValue;

int endpieces = 0;
// player *blockad[4];
int mistrycell;
int blueOrder = 0;
int playpiece;

// output the begining statmenet and player order
int LUDO()
{
    // seed rand function
    srand(time(0));

    // begining statements
    printbegin();

    // selecting starter by higherst dice value
    int startPlayer;
    startPlayer = firstHand();

    // passing starting player and endpieces count
    gameplay(startPlayer);
    return 1;
}

// the starting statement
void printbegin()
{
    printf("The\tYellow\tplayer has four(04) pieces named Y1,Y2,Y3 and Y4\n");
    printf("The\tBlue\tplayer has four(04) pieces named B1,B2,B3 and B4\n");
    printf("The\tRed\tplayer has four(04) pieces named R1,R2,R3 and R4\n");
    printf("The\tGreen\tplayer has four(04) pieces named G1,G2,G3 and G4\n");
}

// rolling dice to output 1 - 6 values
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

// output player and rolled value
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

// finding highest rolled value and player
int firstHand()
{
    int firstHandValue[4];
    // int *ptrfirst = first;
    for (int i = 0; i < 4; i++)
    {
        int x = firstroll(i);
        firstHandValue[i] = x;
    }
    // return sort(first);

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
        // printf("%d\n",play[i]);
    }

    printf("Round goes to left hand side and order is %s -> %s -> %s -> %s\n",
           arrayplayerlist[0]->color,
           arrayplayerlist[1]->color,
           arrayplayerlist[2]->color,
           arrayplayerlist[3]->color);
    printf("\n");

    char ch;
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
                switch (i)
                {
                case 0: yellowMove();
                    break;
                case 1: blueMove();
                    break;
                case 2: redMove();
                    break;
                case 3: greenMove();
                    break;
                }

            }
            // one round finished
            printf("\n");
            // endpieces++;

            if (round > 2 && (round % 4 == 0))
            {
                // need to fix error can be mistry
                int mistryIs;
                do
                {
                    mistryIs = rand() % 52;
                } while (0); //(!canBeMistry(mistryIs));

                mistrycell = mistryIs;
                // printf("mistry cell on %d\n", mistrycell);
            }
        }
        // printf("Status of player\n");
        printRound();
        if(round>2)
        {
            printf("The mystery cell is at L%d and will be at that location for the next %d values\n", mistrycell,4-(round%4));
        }
    }
}


void yellowMove()
{
    while(1)
    {

        diceValue = roll();
        printf("Yellow player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player1.inBase > 0 )
            {
                baseToStart(arrayplayerlist[0]);
            }
            else if (yellowcatch(diceValue))
            {
                // searching for a catch to satisfy 1 catch
                capturedOutput();
                printf("Capture Player Gets another Roll\n");
                continue;
            }
            else
            {
                playpiece = standmove(&player1, diceValue);
            }
        }
        else
        {
            if (player1.started == 0)
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n", player1.color, diceValue);
            }
            else
            {
                if (yellowcatch(diceValue))
                {
                    capturedOutput();
                    printf("Capture Player Gets another Roll\n");
                    continue;
                }
                else
                {
                    playpiece = standmove(&player1, diceValue);
                }
            }
            // else
            // {
            //     printf("--------------------------------------------------Edge case - fix\n");
            // }
        }

        // captured(&player1);
        if (canCaptureAny(0))
        {
            capturedOutput();
            continue;
        }

        // avoid block catrector

        if (diceValue == 6 && player1.sixrolled < 2)
        {
            player1.sixrolled++;
            {
                printf("Rolled 6 so player gets another roll\n");
                continue;
            }
        }
        else
        {
            player1.sixrolled = 0;
            break;
        }
    };
}


void blueMove()
{
    while (1)
    {
        diceValue = roll();
        printf("Blue player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player2.inBase > 0)
            {
                baseToStart(&player2);
            }
            else
            {
                playpiece = standmove(&player2, diceValue);
            }
        }
        else
        {
            if (player2.started > 0)
            {
                playpiece = standmove(&player2, diceValue);
            }
            else
            {
                printf("Cannot move must roll 6 to start %d\n", diceValue);
            }
        }

        if (canCaptureAny(1))
        {
            capturedOutput();
            continue;
        }

        if (diceValue == 6 && player2.sixrolled < 2)
        {
            player2.sixrolled++;
            {
                printf("Rolled 6 so player gets another roll\n");
                continue;
            }
        }
        else
        {
            player2.sixrolled = 0;
            break;
        }
    };
}


void redMove()
{
    while (1)
    {
        diceValue = roll();
        printf("RED player rolled %d\n", diceValue);
        // redplayer(x);

        if (diceValue == 6)
        {
            if (player3.inBase == 4)
            {
                baseToStart(&player3);
            }
            else if (redcatch(diceValue))
            {
                capturedOutput();
                printf("Capture Player Gets another Roll\n");
                continue;
            }
            else if (player3.inBase > 0)
            {
                baseToStart(&player3);
            }
            else
            {
                playpiece = standmove(&player3, diceValue);
            }
        }
        else
        {
            if ((player3.started > 0))
            {
                if (redcatch(diceValue))
                {
                    capturedOutput();
                    continue;
                }
                else
                {
                    playpiece = standmove(&player3, diceValue);
                }
            }
            else if (player3.started == 0)
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                       player3.color, diceValue);
            }
        }

        if (canCaptureAny(2))
        {
            capturedOutput();
            continue;
        }

        if (diceValue == 6 && player3.sixrolled < 2)
        {
            player3.sixrolled++;
            {
                printf("Rolled 6 so player gets another roll\n");
                continue;
            }
        }
        else
        {
            player3.sixrolled = 0;
            break;
        }
    };
}


void greenMove()
{
    while(1)
    {
        diceValue = roll();
        printf("Green player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player4.inBase > 0)
            {
                baseToStart(&player4);
            }
            else if (greencatch(diceValue))
            {
                capturedOutput();
                continue;
            }
            else
            {
                playpiece = standmove(&player4, diceValue);
            }
        }
        else
        {
            if (player4.started > 0)
            {
                playpiece = standmove(&player4, diceValue);
            }
            else if (player4.started == 0)
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                       player4.color, diceValue);
            }
            else
            {
                printf("--------------------------------------------------Edge case - fix\n");
            }
        }

        if (canCaptureAny(3))
        {
            capturedOutput();
            continue;
        }

        if (diceValue == 6 && player4.sixrolled < 2)
        {
            player4.sixrolled++;
            {
                printf("Rolled 6 so player gets another roll\n");
                continue;
            }
        }
        else
        {
            player4.sixrolled = 0;
            break;
        }
    };
}


void printRound()
{
    for (int j = 0; j < 4; j++)
    {
        printf("\n");
        printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base\n",
               arrayplayerlist[j]->color,
               arrayplayerlist[j]->started,
               arrayplayerlist[j]->inBase);
        printf("=====================================================================================\n");
        printf("Locations of pieces of %s player\n", arrayplayerlist[j]->color);
        printf("=====================================================================================\n");
        for (int i = 0; i < 4; i++)
        {
            if (arrayplayerlist[j]->forpieces[i][2] == -1)
            {
                printf("%c%d -> Base\n", arrayplayerlist[j]->colorfirst, arrayplayerlist[j]->forpieces[i][1]);
            }
            else if(arrayplayerlist[j]->forpieces[i][2] == 100)
            {
                                printf("%c%d -> Home\n", arrayplayerlist[j]->colorfirst, arrayplayerlist[j]->forpieces[i][1]);

            }
            else
            {
                printf("%c%d is at L%d\n", arrayplayerlist[j]->colorfirst, arrayplayerlist[j]->forpieces[i][1], arrayplayerlist[j]->forpieces[i][2]);
            }
        }
        printf("\n");
    }
}


int selectPlayPiece(player *player, int diceValue)
{
    int playpiece;
    switch (player->playernum)
    {
    case 0:
        return yellowPlayPiece(diceValue);
        break;

    case 1:
        return bluePlayPiece(diceValue);
        break;

    case 2:
        return redPlayPiece();
        break;

    case 3:
        return greenPlayPiece();
        break;
    }
}


// firstly to come to x if all in standard area then move
void baseToStart(player *player)
{
    if (player1.inBase > 0 )
    {
        for (int i = 0; i < 4; i++)
        {
            if (player->forpieces[i][2] == BASE)
            {
                printf("%s player moves piece %c%d to the starting point\n",
                        player->color,
                        player->colorfirst,
                        i + 1);
                
                player->started = player->started + 1;
                player->inBase = player->inBase - 1;
                player->forpieces[i][2] = player->x;
                // store direction in pieces array[4]
                player->forpieces[i][4] = coinToss();

                printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base\n",
                        player->color,
                        player->started,
                        player->inBase);

                return;
            }
        }
    }
    else
    {
        printf("Edge Case found\n");
    }
}


int standmove(player *player, int roll)
{
    int playpiece = selectPlayPiece(player, roll);
    //printf("%s playpiece = %d\n",player->color, playpiece);

    if (    isHome(player, playpiece, roll) && 
            player->forpieces[playpiece][7] > 2 &&
            player->forpieces[playpiece][3] > 0 &&
            player->forpieces[playpiece][8] ==0)
    {
        homeMove(player, playpiece, roll);
    }

    if(player->forpieces[playpiece][8]==1)
    {
        homeMove(player, playpiece, roll);
    }
    else if(player->forpieces[playpiece][8]==0)
    {
        // Bhawana impact & kotuwa impact+
        if (player->forpieces[playpiece][5] != 1 )
        {
            roll = player->forpieces[playpiece][5] * roll;
            player->forpieces[playpiece][6]--;

            if(player->forpieces[playpiece][5]==0)
            {
                //rolled consecutive three times
            }

            if(player->forpieces[playpiece][6]==0)
            {
                player->forpieces[playpiece][5] = 1;
            }
        }
        // Kotuwa Impact
        // if (player->forpieces[playpiece][6] > 0 && player->forpieces[playpiece][2] == KOTUWA)
        // {
        //     printf("%s %c%d in KOTUWA cant move for next %d rounds\n",
        //         player->color,
        //         player->colorfirst,
        //         player->forpieces[playpiece][1],
        //         player->forpieces[playpiece][6]--);
        // }

        // selecting player randomplt has to implement player AIs
        if (player->forpieces[playpiece][4] == 1)
        {
            printf("%s\tmoves %c%d from location\tL%d",
                player->color,
                player->colorfirst,
                playpiece,
                player->forpieces[playpiece][2]);
            // player->forpieces[randomplayer][2] = player->forpieces[randomplayer][2]+x;
            player->forpieces[playpiece][2] = ((player->forpieces[playpiece][2]) + roll) % 52;
            printf("to L%d by units\t%d clockwise direction\n", player->forpieces[playpiece][2],roll);
            // captured(player, randomplaypiece);
        }

        else if (player->forpieces[playpiece][4] == -1)
        {
            printf("%s\tmoves %c%d from location\tL%d",
                player->color,
                player->colorfirst,
                playpiece,
                player->forpieces[playpiece][2]);

            player->forpieces[playpiece][2] = player->forpieces[playpiece][2] - roll;
            if (player->forpieces[playpiece][2] <= 0)
            {
                player->forpieces[playpiece][2] = 51 + player->forpieces[playpiece][2];
            }
            printf("to L%d by units\t%d Counter-clockwise direction\n", player->forpieces[playpiece][2],roll);

            if (player->forpieces[playpiece][2] == (mistrycell))
            {
                teleport(player, playpiece, mistrycell);
            }
        }
        player->forpieces[playpiece][7] =+ roll;
    }
    else
    {
        printf("Edge------------------------------------------standmove\n");
    }
    return playpiece;
}


int coinToss()
{
    int x = (rand() % 2);
    if (x == 0)
    {
        printf("Coin tossed\t-> Head -> Piese moving clockwise direction\n");
        return 1;
    }
    else
    {
        printf("Coin tossed\t-> Tail -> Piese moving Counter clockwise direction\n");
        return -1;
    }
}


int capturedOutput()
{
    // 0 - capturer , 1 - piece , 2 - captured , 3 - piece, 4- location
    printf("%s Player %c%d lands on square L%d,captures %s Player %c%d, and returns it to the base\n",
           arrayplayerlist[captureData[0]]->color,
           arrayplayerlist[captureData[0]]->colorfirst,
           arrayplayerlist[captureData[0]]->forpieces[captureData[1]][1] + 1,
           captureData[4],
           arrayplayerlist[captureData[2]]->color,
           arrayplayerlist[captureData[2]]->colorfirst,
           arrayplayerlist[captureData[2]]->forpieces[captureData[3]][1] + 1);

    //increment captured value of capturer
    arrayplayerlist[captureData[0]]->forpieces[captureData[1]][3]++;
    //decremrnting captured pieces started count and increment agian inBase count
    arrayplayerlist[captureData[2]]->inBase++;
    arrayplayerlist[captureData[2]]->started--;
    //captured pieces position to BASE
    arrayplayerlist[captureData[2]]->forpieces[captureData[3]][2] = BASE;
    //captured pieces travelled value to zero
    arrayplayerlist[captureData[2]]->forpieces[captureData[3]][7] = 0;
    //captured pieces captured count to zero
    arrayplayerlist[captureData[2]]->forpieces[captureData[3]][3] = 0;


    printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base\n",
           arrayplayerlist[captureData[2]]->color,
           arrayplayerlist[captureData[2]]->started,
           arrayplayerlist[captureData[2]]->inBase);
}


bool canCaptureAny(int player)
{
    // arrayplayerlist[player];
    // check any captured happende after a move
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if ( // remove comparing same players pieces
                    arrayplayerlist[player] != arrayplayerlist[j] &&
                    // can not catch at starting position
                    //  player->forpieces[i][2] != YX && player->forpieces[i][2] != BX &&
                    //  player->forpieces[i][2] != RX && player->forpieces[i][2] != GX &&
                    //check if it in the homepath
                    arrayplayerlist[j]->forpieces[k][8] == 0 &&
                    // removing in base pieces
                    (arrayplayerlist[player]->forpieces[i][2] != BASE) &&
                    // removing oppenent pieces base pieces
                    (arrayplayerlist[j]->forpieces[k][2] != BASE) &&
                    // if they in a same block
                    (arrayplayerlist[player]->forpieces[i][2] == arrayplayerlist[j]->forpieces[k][2]))
                {
                    captureData[0] = player;
                    captureData[1] = i;
                    captureData[2] = j;
                    captureData[3] = k;
                    captureData[4] = arrayplayerlist[j]->forpieces[k][2];

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
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
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


void teleport(player *player, int playpiece, int onmistry)
{
    switch (rand() % 6)
    {
    case 0:
        printf("%s piece %c%d teleported to Bhawana - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,BHAWANA);

        player->forpieces[playpiece][2] = BHAWANA;
        player->forpieces[playpiece][6] = FOURROUND;
        if (rand() % 2 == 0)
        {
            player->forpieces[playpiece][5] = ENERGIZE;
            printf("%s piece %c%d feels energized, and movement speed doubles.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        else
        {
            player->forpieces[playpiece][5] = SICK;
            printf("%s piece %c%d feels sick, and movement speed halves.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        break;

    case 1:
        printf("%s piece %c%d teleported to Kotuwa - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,KOTUWA);
        player->forpieces[playpiece][2] = KOTUWA;
        player->forpieces[playpiece][6] = FOURROUND;
        player->forpieces[playpiece][5] = FREEZE;
        printf("%s piece %c%d attends briefing and cannot move for four rounds.\n",
                player->color,player->colorfirst,playpiece+1);
        break;

    case 2:
        printf("%s piece %c%d teleported to Pita-Kotuwa - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,PITAKOTUWA);

        if (player->forpieces[playpiece][4] == 1)
        {
            player->forpieces[playpiece][4] = -1;
            printf("The %s piece %c%d which was moving clockwise, has changed to moving coun-terclockwise.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        else
        {
            printf("%s piece %c%d teleported to Kotuwa - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,KOTUWA);

            player->forpieces[playpiece][2] = KOTUWA;
            player->forpieces[playpiece][6] = FOURROUND;
            player->forpieces[playpiece][5] = FREEZE;

            printf("The %s piece %c%d  is moving in a counterclockwise direction. Teleporting to Kotuwa from Pita-Kotuwa.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        break;

    case 3:
        printf("%s piece %c%d teleported to Base - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,BASE);
        player->forpieces[playpiece][2] = BASE;
        break;

    case 4:
        printf("%s piece %c%d teleported to X - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,player->x);
        player->forpieces[playpiece][2] = player->x;
        break;

    case 5:
        printf("%s piece %c%d teleported to O - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,player->o);
        player->forpieces[playpiece][2] = player->o;
        break;
    }
}


bool canBeMistry(int mistryis)
{
    if (isPiecelocated)
    {
        return false;
    }
    else if (mistrycell == mistryis)
    {
        return false;
    }
    else
    {
        return true;
    }
}


int redcatch(int diceValue)
{
    int mintoHome = 52;
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
                        // can not catch at starting position
                        //  player3.forpieces[i][2] != YX && player3.forpieces[i][2] != BX &&
                        //  player3.forpieces[i][2] != RX && player3.forpieces[i][2] != GX &&

                        //remove homepath players
                        arrayplayerlist[j]->forpieces[k][8] == 0 &&
                        // removing in base pieces
                        (player3.forpieces[i][2] != BASE) &&
                        // removing oppenent pieces base pieces
                        (arrayplayerlist[i]->forpieces[k][2] != BASE) &&
                        // if they in a same block
                        (player3.forpieces[i][2] + diceValue == arrayplayerlist[j]->forpieces[k][2]))
                    {
                        if (arrayplayerlist[j]->o - arrayplayerlist[j]->forpieces[k][2] < mintoHome)
                        {
                            mintoHome = arrayplayerlist[j]->o - arrayplayerlist[j]->forpieces[k][2];
                            // capturer color , piece captured color, piece,location
                            captureData[0] = 2;
                            captureData[1] = i;
                            captureData[2] = j;
                            captureData[3] = k;
                            captureData[4] = arrayplayerlist[j]->forpieces[k][2];

                            if (i == 4 && j == 4 && k == 4)
                            {
                                player1.forpieces[captureData[1]][2] = player1.forpieces[captureData[1]][2] + diceValue;
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}


bool yellowcatch(int diceValue)
{
    for (int i = 0; i < 4; i++)
    {
        if (player1.forpieces[i][2] != BASE &&
            player1.forpieces[i][3] == 0)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arrayplayerlist[0] != arrayplayerlist[j] &&
                        arrayplayerlist[j]->forpieces[k][8] == 0 &&
                        player1.forpieces[i][2] + diceValue == arrayplayerlist[j]->forpieces[k][2])
                    {
                        player1.forpieces[i][2] = player1.forpieces[i][2] + diceValue;
                        // capturer color , piece captured color, piece,location
                        captureData[0] = 0;
                        captureData[1] = i;
                        captureData[2] = j;
                        captureData[3] = k;
                        captureData[4] = arrayplayerlist[j]->forpieces[k][2];

                        return true;
                    }
                }
            }
        }
    }
    return false;
}


bool greencatch(int diceValue)
{
    for (int i = 0; i < 4; i++)
    {
        if (player4.forpieces[i][2] != BASE &&
            player4.forpieces[i][3] == 0)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arrayplayerlist[0] != arrayplayerlist[j] &&
                        arrayplayerlist[j]->forpieces[k][8] == 0 &&
                        player4.forpieces[i][2] + diceValue == arrayplayerlist[j]->forpieces[k][2])
                    {
                        player4.forpieces[i][2] = player4.forpieces[i][2] + diceValue;
                        // capturer color , piece captured color, piece,location
                        captureData[0] = 0;
                        captureData[1] = i;
                        captureData[2] = j;
                        captureData[3] = k;
                        captureData[4] = arrayplayerlist[j]->forpieces[k][2];

                        return true;
                    }
                }
            }
        }
    }
    return false;
}


int yellowPlayPiece(int diceValue)
{
    int unitsToHome;
    int minUnits = 100;
    int yellowplaypiece;
    for (int i = 0; i < 4; i++)
    {
        if (player1.forpieces[i][2] != BASE)
        {
            if (player1.forpieces[i][4] == 1)
            {
                unitsToHome = 52 - player1.forpieces[i][2];
                if (unitsToHome < minUnits)
                {
                    minUnits = unitsToHome;
                    yellowplaypiece = i;
                }
            }
            else if (player1.forpieces[i][4] == -1)
            {
                if (player1.forpieces[i][2] <= 2)
                {
                    unitsToHome = 51 + (player1.forpieces[i][2]);
                    if (unitsToHome < minUnits)
                    {
                        minUnits = unitsToHome;
                        yellowplaypiece = i;
                        //player1.forpieces[i][7] = player1.forpieces[i][7] + 2;
                    }
                }
                else
                {
                    unitsToHome = player1.forpieces[i][2];
                    if (unitsToHome < minUnits)
                    {
                        minUnits = unitsToHome;
                        yellowplaypiece = i;
                        printf("playpiece = %d,\n", yellowplaypiece);
                    }
                }
            }
        }
    }
    return yellowplaypiece;
}


int bluePlayPiece(int diceValue)
{
    while (1)
    {
        if (blueOrder > 3)
        {
            blueOrder = 0;
        }
        if (player2.forpieces[blueOrder][2] != BASE)
        {
            return blueOrder;
        }
        blueOrder++;
    }
}


int redPlayPiece()
{
    int x;
    if(player3.started==1)
    {
        for(int i=0;i<4;i++)
        {
            if(player3.forpieces[i][2]!=BASE)
            {
                return i;
            }
        }
    }
    else
    {
        do
        {
            x = rand() % 4;
        } while (player3.forpieces[x][2]==BASE);
        return x;
    }
}


int greenPlayPiece()
{
    int x;
    if(player4.started==1)
    {
        for(int i=0;i<4;i++)
        {
            if(player4.forpieces[i][2]!=BASE)
            {
                return i;
            }
        }
    }
    else
    {
        do
        {
            x = rand() % 4;
        } while (player4.forpieces[x][2]==BASE);
        return x;
    }
}


bool isHome(player *player, int playpiece, int roll)
{
    if (player->forpieces[playpiece][4] == 1)
    {
        //works all but not to yellow
        if (player->forpieces[playpiece][2] < player->o &&
            player->forpieces[playpiece][2] + roll >= player->o)
        {
            return true;;
        }
        else
        {
            return false;
        }
    }
    else if(player->forpieces[playpiece][4] == -1)
    {
        if (player->forpieces[playpiece][2] > player->o &&
            player->forpieces[playpiece][2] + roll <= player->o)
        {
            return true;;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


void homeMove(player *player, int playpiece, int roll)
{
    //indicater for he is in home path
    player->forpieces[playpiece][8] = 1;
    if(player->forpieces[playpiece][9]=0)
    {
        if(player->forpieces[playpiece][3] = 1)
        {
            int togo = roll - (player->o - player->forpieces[playpiece][2]);
            player->forpieces[playpiece][9]=+togo;
        }
        else
        {
            int togo = roll - (player->forpieces[playpiece][2] - player->o);
            player->forpieces[playpiece][9]=+togo;
        }
    }
    else if(player->forpieces[playpiece][9]!=6)
    {
        if(player->forpieces[playpiece][9]+roll < 6)
        {
            player->forpieces[playpiece][9] += roll;
        }
        else if(player->forpieces[playpiece][9]+roll == 6)
        {
            player->forpieces[playpiece][9] += roll;
            printf("%s %c%d====================Player Wins\n",player->color,player->colorfirst,playpiece+1);
            player->forpieces[playpiece][2] = FINISH;
            player->forpieces[playpiece][3] = FINISH;
            player->forpieces[playpiece][9] = FINISH;
            player->finished++;
            player->started--;
            endpieces++;   
        }
        else
        {
            printf("Can not move must roll %d\n",6 - player->forpieces[playpiece][9]);
        }
    }
    if (player->forpieces[playpiece][9]==6)
    {
        // 0 - playercolor , 1 - pircenumber , 2 - position , 3 - captured , 4 - direction(1 - clockwise,-1 - anticlockwise)
        // 5 - Bhawana impact 2* or 0.5* , 6 - counterforimpacts ,7 - travelled , 8 - (not home 0 ,home 1)
        // 9 - homepath value 
             
    }
}
