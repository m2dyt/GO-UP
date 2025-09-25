#include <GL/glut.h>
#include <stdarg.h>
#include <cmath>
#define GL_GLEXT_PROTOTYPES

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	static float lmodel_twoside[] = { GL_TRUE };
	static float lmodel_oneside[] = { GL_FALSE };

	static float ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	static float diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	static float position[] = { -2.0, 2.0, 2.0, 0.0 };

	static float ambient1[] = { 0.3, 0.3, 0.3, 1.0 };
	static float diffuse1[] = { 0.0, 1.0, 0.0, 1.0 };
	static float position1[] = { 2.0, 2.0, 0.0, 0.0 };

	static float ambient2[] = { 1.0, 1.0, 1.0, 1.0 };
	static float diffuse2[] = { 0.0, 0.0, 1.0, 1.0 };
	static float position2[] = { 0.0, -2.0, 0.0, 0.0 };


	static float frontMatShininess[] = { 60.0 };//степень в зерк отраж
	static float frontMatSpecular[] = { 0.5, 0.5, 0.2, 1.0 };
	static float frontMatDiffuse[] = { 0.5, 0.5, 0.28, 1.0 };
	static float backMatShininess[] = { 60.0 };
	static float backMatSpecular[] = { 0.5, 0.5, 0.2, 1.0 };
	static float backMatDiffuse[] = { 1.0, 0.9, 0.2, 1.0 };

	static float lmodelAmbient[] = { 1.0, 1.0, 1.0, 1.0 };

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient); //фоновое изл источ
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);//цвет рассеяного ист
	glLightfv(GL_LIGHT1, GL_POSITION, position);//направленный свет

	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse1);
	glLightfv(GL_LIGHT2, GL_POSITION, position1);

	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT3, GL_POSITION, position2);

	//материал
	glMaterialfv(GL_FRONT, GL_SHININESS, frontMatShininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR, frontMatSpecular); //цвет зеркального отр
	glMaterialfv(GL_FRONT, GL_DIFFUSE, frontMatDiffuse);
	glMaterialfv(GL_BACK, GL_SHININESS, backMatShininess);
	glMaterialfv(GL_BACK, GL_SPECULAR, backMatSpecular);
	glMaterialfv(GL_BACK, GL_DIFFUSE, backMatDiffuse);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodelAmbient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glTranslatef(1.0f, 0.1f, 0.1f); //перенос координат
	glutSolidSphere(0.2, 50, 40); //шарик
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.75f, -0.45f, 0.4f);
	glColor3d(1, 0, 1);
	glutSolidSphere(0.2, 50, 40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -1.0f, 0.7f);
	glutSolidCube(0.5);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.6f, 1.0f, -0.4f);
	glutSolidCube(0.5);
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}


void keyboard1(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT)
		glRotatef(-2, 1, 0, 0);
	else if (key == GLUT_KEY_LEFT)
		glRotatef(2, 1, 0, 0);
	else if (key == GLUT_KEY_UP)
		glRotatef(-2, 0, 1, 0);
	else if (key == GLUT_KEY_DOWN)
		glRotatef(2, 0, 1, 0);

	glutPostRedisplay();
}



void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		2.0f, 0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Работа 3");
	init();
	glutSpecialFunc(keyboard1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
