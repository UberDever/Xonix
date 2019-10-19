#pragma once

namespace enums
{
	enum class GameEvent
	{
		Quit,
		Left,
		Right,
		Up,
		Down,
		Options,
		LeaderBoard,
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
