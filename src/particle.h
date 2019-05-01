#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include "random.h"

class TParticle{
public:	
	glm::vec3   m_position; // Center point of particle
    glm::vec3   m_velocity; // Current particle velocity
    glm::vec3   m_color;    // Particle color
    float       m_rotate;   // Rotate the particle the center
    float       m_size;     // Size of the particle
    float       m_age;
    float       m_life_time;

	TParticle();
    ~TParticle();

    void Init(float);
};

TParticle::TParticle(){
	this->m_position = glm::vec3(0);
    this->m_velocity = glm::vec3(0);
    this->m_color    = glm::vec4(0);
    this->m_rotate = 0;
    this->m_age = 0;
    this->m_life_time = 0;
}

TParticle::~TParticle(){

}

void TParticle::Init(float _y){
	m_age = 0;
	m_life_time = RandomBeetwen(0.5f, 4.0f);

	glm::vec3 unitv = RandomUnitVect();

	m_position	= unitv;
	m_position.y = _y;
	m_velocity	= unitv*10.0f;
    // m_velocity.x *= 3;
	m_color		= RandomColor3();
	m_size		= RandomBeetwen(1,2);
}

#endif