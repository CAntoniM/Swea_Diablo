#pragma once
#include "Enums.h"
#include <string>

class Events
{
public:
	Events();
	std::string GetEventDescription();
	PrimeStats GetAffectedStat();
	int GetStatBuff();

private:
	void SetRandomEvent();
	void Shrine();
	void Poison();
	void Trap();
	std::string myEventDescription;
	EventNames myEventName;
	PrimeStats myAffectedStat;
	int myStatBuff;
};

