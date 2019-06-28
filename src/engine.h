#ifndef _ENGINE_H_
#define _ENGINE_H_

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <GL/glut.h>
#include "particle.h"
#include <math.h>

#define PI 3.14159265

class TEngine{
private:
	std::vector<TParticle> m_particles;
	glm::vec3 m_force;
public:
	TEngine(unsigned);
	TEngine();
	~TEngine();

	void InitParticles(unsigned);
	void Render(glm::vec3, int);
	void Update(float);
};

TEngine::TEngine(unsigned _nparticles){
	this->m_force = glm::vec3(0,-9.81,0);
	InitParticles(_nparticles);
}

TEngine::TEngine(){

}

void TEngine::InitParticles(unsigned _particles){
	m_particles.resize(_particles);
	for(unsigned i=0; i<m_particles.size(); i++){
		m_particles[i].Init();
	}
}

bool CompararParticula(TParticle  p1, TParticle p2) {
    return p1.m_position.z < p2.m_position.z;
}

void TEngine::Render(glm::vec3 _pos, int _tid){
	glTranslatef(0.0f,0.0f,0.0f);
	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, _tid);

	sort(m_particles.begin(), m_particles.end(), CompararParticula);

	glm::vec3 tmp = glm::normalize((_pos - glm::vec3(0, _pos.y, 0)));
	float _angle = glm::orientedAngle(glm::vec2(tmp.x, tmp.z), glm::vec2(0,1))*180/PI;

	for(unsigned i=0; i<m_particles.size(); i++){
		glPushMatrix();
			glTranslatef(
				m_particles[i].m_position.x,
				m_particles[i].m_position.y,
				m_particles[i].m_position.z
			);
			// glRotatef(_angle, 0.0f, 1.0f, 0.0f);

			glBegin(GL_QUADS);
                glTexCoord2f(1, 1);
				glVertex3f(m_particles[i].m_size,   m_particles[i].m_size, 0.0f);
                glTexCoord2f(0, 1);
				glVertex3f(-m_particles[i].m_size,  m_particles[i].m_size, 0.0f);
                glTexCoord2f(0, 0);
				glVertex3f(-m_particles[i].m_size, -m_particles[i].m_size, 0.0f);
                glTexCoord2f(1, 0);
				glVertex3f(m_particles[i].m_size,  -m_particles[i].m_size, 0.0f);
			glEnd();
		glPopMatrix();		
	}

	glDisable(GL_BLEND);
}

void TEngine::Update(float _delta){
	for(unsigned i=0; i<m_particles.size(); i++){
		m_particles[i].m_age += _delta;

		if(m_particles[i].m_age > m_particles[i].m_life_time){
			m_particles[i].Init();
		}

		m_particles[i].m_velocity += m_force*_delta;
		m_particles[i].m_position += m_particles[i].m_velocity*_delta;
	}
}

TEngine::~TEngine(){

}

#endif