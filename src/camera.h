#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <glm/glm.hpp>

class TCamera{
private:	
public:	
	glm::vec4 m_perspective;	// fovy,ratio,znear,zfar

	TCamera(float _fovy, float _ratio,
		float _znear, float _zfar){
		this->m_perspective = glm::vec4(_fovy, _ratio, _znear, _zfar);
	}

	TCamera(){
		this->m_perspective = glm::vec4(0,0,0,0);
	}

	~TCamera(){	};
};

#endif