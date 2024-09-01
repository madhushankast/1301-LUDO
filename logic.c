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
int piecey1[PIECEDATA] = {YELLOW, PIECE1, BASE, 0, 0, 1, 0,0 ,- 1};
int piecey2[PIECEDATA] = {YELLOW, PIECE2, BASE, 0, 0, 1, 0,0 , -1};
int piecey3[PIECEDATA] = {YELLOW, PIECE3, BASE, 0, 0, 1, 0,0 , -1};
int piecey4[PIECEDATA] = {YELLOW, PIECE4, BASE, 0, 0, 1, 0,0 , -1};

// blue pieces
int pieceb1[PIECEDATA] = {BLUE, PIECE1, BASE, 0, 0, 1, 0,0 , -1};
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
// 0 - capturer color 1 - piece 2 - captured color 3 - captured piece 4 - location
int captureData[5];
int mistrycell;
int finishedPlay = 1;

int blueOrder   = 0;
int redorder    = 0;
int greenorder  = 0;


// output the begining statmenet and player order
int LUDO()
{
    // seed rand function
    srand(time(0));

    // begining CLI for game
    printbegin();

    // selecting starter by higherst dice value
    int startPlayer;
    startPlayer = firstHand();

    // passing starting player
    gameplay(startPlayer);

    // printing finished order
    for(int i=0;i<4;i++)
    {
        if(arrayplayerlist[i]->finished == 4)
        {
            printf("%s Finished game %d place\n",
                arrayplayerlist[i]->color,
                arrayplayerlist[i]->playerIndex);     //playerIndex stores the finished place
        }
        if(arrayplayerlist[i]->finished != 4)
        {
            printf("%s Finished game 4 place\n",
                arrayplayerlist[i]->color);
        }
    }
    
    printf("Game Ended\n");
    return 1;
}

// the starting statement
void printbegin()
{
    printf("The\tYellow\tplayer has four (04) pieces named Y1,Y2,Y3 and Y4\n");
    printf("The\tBlue\tplayer has four (04) pieces named B1,B2,B3 and B4\n");
    printf("The\tRed\tplayer has four (04) pieces named R1,R2,R3 and R4\n");
    printf("The\tGreen\tplayer has four (04) pieces named G1,G2,G3 and G4\n");
}

// rolling dice to output 1 - 6 values
int roll()
{
    int x = (rand() % 6);
    if (x == 0)
    {
        x = 6; // make 6 if mod of roll = 0; 
    }
    return x;
}

// output player and rolled value
int firstroll(int i)
{
    int x = roll();
    printf("The \t%s \tplayer rolls \t%d\n", arrayplayerlist[i]->color, x);
    return x;
}


// finding highest rolled value and player
int firstHand()
{
    int firstHandValue[4];          
    for (int i = 0; i < 4; i++)
    {
        int x = firstroll(i);
        firstHandValue[i] = x;      //store dice value rolled by each player
    }

    int sortplayer[4];              //player array
    for (int i = 0; i < 4; i++)
    {
        sortplayer[i] = i;
    }

    //sorting the firstHandValue array
    //following the lead of that auto sort sortplayer array
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

        //print dice rolled value order by highest to lowest 
        printf("%s player has the highest roll and will begin the game\n",
        players[*(sortplayer + 3)]);
        printf("The rolled dise value order is %s, %s, %s, and %s\n",
            players[*(sortplayer + 3)],
            players[*(sortplayer + 2)],
            players[*(sortplayer + 1)],
            players[*(sortplayer)]);

    //return highest rolled player
    return sortplayer[3];
}

