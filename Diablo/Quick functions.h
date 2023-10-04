#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Enums.h"
#include "Enemy.h"

void Clear();
void Pause();
void Sleep(int miliseconds = static_cast<int>(ExtraInts::SleepStandardTime));
void Print(std::string aString);
void PrintInMenu(std::string aString);
void ClearArea(int anX, int anY, int aXLength, int aYLength = 1);
void ClearGame();
void ClearMenu();
void SetColor(ColorInt aColor);
void SetCursorPosition(int aX, int aY);
void FlipCursorVisibility(bool aSetCursor);
double RandomFloatNumber(double min, double max);
int DamageAdjustment(int setDamage);
int RandomNumber(int min, int max);
MenuOptions ButtonPress();