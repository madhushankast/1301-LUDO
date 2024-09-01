#ifndef TYPE_H
#define TYPE_H

//X value and O value in standard path starting from yellow x
#define YO 0
#define YX 2
#define BO 13
#define BX 15
#define RO 26
#define RX 28
#define GO 39
#define GX 41

#define BASE -1
#define HOME 60
#define FINISH 100

#define YELLOW 0
#define BLUE 1
#define RED 2
#define GREEN 3

#define PIECE1 0
#define PIECE2 1
#define PIECE3 2
#define PIECE4 3

//mistryTeleport
#define BHAWANA 9
#define KOTUWA 27
#define PITAKOTUWA 46
#define ENERGIZE 2
#define SICK 0.5
#define FOURROUND 4 
#define FREEZE 0

//data count one piece holds
#define PIECEDATA 9

extern const char* players[4];


typedef struct player
{
    int playerIndex;          //yellow = 0 , blue = 1 , red = 2 , green = 3,
    int inBase;             //Pieces count Base out of 4
    int started;            //Pieces count in Standard Path
    int finished;           //Pieces Count finished the game
    char *color;            //String for Color
    char colorfirst;        //First Letter of Colour
    int x;                  //Starting position of player
    int o;                  //Apporoach cell of player
    int sixrolled;          //count for rolling six 
    int *pieceData[4];   //Four size array for hold each piece
}player;





#endif