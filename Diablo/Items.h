#pragma once
#include <string>
#include "Enums.h"

class Items
{
	private:

		int SetLevel();
		void SetStats();
		ItemType myItemType;
		ItemSlot myItemSlot;
		PrimeStats myPrimeStat;
		SecondaryStats mySecondaryStat;
		int myPrimeStatBuff;
		int mySecondaryStatBuff;
		int myLevel;

	public:
		Items(ItemType aItems);
		ItemType GetItemType();
		PrimeStats GetPrimeStat();
		SecondaryStats GetSecondaryStat();
		int GetPrimeStatBuff();
		int GetSecondaryStatBuff();
		ItemSlot GetItemSlot();




};

