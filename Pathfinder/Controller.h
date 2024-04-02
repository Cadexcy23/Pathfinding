#pragma once
class Controller {
public:
	static bool quit;
	//Keeps track of mouse Pos
	static int mouseX, mouseY;
	//Checks for inputs from the user
	void controller();
};