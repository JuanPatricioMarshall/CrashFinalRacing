/*
 * GameObjectFactory.h
 *
 *  Created on: May 10, 2016
 *      Author: gonzalo
 */

#ifndef UTILS_GAMEOBJECTFACTORY_H_
#define UTILS_GAMEOBJECTFACTORY_H_

#include "../GameObject.h"
#include <string>

class GameObjectFactory
{
public:
	GameObject* createGameObject(const std::string& gameObjectID);

private:
};


#endif /* UTILS_GAMEOBJECTFACTORY_H_ */
