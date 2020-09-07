#include <GL/glut.h>
#include <stdlib.h>

GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

int luz = 0;

// Posição de cada luz
GLfloat posLuz[3][4] = {
	{  10, 30,  10, 1 },
	{ -10, 30,  10, 1 },
	{   0, 30, -10, 1 }
};

// Direção de cada luz
GLfloat dirLuz[3][3] = {
	{ 0,-1,0 },
	{ 0,-1,0 },
	{ 0,-1,0 }
};

// Cor difusa de cada luz
GLfloat luzDifusa[3][4] = {
	{ 1,0,0,1 },
	{ 0,1,0,1 },
	{ 0,0,1,1 }
};

// Cor especular de cada luz
GLfloat luzEspecular[3][4] = {
	{ 1,0,0,1 },
	{ 0,1,0,1 },
	{ 0,0,1,1 }
};

// Função responsável pela especificação dos parâmetros de iluminaç¿o
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
 
	// Capacidade de brilho do material
	GLfloat especularidade[4]={0.5,0.5,0.5,1.0}; 
	GLint especMaterial = 90;

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros das fontes de luz
	for(int i=0;i<3;++i)
	{
		glLightfv(GL_LIGHT0+i, GL_AMBIENT, luzAmbiente); 
		glLightfv(GL_LIGHT0+i, GL_DIFFUSE, luzDifusa[i] );
		glLightfv(GL_LIGHT0+i, GL_SPECULAR, luzEspecular[i] );
		glLightfv(GL_LIGHT0+i, GL_POSITION, posLuz[i] );
		glLightfv(GL_LIGHT0+i,GL_SPOT_DIRECTION,dirLuz[i]);
		glLightf(GL_LIGHT0+i,GL_SPOT_CUTOFF,40.0);
		glLightf(GL_LIGHT0+i,GL_SPOT_EXPONENT,10.0);
	}
}

void DesenhaChao(void)
#define TAM 40
#define D 2
{
	// Flags para determinar a cor de cada quadrado
	bool flagx,flagz;
	// Define a normal apontando para cima
	glNormal3f(0,1,0);
	glBegin(GL_QUADS);
	flagx = false;
	// X varia de -TAM a TAM, de D em D
	for(float x=-TAM;x<TAM;x+=D)
	{
		// Flagx determina a cor inicial
		if(flagx) flagz = false;
		else flagz = true;
		// Z varia de -TAM a TAM, de D em D
		for(float z=-TAM;z<TAM;z+=D)
		{
			// Escolhe cor
			if(flagz) glColor3f(0.4,0.9,0.2);
			else glColor3f(0.3,1,1);
			// E desenha o quadrado
			glVertex3f(x,0,z);
			glVertex3f(x+D,0,z);
			glVertex3f(x+D,0,z+D);
			glVertex3f(x,0,z+D);
			flagz=!flagz;
		}

		flagx=!flagx;
	}
	glEnd();
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao();

	// Desabilita a iluminação para desenhar as esferas
	glDisable(GL_LIGHTING);
	for(int i=0;i<3;++i)
	{
		// Desenha "esferas" nas posições das fontes de luz
		glPushMatrix();
		glTranslatef(posLuz[i][0],posLuz[i][1],posLuz[i][2]);
		glColor3f(luzDifusa[i][0],luzDifusa[i][1],luzDifusa[i][2]);
		glutSolidSphere(1,5,5);
		glPopMatrix();
	}
	// Habilita iluminação novamente
	glEnable(GL_LIGHTING);

	// Altera a cor do desenho para branco
	glColor3f(1,1,0);

	// Desenha o teapot e o chão
	// glPushMatrix();
	// glTranslatef(0,7.5,0);
	// glutSolidTeapot(10);
	// glPopMatrix();
	DesenhaChao(); //manter comentado - remoção chão
	
	glColor3f(1,1,1);
	
	glPushMatrix();
	glColor3f(0.6,0.5,0);
	glTranslatef(0,10,0);
	glutSolidTorus(2, 6, 3, 20);
	
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(1,0.2,0.9);
	glTranslatef(20,10,0);
	glutSolidSphere(4, 20, 6);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-20,10,0);
	glColor3f(0,0.2,0.6);
	glRotatef(90, -90, 0, 0);
	glutSolidCone(8, 10, 15, 15);
	glPopMatrix();

	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);
	if(tecla>='0' && tecla<='2') luz = tecla - '0';
}

// Função callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_LEFT:			posLuz[luz][0] -=2;
									break;
		case GLUT_KEY_RIGHT:		posLuz[luz][0] +=2;
									break;
		case GLUT_KEY_UP:			posLuz[luz][1] +=2;
									break;
		case GLUT_KEY_DOWN:			posLuz[luz][1] -=2;
									break;
		case GLUT_KEY_PAGE_UP:		posLuz[luz][2] -=2;
									break;
		case GLUT_KEY_PAGE_DOWN:	posLuz[luz][2] +=2;
									break;
		case GLUT_KEY_HOME:			if(angle>=10)  angle -=5;
									break;
		case GLUT_KEY_END:			if(angle<=150) angle +=5;
									break;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Funç¿o callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void GerenciaMovim(int x, int y)
{
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if(h==0)h=1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 0.8f, 0.1f, 1.0f);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita as fontes de luz
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=45;

	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 30;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 100;
}

// Programa Principal 
int main(void)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho_Trabalho");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interação do usuário
	glutMainLoop();
 
	return 0;
} 
