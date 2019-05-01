#ifndef _AXIS_H_
#define _AXIS_H_

void Axis(float _x, float _y, float _z, float _size){
	glBegin(GL_LINES);
		// x
		glColor3f(1,0,0);
		glVertex3f(_x,_y,_z);
		glVertex3f(_x+_size,_y,_z);

		// y
		glColor3f(0,1,0);
		glVertex3f(_x,_y,_z);
		glVertex3f(_x,_y+_size,_z);

		// z
		glColor3f(0,0,1);
		glVertex3f(_x,_y,_z);
		glVertex3f(_x,_y,_z+_size);
	glEnd();
}

#endif