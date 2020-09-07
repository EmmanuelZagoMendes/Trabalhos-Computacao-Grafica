//===========================================================================================
//||																					   ||
//||			                         JOGO DE XADREZ									   ||
//|| 																					   ||
//|| ***************Apenas o Primeiro Peão Azul move-se pra frente e trás;***************  ||
//||						 (MOVER USANDO AS DUAS SETAS DIRECIONAIS)                      ||
//||  ********As luzes estão bem acima do XADREZ para gerar reflexo nas peças********      ||
//|| 						   O REI BRANCO ESTÁ TRANSPARENTE 						   ||
//||																					   ||
//===========================================================================================

#include <GL/glut.h>
#include <stdlib.h>
GLfloat Tx = 0;
GLfloat Ty = 0;
// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Luz selecionada
int luz = 0;

// Posição de cada luz
GLfloat posLuz[4][4] = {
	{ 0, 120, 0, 1 },
	{-40, 120, 0, 1 },
	{ 40, 120, 0, 1 },
	{ 70, 120, 0, 1 }		
};

// Direção de cada luz
GLfloat dirLuz[4][3] = {
	{ 0,-1,0 },
	{ 0,-1,0 },
	{ 0,-1,0 },
	{ 0,-1,0 }
};

// Cor difusa de cada luz
GLfloat luzDifusa[4][4] = {
	{ 1,0,0,1 },
	{ 0,1,0,1 },
	{ 0,0,1,1 },
	{ 1,1,0,1 }
};

// Cor especular de cada luz
GLfloat luzEspecular[4][4] = {
	{ 1,0,0,1 },
	{ 0,1,0,1 },
	{ 0,0,1,1 },
	{ 0,1,1,1 }
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
	for(int i=0;i<4;++i)
	{
		glLightfv(GL_LIGHT0+i, GL_AMBIENT, luzAmbiente); 
		glLightfv(GL_LIGHT0+i, GL_DIFFUSE, luzDifusa[i]);
		glLightfv(GL_LIGHT0+i, GL_SPECULAR, luzEspecular[i]);
		glLightfv(GL_LIGHT0+i, GL_POSITION, posLuz[i]);
		glLightfv(GL_LIGHT0+i,GL_SPOT_DIRECTION,dirLuz[i]);
		glLightf(GL_LIGHT0+i,GL_SPOT_CUTOFF,40.0);
		glLightf(GL_LIGHT0+i,GL_SPOT_EXPONENT,10.0);
	}
}

// Função para desenhar um "chão" no ambiente
void DesenhaChao(void)
#define TAM 40
#define D 10

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
			if(flagz) glColor3f(0.4,0.4,0.4);
			else glColor3f(1,1,1);
			// E desenha o quadrado
			glVertex3f(x,0,z);
			glVertex3f(x+D,0,z);
			glVertex3f(x+D,0,z+D);
			glVertex3f(x,0,z+D);
			// Alterna cor
			flagz=!flagz;
		}
		
		// A cada coluna, alterna cor inicial
		flagx=!flagx;
	}

	glEnd();
}

