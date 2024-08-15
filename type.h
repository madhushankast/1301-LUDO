#ifndef TYPE_H
#define TYPE_H


#define YX 0
#define YO 50
#define BX 13
#define BO 11
#define RX 26
#define RO 24
#define GX 39
#define GO 37
#define BASE -1
#define YELLOW 0
#define BLUE 1
#define RED 2
#define GREEN 3
#define PIECE1 1
#define PIECE2 2
#define PIECE3 3
#define PIECE4 4
#define FINISH 100
#define PDATA 5

extern const char* players[4];
//extern struct player *playerlsit[4];



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
    int finished;
    char *color;
    char colorfirst;
    int x;
    int o;
    int *forpieces[4];
}player;




#endif