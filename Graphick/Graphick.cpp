#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int selectedFunction = 1;
float xMin = -20.0f, xMax = 20.0f, yMin = -15.0f, yMax = 15.0f;

float function(float x) {
    switch (selectedFunction) {
    case 1: return sin(x);
    case 2: return cos(x) * sin(2 * x);
    case 3: return cos(x) * x * x;
    case 4: return log(x) + sin(x);
    case 5: return exp(x) + sin(x);
    case 6: return sqrt(x) * tan(x) * sin(2 * x);
    default: return sin(x);
    }
}

float derivative(float x) {
    float h = 0.001f;
    return (function(x + h) - function(x - h)) / (2 * h);
}

vector<float> findExtrema() {
    vector<float> extrema;
    for (float x = xMin; x <= xMax; x += 0.01f) {
        if (derivative(x - 0.01f) * derivative(x + 0.01f) < 0) {
            extrema.push_back(x);
        }
    }
    return extrema;
}

void drawAxes() {
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(xMin, 0);
    glVertex2f(xMax, 0);
    glVertex2f(0, yMin);
    glVertex2f(0, yMax);
    glEnd();

    for (int i = xMin; i <= xMax; ++i) {
        glRasterPos2f(i, -0.5f);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0' + abs(i % 10));
    }
    for (int i = yMin; i <= yMax; ++i) {
        glRasterPos2f(-0.5f, i);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0' + abs(i % 10));
    }
}

void drawGraph() {
    glBegin(GL_LINE_STRIP);
    for (float x = xMin; x <= xMax; x += 0.01f) {
        float y = function(x);
        if (y < yMin || y > yMax) continue;
        glColor3f(derivative(x) > 0 ? 0 : 1, derivative(x) > 0 ? 1 : 0, 0);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawExtrema() {
    vector<float> extrema = findExtrema();
    glColor3f(0, 0, 1);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (float x : extrema) {
        float y = function(x);
        if (y < yMin || y > yMax) continue;
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawAxes();
    drawGraph();
    drawExtrema();
    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xMin, xMax, yMin, yMax);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    cout << "1: y = sin(x)\n";
    cout << "2: y = cos(x)*sin(2*x)\n";
    cout << "3: y = cos(x)*x*x\n";
    cout << "4: y = log(x)+sin(x)\n";
    cout << "5: y = exp(x)+sin(x)\n";
    cout << "6: y = sqrt(x)*tan(x)*sin(2*x)\n";
    cin >> selectedFunction;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Graph Plotter");
    glClearColor(0, 0, 0, 1);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}