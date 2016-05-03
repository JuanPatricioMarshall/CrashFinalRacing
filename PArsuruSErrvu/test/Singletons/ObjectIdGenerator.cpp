#include "ObjectIdGenerator.h"

ObjectIdGenerator* ObjectIdGenerator::s_pInstance = 0;


int	ObjectIdGenerator::generateId(){

	m_IdCounterStrike++;
	return m_IdCounterStrike;
}

