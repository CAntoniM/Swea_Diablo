#include "Items.h"
#include "Quick functions.h"
#include "Enums.h"
#include <string>
#include <vector>

Items::Items(ItemType aItems)
{
	myItemType = aItems;
	myLevel = SetLevel();
	SetStats();
}

int Items::SetLevel()
{
	int level = RandomNumber(1, 100);
	return level >= static_cast<int>(ItemBase::ProcentalChansLvlThree) ? 3 : level >= static_cast<int>(ItemBase::procentalChansLvlTwo) ? 2 : 1;
}
void Items::SetStats()
{
	std::vector<PrimeStats> randomPrimeStat;
	std::vector<SecondaryStats> randomSecondaryStats;
	int buffDivider = RandomNumber(1, 5);
	switch (myItemType)
	{
	case ItemType::Dagger:

		randomPrimeStat =
		{
			PrimeStats::Dexterety,
			PrimeStats::Charisma,
		};

		randomSecondaryStats = 
		{
			SecondaryStats::Strength,
			SecondaryStats::Charisma,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::SlightOfHand
		};

		myItemSlot = ItemSlot::Weapon;
		myPrimeStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		myPrimeStatBuff = RandomNumber(buffDivider, (buffDivider + 2)) * myLevel;
		mySecondaryStatBuff = RandomNumber(1, buffDivider) * myLevel;
		break;
	case ItemType::Sword:

		randomPrimeStat =
		{
			PrimeStats::Dexterety,
			PrimeStats::Strength,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Dexterety,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp
		};

		myItemSlot = ItemSlot::Weapon;
		myPrimeStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		myPrimeStatBuff = RandomNumber(buffDivider, (buffDivider + 2)) * myLevel;
		mySecondaryStatBuff = RandomNumber(1, buffDivider) * myLevel;
		break;
	case ItemType::GreatSword: 

		randomPrimeStat =
		{
			PrimeStats::Armor,
			PrimeStats::Strength,
		};
		
		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Armor,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp,
			SecondaryStats::Athletics,
		};

		myItemSlot = ItemSlot::Weapon;
		myPrimeStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		myPrimeStatBuff = RandomNumber(buffDivider, (buffDivider + 2)) * myLevel;
		mySecondaryStatBuff = RandomNumber(1, buffDivider) * myLevel;
		break;
	case ItemType::Helm:

		randomPrimeStat =
		{
			PrimeStats::Charisma,
			PrimeStats::Dexterety,
			PrimeStats::Armor,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Charisma,
			SecondaryStats::Armor,
			SecondaryStats::MaxHp,
			SecondaryStats::Persuasion,
		};

		myItemSlot = ItemSlot::Helm;
		myPrimeStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		myPrimeStatBuff = RandomNumber(buffDivider, (buffDivider + 2)) * myLevel;
		mySecondaryStatBuff = RandomNumber(1, buffDivider) * myLevel;
		break;
	case ItemType::Armor:

		randomPrimeStat =
		{
			PrimeStats::Strength,
			PrimeStats::Armor,
		};

		randomSecondaryStats =
		{
			SecondaryStats::Strength,
			SecondaryStats::Armor,
			SecondaryStats::Damage,
			SecondaryStats::Persuasion,
			SecondaryStats::MaxHp,
			SecondaryStats::Athletics,
		};

		myItemSlot = ItemSlot::Armor;
		myPrimeStat = randomPrimeStat[RandomNumber(0, (static_cast<int>(randomPrimeStat.size()) - 1))];
		myPrimeStatBuff = RandomNumber(buffDivider, (buffDivider + 2)) * myLevel;
		mySecondaryStatBuff = RandomNumber(1, buffDivider) * myLevel;
		break;
	default:
		break;
	}
}

PrimeStats Items::GetPrimeStat()
{
	return myPrimeStat;
}

SecondaryStats Items::GetSecondaryStat()
{
	return mySecondaryStat;
}

int Items::GetPrimeStatBuff()
{
	return myPrimeStatBuff;
}

int Items::GetSecondaryStatBuff() 
{
	return mySecondaryStatBuff;
}

ItemType Items::GetItemType()
{
	return myItemType;
}

ItemSlot Items::GetItemSlot()
{
	return myItemSlot;
}