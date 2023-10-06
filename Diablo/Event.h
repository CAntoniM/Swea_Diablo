#pragma once
#include "Enums.h"
#include <string>

class Event
{
public:
	Event();
	std::string GetEventDescription();
	PrimeStats GetAffectedStat();
	int GetStatBuff();

private:
	void SetRandomEvent();
	void Shrine();
	void Poison();
	void Trap();
	std::string _description;
	EventNames _name;
	PrimeStats _affected_stat;
	int _stat_buff;
};

