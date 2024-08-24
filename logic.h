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

void gameplay(int);

void move(int);

char checkcometox(player*,int);

int standmove(player *player, short y);

int selectPlayPiece(player *player,int x);

int checkpos(int);

int coinToss();

int captured(player *player,int playedpiece);

bool cancaptured(player *player,int x);

int createBlocks(player *player, int randomplaypiece);

void telport(player* player,int randomplaypiece,int onmistry);

bool canBeMistry(int mistryIs);

bool redcatch(short x);

void yellowcatch(int x);

void printround();

int yellowPlayPiece(player *player,int x);

int bluePlayPiece(int x);

int redPlayPiece();

bool isPiecelocated(int mistryis);


#endif