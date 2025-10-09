#include <iostream>
#include <math.h>
#include <stdarg.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>


int Angle = 10.0;

//координаты поверхности
GLfloat ctrlpoints[4][4][3] = {
{{-4, 2.0, -4.5},  {-0.5, 2.0,-4.5 }, {0.5, 2.0, -4.5 },   {3.5, 2.0,-4.5}},
{{-3.5, 1.5, -0.5},  {-0.5, 1.5, -0.5 }, {0.5, 2.5, -0.5}, {3.5, 1.5,-0.5}},
{{-3.5, 1.0,  0.5},  {-0.5, 1.0, 0.5 }, {0.5, 2.0,  0.5 },   {3.5, 1.0, 0.5}},
{{-3.5, -1.5,  4.5},  {-0.5, -1.5, 4.5 }, {0.5, -1.5,  4.5 },   {3.5, -1.5, 4.5}}
};

GLfloat m[] = { -15, -30, -20, -10 };

/* параметры:   m – коэффициенты уравнения плоскости
        lpos0 – координаты источника света
   возвращает: matrix – результирующая матрица */
void shadowmatrix(GLfloat matrix[4][4], GLfloat m[4], GLfloat lpos0[4]) {
    GLfloat dot;

    dot = m[0] * lpos0[0] +
        m[1] * lpos0[1] +
        m[2] * lpos0[2] +
        m[3] * lpos0[3];

    matrix[0][0] = dot - lpos0[0] * m[0];
    matrix[1][0] = 0.f - lpos0[0] * m[1];
    matrix[2][0] = 0.f - lpos0[0] * m[2];
    matrix[3][0] = 0.f - lpos0[0] * m[3];

    matrix[0][1] = 0.f - lpos0[1] * m[0];
    matrix[1][1] = dot - lpos0[1] * m[1];
    matrix[2][1] = 0.f - lpos0[1] * m[2];
    matrix[3][1] = 0.f - lpos0[1] * m[3];

    matrix[0][2] = 0.f - lpos0[2] * m[0];
    matrix[1][2] = 0.f - lpos0[2] * m[1];
    matrix[2][2] = dot - lpos0[2] * m[2];
    matrix[3][2] = 0.f - lpos0[2] * m[3];

    matrix[0][3] = 0.f - lpos0[3] * m[0];
    matrix[1][3] = 0.f - lpos0[3] * m[1];
    matrix[2][3] = 0.f - lpos0[3] * m[2];
    matrix[3][3] = dot - lpos0[3] * m[3];

}

//для работы с поверхностью 
void initMap(void) {
    glColor3f(1, 1, 1);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(2, 0.0, 2.0, 2, 0.0, 2.0);
}

// инициализация
void init(void) {
    // рассчет освещения
    glEnable(GL_LIGHTING);
    // двухсторонний расчет освещения
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    initMap();
}
void changeSize(int w, int h) {
    // предотвращение деления на ноль
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    // используем матрицу проекции
    glMatrixMode(GL_PROJECTION);
    // обнуляем матрицу
    glLoadIdentity();
    // установить корректную перспективу
    gluPerspective(4.5f, ratio, 0.1f, 1.0f);
    // вернуться к матрице проекции
    glMatrixMode(GL_MODELVIEW);
}

// обработка событий клавиш
void Keyboard(unsigned char key, int x, int y) {
    if (key == 'q') { exit(0); }
    else if (key == 'x') { Angle++; }
    else if (key == 't') { Angle--; }
}

void Reshape(GLint w, GLint h) {
    // glClearColor(1.0, 0.5, 0.0, 1.0); //цвет фона 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0); // приблизить/отдалить
    glMatrixMode(GL_MODELVIEW);
}

float ambient[] = { 0.4, 0.4, 0.4, 1.0 }; //рассеянный свет
float spec[] = { 1.0, 1.0, 1.0, 1.0 }; //отраженный (зеркальный)
float specref[] = { 0.4, 0.4, 1.0, 1.0 }; //отраженный
float lpos0[] = { -5, -5, -5, 0 }; //позиция источника света
float black[] = { 0.0, 0.0, 0.0, 1.0 }; //задание цвета

void renderScene(void) {
    glScalef(1.5, 1.5, 1.5); //увеличиваем поверхность
    //задание параметров nurbe поверхности
    int i, j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); //фигуры не просвечиваются
    glPushMatrix();
    glRotatef(50.0, 0.5, 1.0, 0.0);
    for (j = 0; j <= 500; j++) {
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 500; i++)
            glEvalCoord2f((GLfloat)i / 500.0, (GLfloat)j / 500.0);
        glEnd();
        glBegin(GL_LINE_STRIP);
        for (i = 0; i <= 500; i++)
            glEvalCoord2f((GLfloat)j / 500.0, (GLfloat)i / 500.0);
        glEnd();
    }
    glPopMatrix();

    // обнулить трансформацию
    glLoadIdentity();

    // установить камеру
    gluLookAt(-1.0f, 0.0f, -2.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f);

    // установка источников света
    // несколько источников света
    // свойства материала
    glPushMatrix();

    GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

    GLfloat light5_diffuse[] = { 0.5, 0, 1 }; //цвет источника света,который отвечает за весь цвет шариков и поверхности
    glEnable(GL_LIGHT5);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black); //глобальное освещение
    glLightfv(GL_LIGHT5, GL_AMBIENT, ambient); //зеркальное освещение
    glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse); //глобальное фоновое освещение  
    glLightfv(GL_LIGHT5, GL_POSITION, lpos0); //вершинное освещение
    glLightfv(GL_LIGHT5, GL_SPECULAR, spec); //слабая подсветка белым цветом

    GLfloat matrix[4][4]; //объявляем матрицу
    shadowmatrix(matrix, m, lpos0); //подключаем ф-ю матрицы для тени

    /* Делаем тени полупрозрачными с использованием смешения цветов(blending) */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);
    glColor4f(0.0, 0.0, 0.0, 0.5);
    glPushMatrix();
    /* Проецируем тень */
    glMultMatrixf(*matrix);
    /* Визуализируем сцену в проекции */
    //объекты
    glColor3f(0.1, 0.1, 0.1); //можно цвет тени поменять
    glRotatef(Angle, 0.0, 1.0, 1.0);
    glTranslatef(0.0, -5.0, 0.0);
    glutSolidSphere(0.5, 50, 50);

    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(-3.0, 0.0, -2.0);
    glutSolidSphere(1.0, 100, 100);

    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(5.0, 1.0, -0.3);
    glutSolidIcosahedron();

    glPopMatrix();
    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);

    //
    glColor3f(0.1, 0.1, 0.1);
    glRotatef(Angle, 0.0, 1.0, 1.0);
    glTranslatef(0.0, -5.0, 0.0);
    glColor3d(0.5, 1, 0);
    glutSolidSphere(0.5, 50, 50);

    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(-3.0, 0.0, -2.0);
    glutSolidSphere(1.0, 100, 100);

    glRotatef(90.0, 1.0, 0.0, 0.0);
    glTranslatef(5.0, 1.0, -0.3);
    glutSolidIcosahedron();

    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 700);
    glutCreateWindow("шарики");
    glutDisplayFunc(renderScene);

    // регистрация
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutReshapeFunc(Reshape);
    init();

    // функция работы с клавиатурой
    glutKeyboardFunc(Keyboard);
    glutMainLoop();

    return 1;
}