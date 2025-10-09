#include <iostream>
#include <GL/glut.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

// параметры материалов куба
float cubeDif[] = { 0.3, 0.5, 0.2 };
float cubeAmb[] = { 0.5, 0.5, 0.5 };
float cubeSpec[] = { 0.8, 0.7, 0.8 };
float cubeShininess = 40;

float cubeDif1[] = { 0.0f , 0.9f , 0.8f };
float cubeAmb1[] = { 0.2f , 0.2f , 0.2f };
float cubeSpec1[] = { 0.9f , 0.9f , 0.9f };
float cubeShininess1 = 0.7f * 128;

// параметры материалов сферы
float sphereDif[] = { 1.0f , 0.9f , 0.0f };
float sphereAmb[] = { 0.6f , 0.0f , 0.8f };
float sphereSpec[] = { 0.2f , 0.2f , 0.8f };
float sphereShininess = 0.3f * 128;

// переменные необходимая для вращения
int angleX = 0, angleY = 0, angleZ = 0;
int q = 0, a = 0, z = 0;
float k = 1;

//Инициализация параметров и источника света
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glPushMatrix();
	glRotatef(q, 0.7, 0.0, 0.0);
	glRotatef(q, 0.0, 0.6, 0.0);
	glRotatef(q, 0.0, 0.0, 0.8);

	GLfloat lightAmbient[] = { 0.7 , 0.0 , 0.0 , 1.0 };
	GLfloat lightDiff[] = { 1.0 , 0.3 , 0.3 , 1.0 };
	GLfloat lightSpec[] = { 0.3 , 0.3 , 0.3 , 1.0 };
	GLfloat lightPosit[] = { 1.0 , 1.0 , 2.0 , 0.0 };

	// устанавливаем параметры источника света
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);//цвет фонового излучения источника света
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);//цвет рассеянного излучения источника света
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);//цвет зеркального излучения источника света
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosit);//Первые три компоненты (x, y, z) задают вектор направления, а w = 0 (иначе источник превратится в точечный).
	glEnable(GL_LIGHT0);

	glPopMatrix();
	glPushMatrix();

	//текущую матрицу на матрицу вращения
	glRotatef(a, 0.7, 0.0, 0.0);
	glRotatef(a, 0.0, 0.6, 0.0);
	glRotatef(a, 0.0, 0.0, 0.8);

	GLfloat lightAmbient1[] = { 0.1 , 0.8 , 0.9 , 1.1 };
	GLfloat lightDiff1[] = { 0.5 , 0.2 , 0.6 , 1.0 };
	GLfloat lightSpec1[] = { 0.1 , 0.1 , 0.1 , 1.0 };
	GLfloat lightPosit1[] = { -1.0 , 1.0 , 2.0 , 0.0 };

	// устанавливаем параметры источника света
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosit1);
	glEnable(GL_LIGHT1);

	glPopMatrix();
	glPushMatrix();

	glRotatef(z, 0.7, 0.0, 0.0);
	glRotatef(z, 0.0, 0.6, 0.0);
	glRotatef(z, 0.0, 0.0, 0.8);

	GLfloat lightAmbient2[] = { 0.9 , 0.2 , 0.0 , 1.0 };
	GLfloat lightDiffuse2[] = { 0.1 , 0.7 , 0.3 , 1.0 };
	GLfloat lightSpecular2[] = { 0.1 , 0.1 , 0.1 , 1.0 };
	GLfloat lightPosition2[] = { 0.0 , -1.0 , 2.0 , 0.0 };

	// устанавливаем параметры источника света
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDiffuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glEnable(GL_LIGHT2);

	glPopMatrix();
	glEnable(GL_LIGHTING);//включаем освещение и источник света
	glEnable(GL_DEPTH_TEST);
}
void reshape(int w, int h) {
	glViewport(0, 0, w, h);//устанавливаем размер области вывода равным размеру окна
	glMatrixMode(GL_PROJECTION);//задаем матрицу проекции с учетом размеров окна
	glLoadIdentity();//очистки текущей матрицы для будущих преобразований
	gluPerspective(120.0, w / h, 1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 1.0, 5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0f);
	glFlush();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//очистка буфера кадра и буфера глубины
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, cubeAmb);//фоновый цвет материала
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cubeDif);//диффузный цвет материала
	glMaterialfv(GL_FRONT, GL_SPECULAR, cubeSpec);//зеркальный цвет материала
	glMaterialf(GL_FRONT, GL_SHININESS, cubeShininess);//показатель зеркального отражения

	glPushMatrix();
	glTranslatef(-4.75, 0.0, -1.0);
	glRotatef(angleX, 0.7, 0.0, 0.0);
	glRotatef(angleY, 0.0, 0.6, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 0.8);
	glutSolidCube(2.5);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, cubeAmb1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cubeDif1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cubeSpec1);
	glMaterialf(GL_FRONT, GL_SHININESS, cubeShininess1);
	glPushMatrix();
	glTranslatef(0.0, -3.0, 0.0);
	glRotatef(angleX, 0.7, 0.0, 0.0);
	glRotatef(angleY, 0.0, 0.6, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 0.8);
	glutSolidCube(1.0);
	glPopMatrix();

	// сфера
	glEnable(GL_BLEND); //включаем прозрачность
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, sphereAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sphereDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sphereSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, sphereShininess);
	glPushMatrix();

	glRotatef(15, 0.7, 0.0, 0.0);
	glRotatef(angleX, 0.7, 0.0, 0.0);
	glRotatef(angleY, 0.0, 0.6, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 0.8);
	glTranslatef(3.75, 0.0, -1.0);

	glScalef(k, k, k); //изменение масштаба
	glutSolidSphere(2, 150, 150);
	glPopMatrix();
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glMaterialfv(GL_FRONT, GL_AMBIENT, cubeAmb1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cubeDif1);
	glMaterialfv(GL_FRONT, GL_SPECULAR, cubeSpec1);
	glMaterialf(GL_FRONT, GL_SHININESS, cubeShininess1);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(angleX, 0.7, 0.0, 0.0);
	glRotatef(angleY, 0.0, 0.6, 0.0);
	glRotatef(angleZ, 0.0, 0.0, 0.8);
	glutSolidCube(1);
	glDisable(GL_BLEND);
	glPopMatrix();// вид камеры сд другой  стороны


	init();//заново запускаем эту функцию чтобы сменить координаты камеры
	glFlush();//выводим сцену на экран
}
// выход при нажатии esc
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'q':
		angleX = (angleX + 5) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		angleY = (angleY + 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		angleZ = (angleZ + 5) % 360;
		glutPostRedisplay();
		break;
	case 'r':
		q = (q - 5) % 360;
		glutPostRedisplay();
		break;
	case 't':
		a = (a - 5) % 360;
		glutPostRedisplay();
		break;
	case 'y':
		z = (z - 5) % 360;
		glutPostRedisplay();
		break;
	case 'u':
		z = (z + 5) % 360;
		glutPostRedisplay();
		break;
	case 'i':
		k += 0.1;
		if (k >= 2)
			k = -2;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Рандом фигурки");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
