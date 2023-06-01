/*
Projeto de : Cauã Tavares Nunes,
Atividade de Hierarquia de Objetos em OpenGl
Créditos de artigo base : http://titan.csit.rmit.edu.au/~e20068/teaching/i3dg&a/2015/hierarchical-modelling.html
*/

/*
 Para usar: 'q' -> move tudo em sentido anti-horario
 'Q' -> move tudo em sentido horario
 'w' -> move tudo em sentido anti-horario
 'W' -> move tudo em sentido horario
 'e' -> move tudo em sentido anti-horario
 'E' -> move tudo em sentido horario
*/

#include <GL/glew.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

GLint ano = 0, dia = 0, rotl = 0;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glRotatef((GLfloat)ano, 0.0, 1.0, 0.0); /* rotaciona todos os objetos */
    glutWireSphere(1.0, 20, 16);   /* desenha o sol */

    glTranslatef(2.0, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glRotatef((GLfloat)dia, 0.0, 1.0, 0.0); /* rotaciono ele "dia" vezes */
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireSphere(0.2, 10, 8);    /* desenha a terra */

    glTranslatef(0.5, 0.0, 0.0); /* movo o terceiro objeto */
    glColor3f(1.0f, 1.0f, 1.0f); 
    glRotatef((GLfloat)rotl, 0.0, 1.0, 0.0); /* rotaciono "rotl" vezes */
    glutWireSphere(0.1, 10, 4); /* desenha a lua */

    glPopMatrix();

    glutSwapBuffers();
}

void alterarVisualizacao(GLsizei w, GLsizei h)
{
    GLsizei altura, largura;

    if (h == 0)
        h = 1;

    altura = h;
    largura = w;

    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (GLfloat)largura / (GLfloat)altura, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 6.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

/* Teclas */
void teclas(unsigned char key, int x, int y)
{

    if (key == 'q')
    {
        ano = (ano + 5) % 360;
        glutPostRedisplay();
    }
    if (key == 'Q')
    {
        ano = (ano - 5) % 360;
        glutPostRedisplay();
    }

    if (key == 'w')
    {
        dia = (dia + 5) % 360;
        glutPostRedisplay();
    }
    if (key == 'W')
    {
        dia = (dia - 5) % 360;
        glutPostRedisplay();
    }

    if (key == 'e')
    {
        rotl = (rotl + 5) % 360;
        glutPostRedisplay();
    }
    if (key == 'E')
    {
        rotl = (rotl - 5) % 360;
        glutPostRedisplay();
    }

    
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100); /* (5,5) */
    glutCreateWindow("Planetario");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutReshapeFunc(alterarVisualizacao);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclas);

    if (glewInit() != GLEW_OK) {
        printf("erro ai iniciar o GLEW.\n");
        return 1;
    }

    glutMainLoop();
    return 0;
}
