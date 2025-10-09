
#include <GL/glut.h>
#include<Windows.h>
#include <math.h>
using namespace std;

#define checkImageWidth 192
#define checkImageHeight 192
GLubyte checkImage[checkImageHeight][checkImageWidth][4];
GLuint texName;

GLuint myList;
bool fogFlag = 0;
// задание нурб-поверхности
GLfloat ctrlPoints[4][4][3] = {
    {{-3.5, 1, -4.5}, {-0.5, 1.0, -4.5}, {5.0, 1.0, -4.5}, {3.5, 1.0, -4.5}},
    {{-3.5, 1, -0.5}, {-0.5, -2.0, -0.5}, {5.5, -2.0, -5}, {3.5, 1.0, -0.5}},
    {{-3.5, 1, 0.5}, {-1.5, 2.0, 3.5}, {5.5, 1.0, 3.5},{3.5, 1.0, 3.5} },
    {{-3.5, 1, 4.5}, {-0.5, 2.0, 4.5}, {5.5, 1.0, 4.5}, {3.5, 1.0,4.5}}
};


void figure() {
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texName);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 0.0, 0.0); glTexCoord2f(0, 0);
    glVertex3f(0.0, 0.0, 1.0);  glTexCoord2f(0, 1);
    glVertex3f(0.0, 1.0, 0.0);  glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 1.0); glTexCoord2f(0, 0);
    glVertex3f(1.0, 0.0, 0.0); glTexCoord2f(0, 1);
    glVertex3f(0.0, 1.0, 0.0); glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 0.0, 0.0); glTexCoord2f(0, 0);
    glVertex3f(0.0, -1.0, 0.0); glTexCoord2f(0, 1);
    glVertex3f(0.0, 0.0, 1.0);  glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, 1.0);  glTexCoord2f(0, 0);
    glVertex3f(0.0, -1.0, 0.0); glTexCoord2f(0, 1);
    glVertex3f(1.0, 0.0, 0.0);  glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 0.0, 0.0); glTexCoord2f(0, 0);
    glVertex3f(0.0, 0.0, -1.0); glTexCoord2f(0, 1);
    glVertex3f(0.0, 1.0, 0.0);  glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-1.0, 0.0, 0.0); glTexCoord2f(0, 0);
    glVertex3f(0.0, -1.0, 0.0); glTexCoord2f(0, 1);
    glVertex3f(0.0, 0.0, -1.0); glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.0, -1.0); glTexCoord2f(0, 0);
    glVertex3f(0.0, -1.0, 0.0); glTexCoord2f(0, 1);
    glVertex3f(1.0, 0.0, 0.0);  glTexCoord2f(0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //сохраняет как список
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glVertex3f(2, 0, 0); glTexCoord2f(0, 1);
    glVertex3f(2.5, 0.0, 0.5);  glTexCoord2f(0, 0);
    glVertex3f(2.5, 0.5, 0);  glTexCoord2f(0, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.5, 0, 0.5); glTexCoord2f(0, 1);
    glVertex3f(3, 0, 0); glTexCoord2f(0, 0);
    glVertex3f(2.5, 0.5, 0); glTexCoord2f(0, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2, 0, 0); glTexCoord2f(0, 1);
    glVertex3f(2.5, -0.5, 0); glTexCoord2f(0, 0);
    glVertex3f(2.5, 0, 0.5);  glTexCoord2f(0, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.5, 0, 0.5);  glTexCoord2f(0, 1);
    glVertex3f(2.5, -0.5, 0); glTexCoord2f(0, 0);
    glVertex3f(3, 0, 0);  glTexCoord2f(0, 1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2, 0, 0); glTexCoord2f(0, 0);
    glVertex3f(2.5, 0, -0.5); glTexCoord2f(0, 1);
    glVertex3f(2.5, 0.5, 0);  glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2, 0, 0); glTexCoord2f(0, 0);
    glVertex3f(2.5, -0.5, 0); glTexCoord2f(0, 1);
    glVertex3f(2.5, 0, -0.5); glTexCoord2f(0, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(2.5, 0, -0.5); glTexCoord2f(0, 0);
    glVertex3f(2.5, -0.5, 0); glTexCoord2f(0, 1);
    glVertex3f(3, 0, 0);  glTexCoord2f(0, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

//задается поверхность
void surface() {
    int i, j;
    glPushMatrix();
    glTranslatef(0, -2, 0);
    glColor3f(1, 0, 0);
    for (int j = 0; j <= 30; j++) {
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 100; i++)
            glEvalCoord2f((GLfloat)i / 100.0, (GLfloat)j / 30.0);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 100; i++)
            glEvalCoord2f((GLfloat)j / 30.0, (GLfloat)i / 100.0);
        glEnd();
    }
    glPopMatrix();
    //glFlush();
}

