#ifndef _GAMESPECS_H
#define _GAMESPECS_H

#include <windows.h>
#include <random>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

const int GRIDSIZE = 20;
const int HUMAN_STARTCOUNT = 100;
const int ZOMBIE_STARTCOUNT = 5;
const int HUMAN_BREED = 3;
const int ZOMBIE_BREED = 8;
const int ZOMBIE_STARVE = 3;
const char HUMAN_CH = 72;
const char SPACE_CH = 32;
const char ZOMBIE_CH = 90;
const double PAUSE_SECONDS = .09;

const int HUMAN_COLOR = 6;
const int ZOMBIE_COLOR = 4;
const int DEFAULT_COLOR = 7;

#endif