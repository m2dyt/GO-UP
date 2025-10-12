#include <Windows.h>
#include <GL/glew.h>  
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>

using namespace std;

GLdouble up_val_camera = 1.0;
GLdouble up_val_speed = 0.05;
GLdouble eyex = -16.0, eyey = -16.0, eyez = 15.0;
GLdouble centerx = 1.0, centery = 1.0, centerz = 0.0;
GLdouble upx = 1., upy = 1.0, upz = 1.0;
GLuint ps, vs, prog, r_mod;

void set_shader() {
	const char* f =
		"varying float x, y, z;"
		"uniform float r_mod;"
		"float rand(float s, float r) { return mod(mod(s, r + r_mod) * 112341, 1); }"
		"void main() {"
		" gl_FragColor = vec4(rand(gl_FragCoord.x, x), 180, rand(gl_FragCoord.z, z), 1);"
		"}";
	ps = glCreateShader(GL_FRAGMENT_SHADER); //пустой объект шейдера. Фрагментный шейдер
	glShaderSource(ps, 1, &f, 0);//берет исходник шейдера из строки и ассоциирует его с шейдером ps
	glCompileShader(ps);//компилирует шейдер ps
	prog = glCreateProgram();
	glAttachShader(prog, ps);//говорим системе, что шейдеры vertexShaderId и fragmentShaderId будут частями программы prog
	glLinkProgram(prog);// формирует программу из приаттаченных шейдеров
	glUseProgram(prog);//сообщаем системе, что эту программу надо использовать для построения изображения
}

void draw(void) {
	glShadeModel(GL_SMOOTH);
	float MatSpecular[] = { 1.0f, 2.0f, 4.0f, 0.0f };
	float MatShininess = 60.0f;
	float MatEmission[] = { 3.0f, 10.0f, 3.0f, 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatEmission);
	glNormal3f(1, 0, 1); //нормали для освещения сцена
	glColor3f(1.0, 0.9, 0.8);
	glutWireDodecahedron();
	glutWireSphere(5, 8, 8);
	glutSolidSphere(1, 100, 100);
}

void init_l() {
	float light0_diffuse[] = { 1.0, 1.0, 0.9, 1.0 };// устанавливаем диффузный цвет света
	GLfloat light0_position[] = { 1.0, 0.0, 3.0, 1.0 }; // позиция источника света
	GLfloat light0_spot_direction[] = { 0.3, 0.0, -1.0 };
	glClearColor(0.9, 0.8, 0.9, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glColor3f(0.0, 0.0, 0.0);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
	glEnable(GL_LIGHT0); // разрешаем использовать light0
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // диффузный свет
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position); // положение света
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_diffuse);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 18);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 5.0);

	float light1_diffuse[] = { -1.0, 0.5, -1.0, 1.0 };// устанавливаем диффузный цвет света
	GLfloat light1_position[] = { -5.0, -5.0, 4.0, 1.0 }; // позиция источника света
	GLfloat light1_spot_direction[] = { 0.3, 0.0, -1.0 };

	glClearColor(1.0, 0.6, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glColor3f(0.0, 0.0, 0.0);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
	glEnable(GL_LIGHT1); // разрешаем использовать light0
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse); // устанавливаем источнику света light0 диффузный свет, который указали ранее
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position); // устанавливаем положение источника света, указанное ранее
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_diffuse);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 18);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 5.0);
	float light2_diffuse[] = { 0.5, 0.5, 1.0, 1.0 };// устанавливаем диффузный цвет света
	GLfloat light2_position[] = { -10.0, 12.0, 4.0, 1.0 }; // позиция источника света
	GLfloat light2_spot_direction[] = { 0.4, 0.0, -1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glColor3f(0.0, 0.0, 0.0);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
	glEnable(GL_LIGHT2); // разрешаем использовать light0
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse); // устанавливаем источнику света light0 диффузный свет, который указали ранее
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position); // устанавливаем положение источника света, указанное ранее
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_diffuse);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 18);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_spot_direction);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 5.0);
}

GLfloat spin = 0.0;
GLfloat speed = 0.04;

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	init_l();
	glEnable(GL_NORMALIZE);
	gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	glRotatef(spin, 0, 0, 0.01);
	draw();
	spin += speed;
	glutSwapBuffers();
}

void Systemthing(int w, int h) {
	float ratio = w * 1.2 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		eyez += up_val_camera; break;
	case 's':
		eyez -= up_val_camera; break;
	case 'a':
		spin += 1; break;
	case 'd':
		spin -= 1; break;
	case 27:
		exit(0);
		break;
	}
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	srand(time(NULL));
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(200, 170);
	glutCreateWindow("lab8");
	glewInit();
	set_shader();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(Systemthing);
	glutIdleFunc(RenderScene);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}