void makeCheckImage() {
    int i, j, c;
    for (i = 0; i < checkImageHeight; i++)
        for (j = 0; j < checkImageWidth; j++) {
            c = (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) * 245;
            checkImage[i][j][0] = (GLubyte)c;
            checkImage[i][j][1] = (GLubyte)c;
            checkImage[i][j][2] = (GLubyte)c;
            checkImage[i][j][3] = (GLubyte)255;
        }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_MAP2_VERTEX_3);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glClearColor(0, 0, 0, 0.0);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlPoints[0][0][0]);
    glMapGrid2f(20, 0, 1, 20, 0, 1);
    glShadeModel(GL_FLAT);

    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

    myList = glGenLists(1);
    glNewList(myList, GL_COMPILE);
    figure();
    glEndList();
}

void light_0() {
    float light0_ambient[] = { -1.0, 0.4, 0.5, 1.0 }; //цвет фонового излучения источника света
    float light0_diffuse[] = { -0.5, 0.5, -0.5 }; // устанавливаем диффузный цвет света
    float light0_direction[] = { -3, -4, -2, 1.0 }; // устанавливаем направление света
    glEnable(GL_LIGHT0); // разрешаем использовать light0
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // устанавливаем источнику света light0 диффузный свет, который указали ранее
    glLightfv(GL_LIGHT0, GL_POSITION, light0_direction); // устанавливаем направление источника света, указанное ранее
}
void light_1() {
    float light1_ambient[] = { -0.4, -1.0, 0.0, 1.0 };
    float light1_diffuse[] = { -0.4, -0.4, 1.0 };
    float light1_direction[] = { 5.0, -4, 7, 1.0 };
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_direction);
}
void light_2() {
    float light2_ambient[] = { 0.0, 0.0, 1.0, 1.0 };
    float light2_diffuse[] = { 0.0, 0.0, 1.0 };
    float light2_direction[] = { -5.0, -4, 3, 1.0 };
    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_direction);
}

void fog() {
    glEnable(GL_FOG);
    GLfloat fogColor[4] = { 0.5,0.5,0.5,1 };
    GLint fogMode = GL_EXP;
    glFogi(GL_FOG_MODE, fogMode);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.2);
    glHint(GL_FOG_HINT, GL_NICEST);
    glFogf(GL_FOG_START, 1);
    glFogf(GL_FOG_END, 5);

}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'x':
        glRotatef(30., 1.0, 0.0, 0.0);
        glutPostRedisplay();
        break;
    case 'y':
        glRotatef(30., 0.0, 1.0, 0.0);
        glutPostRedisplay();
        break;
    case 'z':
        glRotatef(30., 0.0, 0.0, 1.0);
        glutPostRedisplay();
        break;
    case 'i':
        glLoadIdentity();
        gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
        glutPostRedisplay();
        break;
    case 'f':
        fogFlag = (fogFlag + 1) % 2;
        glutPostRedisplay();
        break;
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    light_0();
    light_1();
    light_2();

    if (fogFlag) fog();
    else glDisable(GL_FOG);
    surface();

    glPushMatrix();
    glScalef(0.8, 0.8, 0.8);
    glTranslatef(-2, 0, 0);
    glCallList(myList);
    glPopMatrix();
    glPushMatrix();
    glScalef(0.5, 0.5, 0.5);
    glTranslatef(3.5, 0, 0);
    glCallList(myList);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    Sleep(100);
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (GLfloat)w / (GLfloat)h, 1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv)
{
    //инициализация библиотеки
    glutInit(&argc, argv);

    //установка параметров окна
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//  Запрашиваем окно с поддержкой двойной буферизации, z-буферизации и цветовой схемы True Color
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(350, 150);

    glutCreateWindow("лабораторная работа");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

