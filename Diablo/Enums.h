#pragma once
enum PlayerBase
{
	PlayerBaseHp			= 5000,
	PlayerBaseStrength		= 10,
	PlayerBaseDexterety		= 10,
	PlayerBaseDodge			= 5,
	PlayerLivingState		= true,
};

enum EnemyBase
{
	EnemyBaseHp				= 25,
	EnemyBaseStrength		= 5,
	EnemyBaseDexterety		= 5,
	EnemyBaseDodge			= 5,
	EnemyLivingState		= true,
};

enum RoomBase
{
	MaxNumberOfEnemis		= 3,
	MinNumberOfEnemis		= 1,
};

enum MenuOptions
{
	MenuListUp				= 1,
	MenuListDown			= 2,
	MenuListLeft			= 3,
	MenuListRight			= 4,
	MenuListOption			= 0,

	frameSizeStartY			= 0,
	frameSizeStartX			= 0,
	frameSizeEndX			= 100,
	frameSizeEndY			= 27,
	screenSeperatorY		= frameSizeEndY - 10,
	
	gameStartY				= frameSizeStartY + 1,
	gameStartX				= frameSizeStartX + 1,
	
	menyStartY				= screenSeperatorY + 1,
	menyStartX				= frameSizeStartX + 1,
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
	SleepStandardTime = 2000,
};

