#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Enums.h"
#include "Enemy.h"

void Sleep(int miliseconds = static_cast<int>(ExtraInts::SleepStandardTime));
std::string toString(ItemType aItem);
std::string toString(PrimeStats aPrimeStat);
std::string toString(SecondaryStats aSecondaryStat);
double RandomFloatNumber(double min, double max);
int DamageAdjustment(int setDamage);
int RandomNumber(int min, int max);
