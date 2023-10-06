#include "Event.h"
#include "Enums.h"
#include "Quick_functions.h"
#include <string>

Event::Event()
{
	_name;
	_affected_stat;
	_stat_buff;
	_description;
	SetRandomEvent();
}

void Event::SetRandomEvent()
{
	switch (RandomNumber(1, 4)) 
	{
		case 1: 
		{
			Shrine();
			break;
		}
		case 2: 
		{
			Shrine();
			break;
		}
		case 3:
		{
			Poison();
			break;
		}
		case 4:
		{
			Trap();
			break;
		}
	}
}

void Event::Shrine()
{
	_name = EventNames::Shrine;
	std::vector<PrimeStats> randomPrimeStat = {
	PrimeStats::Strength,
	PrimeStats::Dexterety,
	PrimeStats::Charisma,
	PrimeStats::Armor,
	};

	_stat_buff = RandomNumber(5, 10);
	_affected_stat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
	_description = "You feel a growing light inside of you. Your " + toString(_affected_stat) + " has improved!";
}

void Event::Poison()
{
	_name = EventNames::Poison;
	std::vector<PrimeStats> randomPrimeStat = {
	PrimeStats::Strength,
	PrimeStats::Dexterety,
	PrimeStats::Charisma,
	};

	_stat_buff = -RandomNumber(5, 10);
	_affected_stat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
	_description = "You have been poisoned. Your " + toString(_affected_stat) + " has deteriorated!";
}

void Event::Trap()
{
	_name = EventNames::Trap;
	_affected_stat = PrimeStats::Hp;
	bool dodge = RandomNumber(0, 1) == 1 ? true : false;
	if (dodge)
	{
		_stat_buff = 0;
		_description = "There is a trap! You dodge it without taking any damage!";
	}
	else
	{
		_stat_buff = -RandomNumber(10, 30);
		_description = "There is a trap! You get hit and take " + std::to_string(_stat_buff) + " damge!";
	}
}

std::string Event::GetEventDescription()
{
	return _description;
}

PrimeStats Event::GetAffectedStat()
{
	return _affected_stat;
}

int Event::GetStatBuff()
{
	return _stat_buff;
}