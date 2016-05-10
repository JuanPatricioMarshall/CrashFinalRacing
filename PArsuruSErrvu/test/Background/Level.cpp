/*
 * Level.cpp
 *
 *  Created on: May 9, 2016
 *      Author: gonzalo
 */

#include "Level.h"

Level::Level():
m_virtualPosition(0),
m_backgroundTextureID(3),
m_levelWidth(400),
m_levelHeight(1000),
m_scrollSpeed(5)
{
}

Level::~Level()
{

}

void Level::update()
{
	 if (m_virtualPosition >= m_levelHeight)
	 {
		 reset();
	 }

	 for (std::vector<GameObject*>::iterator it = m_levelObjects.begin() ; it != m_levelObjects.end(); ++it)
	 {
		 (*it)->update();
	 }

	m_virtualPosition += m_scrollSpeed;

}

void Level::addObject(GameObject* gameObject, int x, int y)
{
	Vector2D virtualPosition;
	virtualPosition.setX(x);
	//El cero esta en la pos alto de ventana e incrementa hacia arriba
	virtualPosition.setY(Game::Instance()->getGameHeight() - y);

	gameObject->setPosition(virtualPosition);
	m_levelObjects.push_back(gameObject);

}

void Level::reset()
{
	 for (std::vector<GameObject*>::iterator it = m_levelObjects.begin() ; it != m_levelObjects.end(); ++it)
	 {
		 int newPosY =  (*it)->getPosition().getY() + m_virtualPosition;
		 int newPosX = (*it)->getPosition().getX();
		 (*it)->setPosition(Vector2D (newPosX, newPosY));
	 }
}

void Level::clean()
{
	 for (std::vector<GameObject*>::iterator it = m_levelObjects.begin() ; it != m_levelObjects.end(); ++it)
	 {
		 delete (*it);
	 }
	 m_levelObjects.clear();
}
