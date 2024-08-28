#include <stdbool.h>
#ifndef LOGIC_H
#define LOGIC_H

#include "type.h"

int LUDO();

void printbegin();

int roll();

int firstroll(int i);

int firstHand();

void printvalues(int *ptr);

//int sort(int *arr);

void yellowMove();

void blueMove();

void redMove();

void greenMove();

void gameplay(int);

void baseToStart(player*);

int standmove(player *player, int y);

int selectPlayPiece(player *player,int x);

int checkpos(int);

int coinToss();

int captured(player *player,int playpiece);

bool canCaptureAny(int);

int createBlocks(player *player, int randomplaypiece);

void teleport(player* player,int randomplaypiece,int onmistry);

bool canBeMistry(int mistryIs);

int capturedOutput();

int redcatch(int);

bool yellowcatch(int);

bool greencatch(int);

void printRound();

int yellowPlayPiece(int);

int bluePlayPiece(int x);

int redPlayPiece();

int greenPlayPiece();

bool isPiecelocated(int mistryis);


bool isHome(player *player,int playpiece,int roll);

void homeMove(player *player,int playpiece,int roll);


#endif