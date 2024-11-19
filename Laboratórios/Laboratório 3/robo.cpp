#include "robo.h"
#include <math.h>

void Robo::DesenhaRect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B) {
    glColor3f(R, G, B);

    // A origem deve ser o centro da base do retângulo
    glBegin(GL_POLYGON);
        glVertex2f(-width/2, 0);
        glVertex2f(width/2, 0);
        glVertex2f(width/2, height);
        glVertex2f(-width/2, height);
    glEnd();
}

void Robo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {

}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B) {

}

void Robo::DesenhaBraco(GLfloat x, GLfloat y, GLfloat theta1, GLfloat theta2, GLfloat theta3) {
    glPushMatrix();

    // Desenhar a primeira haste
    glTranslatef(x, y, 0); // Colocando o sistema de coordenadas na base da primeira haste
    glRotatef(theta1, 0, 0, 1); // Rotaciona a base
    DesenhaRect(paddleHeight, paddleWidth, 0.0, 0.0, 1.0); // Desenha a haste em si (retângulo)

    // Desenhar a segunda haste
    glTranslatef(0, paddleHeight, 0); // Colocando o sistema de coordenadas na base da segunda haste
    glRotatef(theta2, 0, 0, 1); // Rotaciona a base
    DesenhaRect(paddleHeight, paddleWidth, 1.0, 1.0, 0.0); // Desenha a haste em si (retângulo)

    // Desenhar a terceira haste
    glTranslatef(0, paddleHeight, 0); // Colocando o sistema de coordenadas na base da terceira haste
    glRotatef(theta3, 0, 0, 1); // Rotaciona a base
    DesenhaRect(paddleHeight, paddleWidth, 0.0, 1.0, 0.0); // Desenha a haste em si (retângulo)

    glPopMatrix();
}

void Robo::DesenhaRobo(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat theta1, GLfloat theta2, GLfloat theta3) {
    glPushMatrix();

    // Desenha a base (corpo)
    glTranslatef(x, y, 0);    
    DesenhaRect(baseHeight, baseWidth, 1.0, 0.0, 0.0);

    // Desenha o braço
    DesenhaBraco(0, baseHeight, theta1, theta2, theta3);


    glPopMatrix();
}

void Robo::RodaBraco1(GLfloat inc) {
    gTheta1 += inc;
}

void Robo::RodaBraco2(GLfloat inc) {
    gTheta2 += inc;
}

void Robo::RodaBraco3(GLfloat inc) {
    gTheta3 += inc;
}

void Robo::MoveEmX(GLfloat dx) {
    gX += dx;
}

//Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut){

}

Tiro* Robo::Atira() {

}
