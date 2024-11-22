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
    glColor3f(R, G, B);

    glPointSize(4.0);

    glBegin(GL_POINTS);
        for (int i = 0; i < 360; i += 20) {
            GLfloat angle = 2.0f * M_PI * i / 360;
            GLfloat x = radius * cos(angle);
            GLfloat y = radius * sin(angle);   
            glVertex2f(x, y);
        }
    glEnd();
}

void Robo::DesenhaRoda(GLfloat x, GLfloat y, GLfloat thetaWheel, GLfloat R, GLfloat G, GLfloat B) {
    glPushMatrix();
        glTranslatef(x, y, 0); // Colocando o sistema de coordenadas no centro da roda
        glRotatef(thetaWheel, 0, 0, 1); // Rotaciona a roda
        DesenhaCirc(radiusWheel, R, G, B); // Desenha a roda
    glPopMatrix();
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

        // Desenha as rodas
        DesenhaRoda(-baseWidth/2, 0, thetaWheel, 1.0, 1.0, 1.0);
        DesenhaRoda(baseWidth/2, 0, thetaWheel, 1.0, 1.0, 1.0);
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
    gThetaWheel += -(dx / radiusWheel) * 180 / M_PI;
}

// Funcao auxiliar de rotacao
void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut) {
    // Matriz de rotacao
    GLfloat rotMatrix[3][3] = {
        {cos(angle), -sin(angle), 0},
        {sin(angle), cos(angle) , 0},
        {0         , 0          , 1},
    };

    // Vetor de entrada
    GLfloat inVector[3] = {x, y, 1};

    // Vetor de saida
    GLfloat outVector[3] = {0, 0, 0};

    // Multiplicacao de matriz por vetor
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outVector[i] += rotMatrix[i][j] * inVector[j];
        }
    }

    // Atribuindo valores de saida
    xOut = outVector[0];
    yOut = outVector[1];
    printf("xOut = %f, yOut = %f\n", xOut, yOut);
}

// Função auxiliar de translação
void TranslatePoint(GLfloat x, GLfloat y, GLfloat dx, GLfloat dy, GLfloat &xOut, GLfloat &yOut) {
    // Matriz de translação
    GLfloat transMatrix[3][3] = {
        {1, 0, dx},
        {0, 1, dy},
        {0, 0, 1},
    };

    // Vetor de entrada
    GLfloat inVector[3] = {x, y, 1};

    // Vetor de saida
    GLfloat outVector[3] = {0, 0, 0};

    // Multiplicacao de matriz por vetor
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outVector[i] += transMatrix[i][j] * inVector[j];
        }
    }

    // Atribuindo valores de saida
    xOut = outVector[0];
    yOut = outVector[1];
    printf("xOut = %f, yOut = %f\n", xOut, yOut);
}

// Função auxiliar de escala
void ScalePoint(GLfloat x, GLfloat y, GLfloat sx, GLfloat sy, GLfloat &xOut, GLfloat &yOut) {
    // Matriz de escala
    GLfloat scaleMatrix[3][3] = {
        {sx, 0 , 0},
        {0 , sy, 0},
        {0 , 0 , 1},
    };

    // Vetor de entrada
    GLfloat inVector[3] = {x, y, 1};

    // Vetor de saida
    GLfloat outVector[3] = {0, 0, 0};

    // Multiplicacao de matriz por vetor
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            outVector[i] += scaleMatrix[i][j] * inVector[j];
        }
    }

    // Atribuindo valores de saida
    xOut = outVector[0];
    yOut = outVector[1];
    printf("xOut = %f, yOut = %f\n", xOut, yOut);
}

Tiro* Robo::Atira() {
    return NULL;
}


