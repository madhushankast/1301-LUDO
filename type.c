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

//teleport
#define BHAWANA 9
#define KOTUWA 27
#define PITAKOTUWA 46
#define ENERGIZE 2
#define SICK 0.5
#define FOURROUND 4 



//data count one piece holds
#define PDATA 10

extern const char* players[4];
//extern struct player *playerlist[4];



//for each color

//for each piece
// typedef struct piece
// {
//     int player;
//     int piecenum;
//     int position;
//     //green = 0,yellow = 1,blue = 2,red = 3  
// }piece;


typedef struct player
{
    //defined by array number
    //yellow = 0,blue = 1,red = 2 green = 3,
    int playernum;
    int started;
    int inPlay;
    int finished;
    char *color;
    char colorfirst;
    int x;
    int o;
    int sixrolled;
    int *forpieces[4];
}player;

// typedef struct blockad
// {
//     int playernum;
//     int blockadPieces[4];
//     int blockaedPosition;
//     int pieceCount;
// }blockad;



#endif