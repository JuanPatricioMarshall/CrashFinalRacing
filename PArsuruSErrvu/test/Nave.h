/*
 * Nave.h
 *
 *  Created on: Apr 8, 2016
 *      Author: gonzalo
 */

#ifndef NAVE_H_
#define NAVE_H_

#include "GameObject.h"
//#include "Game.h"
//#include "Singletons/TextureManager.h"
#include "Vector2D.h"
#include <string>

#define DIRECTION_UP -1
#define DIRECTION_DOWN 1
#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT -1

class Nave : public GameObject
{
public:
    virtual ~Nave() {}

    virtual void load(int x, int y, int width, int height, int textureID, int numFrames);
    
    //Funciones Generales
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void collision();
    
    //Getters
    bool isDead() { return m_dead; }
    bool isDying() { return m_dying; }

    Vector2D& getDirection() { return m_direction; }
    Vector2D& getSpeed() { return m_speed; }



protected:

    Nave();

    // variables de movimiento
    Vector2D m_direction;
    Vector2D m_speed;

    // variables de control de estado
    bool m_dead;
    bool m_dying;
};

#endif /* NAVE_H_ */
