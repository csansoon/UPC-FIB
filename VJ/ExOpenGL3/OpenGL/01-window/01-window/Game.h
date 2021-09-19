#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE
#include <GL/glut.h>


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

private:
	bool bPlay; // Continue to play game?

};


#endif // _GAME_INCLUDE


