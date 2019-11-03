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
		Void,
		Wall,
		PlayerSide,
		PlayerVoid,
		PlayerTrail,
		Enemy,
		EnemySide
	};
}