//main game loop runs
void gameplay(int starter)
{
    // creating an new array to keep order and for looping
    int play[4];
    for (int i = 0; i < 4; i++)
    {
        starter = starter % 4;
        play[i] = starter;
        starter++;
    }

    printf("Round goes to left hand side and order is %s -> %s -> %s -> %s\n",
           arrayplayerlist[play[0]]->color,
           arrayplayerlist[play[1]]->color,
           arrayplayerlist[play[2]]->color,
           arrayplayerlist[play[3]]->color);
    printf("\n");

    int round = 1;              //round start here
    while (finishedPlay < 2 )   //loop until 3 players finish the game
    {
        printf("This is round ----> %d\n", round++);

        // repeating the players order
        for (int i = 0; i < 4; i++)
        {
            //calling the player according to the order in play[] array that keeps the order
            switch (play[i])
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
        printf("\n");

        //if round greater than 2 and after each four round mistry cell get updates
        if(round>2)
        {
            if (round % 4 == 0)
            {
                int mistryIs;                   //local variable to check a cell can be a mistry cell
                do
                {
                    mistryIs = rand() % 52;
                    if(canBeMistry(mistryIs))   //check the generated mistry cell satisfy the requierments
                    {
                        break;
                    }
                } while (0); 
                mistrycell = mistryIs;
            }

            printf("The mystery cell is at L%d and will be at that location for the next %d values\n",
                        mistrycell,
                        4-(round%4));   //for next round count
        }

                
        //printing function for status in each round
        printRound();
    };
}

//yellow specific behavior
void yellowMove()
{
    //return if player pieces all have Reached Home
    if(player1.finished == 4)
    {
        printf("%s Finished game\n",arrayplayerlist[0]->color);
        return;
    }

    while(1)
    {
        int diceValue = roll();                 //get dice value by roll
        printf("Yellow player rolled %d\n", diceValue);

        if (diceValue == 6)
        {
            if (player1.inBase > -1 )           //if any pieces in base get to start location
            {
                baseToStart(arrayplayerlist[0]);
            }
            else if (yellowcatch(diceValue))    //check for catch and take it
            {
                capturedOutput();
                printf("Yellow Captures a piece, Yellow Gets another Roll\n");
                continue;
            }
            else                                //(player1.started > 0)
            {
                standardMove(&player1, diceValue);
            }
        }
        else
        {
            if (player1.started == 0)           //no playing pieces in board
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n", player1.color, diceValue);
                return;
            }
            else                                //started pieces in board        
            {
                if (yellowcatch(diceValue))     //check can take a catch
                {
                    capturedOutput();
                    printf("Capture Player Gets another Roll\n");
                    continue;
                }
                else                            //make a general move to a piece
                {
                    standardMove(&player1, diceValue);
                }
            }
        }

        //after all moves check is there any piece that has captured if so another roll given
        if (canCaptureAny(0))
        {
            capturedOutput();
            printf("Yellow Captures a piece, Yellow Gets another Roll\n");
            continue;
        }

        // avoid block catrector

        //checking has player rolled value 6 for three consecutive times
        if (diceValue == 6 && player1.sixrolled < 2)
        {
            player1.sixrolled++;
            {
                printf("Rolled 6 so player gets another roll\n");
                continue;
            }
        }
        else //if so dice roll will cancel and dice passes to the next player
        {
            player1.sixrolled = 0;
            break;
        }
    };
}

//blue specific behavior
void blueMove()
{
    //return if player pieces all have Reached Home
    if(player2.finished == 4)
    {
        printf("%s Finished game\n",arrayplayerlist[1]->color);
        return;
    }

    while (1)
    {
        int diceValue = roll();                         //get dice value by roll
        printf("Blue player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player2.inBase > -1)                    //if any pieces in base get it to start location
            {
                baseToStart(&player2);
            }
            else                                        //if pieces in board make a general move
            {
                standardMove(&player2, diceValue);
            }
        }
        else //did not rolled dice six
        {
            if (player2.started > 0)                    //players in board make general move
            {
                standardMove(&player2, diceValue);
            }
            else                                        //give error massege that no pieces in board to move
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n", player2.color, diceValue);
            }
        }

        //after all moves check is there any piece that has captured if so another roll given
        if (canCaptureAny(1))
        {
            capturedOutput();
            printf("Blue Captures a piece, Blue Gets another Roll\n");
            continue;
        }

        //checking has player rolled value 6 for three consecutive times
        if (diceValue == 6 && player2.sixrolled < 2)
        {
            player2.sixrolled++;
            {
                printf("Rolled 6 so player gets another roll\n");
                continue;
            }
        }
        else //dice roll will cancel and dice passes to the next player
        {
            player2.sixrolled = 0;
            break;
        }
    };
}

