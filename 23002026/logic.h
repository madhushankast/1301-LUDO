#include <stdbool.h>
#ifndef LOGIC_H
#define LOGIC_H

#include "type.h"

short LUDO();


void printbegin();

short roll();

short firstroll(short i);

short firstHand();

//short sort(short *arr);

void yellowMove();

void blueMove();

void redMove();

void greenMove();

void gameplay(short);

void baseToStart(player*);

short standardMove(player *player, short y);

short selectPlayPiece(player *player,short x);

//short checkpos(short);

short coinToss();

short captured(player *player,short playpiece);

bool canCaptureAny(short);

short createBlocks(player *player, short randomplaypiece);

void mistryTeleport(player* player,short randomplaypiece);

bool canBeMistry(short mistryIs);

short capturedOutput();

short redcatch(short);

bool yellowcatch(short);

bool greencatch(short);

void printRound();

short yellowPlayPiece(short);

short bluePlayPiece(short x);

short redPlayPiece();

short greenPlayPiece();

bool isPiecelocated(short mistryis);


bool passApporoach(player *player,short playpiece,short roll);

void homeMove(player *player,short playpiece,short roll);


#endif