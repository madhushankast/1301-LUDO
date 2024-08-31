#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "type.h"
#include "logic.h"

const char *players[4] = {"Yellow", "Blue", "Red", "Green"};

// pieces all goes with numbers
// 0 - playercolor  |   1 - pircenumber |   2 - position    |   3 - captured 
// 4 - direction (1 - clockwise / -1 - anticlockwise)
// 5 - Bhawana impact 2* or 0.5*        |    6 - counterforimpacts
// 7 - travelled    |   8  - homepath value |   9 - finneshed the play

// yellow
int piecey1[PIECEDATA] = {YELLOW, PIECE1, BASE, 0, 0, 1, 0,0 ,-1};
int piecey2[PIECEDATA] = {YELLOW, PIECE2, BASE, 0, 0, 1, 0,0 , -1};
int piecey3[PIECEDATA] = {YELLOW, PIECE3, BASE, 0, 0, 1, 0,0 ,-1};
int piecey4[PIECEDATA] = {YELLOW, PIECE4, BASE, 0, 0, 1, 0,0 , -1};

// blue pieces
int pieceb1[PIECEDATA] = {BLUE, PIECE1, BASE, 0, 0, 1, 0,0 ,-1};
int pieceb2[PIECEDATA] = {BLUE, PIECE2, BASE, 0, 0, 1, 0,0 , -1};
int pieceb3[PIECEDATA] = {BLUE, PIECE3, BASE, 0, 0, 1, 0,0 , -1};
int pieceb4[PIECEDATA] = {BLUE, PIECE4, BASE, 0, 0, 1, 0,0 , -1};

// red pieces
int piecer1[PIECEDATA] = {RED, PIECE1, BASE, 0, 0, 1, 0,0 , -1};
int piecer2[PIECEDATA] = {RED, PIECE2, BASE, 0, 0, 1, 0,0 , -1};
int piecer3[PIECEDATA] = {RED, PIECE3, BASE, 0, 0, 1, 0,0 , -1};
int piecer4[PIECEDATA] = {RED, PIECE4, BASE, 0, 0, 1, 0,0 , -1};

// green pieces
int pieceg1[PIECEDATA] = {GREEN, PIECE1, BASE, 0, 0, 1, 0,0 , -1};
int pieceg2[PIECEDATA] = {GREEN, PIECE2, BASE, 0, 0, 1, 0,0 , -1};
int pieceg3[PIECEDATA] = {GREEN, PIECE3, BASE, 0, 0, 1, 0,0 , -1};
int pieceg4[PIECEDATA] = {GREEN, PIECE4, BASE, 0, 0, 1, 0,0 , -1};

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
int redorder = 0;
int greenorder = 0;
//int playpiece;

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

    printf("ENDGAME\n");
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

        printf("%s player has the highest roll and will begin the game\n",
        players[*(sortplayer + 3)]);
        printf("The rolled dise value order is %s, %s, %s, and %s\n",
            players[*(sortplayer + 3)],
            players[*(sortplayer + 2)],
            players[*(sortplayer + 1)],
            players[*(sortplayer)]);

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
           arrayplayerlist[play[0]]->color,
           arrayplayerlist[play[1]]->color,
           arrayplayerlist[play[2]]->color,
           arrayplayerlist[play[3]]->color);
    printf("\n");


    int round = 1;

    while (endpieces < 16 )
    {
    
    // while (1) {
    //     if ( getchar()) { // '\r' is the Enter key
            printf("Code is running...\n");


            printf("This is round ----> %d\n", round++);

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
                    if(canBeMistry(mistryIs))
                    {
                        break;
                    }
                } while (0); 

                mistrycell = mistryIs;
                // printf("mistry cell on %d\n", mistrycell);
            }
    
        // printf("Status of player\n");
        printRound();
        if(round>2)
        {
            printf("The mystery cell is at L%d and will be at that location for the next %d values\n",
                        mistrycell,
                        4-(round%4));
        }
//         break;
//     }
//

        for(int i=0;i<4;i++)
        {
            if(arrayplayerlist[i]->finished == 4)
            {
                printf("%s wins game\n",arrayplayerlist[i]->color);
                return;
            }
        }
    }
}


