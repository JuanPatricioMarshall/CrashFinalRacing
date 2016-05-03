/*
 * Player.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: gonzalo
 */

#include "Player.h"

using namespace std;

Player::Player() :  MoveableObject(),
					m_controllable(true),
					m_dead(false),
					m_dying(false)
{
	m_tag = "Player";
}

Player::Player(bool canControl) :  MoveableObject(),
									m_dead(false),
									m_dying(false)
{
	m_controllable = canControl;
	m_tag = "Player";
}

void Player::collision()
{

}

void Player::load(int x, int y, int width, int height, int textureID, int numFrames)
{
    // Load comun. Inicializa variables
    MoveableObject::load(x, y, width, height, textureID, numFrames);

    TextureManager::Instance()->load("Assets/Sprites/BlackShip.png", m_textureID, Game::Instance()->getRenderer());

    // Otras acciones de inicialización del Player más especificas

}

void Player::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, m_position.getX(), m_position.getY(), m_width, m_height,
    										m_currentRow, m_currentFrame, Game::Instance()->getRenderer(), m_angle, m_alpha, SDL_FLIP_NONE);
	//Nave::draw();
}

void Player::update()
{
	MoveableObject::update();
	//Probar valores para animacion
	//m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
}


void Player::clean()
{
    MoveableObject::clean();
}

void Player::handleInput(InputMessage dataMsg)
{

    if(m_controllable && !m_dead)
    {
        // handle keys
        if ((dataMsg.buttonUp ==1) && (m_position.getY() > 0))
        {
            m_direction.setY(DIRECTION_UP);
        }
        else if ((dataMsg.buttonDown == 1) && ((m_position.getY() + m_height) < Game::Instance()->getGameHeight() - 10))
        {
        	m_direction.setY(DIRECTION_DOWN);
        }

        if ((dataMsg.buttonLeft == 1)	&& m_position.getX() > 0)
        {
        	m_direction.setX(DIRECTION_LEFT);
        }
        else if ((dataMsg.buttonRight == 1) && ((m_position.getX() + m_width) < Game::Instance()->getGameWidth()))
        {
        	m_direction.setX(DIRECTION_RIGHT);
        }
        //Se mueve a velocidades constantes. Evita que vaay a mayot velocidad en diagonal
        m_direction.normalize();

    }

}
