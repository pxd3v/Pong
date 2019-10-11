#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL.h>
#include <stdio.h>

float person1y = -20.0, person2y = -20.0, bolay = -3.0, bolax = -3.0; //posição y inicial da base barra da esquerda, posição y inicial da base barra da direita, posição y inicial da base da bola, posição x inicial da esquerda da bola
float bolaL = 6, bolah = 6, Vxbola = 2, Vybola = 1.3; //largura da bola, altura da bola, velocidade x da bola, velocidade y da bola
bool statusbola = true; //variavel booleana para ver se a bola esta em movimento
float limiteD = 144.0, limiteE = 150; // limite da tela na direita e limite da tela na esquerda
float person1x = -135.0, person1h = 40.0, person1L = 10; //posição x da esquerda da barra da esquerda, altura da barra da esquerda, largura da barra da esquerda
float person2x = 125.0, person2h = 40.0, person2L = 10; // posição x da esquerda da barra da direita, altura da barra da direita, largura da barra da direita
float vetor1[28]; //vetor de animação da barra esquerda
float vetor2[28]; //vetor de animação da barra direita
float vetor3[28]; //vetor de animação da bola
int i=0;
GLuint textura; //sprite das barras
GLuint texturaBola; //sprite da bola
GLuint texturaFundo; //imagem de fundo

//preenche os vetores de animação com coordenada.
void montarVetor()
{
    for(int j=0; j<7; j++)
    {
        vetor1[j]=0;
        vetor2[j]=0.25;
        vetor3[j]=0;

    }
    for(int j=7; j<14; j++)
    {
        vetor1[j]=0.25;
        vetor2[j]=0.50;
        vetor3[j]=0.25;
    }
    for(int j=14; j<21; j++)
    {
        vetor1[j]=0.50;
        vetor2[j]=0.75;
        vetor3[j]=0.50;
    }
    for(int j=21; j<28; j++)
    {
        vetor1[j]=0.75;
        vetor2[j]=0;
        vetor3[j]=0.75;
    }
}

//carrega textura
GLuint carregaTextura(char* arquivo)
{
    GLuint idTextura = SOIL_load_OGL_texture(
        arquivo,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (idTextura == 0)
    {
        printf("erro carregando a textura: '%s'\n", SOIL_last_result());
    }

    return idTextura;
}

//inicializa variaveis de textura
void inicializa()
{
    glClearColor(1, 1, 1, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textura = carregaTextura("sprite.png");
    texturaBola = carregaTextura("bola.png");
    texturaFundo = carregaTextura("fundo.png");
}
void desenhaFundo ()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaFundo);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 0); glVertex3f(-150, -100, -0.1);
    glTexCoord2f(1, 0); glVertex3f(150, -100, -0.1);
    glTexCoord2f(1, 1); glVertex3f(150, 100, -0.1);
    glTexCoord2f(0, 1); glVertex3f(-150, 100, -0.1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
//desenha barra da esquerda
void desenhaPerson1 ()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_POLYGON);
    glTexCoord2f(vetor1[i], 0); glVertex3f(person1x, person1y, 0.0);
    glTexCoord2f(vetor1[i] + 0.25, 0); glVertex3f(person1x+person1L, person1y, 0.0);
    glTexCoord2f(vetor1[i] + 0.25, 1); glVertex3f(person1x+person1L, person1y+person1h, 0.0);
    glTexCoord2f(vetor1[i], 1); glVertex3f(person1x, person1y+person1h, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//função que desenha a barra da direita
void desenhaPerson2 ()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);
    glBegin(GL_POLYGON);
    glTexCoord2f(vetor2[i], 0); glVertex3f(person2x, person2y, 0.0);
    glTexCoord2f(vetor2[i] + 0.25, 0); glVertex3f(person2x+person2L, person2y, 0.0);
    glTexCoord2f(vetor2[i] + 0.25, 1); glVertex3f(person2x+person2L, person2y+person2h, 0.0);
    glTexCoord2f(vetor2[i], 1); glVertex3f(person2x, person2y+person2h, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//adiciona a velocidade a posição da bola
void movBola()
{
   bolax += Vxbola;
   bolay += Vybola;
}

//verifica se a bola esta tocando as extremidades para poder mudar as velocidades
void limiteBola()
{
    if (bolay > 93)
    {
            Vybola = -Vybola;
    }
    if (bolay < -99)
    {
        Vybola = -Vybola;
    }
    if(bolax > 145)
    {
        Vxbola = -Vxbola;
    }
    if(bolax < -149)
    {
        Vxbola = -Vxbola;
    }
    movBola();
}

//desenha a bola na posição inicial
void desenhaBola()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaBola);
    glBegin(GL_POLYGON);
    glTexCoord2f(vetor3[i], 0); glVertex3f(bolax, bolay, 0.0);
    glTexCoord2f(vetor3[i] + 0.25, 0); glVertex3f(bolax+bolaL, bolay, 0.0);
    glTexCoord2f(vetor3[i] + 0.25, 1); glVertex3f(bolax+bolaL, bolay+bolah, 0.0);
    glTexCoord2f(vetor3[i], 1); glVertex3f(bolax, bolay+bolah, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//verifica se houve colisão com a barra da esquerda
bool colisao1()
{
    if (bolax == person1x + person1L && ((bolay <= person1y + person1h) && (bolay >= person1y)))
    return true;
    else return false;
}

//verifica se houve colisão com a barra da direita
bool colisao2()
{
    if (bolax + bolaL == person2x && ((bolay <= person2y + person2h) &&(bolay >= person2y)))
    return true;
    else return false;
}

//função que chama colisao1 e colisao2 para mudar o sentido do movimento caso seja true
void colisao()
{
    if (colisao1() == true)
    Vxbola = -Vxbola;
    if (colisao2() == true)
    Vxbola = -Vxbola;
}

//verifica se houve ponto
void verificaPonto()
{
    if(bolax < -149)
    {
        statusbola = false;
        bolax = -3.0;
        bolay = -3.0;
    }
    if(bolax > 145)
    {
        statusbola = false;
        bolax = -3.0;
        bolay = -3.0;
    }
}

//função que atualiza o vetor de animação
void animaSprite()
{
    if(i<28)
    {
        i++;
    }else i=0;
}

//função que atualiza o display a 60 fps
void atualizaCena(int tempo)
{
    if(statusbola == true)
    {
    colisao();
    limiteBola();
    verificaPonto();
    }
    animaSprite();
    glutPostRedisplay();
    glutTimerFunc(17, atualizaCena, 1);
}

//função de display
void desenhaMinhaCena()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(0.0, 0.0, 0.0);
    desenhaFundo();
    desenhaPerson1();
    desenhaPerson2();
    desenhaBola();
    glutSwapBuffers();
}