void yellowMove()
{
    if(player1.finished == 4)
    {
        return;
    }
    while(1)
    {

        diceValue = roll();
        printf("Yellow player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player1.inBase > -1 )
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
            else if(player1.started > 0)
            {
                standmove(&player1, diceValue);
            }
        }
        else
        {
            if (player1.started == 0)
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n", player1.color, diceValue);
                return;
            }
            else if(player1.started > 0)
            {
                if (yellowcatch(diceValue))
                {
                    capturedOutput();
                    printf("Capture Player Gets another Roll\n");
                    continue;
                }
                else
                {
                    standmove(&player1, diceValue);
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
            printf("Capture Player Gets another Roll\n");
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
    if(player2.finished == 4)
    {
        return;
    }
    while (1)
    {
        diceValue = roll();
        printf("Blue player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player2.inBase > -1)
            {
                baseToStart(&player2);
            }
            else if(player2.started > 0)
            {
                standmove(&player2, diceValue);
            }
        }
        else
        {
            if (player2.started > 0)
            {
                standmove(&player2, diceValue);
            }
            else
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n", player2.color, diceValue);
            }
        }

        if (canCaptureAny(1))
        {

            capturedOutput();
            printf("Capture Player Gets another Roll\n");
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
    if(player3.finished == 4)
    {
        return;
    }
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
            else if (player3.inBase > -1)
            {
                baseToStart(&player3);
            }
            else
            {
                standmove(&player3, diceValue);
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
                    standmove(&player3, diceValue);
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
            printf("Capture Player Gets another Roll\n");
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
    if(player4.finished == 4)
    {
        return;
    }
    while(1)
    {
        diceValue = roll();
        printf("Green player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player4.inBase > -1)
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
                standmove(&player4, diceValue);
            }
        }
        else
        {
            if (player4.started > 0)
            {
                standmove(&player4, diceValue);
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
            printf("Capture Player Gets another Roll\n");
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
        printf("%s player now has\n%d/4 on pieces on the board | %d/4 pieces on the base | %d/4 Finished\n",
               arrayplayerlist[j]->color,
               arrayplayerlist[j]->started,
               arrayplayerlist[j]->inBase,
               arrayplayerlist[j]->finished);
        printf("=====================================================================================\n");
        printf("Locations of pieces of %s player\n", arrayplayerlist[j]->color);
        printf("=====================================================================================\n");
        for (int i = 0; i < 4; i++)
        {
            if (arrayplayerlist[j]->pieceDeatail[i][2] == BASE)
            {
                printf("%c%d -> Base\tcaptured - %d\tTravelled - %d\tDirection - %d\tHome L=%d\n",
                arrayplayerlist[j]->colorfirst,
                arrayplayerlist[j]->pieceDeatail[i][1],
                arrayplayerlist[j]->pieceDeatail[i][3],
                arrayplayerlist[j]->pieceDeatail[i][7],
                arrayplayerlist[j]->pieceDeatail[i][4],
                arrayplayerlist[j]->pieceDeatail[i][8]);
            }
            else if(arrayplayerlist[j]->pieceDeatail[i][8] >= 6)
            {
                printf("%c%d -> Home\tcaptured - %d\tTravelled - %d\tDirection - %d\tHome L= %d\n",
                arrayplayerlist[j]->colorfirst,
                arrayplayerlist[j]->pieceDeatail[i][1],
                arrayplayerlist[j]->pieceDeatail[i][3],
                arrayplayerlist[j]->pieceDeatail[i][7],
                arrayplayerlist[j]->pieceDeatail[i][4],
                arrayplayerlist[j]->pieceDeatail[i][8]);

            }
            else
            {
                printf("%c%d is at L%d\tcaptured - %d\tTravelled - %d\tDirection - %d\tHome L= %d\n",
                arrayplayerlist[j]->colorfirst,
                arrayplayerlist[j]->pieceDeatail[i][1],
                arrayplayerlist[j]->pieceDeatail[i][2],
                arrayplayerlist[j]->pieceDeatail[i][3],
                arrayplayerlist[j]->pieceDeatail[i][7],
                arrayplayerlist[j]->pieceDeatail[i][4],
                arrayplayerlist[j]->pieceDeatail[i][8]);
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
    if(player->finished == 4)
    {
        return;
    }

    if (player1.inBase > -1 )
    {
        for (int i = 0; i < 4; i++)
        {
            if (player->pieceDeatail[i][2] == BASE  && player->pieceDeatail[i][8] != FINISH)
            {
                printf("%s player moves piece %c%d to the starting point\n",
                        player->color,
                        player->colorfirst,
                        i + 1);
                
                player->started = player->started + 1;
                player->inBase = player->inBase - 1;
                player->pieceDeatail[i][2] = player->x;
                // store direction in pieces array[4]
                player->pieceDeatail[i][4] = coinToss();

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
    int playpiece;
    
    if(player->finished == 4)
    {
        return 0;
    }

    //printf("%s playpiece = %d\n",player->color, playpiece);

    // for(int i =0;i<4;i++)
    // {
    //     if(player->pieceDeatail[i][8] >-1 && player->pieceDeatail[i][8]+roll <= 6)
    //     {
    //         playpiece = i;
    //     }
    // }
    for(int i=0;i<4;i++)
    {
        if(player->pieceDeatail[i][8] > -1 && player->pieceDeatail[i][8]+roll <= 6)
        {
            homeMove(player, i, roll);
            return 0;
        }
    }

    playpiece = selectPlayPiece(player, roll);
        if(playpiece == -1)
        {
            return 0;
        }
    

    if(player->pieceDeatail[playpiece][8] == -1)
    {

        if(passApporoach(player, playpiece, roll) &&          //can enter to the hoempath
            player->pieceDeatail[playpiece][7] > 2 &&      //must travelled more than two sells
            player->pieceDeatail[playpiece][3] > 0 )      //must have captured at least one piece  )      //not already in the homepath
        {
            printf("------------------------------------------Homemove move\n");

            homeMove(player, playpiece, roll);
            return 0;
        }

        // Bhawana impact & kotuwa impact+
        if (player->pieceDeatail[playpiece][5] != 1 )
        {
            roll = player->pieceDeatail[playpiece][5] * roll;
            player->pieceDeatail[playpiece][6]--;

            if(player->pieceDeatail[playpiece][5]==0)
            {
                //rolled consecutive three times
            }

            if(player->pieceDeatail[playpiece][6]==0)
            {
                player->pieceDeatail[playpiece][5] = 1;
            }
        }
        // Kotuwa Impact
        // if (player->pieceDeatail[playpiece][6] > 0 && player->pieceDeatail[playpiece][2] == KOTUWA)
        // {
        //     printf("%s %c%d in KOTUWA cant move for next %d rounds\n",
        //         player->color,
        //         player->colorfirst,
        //         player->pieceDeatail[playpiece][1],
        //         player->pieceDeatail[playpiece][6]--);
        // }

        // selecting player randomplt has to implement player AIs
        if (player->pieceDeatail[playpiece][4] == 1)
        {
            printf("%s\tmoves %c%d from location\tL%d",
                player->color,
                player->colorfirst,
                playpiece,
                player->pieceDeatail[playpiece][2]);
            // player->pieceDeatail[randomplayer][2] = player->pieceDeatail[randomplayer][2]+x;
            player->pieceDeatail[playpiece][2] = ((player->pieceDeatail[playpiece][2]) + roll) % 52;
            printf("to L%d by units\t%d clockwise direction\n", player->pieceDeatail[playpiece][2],roll);

            player->pieceDeatail[playpiece][7] = player->pieceDeatail[playpiece][7]+roll;
            // captured(player, randomplaypiece);
        }

        else if (player->pieceDeatail[playpiece][4] == -1)
        {
            printf("%s\tmoves %c%d from location\tL%d",
                player->color,
                player->colorfirst,
                playpiece,
                player->pieceDeatail[playpiece][2]);

            player->pieceDeatail[playpiece][2] = player->pieceDeatail[playpiece][2] - roll;
            if (player->pieceDeatail[playpiece][2] <= 0)
            {
                player->pieceDeatail[playpiece][2] = 51 + player->pieceDeatail[playpiece][2];
            }
            printf("to L%d by units\t%d Counter-clockwise direction\n", player->pieceDeatail[playpiece][2],roll);

            player->pieceDeatail[playpiece][7] = player->pieceDeatail[playpiece][7]+roll;
        }

        if (player->pieceDeatail[playpiece][2] == mistrycell)
        {
            mistryTeleport(player, playpiece);
        }
        
    }
    else
    {
        printf("Edge------------------------------------------standmove\n");
    }
    return 0;
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
           arrayplayerlist[captureData[0]]->pieceDeatail[captureData[1]][1] + 1,
           captureData[4],
           arrayplayerlist[captureData[2]]->color,
           arrayplayerlist[captureData[2]]->colorfirst,
           arrayplayerlist[captureData[2]]->pieceDeatail[captureData[3]][1] + 1);

    //increment captured value of capturer
    arrayplayerlist[captureData[0]]->pieceDeatail[captureData[1]][3]++;
    //decremrnting captured pieces started count and increment agian inBase count
    arrayplayerlist[captureData[2]]->inBase=arrayplayerlist[captureData[2]]->inBase+1;
    arrayplayerlist[captureData[2]]->started=arrayplayerlist[captureData[2]]->started-1;
    //captured pieces position to BASE
    arrayplayerlist[captureData[2]]->pieceDeatail[captureData[3]][2] = BASE;
    //captured pieces travelled value to zero
    arrayplayerlist[captureData[2]]->pieceDeatail[captureData[3]][7] = 0;
    //captured pieces captured count to zero
    arrayplayerlist[captureData[2]]->pieceDeatail[captureData[3]][3] = 0;
    arrayplayerlist[captureData[2]]->pieceDeatail[captureData[3]][8] = -1;


    printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base\n",
           arrayplayerlist[captureData[2]]->color,
           arrayplayerlist[captureData[2]]->started,
           arrayplayerlist[captureData[2]]->inBase);

    // captureData[0] = 0;
    // captureData[1] = 0;
    // captureData[2] = 0;
    // captureData[3] = 0;
    // captureData[4] = 0;
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
                    //  player->pieceDeatail[i][2] != YX && player->pieceDeatail[i][2] != BX &&
                    //  player->pieceDeatail[i][2] != RX && player->pieceDeatail[i][2] != GX &&
                    //check if it in the homepath
                    arrayplayerlist[player]->pieceDeatail[i][8] == -1 &&
                    //arrayplayerlist[player]->pieceDeatail[i][2] != FINISH &&
                    // removing in base pieces
                    arrayplayerlist[player]->pieceDeatail[i][2] != BASE &&
                    // removing oppenent pieces base pieces
                    //arrayplayerlist[j]->pieceDeatail[k][2] != BASE &&
                    // if they in a same block
                    arrayplayerlist[player]->pieceDeatail[i][2] == arrayplayerlist[j]->pieceDeatail[k][2])
                {
                    captureData[0] = player;
                    captureData[1] = i;
                    captureData[2] = j;
                    captureData[3] = k;
                    captureData[4] = arrayplayerlist[j]->pieceDeatail[k][2];

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
        if (((player->pieceDeatail[randomplaypiece][2]) || (player->pieceDeatail[i][2])) != BASE &&
            player->pieceDeatail[randomplaypiece][2] == player->pieceDeatail[i][2])
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
            if (((player->pieceDeatail[i][2]) || (player->pieceDeatail[j][2])) != BASE &&
                player->pieceDeatail[i][2] == player->pieceDeatail[j][2])
            {
                return 1;
            }
        }
    }
    return 0;
}


void mistryTeleport(player *player, int playpiece)

{
    switch (rand() % 6)
    {
    case 0:
        printf("%s piece %c%d teleported to Bhawana - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,BHAWANA);

        player->pieceDeatail[playpiece][2] = BHAWANA;
        player->pieceDeatail[playpiece][6] = FOURROUND;
        if (rand() % 2 == 0)
        {
            player->pieceDeatail[playpiece][5] = ENERGIZE;
            printf("%s piece %c%d feels energized, and movement speed doubles.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        else
        {
            player->pieceDeatail[playpiece][5] = SICK;
            printf("%s piece %c%d feels sick, and movement speed halves.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        break;

    case 1:
        printf("%s piece %c%d teleported to Kotuwa - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,KOTUWA);
        player->pieceDeatail[playpiece][2] = KOTUWA;
        player->pieceDeatail[playpiece][6] = FOURROUND;
        player->pieceDeatail[playpiece][5] = FREEZE;
        printf("%s piece %c%d attends briefing and cannot move for four rounds.\n",
                player->color,player->colorfirst,playpiece+1);
        break;

    case 2:
        printf("%s piece %c%d teleported to Pita-Kotuwa - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,PITAKOTUWA);

        if (player->pieceDeatail[playpiece][4] == 1)
        {
            player->pieceDeatail[playpiece][4] = -1;
            printf("The %s piece %c%d which was moving clockwise, has changed to moving coun-terclockwise.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        else
        {
            printf("%s piece %c%d teleported to Kotuwa - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,KOTUWA);

            player->pieceDeatail[playpiece][2] = KOTUWA;
            player->pieceDeatail[playpiece][6] = FOURROUND;
            player->pieceDeatail[playpiece][5] = FREEZE;

            printf("The %s piece %c%d  is moving in a counterclockwise direction. mistryTeleporting to Kotuwa from Pita-Kotuwa.\n",
                player->color,player->colorfirst,playpiece+1);
        }
        break;

    case 3:
        printf("%s piece %c%d teleported to Base - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,BASE);
        player->pieceDeatail[playpiece][2] = BASE;
        player->inBase++;
        player->started--;
        break;

    case 4:
        printf("%s piece %c%d teleported to X - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,player->x);
        player->pieceDeatail[playpiece][2] = player->x;
        break;

    case 5:
        printf("%s piece %c%d teleported to O - Cell - %d.\n",
                player->color,player->colorfirst,playpiece+1,player->o);
        player->pieceDeatail[playpiece][2] = player->o;
        break;
    }
}


bool canBeMistry(int mistryis)
{
    if (isPiecelocated(mistryis))
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


bool isPiecelocated(int mistryis)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arrayplayerlist[i]->pieceDeatail[j][2] == mistryis)
            {
                return true;
            }
        }
    }
    return false;
}


int redcatch(int diceValue)
{
    int mintoHome = 52;
    for (int i = 0; i < 4; i++)
    {
        if (player3.pieceDeatail[i][2] != BASE && player3.pieceDeatail[i][8] == -1)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if ( // remove comparing same players pieces
                        &player3 != arrayplayerlist[j] &&
                        // can not catch at starting position
                        player3.pieceDeatail[i][2]+ diceValue != YX &&
                        player3.pieceDeatail[i][2]+ diceValue != BX &&
                        player3.pieceDeatail[i][2]+ diceValue != RX &&
                        player3.pieceDeatail[i][2]+ diceValue != GX &&

                        //remove homepath players
                        arrayplayerlist[j]->pieceDeatail[k][8] == 0 &&
                        // removing in base pieces
                        (player3.pieceDeatail[i][2] != BASE) &&
                        // removing oppenent pieces base pieces
                        (arrayplayerlist[i]->pieceDeatail[k][2] != BASE) &&
                        // if they in a same block
                        (player3.pieceDeatail[i][2] + diceValue == arrayplayerlist[j]->pieceDeatail[k][2]))
                    {
                        if (arrayplayerlist[j]->o - arrayplayerlist[j]->pieceDeatail[k][2] < mintoHome)
                        {
                            mintoHome = arrayplayerlist[j]->o - arrayplayerlist[j]->pieceDeatail[k][2];
                            // capturer color , piece captured color, piece,location
                            captureData[0] = 2;
                            captureData[1] = i;
                            captureData[2] = j;
                            captureData[3] = k;
                            captureData[4] = arrayplayerlist[j]->pieceDeatail[k][2];

                            if (i == 4 && j == 4 && k == 4)
                            {
                                player1.pieceDeatail[captureData[1]][2] = player1.pieceDeatail[captureData[1]][2] + diceValue;
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
        if (player1.pieceDeatail[i][2] != BASE &&
            player1.pieceDeatail[i][8] == -1 &&
            player1.pieceDeatail[i][3] == 0 &&
            player1.pieceDeatail[i][2]+ diceValue != YX &&
            player1.pieceDeatail[i][2]+ diceValue != BX &&
            player1.pieceDeatail[i][2]+ diceValue != RX &&
            player1.pieceDeatail[i][2]+ diceValue != GX)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arrayplayerlist[0] != arrayplayerlist[j] &&
                        arrayplayerlist[j]->pieceDeatail[k][8] == -1 &&
                        player1.pieceDeatail[i][2] + diceValue == arrayplayerlist[j]->pieceDeatail[k][2])
                    {
                        player1.pieceDeatail[i][2] = player1.pieceDeatail[i][2] + diceValue;
                        // capturer color , piece captured color, piece,location
                        captureData[0] = 0;
                        captureData[1] = i;
                        captureData[2] = j;
                        captureData[3] = k;
                        captureData[4] = arrayplayerlist[j]->pieceDeatail[k][2];

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
        if (player4.pieceDeatail[i][2] != BASE &&
            player4.pieceDeatail[i][8] == -1 &&
            player4.pieceDeatail[i][3] == 0)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arrayplayerlist[0] != arrayplayerlist[j] &&
                        arrayplayerlist[j]->pieceDeatail[k][8] == 0 &&
                        player3.pieceDeatail[i][2]+ diceValue != YX &&
                        player3.pieceDeatail[i][2]+ diceValue != BX &&
                        player3.pieceDeatail[i][2]+ diceValue != RX &&
                        player3.pieceDeatail[i][2]+ diceValue != GX &&

                        player4.pieceDeatail[i][2] + diceValue == arrayplayerlist[j]->pieceDeatail[k][2])
                    {
                        player4.pieceDeatail[i][2] = player4.pieceDeatail[i][2] + diceValue;
                        // capturer color , piece captured color, piece,location
                        captureData[0] = 0;
                        captureData[1] = i;
                        captureData[2] = j;
                        captureData[3] = k;
                        captureData[4] = arrayplayerlist[j]->pieceDeatail[k][2];

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
    int yellowpiece = -1;
    for (int i = 0; i < 4; i++)
    {
        if (player1.pieceDeatail[i][2] != BASE &&  player1.pieceDeatail[i][8] < 0)
        {
            if (player1.pieceDeatail[i][4] == 1)
            {
                unitsToHome = 52 - player1.pieceDeatail[i][2];
                if (unitsToHome < minUnits)
                {
                    minUnits = unitsToHome;
                    yellowpiece = i;
                }
            }
            else if (player1.pieceDeatail[i][4] == -1)
            {
                if (player1.pieceDeatail[i][2] <= 2)
                {
                    unitsToHome = 51 + player1.pieceDeatail[i][2];
                    if (unitsToHome < minUnits)
                    {
                        minUnits = unitsToHome;
                        yellowpiece = i;
                        //player1.pieceDeatail[i][7] = player1.pieceDeatail[i][7] + 2;
                    }
                }
                else
                {
                    unitsToHome = player1.pieceDeatail[i][2];
                    if (unitsToHome < minUnits)
                    {
                        minUnits = unitsToHome;
                        yellowpiece = i;
                        //printf("playpiece = %d,\n", yellowplaypiece);
                    }
                }
            }
        }
    }
    return yellowpiece;
}


int bluePlayPiece(int diceValue)
{
    for(int i=0;i<4;i++)
    {
        if (player2.pieceDeatail[blueOrder%4][2] != BASE &&
                player2.pieceDeatail[blueOrder%4][8] == -1)
        {
            return blueOrder%4;
        }
        blueOrder = blueOrder+1;
    }
    return -1;
}


int redPlayPiece()
{
    for(int i=0;i<4;i++)
    {
        if (player3.pieceDeatail[redorder%4][2] != BASE &&
                player3.pieceDeatail[redorder%4][8] == -1)
        {
            return redorder%4;
        }
        redorder = redorder+1;
    }
    return -1;
    // int x;
    // if(player3.started==1)
    // {
    //     for(int i=0;i<4;i++)
    //     {
    //         if(player3.pieceDeatail[i][2]!=BASE  && player3.pieceDeatail[i][8] < 0)
    //         {
    //             return i;
    //         }
    //     }
    //     return -1;
    // }
    // else
    // {
    //     int i=10;
    //     do
    //     {
    //         x = rand() % 4;
    //         printf("\n-------------------------------------R2\n");
    //         if((player3.pieceDeatail[x][2]==BASE || player3.pieceDeatail[x][8] != -1))
    //         {
    //             return x;
    //         }
    //     } while(player3.started<0);//;
    // }
    // return -1;
}


int greenPlayPiece()
{
    for(int i=0;i<4;i++)
    {
        if (player4.pieceDeatail[greenorder%4][2] != BASE &&
                player4.pieceDeatail[greenorder%4][8] == -1)
        {
            return greenorder%4;
        }
        greenorder = greenorder+1;
    }
    return -1;
    // int x;
    // printf("\n-------------------------------------G1\n");
    // if(player4.started == 1)
    // {
    //     printf("\n-------------------------------------G2\n");
    //     for(int i=0;i<4;i++)
    //     {
    //         if(player4.pieceDeatail[i][2] != BASE && player4.pieceDeatail[i][8] < 0)
    //         {
    //             printf("\n-------------------------------------G3-1 - %d\n",i);
    //             return i;
    //         }
    //     }
    //     return -1;
    // }
    // else
    // {
    //     int i=10;
    //     do
    //     {
    //         x = rand() % 4;
    //         printf("\n-------------------------------------G4-2 - %d\n",x);
    //         if((player4.pieceDeatail[x][2] == BASE || player4.pieceDeatail[x][8] != -1))
    //         {
    //             return x;
    //         }
    //     } while(i--);
    //     return -1;
    // }
}


bool passApporoach(player *player, int playpiece, int roll)
{
    if(player->playernum == 0)
    {
        if (player->pieceDeatail[playpiece][4] == 1)
        {
            //works all but not to yellow
            if (player->pieceDeatail[playpiece][2] < 52 &&
                player->pieceDeatail[playpiece][2] + roll >= 52)
            {
                return true;;
            }
            else
            {
                return false;
            }
        }
        else if(player->pieceDeatail[playpiece][4] == -1)
        {
            if (player->pieceDeatail[playpiece][2] > 0 &&
                player->pieceDeatail[playpiece][2] - roll <= 0)
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
    else
    {
        if (player->pieceDeatail[playpiece][4] == 1)
        {
            //works all but not to yellow
            if (player->pieceDeatail[playpiece][2] < player->o &&
                player->pieceDeatail[playpiece][2] + roll >= player->o)
            {
                return true;;
            }
            else
            {
                return false;
            }
        }
        else if(player->pieceDeatail[playpiece][4] == -1)
        {
            if (player->pieceDeatail[playpiece][2] > player->o &&
                player->pieceDeatail[playpiece][2] + roll <= player->o)
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
    
}


void homeMove(player *player, int playpiece, int roll)
{
    //indicater for he is in home path
    if(player->pieceDeatail[playpiece][8] == -1)
    {
        //in O position
        player->pieceDeatail[playpiece][8] = 0;
        //player->pieceDeatail[playpiece][2] = FINISH;
        int togo = 0;

        if(player->playernum == YELLOW)
        {
            if(player->pieceDeatail[playpiece][4] == 1)
            {
                togo = roll - (52 - player->pieceDeatail[playpiece][2]);
                player->pieceDeatail[playpiece][8] = player->pieceDeatail[playpiece][8]+togo;
            }
            else if(player->pieceDeatail[playpiece][4] == -1)
            {
                togo = roll - player->pieceDeatail[playpiece][2];
                player->pieceDeatail[playpiece][8] = player->pieceDeatail[playpiece][8]+togo;
            }
        }
        else
        {
            if(player->pieceDeatail[playpiece][4] == 1)
            {
                togo = roll - (player->o - player->pieceDeatail[playpiece][2]);
                player->pieceDeatail[playpiece][8] = player->pieceDeatail[playpiece][8]+togo;
            }
            else if(player->pieceDeatail[playpiece][4] == -1)
            {
                togo = roll - ((player->pieceDeatail[playpiece][2] - player->o));
                player->pieceDeatail[playpiece][8] = player->pieceDeatail[playpiece][8]+togo;
            }
        }
        
    }
    else if(player->pieceDeatail[playpiece][8]+roll <=6)
    {
        if(player->pieceDeatail[playpiece][8]+roll < 6)
        {
            player->pieceDeatail[playpiece][8] = player->pieceDeatail[playpiece][8]+roll;
        }
        else if(player->pieceDeatail[playpiece][8]+roll == 6)
        {
            player->pieceDeatail[playpiece][8] = player->pieceDeatail[playpiece][8]+roll;
            printf("%s %c%d====================Piece Wins\n",player->color,player->colorfirst,playpiece+1);
            player->pieceDeatail[playpiece][2] = FINISH;
            player->pieceDeatail[playpiece][3] = FINISH;
            player->pieceDeatail[playpiece][8] = FINISH;
            player->finished = player->finished +1;
            player->started = player->started-1;
            endpieces++;
                                                                                                                                                                                                                                                                          
            if (player->finished==4)
            {
                printf("%s %c%d====================Player Wins the game\n",
                    player->color,player->colorfirst,
                    playpiece+1);
            }  
        }
        else
        {
            printf("Can not move must roll %d\n",6 - player->pieceDeatail[playpiece][8]);
        }
    } 
}