void Desenha_Peao1(void){
// Base Inferior do Peão nº1	   	   	
		glPushMatrix();
        glTranslatef(25, 0, 35);//X move pelo tabuleiro, Y tamanho do Cone para baixo e Z move na vertical pelo tabuleiro
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº1
        glPushMatrix();
        glTranslatef(25, 5, 35);
        glColor3f(0, 0, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
	
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
	
	for(int i=0;i<4;++i)
	{
		// Desenha "esferas" nas posições das fontes de luz
		glPushMatrix();
		glTranslatef(posLuz[i][0],posLuz[i][1],posLuz[i][2]);
		glColor3f(luzDifusa[i][0],luzDifusa[i][1],luzDifusa[i][2]);
		glutSolidSphere(5,60,60);
		glPopMatrix();
	}
	
	// Habilita iluminação novamente
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);

//PEÕES
//===========================PEÕES AZUIS===========================
// Base Inferior do Peão nº1	   	   	
//		glPushMatrix();
//      glTranslatef(25, 0, 35);//X move pelo tabuleiro, Y tamanho do Cone para baixo e Z move na vertical pelo tabuleiro
//        glColor3f(0, 0, 1);
//        glRotatef(-90, 1, 0, 0);
//        glutSolidCone(2.5, 5, 100,100);
//        glPopMatrix();
// Base Superior do Peão nº1
//        glPushMatrix();
//        glTranslatef(25, 5, 35);
//        glColor3f(0, 0, 1);
//        glutSolidSphere(1.5, 100, 100);
//        glPopMatrix();

// Base Inferior do Peão nº2	   	   	
		glPushMatrix();
        glTranslatef(15, 0, 25);
		glColor3f(1, 0, 0);
        glRotatef(-90, 1, 0, 0);
	   	glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº2
        glPushMatrix();
        glTranslatef(15, 5, 25);
		glColor3f(1, 0, 0);
		glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº3	   	   	
		glPushMatrix();
        glTranslatef(25, 0, 15);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº3
        glPushMatrix();
        glTranslatef(25, 5, 15);
        glColor3f(0, 0, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº4	   	   	
		glPushMatrix();
        glTranslatef(25, 0, 5);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº4
        glPushMatrix();
        glTranslatef(25, 5, 5);
        glColor3f(0, 0, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº5
		glPushMatrix();
        glTranslatef(25, 0, -5);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº5
        glPushMatrix();
        glTranslatef(25, 5, -5);
        glColor3f(0, 0, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº6
		glPushMatrix();
        glTranslatef(25, 0, -15);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº6
        glPushMatrix();
        glTranslatef(25, 5, -15);
        glColor3f(0, 0, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº7
		glPushMatrix();
        glTranslatef(15, 0, -25);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº7
        glPushMatrix();
        glTranslatef(15, 5, -25);
        glColor3f(0, 0, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº8
		glPushMatrix();
        glTranslatef(25, 0, -35);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº8
        glPushMatrix();
        glTranslatef(25, 5, -35);
        glColor3f(0, 0, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
//===========================PEÕES BRANCOS===========================
// Base Inferior do Peão nº1	   	   	
		glPushMatrix();
        glTranslatef(-25, 0, 35);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº1
        glPushMatrix();
        glTranslatef(-25, 5, 35);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº2	   	   	
		glPushMatrix();
        glTranslatef(-25, 0, 25);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº2
        glPushMatrix();
        glTranslatef(-25, 5, 25);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº3	   	   	
		glPushMatrix();
        glTranslatef(-25, 0, 15);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº3
        glPushMatrix();
        glTranslatef(-25, 5, 15);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº4	   	   	
		glPushMatrix();
        glTranslatef(-15, 0, 5);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº4
        glPushMatrix();
        glTranslatef(-15, 5, 5);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº5	   	   	
		glPushMatrix();
        glTranslatef(-25, 0, -5);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº5
        glPushMatrix();
        glTranslatef(-25, 5, -5);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº6	   	   	
		glPushMatrix();
        glTranslatef(-25, 0, -15);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº6
        glPushMatrix();
        glTranslatef(-25, 5, -15);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº7	   	   	
		glPushMatrix();
        glTranslatef(-25, 0, -25);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº7
        glPushMatrix();
        glTranslatef(-25, 5, -25);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();
// Base Inferior do Peão nº8	   	   	
		glPushMatrix();
        glTranslatef(-25, 0, -35);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Base Superior do Peão nº8
        glPushMatrix();
        glTranslatef(-25, 5, -35);
        glColor3f(1, 1, 1);
        glutSolidSphere(1.5, 100, 100);
        glPopMatrix();

//TORRES
//===========================TORRES BRANCAS===========================
// Base Inferior da Torre nº1	   	   	
		glPushMatrix();
        glTranslatef(-35, 0, 35);
        glColor3f(1, 1, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Meio da Torre nº1	   	   	
        glPushMatrix();
        glTranslatef(-34, 4, 34);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº1
		        glPushMatrix();
        		glTranslatef(-33, 6, 33);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();
        glPushMatrix();
        glTranslatef(-34, 4, 35);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº2        
		        glPushMatrix();
        		glTranslatef(-37, 6, 37);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();        
        glPushMatrix();
        glTranslatef(-34, 4, 36);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº3
			    glPushMatrix();
        		glTranslatef(-37, 6, 33);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();        
        glPushMatrix();
        glTranslatef(-35, 4, 34);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-36, 4, 34);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glPushMatrix();
        glTranslatef(-34, 4, 35);
        glColor3f(1, 0, 0);
        glutSolidCube(2);
        glPopMatrix();
        glTranslatef(-36, 4, 36);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº4
		        glPushMatrix();
        		glTranslatef(-33, 6, 37);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();                

// Base Inferior da Torre nº2	   	   	
		glPushMatrix();
        glTranslatef(-35, 0, -35);
        glColor3f(1, 1, 1);
        glRotatef(-120, 1, 1, 1);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Meio da Torre nº2	   	   	
        glPushMatrix();
        glTranslatef(-34, 4, -34);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº1
		        glPushMatrix();
        		glTranslatef(-33, 6, -33);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();
        glPushMatrix();
        glTranslatef(-34, 4, -35);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº2        
		        glPushMatrix();
        		glTranslatef(-37, 6, -37);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();        
        glPushMatrix();
        glTranslatef(-34, 4, -36);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº3
			    glPushMatrix();
        		glTranslatef(-37, 6, -33);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();        
        glPushMatrix();
        glTranslatef(-35, 4, -34);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-36, 4, -34);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glPushMatrix();
        glTranslatef(-34, 4, -35);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        glTranslatef(-36, 4, -36);
        glColor3f(1, 1, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº4
		        glPushMatrix();
        		glTranslatef(-33, 6, -37);
        		glColor3f(1, 1, 1);
        		glutSolidCube(2);
        		glPopMatrix();                        

//===========================TORRES AZUIS===========================
// Base Inferior da Torre nº1	   	   	
		glPushMatrix();
        glTranslatef(35, 0, 35);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Meio da Torre nº1	   	   	
        glPushMatrix();
        glTranslatef(34, 4, 34);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº1
		        glPushMatrix();
        		glTranslatef(33, 6, 33);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();
        glPushMatrix();
        glTranslatef(34, 4, 35);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº2        
		        glPushMatrix();
        		glTranslatef(37, 6, 37);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();                
        glPushMatrix();
        glTranslatef(34, 4, 36);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº3
			    glPushMatrix();
        		glTranslatef(37, 6, 33);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();                
        glPushMatrix();
        glTranslatef(35, 4, 34);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(36, 4, 34);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glPushMatrix();
        glTranslatef(34, 4, 35);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        glTranslatef(36, 4, 36);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº4
		        glPushMatrix();
        		glTranslatef(33, 6, 37);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();                        

// Base Inferior da Torre nº2   	   	
		glPushMatrix();
        glTranslatef(35, 0, -35);
        glColor3f(0, 0, 1);
        glRotatef(-90, 1, 0, 0);
        glutSolidCone(2.5, 5, 100,100);
        glPopMatrix();
// Meio da Torre nº2	
        glPushMatrix();
        glTranslatef(34, 4, -34);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº1
		        glPushMatrix();
        		glTranslatef(33, 6, -33);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();
        glPushMatrix();
        glTranslatef(34, 4, -35);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº2        
		        glPushMatrix();
        		glTranslatef(37, 6, -37);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();                
        glPushMatrix();
        glTranslatef(34, 4, -36);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº3
			    glPushMatrix();
        		glTranslatef(37, 6, -33);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();                
        glPushMatrix();
        glTranslatef(35, 4, -34);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(36, 4, -34);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
        glPushMatrix();
        glTranslatef(34, 4, -35);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        glTranslatef(36, 4, -36);
        glColor3f(0, 0, 1);
        glutSolidCube(2);
        glPopMatrix();
        		//Parte de cima da Torre nº4
		        glPushMatrix();
        		glTranslatef(33, 6, -37);
        		glColor3f(0, 0, 1);
        		glutSolidCube(2);
        		glPopMatrix();        		
//CAVALOS			
//===========================CAVALOS AZUIS============================				
//Base Superior
glPushMatrix();
	glTranslatef(35, 4, 25);	
	glColor3f(0, 0, 1);
	glRotatef(180, 0, 1, 0);
	glutSolidTeapot(3);
	glPopMatrix();
//Base Superior nº2
glPushMatrix();
	glTranslatef(35, 4, -25);
	glColor3f(0, 0, 1);
	glRotatef(180, 0, 1, 0);
	glutSolidTeapot(3);
	glPopMatrix();

//===========================CAVALOS BRANCOS=========================			
//Base Superior
glPushMatrix();
	glTranslatef(-35, 4, 25);
	glColor3f(1, 1, 1);
	glutSolidTeapot(3);
	glPopMatrix();

//Base Superior nº2
glPushMatrix();
	glTranslatef(-35, 4, -25);
	glColor3f(1, 1, 1);
	glutSolidTeapot(3);
	glPopMatrix();
		
//BISPOS			
//===========================BISPOS AZUIS===========================
//Base Inferior nº1
	glPushMatrix();
	glTranslatef(35, 0, 15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3, 9, 100,100);
	glPopMatrix();
//Meio do Bispo nº1
	glPushMatrix();
	glTranslatef(35, 1, 15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 3, 20, 40); 
	glPopMatrix();

//Meio do Bispo nº1V2
	glPushMatrix();
	glTranslatef(35, 6, 15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 2, 20, 40); 
	glPopMatrix();
//Meio do Bispo nº1V3
	glPushMatrix();
	glTranslatef(35, 7, 15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Parte de Cima	nº1
    glPushMatrix();
    glTranslatef(35, 9, 15);
    glColor3f(0, 0, 1);
    glutSolidSphere(2, 10, 100);
    glPopMatrix();
//Parte de Cima nº1V2	
    glPushMatrix();
    glTranslatef(35, 11, 15);
    glColor3f(0, 0, 1);
    glutSolidSphere(1, 10, 30);
    glPopMatrix();

//Base Inferior nº2
	glPushMatrix();
	glTranslatef(35, 0, -15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3, 9, 100,100);
	glPopMatrix();
//Meio do Bispo nº2
	glPushMatrix();
	glTranslatef(35, 1, -15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 3, 20, 40); 
	glPopMatrix();
//Meio do Bispo nº2V2
	glPushMatrix();
	glTranslatef(35, 6, -15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 2, 20, 40); 
	glPopMatrix();
//Meio do Bispo nº2V3
	glPushMatrix();
	glTranslatef(35, 7, -15);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Parte de Cima	nº2
    glPushMatrix();
    glTranslatef(35, 9, -15);
    glColor3f(0, 0, 1);
    glutSolidSphere(2, 10, 100);
    glPopMatrix();
//Parte de Cima nº2V2	
    glPushMatrix();
    glTranslatef(35, 11, -15);
    glColor3f(0, 0, 1);
    glutSolidSphere(1, 10, 30);
    glPopMatrix();
    
//===========================BISPOS BRANCOS===========================
//Base Inferior nº1
	glPushMatrix();
	glTranslatef(-35, 0, -15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3, 9, 100,100);
	glPopMatrix();
//Meio nº1
	glPushMatrix();
	glTranslatef(-35, 1, -15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 3, 20, 40); 
	glPopMatrix();
//Meio nº1V2
	glPushMatrix();
	glTranslatef(-35, 6, -15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 2, 20, 40); 
	glPopMatrix();
//Meio nº1V3
	glPushMatrix();
	glTranslatef(-35, 7, -15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Parte de Cima	nº1
    glPushMatrix();
    glTranslatef(-35, 9, -15);
    glColor3f(1, 1, 1);
    glutSolidSphere(2, 10, 100);
    glPopMatrix();
//Parte de Cima nº1V2	
    glPushMatrix();
    glTranslatef(-35, 11, -15);
    glColor3f(1, 1, 1);
    glutSolidSphere(1, 10, 30);
    glPopMatrix();

//Base Inferior nº2
	glPushMatrix();
	glTranslatef(-15, 0, 15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3, 9, 100,100);
	glPopMatrix();
//Meio nº2
	glPushMatrix();
	glTranslatef(-15, 1, 15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 3, 20, 40); 
	glPopMatrix();
//Meio nº2V2
	glPushMatrix();
	glTranslatef(-15, 6, 15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 2, 20, 40); 
	glPopMatrix();
//Meio nº2V3
	glPushMatrix();
	glTranslatef(-15, 7, 15);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Topo nº2
    glPushMatrix();
    glTranslatef(-15, 9, 15);
    glColor3f(1, 1, 1);
    glutSolidSphere(2, 10, 100);
    glPopMatrix();
//Topo nº2V2	
    glPushMatrix();
    glTranslatef(-15, 11, 15);
    glColor3f(1, 1, 1);
    glutSolidSphere(1, 10, 30);
    glPopMatrix();

//RAINHA
//===========================RAINHA BRANCA===========================
//Base Inferior
	glPushMatrix();
	glTranslatef(-35, 0, -5);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3, 13, 100,100);
	glPopMatrix();
//Meio Inferior da Base
	glPushMatrix();
	glTranslatef(-35, 1, -5);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 3, 20, 40); 
	glPopMatrix();
//Meio InferiorV1
	glPushMatrix();
	glTranslatef(-35, 9, -5);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 2, 20, 40); 
	glPopMatrix();	
//Meio InferiorV2
	glPushMatrix();
	glTranslatef(-35, 10, -5);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Meio InferiorV3
	glPushMatrix();
	glTranslatef(-35, 11, -5);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Base Superior
	glPushMatrix();
	glTranslatef(-35, 12, -5);
	glColor3f(1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3.5, 1, 100,100);
	glPopMatrix();
//Topo
    glPushMatrix();
    glTranslatef(-35, 13, -5);
    glColor3f(1, 1, 1);
    glutSolidSphere(1, 5, 10);
    glPopMatrix();

//===========================RAINHA PRETA===========================
//Base Inferior
	glPushMatrix();
	glTranslatef(35, 0, -5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3, 13, 100,100);
	glPopMatrix();
//Meio Inferior da Base
	glPushMatrix();
	glTranslatef(35, 1, -5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 3, 20, 40); 
	glPopMatrix();
//Meio InferiorV1
	glPushMatrix();
	glTranslatef(35, 9, -5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 2, 20, 40); 
	glPopMatrix();	
//Meio InferiorV2
	glPushMatrix();
	glTranslatef(35, 10, -5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Meio InferiorV3
	glPushMatrix();
	glTranslatef(35, 11, -5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Base Superior
	glPushMatrix();
	glTranslatef(35, 12, -5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3.5, 1, 100,100);
	glPopMatrix();
//Topo
    glPushMatrix();
    glTranslatef(35, 13, -5);
    glColor3f(0, 0, 1);
    glutSolidSphere(1, 5, 10);
    glPopMatrix();

//REI
//===========================REI BRANCO===========================
//Base Inferior
	glPushMatrix();
	glTranslatef(-35, 0, 5);
	glColor4f(0,1,1,0.9);
	glRotatef(-90, 1, 0, 0);
	glDepthMask(GL_FALSE);
	glutSolidCone(3, 13, 100, 100);
 	glDepthMask(GL_TRUE);
	glPopMatrix();
	//Base Inferior SÓLIDA
		glPushMatrix();
		glTranslatef(-35, 0, 5);
		glColor3f(0,1,0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(3, 7, 100, 100);
		glPopMatrix();
//Meio Inferior da Base
	glPushMatrix();
	glTranslatef(-35, 1, 5);
	glColor4f(0,1,1,0.5);
	glRotatef(-90, 1, 0, 0);
	glDepthMask(GL_FALSE);
	glutSolidTorus(1, 3, 20, 40);
 	glDepthMask(GL_TRUE);
	glPopMatrix();
//Meio InferiorV1
	glPushMatrix();
	glTranslatef(-35, 9, 5);
	glColor4f(0,1,1,0.5);
	glRotatef(-90, 1, 0, 0);
	glDepthMask(GL_FALSE);
	glutSolidTorus(1, 2, 20, 40);
 	glDepthMask(GL_TRUE);
	glPopMatrix();	
//Meio InferiorV2
	glPushMatrix();
	glTranslatef(-35, 10, 5);
	glColor4f(0,1,1,0.5);
	glRotatef(-90, 1, 0, 0);
	glDepthMask(GL_FALSE);
	glutSolidTorus(1, 1, 20, 40);
 	glDepthMask(GL_TRUE);
	glPopMatrix();
//Meio InferiorV3
	glPushMatrix();
	glTranslatef(-35, 11, 5);
	glColor4f(0,1,1,0.5);
	glRotatef(-90, 1, 0, 0);
	glDepthMask(GL_FALSE);
	glutSolidTorus(1, 1, 20, 40);
 	glDepthMask(GL_TRUE);
	glPopMatrix();
//Base Superior
	glPushMatrix();
	glTranslatef(-35, 12, 5);
	glColor4f(0,1,1,0.5);
	glRotatef(-90, 1, 0, 0);
	glDepthMask(GL_FALSE);
	glutSolidCone(3.5, 1, 100,100);
 	glDepthMask(GL_TRUE);
	glPopMatrix();
//Topo
    glPushMatrix();
    glTranslatef(-35, 13, 5);
	glColor4f(0,1,1,0.5);
   	glDepthMask(GL_FALSE);
    glutSolidSphere(1, 5, 10);
 	glDepthMask(GL_TRUE);
    glPopMatrix();
//Cruz do Topo nº1
    glPushMatrix();
	glTranslatef(-35, 13.5, 5);
	glColor4f(0,1,1,0.5);
	glDepthMask(GL_FALSE);
	glutSolidCube(2);
 	glDepthMask(GL_TRUE);
	glPopMatrix();                
//Cruz do Topo nº2
    glPushMatrix();
	glTranslatef(-35, 14.5, 5);
	glColor4f(0,1,1,0.5);
	glDepthMask(GL_FALSE);
	glutSolidCube(2);
 	glDepthMask(GL_TRUE);
	glPopMatrix();                
//Cruz do Topo nº3
    glPushMatrix();
	glTranslatef(-35, 15.5, 5);
	glColor4f(0,1,1,0.5);
	glDepthMask(GL_FALSE);
	glutSolidCube(2);
 	glDepthMask(GL_TRUE);
	glPopMatrix();                
//Cruz do Topo nº4
    glPushMatrix();
	glTranslatef(-35, 15.5, 7);
	glColor4f(0,1,1,0.5);
	glDepthMask(GL_FALSE);
	glutSolidCube(2);
 	glDepthMask(GL_TRUE);
	glPopMatrix();                
//Cruz do Topo nº5
    glPushMatrix();
	glTranslatef(-35, 15.5, 3);
	glColor4f(0,1,1,0.5);
	glDepthMask(GL_FALSE);
	glutSolidCube(2);
 	glDepthMask(GL_TRUE);
	glPopMatrix();                
//Cruz do Topo nº6
    glPushMatrix();
	glTranslatef(-35, 17.5, 5);
	glColor4f(0,1,1,0.5);
	glDepthMask(GL_FALSE);
	glutSolidCube(2);
 	glDepthMask(GL_TRUE);
	glPopMatrix();                

//===========================REI AZUL===========================
//Base Inferior
	glPushMatrix();
	glTranslatef(35, 0, 5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3, 13, 100,100);
	glPopMatrix();
//Meio Inferior da Base
	glPushMatrix();
	glTranslatef(35, 1, 5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 3, 20, 40); 
	glPopMatrix();
//Meio InferiorV1
	glPushMatrix();
	glTranslatef(35, 9, 5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 2, 20, 40); 
	glPopMatrix();	
//Meio InferiorV2
	glPushMatrix();
	glTranslatef(35, 10, 5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Meio InferiorV3
	glPushMatrix();
	glTranslatef(35, 11, 5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidTorus(1, 1, 20, 40); 
	glPopMatrix();
//Base Superior
	glPushMatrix();
	glTranslatef(35, 12, 5);
	glColor3f(0, 0, 1);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(3.5, 1, 100,100);
	glPopMatrix();
//Topo
    glPushMatrix();
    glTranslatef(35, 13, 5);
    glColor3f(0, 0, 1);
    glutSolidSphere(1, 5, 10);
    glPopMatrix();
//Cruz do Topo nº1
    glPushMatrix();
	glTranslatef(35, 13, 5);
	glColor3f(0, 0, 1);
	glutSolidCube(2);
	glPopMatrix();                
//Cruz do Topo nº2
    glPushMatrix();
	glTranslatef(35, 14.5, 5);
	glColor3f(0, 0, 1);
	glutSolidCube(2);
	glPopMatrix();                
//Cruz do Topo nº3
    glPushMatrix();
	glTranslatef(35, 15.5, 5);
	glColor3f(0, 0, 1);
	glutSolidCube(2);
	glPopMatrix();                
//Cruz do Topo nº4
    glPushMatrix();
	glTranslatef(35, 15.5, 7);
	glColor3f(0, 0, 1);
	glutSolidCube(2);
	glPopMatrix();                
//Cruz do Topo nº5
    glPushMatrix();
	glTranslatef(35, 15.5, 3);
	glColor3f(0, 0, 1);
	glutSolidCube(2);
	glPopMatrix();
//Cruz do Topo nº6
    glPushMatrix();
	glTranslatef(35, 17.5, 5);
	glColor3f(0, 0, 1);
	glutSolidCube(2);
	glPopMatrix();                

	DesenhaChao();	
glPushMatrix();
glTranslatef(Tx,0.0f,0.0f);
glPushMatrix();
Desenha_Peao1();
glPopMatrix();

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
	//Mover Peao1
		if(tecla == GLUT_KEY_LEFT)
	{
		Tx-=10;
		if ( Tx < -300 )
			Tx = -300; 
	}
	if(tecla == GLUT_KEY_RIGHT)
	{
		Tx+=10;
		if ( Tx > 140 )
			Tx = 140; 
	}
	switch (tecla)
	{
	//	case GLUT_KEY_LEFT:			posLuz[luz][0] -=2;
	//								break;
	//	case GLUT_KEY_RIGHT:		posLuz[luz][0] +=2;
	//								break;
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
	// Botão esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botão direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Botão do meio ?
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
	if ( h == 0 ) h = 1;

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
	glClearColor(0, 0, 0, 0);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita as fontes de luz
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
	//Transparencia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
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
	glutCreateWindow("Desenho de um teapot iluminado por spots");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

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
