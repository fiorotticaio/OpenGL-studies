#include "alvo.h"
#include <math.h>

void Alvo::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B) {
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

void Alvo::DesenhaAlvo(GLfloat x, GLfloat y) {
    glPushMatrix();
    
    glTranslatef(x, y, 0); // Colocando o sistema de coordenadas no centro do alvo
    
    switch (gColor) {
        case 0:
            DesenhaCirc(radiusAlvo, 1.0, 0.0, 0.0);
            break;
        case 1:
            DesenhaCirc(radiusAlvo, 0.0, 1.0, 0.0);
            break;
        case 2:
            DesenhaCirc(radiusAlvo, 0.0, 0.0, 1.0);
            break;
    }

    glPopMatrix();
}

void Alvo::Recria(GLfloat x, GLfloat y) {
    // Atualizar a posição do alvo e incrementar a cor gColor para o próximo valor possível entre (0, 1 e 2)
    gX = x;
    gY = y;
    gColor = (gColor + 1) % 3;
}

bool Alvo::Atingido(Tiro *tiro) {
    // Deve retornar verdadeiro se o tiro estiver dentro do raio do alvo radiusAlvo
    GLfloat x, y;
    tiro->GetPos(x, y);
    return sqrt(pow(x - gX, 2) + pow(y - gY, 2)) < radiusAlvo;
}
