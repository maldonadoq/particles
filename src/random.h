#ifndef _RANDOM_H_
#define _RANDOM_H_

float Random(){
	return rand()/(float)RAND_MAX;
}

glm::vec3 RandomUnitVect(){
	float x = (Random()*2.0f)-1;
	float y = (Random()*2.0f)-1;
	float z = (Random()*2.0f)-1;

	return glm::normalize(glm::vec3(x,y,z));
}

template<class T>
T RandomBeetwen(T a, T b){
	float rnd = Random();
	T diff = b-a;
	return (T) (rnd*diff) + a;
}



glm::vec4 RandomColor4(){
	return glm::vec4(Random(), Random(), Random(), 0);
}

glm::vec3 RandomColor3(){
	return glm::vec3(Random(), Random(), Random());
}

#endif