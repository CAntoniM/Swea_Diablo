#pragma once
enum PlayerBase
{
	PlayerBaseStrength		= 15,
	PlayerBaseDexterety		= 10,
	PlayerBaseDodge			= 5,
	PlayerBaseCharisma		= 12,
	NumberOfPlayerAbilitys	= 3,
	PlayerLivingState		= true,

	AthleticsPlayerSkill	= 0,
	SlightOfHandPlayerSkill = 1,
	PersuasionPlayerSkill	= 2,
};

enum EnemyBase
{
	EnemyBaseHp				= 30,
	EnemyBaseStrength		= 10,
	EnemyBaseDexterety		= 10,
	EnemyBaseDodge			= 5,
	EnemyLivingState		= true,
};

enum RoomBase
{
	MaxNumberOfEnemis		= 3,
	MinNumberOfEnemis		= 1,

	MenuExplore				= 0,
	MenuLoot				= 1,
	MenuSwitchRoom			= 2,

	numberOfRooms			= 4,
};

enum DoorBase
{
	doorSpriteSizeX			= 16,
	maxDoorsInARoom			= 4
};

enum MenuOptions
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
	
	gameStartY				= FrameSizeStartY + 1,
	gameStartX				= FrameSizeStartX + 1,
	
	menyStartY				= ScreenSeperatorY + 1,
	menyStartX				= FrameSizeStartX + 1,

};

enum ColorInt
{
	WhiteColorText			= 0,
	GreenColorText			= 1,
	RedColorText			= 2,
	LightGrayColorText		= 3,
};

enum ExtraInts
{
	SleepStandardTime		= 2000,
	OfSet					= 3,
	
};

