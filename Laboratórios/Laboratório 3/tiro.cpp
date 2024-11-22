#include "tiro.h"
#include <math.h>
#define DISTANCIA_MAX 350

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
    // Similar ao DesenhaCirc de Robo, porém com polígonos fechados ao invés de pontos
    glColor3f(R, G, B);

    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 20) {
            GLfloat angle = 2.0f * M_PI * i / 360;
            GLfloat x = radius * cos(angle);
            GLfloat y = radius * sin(angle);   
            glVertex2f(x, y);
        }
    glEnd();
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y) {
    glPushMatrix();
        glTranslatef(x, y, 0); // Colocando o sistema de coordenadas no centro do tiro
        DesenhaCirc(radiusTiro, 1.0, 1.0, 1.0); // Desenha o tiro
    glPopMatrix();
}

void Tiro::Move() {
    gX += gVel * cos(gDirectionAng);
    gY += gVel * sin(gDirectionAng);
}

bool Tiro::Valido() {
    // Verifica se o tiro já percorreu uma distância máxima
    return sqrt(pow(gX - gXInit, 2) + pow(gY - gYInit, 2)) < DISTANCIA_MAX;
}
