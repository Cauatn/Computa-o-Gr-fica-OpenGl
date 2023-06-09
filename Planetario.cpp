/*
Projeto de : Cauã Tavares Nunes,
Atividade de Hierarquia de Objetos em OpenGl
Créditos de artigo base : http://titan.csit.rmit.edu.au/~e20068/teaching/i3dg&a/2015/hierarchical-modelling.html
*/

/*
* 
*/

#include <GL/glew.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

GLint is_fullscreen = 0;
GLint sol = 0, mercurio = 30, venus = -24, terra = 0, marte = 18, jupter = -27, saturno = -24, netuno = 9, urano = -40;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glutWireSphere(1.0, 20, 16);   /* desenha o sol */
    glRotatef((GLfloat)sol, 0.0, 1.0, 0.0); /* rotaciona todos os objetos */


    glTranslatef(1.6, 0.0, 0.0); /* movo o eixo do objeto para longe do centro */
    glColor3f(0.63f, 0.63f, 0.76f);
    glutWireSphere(0.1, 10, 8);    /* desenha a mercurio */
    glTranslatef(-1.6, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glRotatef((GLfloat)mercurio, 0.0, 1.0, 0.0); /* rotaciono ele "mercurio" vezes */
    glTranslatef(1.6, 0.0, 0.0); /* retorno o eixo de volta a origem */


    glTranslatef(0.6, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glColor3f(0.8f, 0.32f, 0.0f);
    glutWireSphere(0.3, 10, 8);    /* desenha a venus */
    glTranslatef(-2.2, 0.0, 0.0);
    glRotatef((GLfloat)venus, 0.0, 1.0, 0.0); /* rotaciono tudo "venus" vezes */
    glTranslatef(2.2, 0.0, 0.0); /* retorno o eixo para de volta a origem */


    glTranslatef(0.8, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glColor3f(0.4f, 0.4f, 1.0f);
    glutWireSphere(0.36, 10, 8);    /* desenha a terra */
    glTranslatef(-3.0, 0.0, 0.0);
    glRotatef((GLfloat)terra, 0.0, 1.0, 0.0); /* rotaciono ele "terra" vezes */
    glTranslatef(3.0, 0.0, 0.0);

    glTranslatef(0.7, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glColor3f(0.9f, 0.0f, 0.0f);
    glutWireSphere(0.2, 10, 8);    /* desenha a marte */
    glTranslatef(-3.7, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glRotatef((GLfloat)marte, 0.0, 1.0, 0.0); /* rotaciono ele "dia" vezes */
    glTranslatef(3.7, 0.0, 0.0); /* movo o segundo objeto para longe do centro */

    glTranslatef(1.1, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glColor3f(0.9f, 0.45f, 0.0f);
    glutWireSphere(0.6, 10, 8);    /* desenha a jupter */
    glTranslatef(-4.8, 0.0, 0.0);
    glRotatef((GLfloat)jupter, 0.0, 1.0, 0.0); /* rotaciono ele "dia" vezes */
    glTranslatef(4.8, 0.0, 0.0);

    glTranslatef(1.2, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glColor3f(0.76f, 0.76f, 0.76f);
    glutWireSphere(0.4, 10, 8);    /* desenha a saturno */
    glTranslatef(-6.0, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glRotatef((GLfloat)saturno, 0.0, 1.0, 0.0); /* rotaciono ele "dia" vezes */
    glTranslatef(6.0, 0.0, 0.0); /* movo o segundo objeto para longe do centro */

    glTranslatef(1.0, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glColor3f(0.8f, 1.0f, 1.0f);
    glutWireSphere(0.38, 10, 8);    /* desenha a urano */
    glTranslatef(-7.0, 0.0, 0.0);
    glRotatef((GLfloat)urano, 0.0, 1.0, 0.0); /* rotaciono ele "dia" vezes */
    glTranslatef(7.0, 0.0, 0.0);

    glTranslatef(1.0, 0.0, 0.0); /* movo o segundo objeto para longe do centro */
    glRotatef((GLfloat)netuno, 0.0, 1.0, 0.0); /* rotaciono ele "dia" vezes */
    glColor3f(0.1f, 0.32f, 1.0f);
    glutWireSphere(0.37, 10, 8);    /* desenha a netuno */

    glPopMatrix();

    glutSwapBuffers();
}
void toggle_fullscreen() {
    if (is_fullscreen) {
        glutReshapeWindow(1080, 720);
    }
    else {
        glutFullScreen();
    }
    is_fullscreen = !(is_fullscreen);
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
    gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

/* Teclas */
void teclas(unsigned char key, int x, int y)
{

    if (key == 's')
    {
        sol = (sol + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'S')
    {
        sol = (sol - 3) % 360;
        glutPostRedisplay();
    }

    if (key == 'm')
    {
        mercurio = (mercurio + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'M')
    {
        mercurio = (mercurio - 3) % 360;
        glutPostRedisplay();
    }

    if (key == 'v')
    {
        venus = (venus + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'V')
    {
        venus = (venus - 3) % 360;
        glutPostRedisplay();
    }
    if (key == 't')
    {
        terra = (terra + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'T')
    {
        terra = (terra - 3) % 360;
        glutPostRedisplay();
    }

    if (key == 'k')
    {
        marte = (marte + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'K')
    {
        marte = (marte - 3) % 360;
        glutPostRedisplay();
    }

    if (key == 'j')
    {
        marte = (marte + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'J')
    {
        marte = (marte - 3) % 360;
        glutPostRedisplay();
    }

    if (key == 'e')
    {
        saturno = (saturno + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'E')
    {
        saturno = (saturno - 3) % 360;
        glutPostRedisplay();
    }

    if (key == 'n')
    {
        netuno = (netuno + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'N')
    {
        netuno = (netuno - 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'u')
    {
        urano = (urano + 3) % 360;
        glutPostRedisplay();
    }
    if (key == 'U')
    {
        urano = (urano - 3) % 360;
        glutPostRedisplay();
    }

    if (key == 27)
        toggle_fullscreen();

}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100); /* (5,5) */
    glutCreateWindow("Planetario");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutReshapeFunc(alterarVisualizacao);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclas);

    glutFullScreen();

    if (glewInit() != GLEW_OK) {
        printf("erro ai iniciar o GLEW.\n");
        return 1;
    }

    glutMainLoop();
    return 0;
}
