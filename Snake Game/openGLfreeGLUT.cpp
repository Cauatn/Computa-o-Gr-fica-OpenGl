#include <GL/glut.h>
#include <GL/gl.h> 
#include <stdio.h>
#include <time.h>

constexpr unsigned int COLUMNS = 40;
constexpr unsigned int ROWS = 40;

constexpr unsigned int POS_INICIAL = 20;

constexpr unsigned int VEL_PADRAO = 10;
constexpr unsigned int VEL_MAXIMA = 35;

constexpr int UP = 1;
constexpr int DOWN = -1;
constexpr int RIGHT = 2;
constexpr int LEFT = -2;

constexpr unsigned int MAX_SIZE_COBRA = 128;

constexpr unsigned int MULT_PADRAO = 100;

// Variaveis do jogo
bool jogoPausado = false;
bool fimDeJogo = false;
bool comecaJogo = false;

float vel_jogo = VEL_PADRAO;
float velBackUp = 0;
float vel_increnento = 0.7;

bool comida = true;
int xComida, yComida;

int tamanho_cobra = 3;
int score = 0;
int multiplicador = MULT_PADRAO;

int gridX, gridY;

short direcaoCobra = RIGHT;
int lastDirCobra = 0;
int posX[MAX_SIZE_COBRA] = { POS_INICIAL };
int posY[MAX_SIZE_COBRA] = { POS_INICIAL };

// declarando as funcoes que vao ser utilizadas no jogo
void Inicializa(); // incializa o grid do jogo
void Janela(int);
void MenuPrincipal();
void InitGameValues(); // inciia os valores padroes do jogo

void ReshapeCallback(int, int);
void GameLoop(int); // loop principal do jogo, o calculo da atualizacao esta dentro dele

void InitGrid(int, int); // incializa um grid baseado em altura e largura
void Render(); // render principal do jogo
void DesenhaBorda(); // desenhar a borda do jogo
void DesenharCobra(); // desenha o personagem cobra do jogo
void AtualziarCobra(); // atualiza os valroes da cobra: tamanho posicao e tambem checa as colisoes da cobra com a parede e com a comida
void DesenhaComida(); // desenhar comida
void RenderScore(); // desenha o score na tels
void DesenharPause(); // desenha o pause do jogo na tela
void DesenhaTeclas(int, int, GLfloat, GLfloat, GLfloat); // mostra as teclas na tela de acordo com um e y e as cores
void IrParaMenu(); // volta para o menu

void UpdateMultiplicador(); // atualiza o multiplicador do score

void GameOver(); // finlizar o jogo
void Pausar(); // pausar e despausar o jogo

void TecladoEspecial(int, int, int);
void Teclado(unsigned char, int, int);
void Mouse(int, int, int, int);

void Random(int& x, int& y); // funcao para gerar numero aleatorio
void Unit(int, int);
void RenderBitmapText(float, float, void*, const char*);

/*#########*/

void InitGameValues() {
    comecaJogo = false;
    jogoPausado = false;
    fimDeJogo = false;

    for (size_t i = 0; i < tamanho_cobra; i++) {
        posX[i] = POS_INICIAL;
        posY[i] = POS_INICIAL;
    }

    score = 0;
    multiplicador = MULT_PADRAO;
    tamanho_cobra = 3;
    vel_jogo = VEL_PADRAO;
    direcaoCobra = RIGHT;
    lastDirCobra = 0;
}

void Unit(int x, int y) {
    /* Caso esteja nas bordas */
    if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1)
    {
        glLineWidth(2.0);
        glColor3f(0.0f, 0.0f, 0.0f);
    }

    else
    {
        glLineWidth(1.0);
        glColor3f(0.94f, 0.92f, 0.82f);
    }

    glBegin(GL_LINE_LOOP); //draw closed figure
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

void InitGrid(int x, int y) {
    gridX = x;
    gridY = y;
}

void DesenhaBorda() {
    for (int x = 0; x <= gridX; x++)
    {
        for (int y = 0; y <= gridY; y++)
        {
            Unit(x, y);
        }
    }
}

void Inicializa() { //Seta a cor do fundo
    glClearColor(0.94f, 0.92f, 0.82f, 0.0f);
    InitGrid(COLUMNS, ROWS);
}

void DesenharCobra() {
    for (int i = 0; i < tamanho_cobra; i++)
    {
        if (i == 0)
        {
            glColor3f(0.07f, 0.16f, 0.07f);
        }

        else
        {
            glColor3f(0.19f, 0.34f, 0.17f);
        }
        glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
    }
}

