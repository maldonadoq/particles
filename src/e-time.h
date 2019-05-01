#ifndef _E_TIME_H_
#define _E_TIME_H_

#include <ctime>

class ETime{
private:
	float m_max_time;
	mutable float m_previous;
public:
	ETime(float _max = 0.03333){
		this->m_max_time = _max;
		this->m_previous = std::clock() / (float)CLOCKS_PER_SEC;
	}
	~ETime(){	};

	float GetElapsed() const{
		float curr_time = std::clock() / (float)CLOCKS_PER_SEC;
		float delta = curr_time - m_previous;
		m_previous = curr_time;

		return delta;
	}
};

#endif