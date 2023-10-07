#pragma once
#include "Quick_functions.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include "Enemy.h"
#include "Enums.h"


void Sleep(int miliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
	while (_kbhit())
	{
		_getch();
	}
}

int DamageAdjustment(int damage)
{
	 return static_cast<int>(damage * RandomFloatNumber(0.8, 1.2) + 0.5);
}

double RandomFloatNumber(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(min, max);  

	return distrib(gen);
}

int RandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}

std::string toString(ItemType item)
{
	switch (item)
	{
	case ItemType::Dagger:
		return "Dagger";
		break;

	case ItemType::Sword:
		return "Sword";
		break;

	case ItemType::GreatSword:
		return "Great Sword";
		break;

	case ItemType::Helm:
		return "Helmet";
		break;

	case ItemType::Armor:
		return "Armor";
		break;

	default:
		return "No Item";
		break;
	}
}
std::string toString(PrimeStats prime_stat)
{
	switch (prime_stat)
	{
	case PrimeStats::Strength:
		return "Srenght";
		break;

	case PrimeStats::Dexterety:
		return "Dexterety";
		break;

	case PrimeStats::Charisma:
		return "Charisma";
		break;

	case PrimeStats::Armor:
		return "Armor";
		break;

	default:
		return "No Stat";
		break;
	}
}

std::string toString(SecondaryStats secondary_stat)
{
	switch (secondary_stat)
	{
	case SecondaryStats::Strength:
		return "Srenght";
		break;

	case SecondaryStats::Dexterety:
		return "Dexterety";
		break;

	case SecondaryStats::Charisma:
		return "Charisma";
		break;

	case SecondaryStats::MaxHp:
		return "Max Hp";
		break;

	case SecondaryStats::Damage:
		return "Damage";
		break;

	case SecondaryStats::Athletics:
		return "Athletics";
		break;

	case SecondaryStats::SlightOfHand:
		return "Slight of Hand";
		break;

	case SecondaryStats::Persuasion:
		return "Persuasion";
		break;

	case SecondaryStats::Armor:
		return "Armor";
		break;
	default:
		return "No Stat";
		break;
	}
}
