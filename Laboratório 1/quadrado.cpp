#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define TAMANHO_JANELA 500

/* Variáveis globais para controlar a posição do polígono */
float gX = 0.0;
float gY = 0.0;

/* Vetor para armazenar o estado de cada tecla (press = 1, ñ-press = 0) */
int keyStatus[256];

void display(void) {
   /* Limpar todos os pixels  */
   glClear (GL_COLOR_BUFFER_BIT); // Inicializa o buffer de cores

   /* Define cor dos vértices com os valores R, G e B variando de 0.0 a 1.0 */
   glColor3f (1.0, 1.0, 1.0);

   /* Desenhar um polígono branco (retângulo) */
   glBegin(GL_POLYGON);
      glVertex3f (0.00 + gX, 0.00 + gY, 0.0);
      glVertex3f (0.50 + gX, 0.00 + gY, 0.0);
      glVertex3f (0.50 + gX, 0.50 + gY, 0.0);
      glVertex3f (0.00 + gX, 0.50 + gY, 0.0);
   glEnd();

   /* Desenhar no frame buffer! */
   glutSwapBuffers(); //Funcao apropriada para janela double buffer
}

void keyPress(unsigned char key, int x, int y) {
   if(key == 'w') {
      keyStatus['w'] = 1;
   } else if(key == 's') {
      keyStatus['s'] = 1;
   } else if(key == 'a') {
      keyStatus['a'] = 1;
   } else if(key == 'd') {
      keyStatus['d'] = 1;
   }

   /* Indicar que a tela deve ser renderizada novamente */
   glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
   if(key == 'w') {
      keyStatus['w'] = 0;
   } else if(key == 's') {
      keyStatus['s'] = 0;
   } else if(key == 'a') {
      keyStatus['a'] = 0;
   } else if(key == 'd') {
      keyStatus['d'] = 0;
   }

   /* Indicar que a tela deve ser renderizada novamente */
   glutPostRedisplay();
}

void idle(void) {
   if(keyStatus['w'] == 1) {
      gY += 0.001;
   } else if(keyStatus['s'] == 1) {
      gY -= 0.001;
   }

   if(keyStatus['a'] == 1) {
      gX -= 0.001;
   } else if(keyStatus['d'] == 1) {
      gX += 0.001;
   }

   /* Indicar que a tela deve ser renderizada novamente */
   glutPostRedisplay();
}

void motion(int x, int y) {
   /* Inverter o y */
   y = TAMANHO_JANELA - y;

   printf("Motion: %d %d\n", x, y);

   /* Fazer gX e gY receberem a posição do clique do mouse */
   gX = (float)x / TAMANHO_JANELA;
   gY = (float)y / TAMANHO_JANELA;

   /* Indicar que a tela deve ser renderizada novamente */
   glutPostRedisplay();
}

void init (void)  {
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* inicializar sistema de visualizacao */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (TAMANHO_JANELA, TAMANHO_JANELA); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("hello world");
   init ();
   glutDisplayFunc(display);

   /* Registrar a função de callback para teclas pressionadas */
   glutKeyboardFunc(keyPress); 

   /* Registrar a função de callback para teclas liberadas */
   glutKeyboardUpFunc(keyUp);

   /* Registrar a função de callback para idle */
   glutIdleFunc(idle);

   /* Registra a função de deslize do mouse clicado */
   glutMotionFunc(motion);

   glutMainLoop();

   return 0;
}
