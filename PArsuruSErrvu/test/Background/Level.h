/*
 * Level.h
 *
 *  Created on: May 9, 2016
 *      Author: gonzalo
 */

#ifndef BACKGROUND_LEVEL_H_
#define BACKGROUND_LEVEL_H_

#include "../Game.h"
#include "../GameObject.h"
#include "Background.h"
#include "Island.h"
#include <vector>

class Level
{
public:
	Level();
	~Level();

	void initialize(int backgroundTextureID, int levelWidth, int levelHeigth, float scrollSpeed);
	void addObject(GameObject* gameObject, int x, int y);
	void update();
	void clean();

private:

	void reset();

	int m_virtualPosition; // Posicion en Y virtual, tiene el cero en la esquina de abajo e incrementa hacia arriba

	int m_backgroundTextureID;
	int m_levelWidth;
	int m_levelHeight;
	int m_scrollSpeed;
	std::vector<GameObject*> m_levelObjects;
};



#endif /* BACKGROUND_LEVEL_H_ */
