#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <iostream>
#include <vector>
#include <assert.h>
#include "particle.h"
#include <math.h>

class TEngine{
private:
	unsigned m_nparticles;
	std::vector<TParticle> m_particles;
	glm::vec3 m_force;
	glm::vec3 m_init;
public:
	TEngine(unsigned);
	TEngine();
	~TEngine();

	void InitParticles();
	void Render();
	void Update(float);
};

TEngine::TEngine(unsigned _nparticles){
	this->m_nparticles = _nparticles;
	this->m_particles.resize(m_nparticles, TParticle());
	this->m_force = glm::vec3(0,-9.81,0);
	this->m_init = glm::vec3(0,50,0);

	InitParticles();
}

TEngine::TEngine(){

}

void TEngine::InitParticles(){
	assert(m_particles.size() == m_nparticles);
	for(unsigned i=0; i<m_particles.size(); i++){
		m_particles[i].Init();
	}
}

void TEngine::Render(){
	for(unsigned i=0; i<m_particles.size(); i++){
		glPushMatrix();
			glTranslatef(
				m_particles[i].m_position.x,
				m_particles[i].m_position.y,
				m_particles[i].m_position.z
			);

			glColor3f(
				m_particles[i].m_color.x,
				m_particles[i].m_color.y,
				m_particles[i].m_color.z
			);			
			glutSolidSphere(m_particles[i].m_size,10,10);
		glPopMatrix();		
		// std::cout << "size: " << i << " is " << m_particles[i].m_size << "\n";
		/*
		std::cout << "[" << m_particles[i].m_position[0] << ","
						 << m_particles[i].m_position[1] << ","
						 << m_particles[i].m_position[2] << "]\n";
		*/
	}	
}

void TEngine::Update(float _delta){
	// assert(m_particles.size() == m_nparticles);
	for(unsigned i=0; i<m_particles.size(); i++){
		m_particles[i].m_age += _delta;

		if(m_particles[i].m_age > m_particles[i].m_life_time){
			m_particles[i].Init();
		}

		m_particles[i].m_position = m_init +
						 (m_particles[i].m_velocity*m_particles[i].m_age) + 
						 (m_force*((float)pow(m_particles[i].m_age, 2)/2));

		//m_particles[i].m_velocity += m_force*_delta;
		//m_particles[i].m_position += m_particles[i].m_velocity*_delta;

	}
}

TEngine::~TEngine(){

}

#endif