#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <glm/glm.hpp>
#include "random.h"

class TParticle{
public:	
	glm::vec3   m_position; // Center point of particle
    glm::vec3   m_velocity; // Current particle velocity
    float       m_size;     // Size of the particle
    float       m_age;
    float       m_life_time;

	TParticle();
    ~TParticle();

    void Init();
};

TParticle::TParticle(){
	this->m_position = glm::vec3(0);
    this->m_velocity = glm::vec3(0);    
    this->m_age = 0;
    this->m_life_time = 0;
}

TParticle::~TParticle(){

}

void TParticle::Init(){
	m_age       = 0;
	m_life_time = RandomBeetwen(0.5f, 7.0f);
    float range = 30;
	m_position	= glm::vec3(RandomBeetwen(-range, range),
                            60.0f,
                            RandomBeetwen(-range, range));
	m_velocity	= glm::vec3(0.0f);
	m_size		= RandomBeetwen(0.5f, 2.0f);
}

#endif