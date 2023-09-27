#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Enums.h"
#include "Enemy.h"

void Clear();
void Pause();
void Sleep(int miliseconds = ExtraInts::SleepStandardTime);
void Print(std::string aString);
void PrintInMenu(std::string aString);
void ClearArea(int anX, int anY, int aXLength, int aYLength);
void ClearGame();
void ClearMenu();
void SetColor(int aColor);
void SetCursorPosition(int aX, int aY);
double RandomFloatNumber(double min, double max);
int DamageAdjustment(int setDamage);
int RandomNumber(int min, int max);
int ButtonPress();