//red specific behavior
void redMove()
{
    //return if player pieces all have Reached Home
    if(player3.finished == 4)
    {
        printf("%s Finished game\n",arrayplayerlist[2]->color);
        return;
    }

    while (1)
    {
        int diceValue = roll();                     //get dice value by roll
        printf("RED player rolled %d\n", diceValue);
        // redplayer(x);

        if (diceValue == 6)
        {
            if (player3.inBase == 4)                //If all pieces in base take stating position
            {
                baseToStart(&player3);
            }
            else if (redcatch(diceValue))           //can take a capture if so get
            {
                capturedOutput();
                printf("Capture Player Gets another Roll\n");
                continue;
            }
            else if (player3.inBase > -1)           //if cannot capture take piece to start           
            {
                baseToStart(&player3);
            }
            else                                    //if pieces in board make a general move
            {
                standardMove(&player3, diceValue); 
            }
        }
        else    //did not rolled dice 6
        {
            if (player3.started > 0)                //if pieces in board actively playing
            {
                if (redcatch(diceValue))
                {
                    capturedOutput();
                    continue;
                }
                else                                //if pieces in board make a general move
                {
                    standardMove(&player3, diceValue);
                }
            }
            else //if no piece has started
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                       player3.color, diceValue);
            }
        }

        //after all moves check is there any piece that has captured if so another roll given
        if (canCaptureAny(2))
        {
            capturedOutput();
            printf("Red Captures a piece, Red Gets another Roll\n");
            continue;
        }
        
        //checking has player rolled value 6 for three consecutive times
        if (diceValue == 6 && player3.sixrolled < 2)
        {
            player3.sixrolled++;
            {
                printf("Rolled 6 so player gets another roll\n");
                continue;
            }
        }
        else //dice roll will cancel and dice passes to the next player
        {
            player3.sixrolled = 0;
            break;
        }
    };
}

