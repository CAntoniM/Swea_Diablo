#include "Events.h"
#include "Enums.h"
#include "Quick functions.h"
#include <string>

Events::Events()
{
	myEventName;
	myAffectedStat;
	myStatBuff;
	myEventDescription;
	SetRandomEvent();
}

void Events::SetRandomEvent()
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

void Events::Shrine()
{
	myEventName = EventNames::Shrine;
	std::vector<PrimeStats> randomPrimeStat = {
	PrimeStats::Strength,
	PrimeStats::Dexterety,
	PrimeStats::Charisma,
	PrimeStats::Armor,
	};

	myStatBuff = RandomNumber(5, 10);
	myAffectedStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
	myEventDescription = "You feel a growing light inside of you. Your " + PrimeStatToString(myAffectedStat) + " has improved!";
}

void Events::Poison()
{
	myEventName = EventNames::Poison;
	std::vector<PrimeStats> randomPrimeStat = {
	PrimeStats::Strength,
	PrimeStats::Dexterety,
	PrimeStats::Charisma,
	};

	myStatBuff = -RandomNumber(5, 10);
	myAffectedStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
	myEventDescription = "You have been poisoned. Your " + PrimeStatToString(myAffectedStat) + " has deteriorated!";
}

void Events::Trap()
{
	myEventName = EventNames::Trap;
	myAffectedStat = PrimeStats::Hp;
	bool dodge = RandomNumber(0, 1) == 1 ? true : false;
	if (dodge)
	{
		myStatBuff = 0;
		myEventDescription = "There is a trap! You dodge it without taking any damage!";
	}
	else
	{
		myStatBuff = -RandomNumber(10, 30);
		myEventDescription = "There is a trap! You get hit and take " + std::to_string(myStatBuff) + " damge!";
	}
}

std::string Events::GetEventDescription()
{
	return myEventDescription;
}

PrimeStats Events::GetAffectedStat()
{
	return myAffectedStat;
}

int Events::GetStatBuff()
{
	return myStatBuff;
}