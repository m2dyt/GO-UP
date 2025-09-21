#include <stdarg.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/freeglut.h>


void initLab1() {
    // Цвет фона (синий)
    glClearColor(0.0, 0.0, 0.3, 0.0);
    glShadeModel(GL_SMOOTH); // сглаживание цветов
}


void initLab3() {
    // Настройка источника света
    static float position[] = { 1.0, 1.0, 1.0, 1.0 };
    static float frontMatShininess[] = { 50.0 }; // блеск лицевой стороны
    static float backMatShininess[] = { 0.0 };   // блеск задней стороны
    static float lmodelTwoside[] = { GL_TRUE };  // двустороннее освещение

    glEnable(GL_DEPTH_TEST);                // проверка глубины
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_LIGHTING);                  // включаем освещение
    glEnable(GL_LIGHT0);                    // включаем нулевой источник света
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMaterialfv(GL_FRONT, GL_SHININESS, frontMatShininess);
    glMaterialfv(GL_BACK, GL_SHININESS, backMatShininess);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodelTwoside);
}

// Функция отображения объектов
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Включаем цвет материала
    glEnable(GL_COLOR_MATERIAL);
    // Работа с 3D-объектами


    // Куб
    glBegin(GL_QUADS);
    // лицевая грань (фиолетовая)
    glColor3f(0.5, 0.3, 0.5);
    glVertex3f(0.3, -0.3, -0.3);
    glVertex3f(0.3, 0.3, -0.3);
    glVertex3f(-0.3, 0.3, -0.3);
    glVertex3f(-0.3, -0.3, -0.3);

    // верхняя грань (белая)
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.3, -0.3, 0.3);
    glVertex3f(0.3, 0.3, 0.3);
    glVertex3f(-0.3, 0.3, 0.3);
    glVertex3f(-0.3, -0.3, 0.3);

    // правая грань (зеленая)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.3, 0.3, 0.3);
    glVertex3f(0.3, 0.3, -0.3);
    glVertex3f(-0.3, 0.3, -0.3);
    glVertex3f(-0.3, 0.3, 0.3);

    // левая грань (оранжевая)
    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(0.3, -0.3, -0.3);
    glVertex3f(0.3, -0.3, 0.3);
    glVertex3f(-0.3, -0.3, 0.3);
    glVertex3f(-0.3, -0.3, -0.3);
    glEnd();

    // Объект со светом — сферический
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.5);
    glColor3f(0.8, 0.0, 0.0); // красный
    glutSolidSphere(0.25, 30, 30);
    glPopMatrix();

    glutSwapBuffers();
}


// Настройка окна и камеры
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        2.0, 2.0, 2.0,  // положение камеры
        0.0, 0.0, 0.0,  // центр сцены
        0.0, 0.0, 1.0   // направление вверх
    );
}

// Главная функция
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Лабораторные работы OpenGL");

    initLab1(); // настройка среды 
    initLab3(); // включение света и материалов 

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
