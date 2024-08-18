#include <stdbool.h>
#ifndef LOGIC_H
#define LOGIC_H

#include "type.h"
 
int LUDO();

void gamerun(int, int);

void move(int);

char checkcometox(player*,int);

int standmove(player *player, int y,int playpiece);

int randompiece();

int checkpos(int);

void printbegin();

int roll();

int firstroll(int i);

void printvalues(int *ptr);

int sort(int *arr);

int begin();

int decideDirection();

int checkcatch(player *player);

void createBlocks(player *player, int randomplaypiece);

void telport(player* player,int randomplaypiece,int onmistry);

bool isMistry(int canmistry);

void redcatch(int x);
void yellowcatch(int x);

void printround();

#endif