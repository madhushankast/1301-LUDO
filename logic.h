#ifndef LOGIC_H
#define LOGIC_H

#include "type.h"
 
int LUDO();

void gamerun(int, int);

void move(int);

char checkcometox(player*,int);

void standmove(player* player,int x);

int randompiece();

int checkpos(int);

void printbegin();

int roll();

int firstroll(int i);

void printvalues(int *ptr);

int sort(int *arr);

int begin();

int decideDirection();

int checkcatch(player *player,int randomplaypiece);

#endif