//green specific behavior
void greenMove()
{
    //return if player pieces all have Reached Home
    if(player4.finished == 4)
    {
        printf("%s Finished game\n",arrayplayerlist[3]->color);
        return;
    }
    
    while(1)
    {
        int diceValue = roll();                             //get dice value by roll
        printf("Green player rolled %d\n", diceValue);
        if (diceValue == 6)
        {
            if (player4.inBase > -1)                        //if all pieces at base take one to start position
            {
                baseToStart(&player4);
            }
            else if (greencatch(diceValue))                 //check can make a capture
            {
                capturedOutput();
                //continue;
            }
            else
            {
                standardMove(&player4, diceValue);          //general move in standard path
            }
        }
        else
        {
            if (player4.started > 0)
            {
                standardMove(&player4, diceValue);          //if acrive pieces in board make general move
            }
            else    //player have not any activer pices at standard path
            {
                printf("%s must roll 6 to move pieces to X but player rolled %d\n",
                       player4.color, diceValue);
            }
        }

        //after all moves check is there any piece that has captured if so another roll given
        if (canCaptureAny(3))
        {
            capturedOutput();
            printf("Green Captures a piece, Green Gets another Roll\n");
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

//CLO for each round
void printRound()
{
    for (int j = 0; j < 4; j++)
    {
        printf("\n");
        printf("%s player now has\n%d/4 on pieces on the board | %d/4 pieces on the base | %d/4 Finished\n",
               arrayplayerlist[j]->color,       //Player by colour
               arrayplayerlist[j]->started,     //started count
               arrayplayerlist[j]->inBase,      //In base count
               arrayplayerlist[j]->finished);   //Finished Count
        printf("=====================================================================================\n");
        printf("Locations of pieces of %s player\n", arrayplayerlist[j]->color);
        printf("=====================================================================================\n");
        for (int i = 0; i < 4; i++)
        {
            if (arrayplayerlist[j]->pieceData[i][2] == BASE)
            {
                printf("%c%d -> Base\tcaptured - %d\tTravelled - %d\tDirection - %d\tHome L=%d\n",
                arrayplayerlist[j]->colorfirst,
                arrayplayerlist[j]->pieceData[i][1]+1,
                arrayplayerlist[j]->pieceData[i][3],
                arrayplayerlist[j]->pieceData[i][7],
                arrayplayerlist[j]->pieceData[i][4],
                arrayplayerlist[j]->pieceData[i][8]);
            }
            else if(arrayplayerlist[j]->pieceData[i][8] >= 6)
            {
                printf("%c%d -> Home\tcaptured - %d\tTravelled - %d\tDirection - %d\tHome L= %d\n",
                arrayplayerlist[j]->colorfirst,
                arrayplayerlist[j]->pieceData[i][1]+1,
                arrayplayerlist[j]->pieceData[i][3],
                arrayplayerlist[j]->pieceData[i][7],
                arrayplayerlist[j]->pieceData[i][4],
                arrayplayerlist[j]->pieceData[i][8]);

            }
            else
            {
                printf("%c%d is at L%d\tcaptured - %d\tTravelled - %d\tDirection - %d\tHome L= %d\n",
                arrayplayerlist[j]->colorfirst,
                arrayplayerlist[j]->pieceData[i][1]+1,
                arrayplayerlist[j]->pieceData[i][2],
                arrayplayerlist[j]->pieceData[i][3],
                arrayplayerlist[j]->pieceData[i][7],
                arrayplayerlist[j]->pieceData[i][4],
                arrayplayerlist[j]->pieceData[i][8]);
            }
        }
        printf("\n");
    }
}

//Selecting the piece for the move
int selectPlayPiece(player *player, int diceValue)
{
    int playpiece;
    switch (player->playerIndex)  //give the player number Y-0,B-1,R-2,G-3
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

//Bringing pices to satrting position
void baseToStart(player *player)
{
    for (int i = 0; i < 4; i++)
    {
        if (player->pieceData[i][2] == BASE  && player->pieceData[i][8] != FINISH)
        {
            printf("%s player moves piece %c%d to the starting point\n",
            player->color,
            player->colorfirst,
            i + 1);
                    
            player->started += 1;                   //increment board piece count
            player->inBase -= 1;                    //decrement base piece count
            player->pieceData[i][2] = player->x; //piece position to start position
            player->pieceData[i][4] = coinToss();//deciding the direction of the piece move

            printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base\n",
                        player->color,
                        player->started,            //In board piece count
                        player->inBase);            //In base piece count
            return;
        }
    }
}

//standard path move for every player
int standardMove(player *player, int roll)
{
    //iterate throuh pieces to find is there any pieces in Home path or going apporoch homepath
    for(int i=0;i<4;i++) 
    {
        if( player->pieceData[i][8] == -1    &&           //currently in standard path
            passApporoach(player, i, roll)   &&           //can enter to the hoempath
            player->pieceData[i][7] > 2      &&           //must travelled more than two sells
            player->pieceData[i][3] > 0 )                 //captured ate least one opponent piece
        {
            homeMove(player, i, roll);
            return 0;
        }
        else if(player->pieceData[i][8] > -1 &&            //currently in homepath
                player->pieceData[i][8] + roll <= 6)         //can move forwad in homepath
        {
            homeMove(player, i, roll);
            return 0;
        }
    }

    int playpiece = selectPlayPiece(player, roll);
    //if can not move any pieces under given conditions dice pass to next player without making move
    if(playpiece == -1)     
    {
        return 0;
    }
    
    if(player->pieceData[playpiece][8] == -1)        //player in the standard path
    {
        // Bhawana impact & kotuwa impact
        if (player->pieceData[playpiece][5] != 1 )
        {
            //pieceData[playpiece][5] hold the multiply value
            //Bhawana enegize   2*roll      doubles
            //Bhawana sick      0.5*roll    half
            //Kotuwa            0*roll      can not move
            roll = player->pieceData[playpiece][5] * roll;
            player->pieceData[playpiece][6]--;              //Counter for four rounds

            if(player->pieceData[playpiece][5]==0)
            {
                //rolled consecutive three times
            }

            if(player->pieceData[playpiece][6]==0)
            {
                player->pieceData[playpiece][5] = 1;
            }
        }
        //selected play piece move clockwise
        if (player->pieceData[playpiece][4] == 1)
        {
            printf("%s moves %c%d from location L%d ",
                player->color,                          //Player by Color
                player->colorfirst,                     //Letter for Piece identity
                playpiece+1,                            //moving piece
                player->pieceData[playpiece][2]);       //location before move

            player->pieceData[playpiece][2] = (player->pieceData[playpiece][2] + roll) % 52;

            printf("to L%d by units %d clockwise direction\n",
                        player->pieceData[playpiece][2],//location after move
                        roll);                          //Dice value

            player->pieceData[playpiece][7] += roll;
            // captured(player, randomplaypiece);
        }
        //selected playpiece move Counter-clockwise
        else if (player->pieceData[playpiece][4] == -1)
        {
            printf("%s\tmoves %c%d from location\tL%d",
                player->color,                          //Player by Color
                player->colorfirst,                     //Letter for Piece identity
                playpiece,                              //moving piece
                player->pieceData[playpiece][2]);       //location before move

            player->pieceData[playpiece][2] -= roll;

            //if piece location less than zero that means it jumped over 0
            if (player->pieceData[playpiece][2] <= 0)
            {
                player->pieceData[playpiece][2] += 51;
            }

            printf("to L%d by units\t%d Counter-clockwise direction\n",
                    player->pieceData[playpiece][2],    //location after move
                    roll);                              //Dice value

            //increment the travelled distance by dice value
            player->pieceData[playpiece][7] += roll;
        }

        //after every move check it landed on a mistry cell or not
        if (player->pieceData[playpiece][2] == mistrycell)
        {
            mistryTeleport(player, playpiece);
        }

        return 0;
    }
    
}

//To get direction randomly
int coinToss()
{
    int x = (rand() % 2);       //Generate 0 and 1 randomly
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

//Output and Re initialize data after caputure has been made
int capturedOutput()
{
    // 0 - capturer , 1 - Capturer piece , 2 - captured , 3 - Captured piece, 4- location
    printf("%s Player %c%d lands on square L%d,captures %s Player %c%d, and returns it to the base\n",
           arrayplayerlist[captureData[0]]->color,                              //Captured by
           arrayplayerlist[captureData[0]]->colorfirst,                         //Piece
           arrayplayerlist[captureData[0]]->pieceData[captureData[1]][1] + 1,   //Piece Number
           captureData[4],                                                      //Location
           arrayplayerlist[captureData[2]]->color,                              //captured
           arrayplayerlist[captureData[2]]->colorfirst,                         //piece
           arrayplayerlist[captureData[2]]->pieceData[captureData[3]][1] + 1);  //Piece number

    //increment captured value of capturer
    arrayplayerlist[captureData[0]]->pieceData[captureData[1]][3]++;
    //decremrnting captured pieces started count and increment agian inBase count
    arrayplayerlist[captureData[2]]->inBase  += 1;
    arrayplayerlist[captureData[2]]->started -= 1;
    //captured pieces position to BASE
    arrayplayerlist[captureData[2]]->pieceData[captureData[3]][2] = BASE;
    //captured pieces travelled value to zero
    arrayplayerlist[captureData[2]]->pieceData[captureData[3]][7] = 0;
    //captured pieces captured count to zero
    arrayplayerlist[captureData[2]]->pieceData[captureData[3]][3] = 0;
    arrayplayerlist[captureData[2]]->pieceData[captureData[3]][8] = -1;


    printf("%s player now has %d/4 on pieces on the board and %d/4 pieces on the base\n",
           arrayplayerlist[captureData[2]]->color,
           arrayplayerlist[captureData[2]]->started,
           arrayplayerlist[captureData[2]]->inBase);

    captureData[0] = 0;
    captureData[1] = 0;
    captureData[2] = 0;
    captureData[3] = 0;
    captureData[4] = 0;
}

//after every move check for any captures
bool canCaptureAny(int player)
{
    // check any captured happende after a every move piece has made
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                if ( arrayplayerlist[player] != arrayplayerlist[j]   &&   // remove comparing same players pieces
                     arrayplayerlist[player]->pieceData[i][2] != YX  &&   // can not catch at starting position
                     arrayplayerlist[player]->pieceData[i][2] != BX  &&
                     arrayplayerlist[player]->pieceData[i][2] != RX  &&
                     arrayplayerlist[player]->pieceData[i][2] != GX  &&
                    arrayplayerlist[player]->pieceData[i][8] == -1   &&   //check if it in the Standardpath
                    arrayplayerlist[player]->pieceData[i][2] != BASE &&   // removing in base pieces
                    // if in the same block capture 
                    arrayplayerlist[player]->pieceData[i][2] == arrayplayerlist[j]->pieceData[k][2])
                {
                    captureData[0] = player;                                //capturer
                    captureData[1] = i;                                     //piece of capturer
                    captureData[2] = j;                                     //captured
                    captureData[3] = k;                                     //piece of captured
                    captureData[4] = arrayplayerlist[j]->pieceData[k][2];   //location

                    return true;
                }
            }
        }
    }
    return false;
}

//creating blocks
int createBlocks(player *player, int randomplaypiece)
{
    int blocksize = 0;
    for (int i = 0; i < 4; i++)
    {
        if (((player->pieceData[randomplaypiece][2]) || (player->pieceData[i][2])) != BASE &&
            player->pieceData[randomplaypiece][2] == player->pieceData[i][2])
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

//condioned to be satisfy to create blocks
int canCreateBlock(player *player)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (((player->pieceData[i][2]) || (player->pieceData[j][2])) != BASE &&
                player->pieceData[i][2] == player->pieceData[j][2])
            {
                return 1;
            }
        }
    }
    return 0;
}

