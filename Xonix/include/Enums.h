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

	enum class TileType // Order and position is important
	{
		Void = 0,
		Wall,
		PlayerSide,
		PlayerVoid,
		PlayerTrail,
		Enemy,
		EnemySide,
		BonusVoid,
		BonusWall,
		BonusMarked,
		Marked
	};

	enum class Bonus
	{
		Void = 0,
		Life,
		Time,
		Score,
		Acceleration,
		Slow,
		Random
	};
}
