#include <iostream>
#include <GL/glut.h>
#include "src/engine.h"
#include "src/camera.h"
#include "src/tmanager.h"

#define RED   	0
#define GREEN 	0
#define BLUE  	0
#define ALPHA 	1
#define KEY_ESC 27

float wsize = 500;
float hsize = 700;
unsigned particles = 3000;

TEngine *engine;
TCamera *camera;

// float delta_time;

// dt init-time time
glm::vec3 etime(0,0,0);
glm::vec2 mouse(0,0);
glm::vec2 delta(0,0);
glm::vec3 center(0,0,0);
glm::vec3 move(0,0,-200);

int tid = -1;

void Draw(){
	etime[2] = glutGet(GLUT_ELAPSED_TIME);		// time
	etime[0] = (etime[2] - etime[1])/1000.0f;	// delta time
	etime[1] = etime[2];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective( camera->m_perspective[0], camera->m_perspective[1],
					camera->m_perspective[2], camera->m_perspective[3]);

	glTranslatef(move.x, move.y, move.z);
	glRotatef(delta.x, 0.0, 1.0, 0.0);
	glRotatef(delta.y, 1.0, 0.0, 0.0);

	engine->Render(move, tid);
	
	glutSwapBuffers();
	glFlush();
}

void WRedraw(GLsizei _w, GLsizei _h){
	glViewport(0, 0, _w, _h);

	// camera->m_perspective[1] = _w/_h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Idle(){
	engine->Update(etime[0]);

	glutPostRedisplay();
}

void Init(void){	
	GLfloat position[] = { 0.0f, 5.0f, 10.0f, 0.0 };

	glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
	glClearColor(RED, GREEN, BLUE, ALPHA);

    float LightA[] = {0.2f, 0.2f, 0.2f, 1.0f};
    float LightD[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float LightS[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT,  LightA);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  LightD);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightS);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	engine = new TEngine(particles);
	camera = new TCamera(45, wsize/hsize, 0.01f, 500);

	tid = TextureManager::Inst()->LoadTexture("texture/rain4.png", GL_BGRA_EXT, GL_RGBA);
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

// build: g++ main.cpp -o main.out -lGL -lglut -lGLU -lfreeimage
int main(int argc, char *argv[]){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(wsize, hsize);
	glutInitWindowPosition(50,10);
	glutCreateWindow("Particle System");
    
    Init();
    InitScene();	

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