void AtualziarCobra() {
    if (jogoPausado == false) {
        for (int i = tamanho_cobra - 1; i > 0; i--)
        {
            posX[i] = posX[i - 1];
            posY[i] = posY[i - 1];
        }

        if (direcaoCobra == UP)
        {
            posY[0]++;
        }

        if (direcaoCobra == DOWN)
        {
            posY[0]--;
        }

        if (direcaoCobra == RIGHT)
        {
            posX[0]++;
        }

        if (direcaoCobra == LEFT)
        {
            posX[0]--;
        }

        DesenharCobra();

        if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1)
        {
            GameOver();
        }

        if (posX[0] == xComida && posY[0] == yComida)
        {
            score += 1 * multiplicador;
            tamanho_cobra++;
            vel_jogo += vel_increnento;
            if (vel_jogo >= VEL_MAXIMA) {
                vel_jogo = VEL_MAXIMA;
            }
            if (tamanho_cobra > MAX_SIZE_COBRA)
            {
                tamanho_cobra = MAX_SIZE_COBRA;
            }
            /* habilita um novo spawn de comida */
            comida = true;
            multiplicador = MULT_PADRAO;
        }

        /* checa se a cauda encostou na cabeca */
        for (int j = 1; j < tamanho_cobra; j++)
        {
            if (posX[j] == posX[0] && posY[j] == posY[0])
            {
                GameOver();
            }
        }
        //UpdateMultiplicador();
    }
    else {
        DesenharCobra();
    }
}

void Random(int& x, int& y) {
    srand(time(NULL)); // trocando a seed para a funcao rand

    int maxX = gridX - 2, maxY = gridY - 2; //from 0 to 38
    int minn = 1;
    x = minn + rand() % (maxX - minn);
    y = minn + rand() % (maxY - minn);
}

void DesenhaComida() {
    if (comida)
    {
        Random(xComida, yComida);
    }

    comida = false;
    glColor3f(1.0, 0.0, 0.0);

    glRectf(xComida, yComida, xComida + 1, yComida + 1);
}

void DesenharPause() {
    glColor3f(0.07f, 0.16f, 0.07f);
    glBegin(GL_QUADS);

    glVertex2f(5.0f, 30.0f);
    glVertex2f(5.0f, 15.0f);
    glVertex2f(35.0f, 15.0f);
    glVertex2f(35.0f, 30.0f);

    glEnd();

    glColor3f(0.94f, 0.92f, 0.82f);
    const char string[] = "JOGO PAUSADO";
    RenderBitmapText(15, 26, GLUT_BITMAP_TIMES_ROMAN_24, string);

    DesenhaTeclas(18, 24, 0.94f, 0.92f, 0.82f);
}

void RenderScore() {
    float x = 2.0f;
    float y = 37.0f;
    char buffer[200];
    sprintf_s(buffer, sizeof(buffer), "SCORE : %d", score);
    glColor3f(0.07f, 0.16f, 0.07f);
    RenderBitmapText(x, y, GLUT_BITMAP_TIMES_ROMAN_24, buffer);
}

void DesenhaTeclas(int x, int y, GLfloat red, GLfloat green, GLfloat blue) {
    glColor3f(red, green, blue);
    const char string1[] = "TECLAS DO JOGO";
    const char string2[] = "[ 1 ] CIMA >> *W*";
    const char string3[] = "[ 2 ] ESQUERDA >> *A*";
    const char string4[] = "[ 3 ] PAUSAR >> *P*";
    const char string5[] = "[ 4 ] BAIXO >> *S * ";
    const char string6[] = "[ 5 ] DIREITA >> *D * ";
    const char string7[] = "[ 6 ] MENU >> *R*";
    const char string8[] = "[ 7 ] FECHAR JOGO >> *ESC*";
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string1);
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string2);
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string3);
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string4);
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string5);
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string6);
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string7);
    RenderBitmapText(x, y--, GLUT_BITMAP_TIMES_ROMAN_10, string8);
}

void ReshapeCallback(int weight, int hight) {
    glViewport(0, 0, (GLsizei)weight, (GLsizei)hight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

}

void GameLoop(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / vel_jogo, GameLoop, 0); //dispaly fun called 10 times in one sec to know some delay is adde (warning high fps if unknown val)

    UpdateMultiplicador();
}