//função setup
void setup()
{
    // define qual é a cor do fundo
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // desenho preenchido vs. contorno
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//callback para o evento "reshape"
void redimensionada(int width, int height)
{
   // left, bottom, right, top
   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-150.0, 150.0, -100.0, 100.0, -1.0, 1.0); // janela indo de -150(esquerda) a 150, e de -100(embaixo) a 100

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

//callback de "keyboard"
void teclaPressionada(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:      // Tecla "ESC"
        exit(0);  // Sai da aplicação
        break;
    //sobe player1
    case 'w':
        if(person1y < 56) // para a barra não sair pra cima
        {
        person1y = person1y + 9;
        break;
        }else
        break;
    //desce player1
    case 's':
        if(person1y > -96) // para a barra não sair pra baixo
        {
        person1y = person1y - 9;
        break;
        }else
        break;
    //sobe player2
    case 'o':
        if(person2y < 56) // para a barra não sair pra cima
        {
        person2y = person2y + 9;
        break;
        }else
        break;
    //desce player2
    case 'l':
        if(person2y > -96) // para a barra não sair pra baixo
        {
        person2y = person2y - 9;
        break;
        }else
        break;
    //Pausa e despausa a bola
    case 'p':
        if(statusbola == false)
        statusbola = true;
        else statusbola = false;
        break;
    default:
        break;
    }
}

// Função principal
int main(int argc, char** argv)
{
    montarVetor();
   glutInit(&argc, argv);

   glutInitContextVersion(1, 1);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(750, 500);
   glutInitWindowPosition(150, 50);

   glutCreateWindow("Ping Phong");


   // Registra callbacks para eventos
   glutDisplayFunc(desenhaMinhaCena);
   glutReshapeFunc(redimensionada);
   glutKeyboardFunc(teclaPressionada);
   inicializa();
    if(statusbola == true)
    {
   glutTimerFunc(17, atualizaCena, 1);
    }
   // Configura valor inicial de algumas
   // variáveis de estado do OpenGL
   setup();
   glutMainLoop();
   return 0;
}
