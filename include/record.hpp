#ifndef RECORDS_H
#define RECORDS_H

#include "misc.hpp"

extern std::set<std::pair<int, std::string>> records;

void readrecords();
void saverecords();
void displayrecords();
void drawrecord(int score);
bool isnewrecord(int score);
void addrecord(int score);

#endif