//Mistry teleport cases
void mistryTeleport(player *player, int playpiece)

{
    switch (rand() % 6)     //generate random value to decide the switch case
    {  
    case 0:     printf("%s piece %c%d teleported to Bhawana - Cell -> %d.\n",
                        player->color,      //player
                        player->colorfirst, //Color
                        playpiece+1,        //piece Number
                        BHAWANA);           //location

                player->pieceData[playpiece][2] = BHAWANA;
                player->pieceData[playpiece][6] = FOURROUND;
                if (rand() % 2 == 0)        //deciding randomly gets enrgize or sick
                {
                    player->pieceData[playpiece][5] = ENERGIZE;     //[5] = 2
                    printf("%s piece %c%d feels energized, and movement speed doubles.\n",
                        player->color,player->colorfirst,playpiece+1);
                }
                else
                {
                    player->pieceData[playpiece][5] = SICK;         //[5] = 0.5
                    printf("%s piece %c%d feels sick, and movement speed halves.\n",
                        player->color,player->colorfirst,playpiece+1);
                }
                break;

    case 1:     printf("%s piece %c%d teleported to Kotuwa - Cell -> %d.\n",
                        player->color,player->colorfirst,playpiece+1,KOTUWA);
                player->pieceData[playpiece][2] = KOTUWA;
                player->pieceData[playpiece][6] = FOURROUND;
                player->pieceData[playpiece][5] = FREEZE;           //[5] = 0
                printf("%s piece %c%d attends briefing and cannot move for four rounds.\n",
                        player->color,player->colorfirst,playpiece+1);
                break;

    case 2:     printf("%s piece %c%d teleported to Pita-Kotuwa -> Cell - %d.\n",
                        player->color,player->colorfirst,playpiece+1,PITAKOTUWA);

                if (player->pieceData[playpiece][4] == 1)
                {
                    player->pieceData[playpiece][4] = -1;
                    printf("The %s piece %c%d which was moving clockwise, has changed to moving coun-terclockwise.\n",
                        player->color,player->colorfirst,playpiece+1);
                }
                else
                {
                    printf("%s piece %c%d teleported to Kotuwa - Cell -> %d.\n",
                        player->color,player->colorfirst,playpiece+1,KOTUWA);

                    player->pieceData[playpiece][2] = KOTUWA;
                    player->pieceData[playpiece][6] = FOURROUND;
                    player->pieceData[playpiece][5] = FREEZE;

                    printf("The %s piece %c%d  is moving in a counterclockwise direction. mistryTeleporting to Kotuwa from Pita-Kotuwa.\n",
                        player->color,player->colorfirst,playpiece+1);
                }
                break;

    case 3:     printf("%s piece %c%d teleported to Base - Cell -> %d.\n",
                        player->color,player->colorfirst,playpiece+1,BASE);
                player->pieceData[playpiece][2] = BASE;
                player->inBase++;
                player->started--;
                break;

    
    case 4:     printf("%s piece %c%d teleported to X - Cell -> %d.\n",
                        player->color,player->colorfirst,playpiece+1,player->x);
                player->pieceData[playpiece][2] = player->x;
                break;

    
    case 5:     printf("%s piece %c%d teleported to O - Cell -> %d.\n",
                        player->color,player->colorfirst,playpiece+1,player->o);
                player->pieceData[playpiece][2] = player->o;
                break;
    }
}

