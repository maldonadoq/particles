#include <iostream>
#include <GL/glut.h>
#include "src/e-time.h"
#include "src/engine.h"
#include "src/camera.h"
#include "src/axis.h"

#define RED   	0
#define GREEN 	0
#define BLUE  	0
#define ALPHA 	1
#define KEY_ESC 27

float wsize = 500;
float hsize = 700;
unsigned particles = 500;

TEngine *engine;
TCamera *camera;

// float delta_time;

// dt init-time time
glm::vec3 etime(0,0,0);
glm::vec2 mouse(0,0);
glm::vec2 delta(0,0);
glm::vec3 center(0,0,0);

void Draw(){
	etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	etime[0] = (etime[2] - etime[1])/1000.0f;	// delta time
	etime[1] = etime[2];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
					camera->m_perspective[2], camera->m_perspective[3]);

	glTranslatef(0,0,-200);
	glRotatef(delta.x, 0.0, 1.0, 0.0);
	glRotatef(delta.y, 1.0, 0.0, 0.0);

	/*std::cout << "[" << camera->m_perspective[0] << ","
					 << camera->m_perspective[1] << ","
					 << camera->m_perspective[2] << ","
					 << camera->m_perspective[3] << "\n";*/	
	
	// Axis(center.x, center.y, center.z ,30);
	engine->Render();
	
	glutSwapBuffers();
	glFlush();
}

void WRedraw(GLsizei _w, GLsizei _h){
	glViewport(0, 0, _w, _h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(-msize,msize,-msize,msize, -25.0f, 25.0f);
	gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
					camera->m_perspective[2], camera->m_perspective[3]);

	glMatrixMode(GL_MODELVIEW);
}

void Idle(){
	// static ETime etime;
	// delta_time = etime.GetElapsed();

	// std::cout << etime[0]  << " update\n";
	// engine->Update(delta_time);
	engine->Update(etime[0]);

	glutPostRedisplay();
}

void Init(void){	
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(RED, GREEN, BLUE, ALPHA);
}

void InitScene(){
}

void WKey(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(0);
            break;
        default:
            break;
    }
}

void Mouse(int button, int state, int x, int y){
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		mouse.x = x;
		mouse.y = y;
	}
}


void MouseMotion(int x, int y){
	delta.x += (x - mouse.x)/10;
	delta.y += (y - mouse.y)/10;
	
	mouse.x = x;
	mouse.y = y;
	glutPostRedisplay();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
	glutInitWindowSize(wsize, hsize);
	glutInitWindowPosition(50,10);
	glutCreateWindow("Particle System");
    
    Init();
    InitScene();

	engine = new TEngine(particles, 50);
	camera = new TCamera(45, wsize/hsize, 0.01f, 500);

    glutDisplayFunc(&Draw);
    glutReshapeFunc(&WRedraw);

    glutMouseFunc(&Mouse);
	glutMotionFunc(&MouseMotion);

    glutKeyboardFunc(&WKey);
    glutIdleFunc(&Idle);

    glutMainLoop();

    delete engine;
    delete camera;

    return 0;
}