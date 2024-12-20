#ifndef TIRO_H
#define	TIRO_H
#include <GL/gl.h>
#include <GL/glu.h>

#define radiusTiro 5

class Tiro {
    GLfloat gXInit; 
    GLfloat gYInit; 
    GLfloat gX; 
    GLfloat gY; 
    GLfloat gDirectionAng;
    GLfloat gVel;
    GLfloat direcaoTiro[2]; 
private:
    void DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void DesenhaTiro(GLfloat x, GLfloat y);
public:
    Tiro(GLfloat x, GLfloat y, GLfloat directionAng, GLfloat* d){
        gXInit = x; 
        gYInit = y; 
        gX = x; 
        gY = y; 
        gDirectionAng = directionAng; 
        gVel = 1;
        direcaoTiro[0] = d[0];
        direcaoTiro[1] = d[1];
    };
    void Desenha(){ 
        DesenhaTiro(gX, gY);
    };
    void Move(GLdouble timeDiference);
    bool Valido();
    void GetPos(GLfloat &xOut, GLfloat &yOut){
        xOut = gX;
        yOut = gY;
    };
};

#endif	/* TIRO_H */