//check randomized location can be a mistry cell
bool canBeMistry(int mistryis)
{
    if (isPiecelocated(mistryis))
    {
        return false;   //mistry can not spawned on a cell that already has piece in it
    }
    else if (mistrycell == mistryis)
    {
        return false;   //mistry can not spawned in same cell for twise
    }
    else
    {
        return true;
    }
}

//iterate through pieces and check mistry cell is on a cell that already has a piece
bool isPiecelocated(int mistryis)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(arrayplayerlist[i]->pieceData[j][2] == mistryis)
            {
                return true;
            }
        }
    }
    return false;
}

//red specific capture behavior
int redcatch(int diceValue)
{
    //catch the closest piece to its own apporoach cell
    int mintoHome = 52;
    for (int i = 0; i < 4; i++)
    {
        if (player3.pieceData[i][2] != BASE &&              // removing in base pieces
            player3.pieceData[i][8] == -1   &&              // remove homepath players 
            player3.pieceData[i][2]+ diceValue != YX    &&  // can not catch at starting position
            player3.pieceData[i][2]+ diceValue != BX    &&
            player3.pieceData[i][2]+ diceValue != RX    &&
            player3.pieceData[i][2]+ diceValue != GX    )
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arrayplayerlist[2] != arrayplayerlist[j]    &&  // remove comparing same players pieces
                        arrayplayerlist[j]->pieceData[k][8] == -1   &&  //remove homepath players 
                        player3.pieceData[i][2] + diceValue == arrayplayerlist[j]->pieceData[k][2])
                    {
                        if ((arrayplayerlist[j]->o - arrayplayerlist[j]->pieceData[k][2]) < mintoHome)
                        {
                            mintoHome = (arrayplayerlist[j]->o - arrayplayerlist[j]->pieceData[k][2]);
                            // 0 - capturer , 1 - Capturer piece , 2 - captured , 3 - Captured piece, 4- location
                            captureData[0] = 2;
                            captureData[1] = i;
                            captureData[2] = j;
                            captureData[3] = k;
                            captureData[4] = arrayplayerlist[j]->pieceData[k][2];

                            if (i == 4 && j == 4 && k == 4)
                            {
                                player3.pieceData[captureData[1]][2] += diceValue;
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

//yellow specific capture behavior
bool yellowcatch(int diceValue)
{
    for (int i = 0; i < 4; i++)
    {
        if (player1.pieceData[i][2] != BASE          &&     // removing in base pieces
            player1.pieceData[i][8] == -1            &&     //remove homepath players    
            player1.pieceData[i][3] ==  0            &&     //has not captured any pices before
            player1.pieceData[i][2]+ diceValue != YX &&     // can not catch at starting position
            player1.pieceData[i][2]+ diceValue != BX &&
            player1.pieceData[i][2]+ diceValue != RX &&
            player1.pieceData[i][2]+ diceValue != GX    )
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arrayplayerlist[0] != arrayplayerlist[j]    &&  //not comparing same player
                        arrayplayerlist[j]->pieceData[k][8] == -1   &&  //homepath player
                        player1.pieceData[i][2] + diceValue == arrayplayerlist[j]->pieceData[k][2])
                    {
                        player1.pieceData[i][2] += diceValue;
                        // 0 - capturer , 1 - Capturer piece , 2 - captured , 3 - Captured piece, 4- location
                        captureData[0] = 0;
                        captureData[1] = i;
                        captureData[2] = j;
                        captureData[3] = k;
                        captureData[4] = arrayplayerlist[j]->pieceData[k][2];

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//green specific capture behavior
bool greencatch(int diceValue)
{
    for (int i = 0; i < 4; i++)
    {
        if (player4.pieceData[i][2] != BASE &&  
            player4.pieceData[i][8] == -1   &&
            player4.pieceData[i][3] ==  0   &&
            player4.pieceData[i][2]+ diceValue != YX &&
            player4.pieceData[i][2]+ diceValue != BX &&
            player4.pieceData[i][2]+ diceValue != RX &&
            player4.pieceData[i][2]+ diceValue != GX    )
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (arrayplayerlist[0] != arrayplayerlist[j] &&
                        arrayplayerlist[j]->pieceData[k][8] == 0 &&
                        player4.pieceData[i][2]+ diceValue == arrayplayerlist[j]->pieceData[k][2])
                    {
                        player4.pieceData[i][2] +=diceValue;
                        // 0 - capturer , 1 - Capturer piece , 2 - captured , 3 - Captured piece, 4- location
                        captureData[0] = 0;
                        captureData[1] = i;
                        captureData[2] = j;
                        captureData[3] = k;
                        captureData[4] = arrayplayerlist[j]->pieceData[k][2];

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//yellow specific piece decide behavior
int yellowPlayPiece(int diceValue)
{
    int unitsToHome = 54;
    int minUnits    = 54;
    int yellowpiece = -1;
    //iterate throuh all yellow pieces and find the minum distanced valued piece
    for (int i = 0; i < 4; i++)
    {
        if (player1.pieceData[i][2] != BASE &&  player1.pieceData[i][8] == -1)
        {
            if (player1.pieceData[i][4] == 1)           //for clockwise pieces
            {
                unitsToHome = 52 - player1.pieceData[i][2];
                if (unitsToHome < minUnits)
                {
                    minUnits = unitsToHome;
                    yellowpiece = i;
                }
            }
            else if (player1.pieceData[i][4] == -1)     //for counter clockwise pieces
            {
                if (player1.pieceData[i][2] <= 2 && player1.pieceData[i][7]<=2)       //just started pieces
                {
                    unitsToHome = 51 + player1.pieceData[i][2];
                    if (unitsToHome < minUnits)
                    {
                        minUnits = unitsToHome;
                        yellowpiece = i;
                    }
                }
                else
                {
                    unitsToHome = player1.pieceData[i][2];
                    if (unitsToHome < minUnits)
                    {
                        minUnits = unitsToHome;
                        yellowpiece = i;
                    }
                }
            }
        }
    }
    return yellowpiece;
}

//blue specific piece decide behavior
int bluePlayPiece(int diceValue)
{
    for(int i=0;i<4;i++)
    {
        if (player2.pieceData[blueOrder%4][2] != BASE &&
                player2.pieceData[blueOrder%4][8] == -1)
        {
            return blueOrder%4;
        }
        blueOrder = blueOrder+1;
    }
    return -1;
}

//red specific piece decide behavior
int redPlayPiece()
{
    for(int i=0;i<4;i++)
    {
        if (player3.pieceData[i][2] != BASE &&
                player3.pieceData[i][8] == -1)
        {
            return i;
        }
    }
    return -1;
}

//green specific piece decide behavior
int greenPlayPiece()
{
    for(int i=0;i<4;i++)
    {
        if (player4.pieceData[i][2] != BASE &&
                player4.pieceData[i][8] == -1)
        {
            return i;
        }
    }
    return -1;
}

//check when piece is moving whther it passes the approach
bool passApporoach(player *player, int playpiece, int roll)
{
    if(player->playerIndex == 0)        //special conditions for yellow player
    {
        if (player->pieceData[playpiece][4] == 1)
        {
            //yellow approch in 0 th cell
            if (player->pieceData[playpiece][2] < 52 &&         //current position less 52
                player->pieceData[playpiece][2] + roll >= 52)   //after position greater 52
            {
                return true;;
            }
            else
            {
                return false;
            }
        }
        else if(player->pieceData[playpiece][4] == -1)
        {
            if (player->pieceData[playpiece][2] > 0 &&          //current position greater 0
                player->pieceData[playpiece][2] - roll <= 0)    //after position less 0
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
    else //for all otherplayers
    {
        if (player->pieceData[playpiece][4] == 1)
        {
            //before move - position less than apporoach
            //after move  - position greater than appraoch
            if (player->pieceData[playpiece][2] < player->o &&
                player->pieceData[playpiece][2] + roll >= player->o)
            {
                return true;;
            }
            else
            {
                return false;
            }
        }
        else if(player->pieceData[playpiece][4] == -1)
        {
            //before move - position greater than apporoach
            //after move  - position less than approaach
            if (player->pieceData[playpiece][2] > player->o &&
                player->pieceData[playpiece][2] + roll <= player->o)
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

//Home path movement
void homeMove(player *player, int playpiece, int roll)
{
    //indicater for he is in home path
    if(player->pieceData[playpiece][8] == -1)
    {
        //in O position
        player->pieceData[playpiece][8] = 0;
        //player->pieceData[playpiece][2] = FINISH;
        int togo = 0;

        if(player->playerIndex == YELLOW)       //specified for yellow move
        {
            if(player->pieceData[playpiece][4] == 1)
            {
                togo = roll - (52 - player->pieceData[playpiece][2]);
                player->pieceData[playpiece][8] = player->pieceData[playpiece][8]+togo;
            }
            else if(player->pieceData[playpiece][4] == -1)
            {
                togo = roll - player->pieceData[playpiece][2];
                player->pieceData[playpiece][8] = player->pieceData[playpiece][8]+togo;
            }
        }
        else                                    //all other players move
        {
            if(player->pieceData[playpiece][4] == 1)
            {
                togo = roll - (player->o - player->pieceData[playpiece][2]);
                player->pieceData[playpiece][8] = player->pieceData[playpiece][8]+togo;
            }
            else if(player->pieceData[playpiece][4] == -1)
            {
                togo = roll - ((player->pieceData[playpiece][2] - player->o));
                player->pieceData[playpiece][8] = player->pieceData[playpiece][8]+togo;
            }
        }
    }
    //roll value must equal to home path next cell count
    else if(player->pieceData[playpiece][8]+roll <=6)
    {
        if(player->pieceData[playpiece][8]+roll < 6)
        {
            player->pieceData[playpiece][8] = player->pieceData[playpiece][8]+roll;
        }
        else if(player->pieceData[playpiece][8]+roll == 6)
        {
            player->pieceData[playpiece][8] = player->pieceData[playpiece][8]+roll;
            printf("%s %c%d Piece Wins\n",player->color,player->colorfirst,playpiece+1);
            player->pieceData[playpiece][2] = FINISH;
            //player->pieceData[playpiece][3] = FINISH;
            player->pieceData[playpiece][8] = FINISH;
            player->finished = player->finished +1;
            player->started = player->started-1;
            
            if (player->finished==4)
            {
                player->playerIndex = finishedPlay;
                finishedPlay++;
            }                                                                                                                                                                                                                                                                         
        }
        else
        {
            printf("Can not move must roll %d\n",6 - player->pieceData[playpiece][8]);
        }
    }
}
