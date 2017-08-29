#pragma once

namespace core { namespace entities {

	class GameActor
	{
	public:
		virtual ~GameActor() {}
		virtual void idle() = 0;
		virtual void up() = 0;
		virtual void down() = 0;
		virtual void left() = 0;
		virtual void right() = 0;
		virtual void upLeft() = 0;
		virtual void upRight() = 0;
		virtual void downLeft() = 0;
		virtual void downRight() = 0;
		virtual bool isMovingUp() = 0;
		virtual bool isMovingDown() = 0;
		virtual bool isMovingLeft() = 0;
		virtual bool isMovingRight() = 0;
		virtual int getSpeed() = 0;
	};

} }