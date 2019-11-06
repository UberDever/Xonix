#pragma once

namespace enums
{
	enum class GameEvent
	{
		Void = 0,
		Quit,
		Left,
		Right,
		Up,
		Down,
		Options,
		LeaderBoard,
		BeginGame,
		GameOver,
		Start,
		MouseButtonPressed
	};

	enum class TileType
	{
		Void = 0,
		Wall,
		PlayerSide,
		PlayerVoid,
		PlayerTrail,
		Enemy,
		EnemySide
	};

	enum class Bonus
	{
		Void = 0,
		Life,
		Time, 
		Slow,
		Score,
		Acceleration,
		Random
	};
}