void UpdateMultiplicador() {
    if (jogoPausado == true || comecaJogo == true || fimDeJogo == true) {
        multiplicador--;
        if (multiplicador <= 1) {
            multiplicador = 1;
        }
    }
    else {

    }
}

void GameOver() {
    printf("Game Over ! :( :(\n");
    printf("SCORE: %d\n", score);
    printf("TAMANHO DA COBRA: %d\n\n", tamanho_cobra);
    fimDeJogo = true;
}

void Pausar() {
    if (lastDirCobra == 0) {
        lastDirCobra = direcaoCobra;
    }

    if (jogoPausado == false) {
        jogoPausado = true;

    }
    else {
        jogoPausado = false;
        direcaoCobra = lastDirCobra;
        lastDirCobra = 0;
    }
}

void RenderBitmapText(float x, float y, void* font, const char* string) {
    glRasterPos2i(x, y);
    while (*string)
    {
        glutBitmapCharacter(font, *string);
        string++;
    }
}

void TecladoEspecial(int key, int x, int y) {

}

void Teclado(unsigned char key, int x, int y) {

    if (key == 32) { // tecla espaço
        comecaJogo = true;
    }
    if (key == 27) { // tecla esc
        exit(0);
    }

    if (key == 'w' && key != 's')
    {
        if (direcaoCobra == DOWN) {
            direcaoCobra = DOWN;
        }
        else {
            direcaoCobra = UP;
        }
    }

    if (key == 's' && key != 'w')
    {
        if (direcaoCobra == UP) {
            direcaoCobra = UP;
        }
        else {
            direcaoCobra = DOWN;
        }
    }

    if (key == 'd' && key != 'a')
    {
        if (direcaoCobra == LEFT) {
            direcaoCobra = LEFT;
        }
        else {
            direcaoCobra = RIGHT;
        }
    }

    if (key == 'a' && key != 'd')
    {
        if (direcaoCobra == RIGHT) {
            direcaoCobra = RIGHT;
        }
        else {
            direcaoCobra = LEFT;
        }
    }

    if (key == 'p') {
        Pausar();
    }

    if (key == 'r') {
        IrParaMenu();
    }
}

void Mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        Pausar();
    }

    glutPostRedisplay();
}

void Janela(int opcao) {
    switch (opcao) {
    case 0:
        comecaJogo = true;
        break;
    case 1:
        glutPositionWindow(250, 200);
        break;
    case 2:
        glutFullScreen();
        break;
    }
    glutPostRedisplay();
}

void MenuPrincipal() {
    float x = 15.3f;
    float y = 35.0f;

    const char texto1[] = "Jogo da Kobraaaaaaaa";
    const char texto2[] = "[ 1 ] APERTE *SPACE* PARA COMECAR O JOGO";
    const char texto3[] = "[ 2 ] APERTE *ESC* PARA FECHAR O JOGO";

    glColor3f(0.07f, 0.16f, 0.07f);
    RenderBitmapText(x, y, GLUT_BITMAP_TIMES_ROMAN_24, texto1);

    x = 7.0f;
    y = 25.0f;

    RenderBitmapText(x, y, GLUT_BITMAP_TIMES_ROMAN_24, texto2);

    y = 20.0f;

    RenderBitmapText(x, y, GLUT_BITMAP_TIMES_ROMAN_24, texto3);

    DesenhaTeclas(32, 10, 0.07f, 0.16f, 0.07f);


    //glutAddMenuEntry("Começa Jogo", 0);
   //glutAddMenuEntry("Tela Cheia", 2);
   //glutAttachMenu(GLUT_LEFT_BUTTON);
}

void IrParaMenu() {
    InitGameValues();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (comecaJogo == true)
    {
        AtualziarCobra();
        DesenhaComida();
        DesenhaBorda();
        if (jogoPausado == true) {
            DesenharPause();
        }
        RenderScore();
    }
    else
    {
        glClearColor(0.94f, 0.92f, 0.82f, 0.0f);
        MenuPrincipal();
    }

    glutSwapBuffers();

    if (fimDeJogo == true)
    {
        IrParaMenu();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(250, 100);
    glutInitWindowSize(780, 520);

    glutCreateWindow("Jogo Cobra");

    glutDisplayFunc(Render);
    glutReshapeFunc(ReshapeCallback);
    glutTimerFunc(0, GameLoop, 0);
    glutSpecialFunc(TecladoEspecial); //keyboard
    glutKeyboardFunc(Teclado);
    //glutMouseFunc(Mouse);

    Inicializa();

    glutMainLoop();
    return 0;
}