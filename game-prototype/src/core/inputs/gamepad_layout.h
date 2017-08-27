#pragma once

class Gamepad_Layout {
public:
	bool up;
	bool down;
	bool left;
	bool right;
	Gamepad_Layout() {
		up = false;
		down = false;
		left = false;
		right = false;
	}
	~Gamepad_Layout() {}
};