#pragma once
enum class PlayerBase
{
	PlayerBaseStrength		= 15,
	PlayerBaseDexterety		= 10,
	PlayerBaseCharisma		= 12,
	PlayerBaseDodge			= 5,
	NumberOfPlayerAbilitys	= 3,
	PlayerBaseArmor			= 1,
	//THIS IS VERY VERY EVIL.... in c 0 == false and 0 != true so this can cuase issues in ways you are not expecting
	PlayerLivingState		= true,
	ResetStats				= 0,

	AthleticsPlayerSkill	= 0,
	SlightOfHandPlayerSkill = 1,
	PersuasionPlayerSkill	= 2,
};


enum class EnemyBase
{
	EnemyBaseHp				= 30,
	EnemyBaseStrength		= 10,
	EnemyBaseDexterety		= 10,
	EnemyBaseDodge			= 5,
	//THIS IS VERY VERY EVIL.... in c 0 == false and 0 != true so this can cuase issues in ways you are not expecting
	EnemyLivingState		= true,
};

enum class RoomBase
{
	MaxNumberOfEnemis		= 3,
	MinNumberOfEnemis		= 1,
	
	MaxNumberOfItemsDropt	= 7,
	MinNumberOfItemsDropt	= 5,

	ChansOfGettingAEvent	= 1, 

	MenuExplore				= 0,
	MenuLoot				= 1,
	MenuInventory			= 2,
	MenuSwitchRoom			= 3,
	

	numberOfRooms			= 4,

};

enum class DoorBase
{
	doorSpriteSizeX			= 16,
	maxDoorsInARoom			= 4
};

enum class ItemBase
{
	ProcentalChansLvlThree	= 80,
	procentalChansLvlTwo	= 50,
};

enum class MenuOptions
{
	MenuListUp				= 1,
	MenuListDown			= 2,
	MenuListLeft			= 3,
	MenuListRight			= 4,
	MenuListOption			= 0,

	FrameSizeStartY			= 0,
	FrameSizeStartX			= 0,
	FrameSizeEndX			= 100,
	FrameSizeEndY			= 27,
	ScreenSeperatorY		= FrameSizeEndY - 10,
	StatsSeperatorX			= FrameSizeEndX - 30,
	ItemStatsPrimeStartX	= FrameSizeEndX - 70,
	ItemStatsSecondaryStartX= ItemStatsPrimeStartX + 17,
	
	gameStartY				= FrameSizeStartY + 1,
	gameStartX				= FrameSizeStartX + 1,
	
	menyStartY				= ScreenSeperatorY + 1,
	menyStartX				= FrameSizeStartX + 1,

};


enum class ColorInt
{
	WhiteColorText			= 0,
	GreenColorText			= 1,
	RedColorText			= 2,
	LightGrayColorText		= 3,
};

enum class ExtraInts
{
	SleepStandardTime		= 2000,
	OfSet					= 3,
	
};

enum class ItemType
{
	Dagger,
	Sword,
	GreatSword,
	Helm,
	Armor,
};

enum class PrimeStats
{
	Strength,
	Dexterety,
	Charisma,
	Armor,
	Hp,
};

enum class SecondaryStats
{
	Strength,
	Dexterety,
	Charisma,
	MaxHp,
	Damage,
	Athletics,
	SlightOfHand,
	Persuasion,
	Armor,
};

enum class ItemSlot
{
	Helm,
	Armor,
	Weapon,
};

enum class EventNames
{
	Shrine,
	Poison,
	Trap,
};