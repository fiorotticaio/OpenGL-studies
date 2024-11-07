#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <cmath>
#define TAMANHO_JANELA 500

//Pontos do triangulo
float pRx = 0.1;
float pRy = 0.1;
float pGx = 0.9;
float pGy = 0.1;
float pBx = 0.5;
float pBy = 0.9;

//Controle dos arrastes
int draggingPointR = 0, draggingPointG = 0, draggingPointB = 0, choosingColor = 0;

//Cor
float gR = 0., gG = 0., gB = 0.;

//Ponto do clique da cor
float pCliqueX = 0, pCliqueY = 0;
//Pronto do clique projetado
float pProjX = 0, pProjY = 0;

        
void display(void)
{
   //Define a cor do fundo
   glClearColor (gR, gG, gB, 0.0);

   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT);

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glColor3f (1.0, 0.0, 0.0);
      glVertex3f (pRx, pRy, 0.0);
      glColor3f (0.0, 1.0, 0.0);
      glVertex3f (pGx, pGy, 0.0);
      glColor3f (0.0, 0.0, 1.0);
      glVertex3f (pBx, pBy, 0.0);
   glEnd();

   /* Desenha o ponto de clique. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
        glVertex3f(pCliqueX, pCliqueY, 0.0);
   glEnd();

   /* Desenha o ponto projetado. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_POINTS);
        glVertex3f(pProjX, pProjY, 0.0);
   glEnd();
   
   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void init (void) 
{
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* inicializar sistema de visualizacao */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void motion(int x, int y){
    //Corrige a posicao do mouse para a posicao da janela de visualizacao
    y = TAMANHO_JANELA - y;
    GLfloat fX = (GLfloat)x/TAMANHO_JANELA;
    GLfloat fY = (GLfloat)y/TAMANHO_JANELA;
    
    if (choosingColor){
        //Atualiza posicao do clique
        pCliqueX = fX;
        pCliqueY = fY;

		/**
			COLOQUE SEU CODIGO AQUI
		**/
        
        // Atualizar a posição do ponto projetado
        // Reta formada pelo ponto azul e o ponto clicado
        float a = pBx - pCliqueX;
        printf("a = %f\n", a);
        float b = pBy - pCliqueY;
        printf("b = %f\n", b);

        // Reta formada pelos pontos vermelho e verde
        float c = pGx - pRx;
        printf("c = %f\n", c);
        float d = pGy - pRy;
        printf("d = %f\n", d);

        float det = -a * d + b * c;
        if (det == 0) {
            printf("As retas são paralelas e não se interceptam.\n");
        } else {
            // Solução de um sistema de equações lineares
            float t = ((pRx - pCliqueX) * (-d) + (pRy - pCliqueY) * c) / det;
            float s = (a * (pRy - pCliqueY) - b * (pRx - pCliqueX)) / det;

            pProjX = pCliqueX + t * a;
            pProjY = pCliqueY + t * b;

            /* Ou
            pProjX = pRx + s * c;
            pProjY = pRy + s * d;
            */

            printf("Ponto de interseção: (%f, %f)\n", pProjX, pProjY);

            // Calculando a cor de fundo a partir da contribuição das três primárias
            // Reta que vai do ponto clicado ao ponto azul
            float e = pBx - pCliqueX;
            float f = pBy - pCliqueY;
            // Módulo do vetor
            float mod = sqrt(e * e + f * f);

            // Reta que vai do ponto projetado ao azul
            float g = pBx - pProjX;
            float h = pBy - pProjY;
            // Módulo do vetor
            float mod2 = sqrt(g * g + h * h);

            gB = 1 - (mod/mod2);

            // Reta que vai do ponto projetado ao ponto vermelho
            float i = pRx - pProjX;
            float j = pRy - pProjY;
            // Módulo do vetor
            float mod3 = sqrt(i * i + j * j);

            // Reta que vai do ponto verde ao ponto vermelho
            float k = pGx - pRx;
            float l = pGy - pRy;
            // Módulo do vetor
            float mod4 = sqrt(k * k + l * l);

            gR = (1 - (mod3/mod4)) * (mod/mod2);

            // Reta que vai do ponto projetado ao ponto verde
            float m = pGx - pProjX;
            float n = pGy - pProjY;
            // Módulo do vetor
            float mod5 = sqrt(m * m + n * n);

            // Reta que vai do ponto verde ao ponto vermelho
            float o = pGx - pRx;
            float p = pGy - pRy;
            // Módulo do vetor
            float mod6 = sqrt(o * o + p * p);

            gG = (1 - (mod5/mod6)) * (mod/mod2);

            printf("gR %f, gG %f, gB %f\n", gR, gG, gB);
        }

    } else if (draggingPointR){
        pRx = (GLfloat)x/TAMANHO_JANELA;
        pRy = (GLfloat)y/TAMANHO_JANELA;
    } else if (draggingPointG){
        pGx = (GLfloat)x/TAMANHO_JANELA;
        pGy = (GLfloat)y/TAMANHO_JANELA;
    } else if (draggingPointB){
        pBx = (GLfloat)x/TAMANHO_JANELA;
        pBy = (GLfloat)y/TAMANHO_JANELA;
    }
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
    //Corrige a posicao do mouse para a posicao da janela de visualizacao
    GLfloat fX = (GLfloat)x/TAMANHO_JANELA;
    GLfloat fY = (GLfloat)(TAMANHO_JANELA - y)/TAMANHO_JANELA;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        choosingColor = 1;
    }else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if (    (pRx-fX)*(pRx-fX) +
                (pRy-fY)*(pRy-fY) < 
                    (30.0/TAMANHO_JANELA)*(30.0/TAMANHO_JANELA) ){
            draggingPointR = 1;
        } else if (     (pGx-fX)*(pGx-fX) +
                        (pGy-fY)*(pGy-fY) < 
                            (30.0/TAMANHO_JANELA)*(30.0/TAMANHO_JANELA) ){
            draggingPointG = 1;
        } else if (     (pBx-fX)*(pBx-fX) +
                        (pBy-fY)*(pBy-fY) < 
                            (30.0/TAMANHO_JANELA)*(30.0/TAMANHO_JANELA) ){
            draggingPointB = 1;
        }

    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        choosingColor = 0;
    }else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
        draggingPointR = draggingPointG = draggingPointB = 0;
    }
    
    motion(x, y);
}
    
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Cores");
    init ();
    glutDisplayFunc(display); 
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
