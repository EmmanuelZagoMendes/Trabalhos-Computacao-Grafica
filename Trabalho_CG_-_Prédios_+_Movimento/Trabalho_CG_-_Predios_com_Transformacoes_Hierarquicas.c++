#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

GLfloat tx = 0;
GLfloat ty = 0;
GLfloat angulo1 = 0;
GLfloat angulo2 = 0;

void DesenhaCarro(void)
{
//Carro	   		 
	glColor3f(0.2, 0.2, 0.2); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(-35.0f,-25.0f);
		glVertex2f(-35.0f, -10.0f);       
		glVertex2f( 10.0f, -10.0f);       
		glVertex2f( 10.0f,-25.0f);
	glEnd();
	
//Teto do Carro	   		 
	glColor3f(0.2, 0.2, 0.2); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(-35.0f,-10.0f);
		glVertex2f(-20.0f, 10.0f);       
		glVertex2f( 10.0f, 10.0f);       
		glVertex2f( 10.0f,-10.0f);
	glEnd();	
		
	glPushMatrix();
	glTranslatef(-30,-35,0);	
//Roda de Trás do Carro
	float angulo,raio;
	int i,x,y,num_lines;
	
	num_lines = 100;
	x = 9.99;
	y = 10;
	raio = 4; //modifica o tamanho do círculo
	

	// Habilita a alteração do estilo das linhas
	glEnable(GL_LINE_STIPPLE);

	// Altera a cor do desenho para vermelho
	glColor3f(1.0, 0.7, 0);

	//Posiciona o círculo
	glTranslatef(23, 0, 0); 
	
	//Cria o círculo
	glBegin (GL_POLYGON); 
		for(i = 0; i < num_lines ; i++) 
			{ 
				angulo = i * 2 * M_PI /num_lines; 
				glVertex2f (x+(cos(angulo)*raio),y+(sin(angulo)*raio));
			} 
	glEnd();	

//Meio da Roda_2	
	glColor3f(0, 0, 0); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(9.0f,10.0f);
		glVertex2f(9.0f, 9.0f);       
		glVertex2f(8.0f, 9.0f);       
		glVertex2f(8.0f,10.0f);
	glEnd();
	
	glTranslatef(-50,0,0);		
//Roda da Frente do Carro
	float angulo10,raio10;
	int j,a,b,num_lines10;
	
	num_lines10 = 100;
	a = 9.99;
	b = 10;
	raio10 = 4; //modifica o tamanho do círculo
	

	// Habilita a alteração do estilo das linhas
	glEnable(GL_LINE_STIPPLE);

	// Altera a cor do desenho para vermelho
	glColor3f(1.0, 0.7, 0);

	//Posiciona o círculo
	glTranslatef(23, 0, 0); 
	
	//Cria o círculo
	glBegin (GL_POLYGON); 
		for(j = 0; j < num_lines10 ; j++) 
			{ 
				angulo10 = j * 2 * M_PI /num_lines10; 
				glVertex2f (a+(cos(angulo10)*raio10),b+(sin(angulo10)*raio10));
			} 
	glEnd();	
						 
	glColor3f(0.4, 0.4, 0.4);    
	glBegin(GL_QUADS);
        glVertex2f(  15.0f, 30.0f);     
        glVertex2f(  15.0f, 40.0f);       
        glVertex2f(  40.0f, 40.0f);  
        glVertex2f(  40.0f, 30.0f);             
    glEnd();

//Meio da Roda	
	glColor3f(0, 0, 0); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(9.0f,10.0f);
		glVertex2f(9.0f,9.0f);       
		glVertex2f(8.0f,9.0f);       
		glVertex2f(8.0f,10.0f);
	glEnd();

	glPopMatrix();	
}

void Casa_Desenho(void)
{
	glClearColor(0.0,0.3,0.9,0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
     
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Aplica uma translação sobre a casinha que será desenhada
	glTranslatef(-50.0f, 0.0f, 0.0f);
	
//Loja	   		 
	glColor3f(0.0, 0.7, 0.9); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(-35.0f,-15.0f);
		glVertex2f(-35.0f, 25.0f);       
		glVertex2f( 14.0f, 25.0f);       
		glVertex2f( 14.0f,-15.0f);
	glEnd();

//Porta da Loja
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);	             		
		glVertex2f(-31.0f,-15.5f);
		glVertex2f(-31.0f, 12.0f);       
		glVertex2f(-20.0f, 12.0f);       
		glVertex2f(-20.0f,-15.5f);
		
//Janela da Loja		
	glColor3f(0, 0.3, 0.7); 		      
		glVertex2f(-15.0f, 1.0f);
		glVertex2f(-15.0f,12.0f);       
		glVertex2f(  7.0f,12.0f);       
		glVertex2f(  7.0f, 1.0f);             
	glEnd();

// Grades da Janela da Loja  
	glColor3f(0.4, 0.4, 0.4);    
	glBegin(GL_LINES);
        glVertex2f( -4.0f, 1.0f); //Vertical      
        glVertex2f( -4.0f,12.0f);       
        glVertex2f(-15.0f, 6.0f); //Horizontal   
        glVertex2f(  7.0f, 6.0f);             
    glEnd();

//Placa da Loja   
   	glColor3f(1.0, 0.9, 0.0);
	glBegin(GL_QUADS); 		       		
		glVertex2f(-31.0f, 19.0f);   
		glVertex2f(-31.0f, 30.0f);
		glVertex2f( -8.0f, 30.0f);    
		glVertex2f( -8.0f, 19.0f);       
	glEnd();

//1º Poste de Luz 	
 	glColor3f(1, 1, 1);			
	glBegin(GL_QUADS);		
		glVertex2f(32.0f,-15.0f);   
		glVertex2f(32.0f,  12.0f);
		glVertex2f(33.0f,  12.0f);    
		glVertex2f(33.0f,-15.0f);       
	glEnd();
	
//Círculo/Luz do 1º Poste de Luz
	float angulo,raio;
	int i,x,y,num_lines;
	
	num_lines = 100;
	x = 9.99;
	y = 10;
	raio = 4; //modifica o tamanho do círculo
	

	// Habilita a alteração do estilo das linhas
	glEnable(GL_LINE_STIPPLE);

	// Altera a cor do desenho para vermelho
	glColor3f(0, 0, 0);

	//Posiciona o círculo
	glTranslatef(23, 0, 0); 
	
	//Cria o círculo
	glBegin (GL_POLYGON); 
		for(i = 0; i < num_lines ; i++) 
			{ 
				angulo = i * 2 * M_PI /num_lines; 
				glVertex2f (x+(cos(angulo)*raio),y+(sin(angulo)*raio));
			} 
	glEnd();
		
//Escola
	glColor3f(1.0, 0.5, 0.4);	   		  		 		            
	glBegin(GL_QUADS);
		glVertex2f( 30.0f,-15.0f); //1ºs X's são largura 
		glVertex2f( 30.0f, 70.0f);       
		glVertex2f(150.0f, 70.0f); //2ºs X's são comprimento       
		glVertex2f(150.0f,-15.0f);
	glEnd();

//Placa da Escola   
   	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_QUADS); 		       		
		glVertex2f( 63.0f,80.0f);   
		glVertex2f( 63.0f,63.0f);
		glVertex2f(117.0f,63.0f);    
		glVertex2f(117.0f,80.0f);       
	glEnd();
		
//Porta dupla da Escola
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_QUADS); 		
		glVertex2f( 70.0f,-15.0f);
		glVertex2f( 70.0f, 12.0f);       
		glVertex2f(110.0f, 12.0f);       
		glVertex2f(110.0f,-15.0f);
    glEnd();

//Meio da Porta 	
 	glColor3f(0.5, 0.5, 0.5);			
	glBegin(GL_QUADS);		
		glVertex2f(89.5f,-15.0f);   
		glVertex2f(89.5f, 12.0f);
		glVertex2f(90.0f, 12.0f);    
		glVertex2f(90.0f,-15.0f);       
	glEnd();
	
//1ª Janela do canto superior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(45.0f,58.0f);
		glVertex2f(45.0f,44.0f);       
		glVertex2f(35.0f,44.0f);       
		glVertex2f(35.0f,58.0f);             
	glEnd();

//2ª Janela do canto superior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(65.0f,58.0f);
		glVertex2f(65.0f,44.0f);       
		glVertex2f(55.0f,44.0f);       
		glVertex2f(55.0f,58.0f);             
	glEnd();
	
//3ª Janela do canto superior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(85.0f,58.0f);
		glVertex2f(85.0f,44.0f);       
		glVertex2f(75.0f,44.0f);       
		glVertex2f(75.0f,58.0f);             
	glEnd();

//4ª Janela do canto superior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(105.0f,58.0f);
		glVertex2f(105.0f,44.0f);       
		glVertex2f(95.0f,44.0f);       
		glVertex2f(95.0f,58.0f);             
	glEnd();

//5ª Janela do canto superior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(125.0f,58.0f);
		glVertex2f(125.0f,44.0f);       
		glVertex2f(115.0f,44.0f);       
		glVertex2f(115.0f,58.0f);             
	glEnd();
	
//6ª Janela do canto superior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(145.0f,58.0f);
		glVertex2f(145.0f,44.0f);       
		glVertex2f(135.0f,44.0f);       
		glVertex2f(135.0f,58.0f);             
	glEnd();
			
//1ª Janela do meio da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(45.0f,38.0f);
		glVertex2f(45.0f,24.0f);       
		glVertex2f(35.0f,24.0f);       
		glVertex2f(35.0f,38.0f);             
	glEnd();

//2ª Janela do meio da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(65.0f,38.0f);
		glVertex2f(65.0f,24.0f);       
		glVertex2f(55.0f,24.0f);       
		glVertex2f(55.0f,38.0f);             
	glEnd();

//3ª Janela do meio da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(85.0f,38.0f);
		glVertex2f(85.0f,24.0f);       
		glVertex2f(75.0f,24.0f);       
		glVertex2f(75.0f,38.0f);             
	glEnd();

//4ª Janela do meio da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(105.0f,38.0f);
		glVertex2f(105.0f,24.0f);       
		glVertex2f(95.0f,24.0f);       
		glVertex2f(95.0f,38.0f);             
	glEnd();

//5ª Janela do meio da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(125.0f,38.0f);
		glVertex2f(125.0f,24.0f);       
		glVertex2f(115.0f,24.0f);       
		glVertex2f(115.0f,38.0f);             
	glEnd();
	
//6ª Janela do meio da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(145.0f,38.0f);
		glVertex2f(145.0f,24.0f);       
		glVertex2f(135.0f,24.0f);       
		glVertex2f(135.0f,38.0f);             
	glEnd();
					
//1ª Janela Maior do canto inferior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(45.0f,-9.0f);
		glVertex2f(45.0f,12.0f);       
		glVertex2f(35.0f,12.0f);       
		glVertex2f(35.0f,-9.0f);             
	glEnd();

//2ª Janela Maior do canto inferior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(65.0f,-9.0f);
		glVertex2f(65.0f,12.0f);       
		glVertex2f(55.0f,12.0f);       
		glVertex2f(55.0f,-9.0f);             
	glEnd();

//3ª Janela Maior do canto inferior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(125.0f,-9.0f);
		glVertex2f(125.0f,12.0f);       
		glVertex2f(115.0f,12.0f);       
		glVertex2f(115.0f,-9.0f);             
	glEnd();

//4ª Janela Maior do canto inferior esquerdo da Escola 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(145.0f,-9.0f);
		glVertex2f(145.0f,12.0f);       
		glVertex2f(135.0f,12.0f);       
		glVertex2f(135.0f,-9.0f);             
	glEnd();

//2º Poste de Luz 	
 	glColor3f(1, 1, 1);			
	glBegin(GL_QUADS);		
		glVertex2f(158.0f,-15.0f);   
		glVertex2f(158.0f,  5.0f);
		glVertex2f(157.0f,  5.0f);    
		glVertex2f(157.0f,-15.0f);       
	glEnd();

//Círculo/Luz do 2º Poste de Luz
	float angulo_1,raio_1;
	int k,xxx,yyy,num_lines_1;
	
	num_lines_1 = 100;
	xxx = 157;
	yyy = 8;
	raio_1 = 4; //modifica o tamanho do círculo
	

	// Habilita a alteração do estilo das linhas
	glEnable(GL_LINE_STIPPLE);

	// Altera a cor do desenho para vermelho
	glColor3f(0, 0, 0);

	//Posiciona o círculo
	//glTranslatef(50, 0, 0); 
	
	//Cria o círculo
	glBegin (GL_POLYGON); 
		for(k = 0; k < num_lines_1 ; k++) 
			{ 
				angulo_1 = k * 2 * M_PI /num_lines_1; 
				glVertex2f (xxx+(cos(angulo_1)*raio_1),yyy+(sin(angulo_1)*raio_1));
			} 
	glEnd();
	
//Igreja	   		 
	glColor3f(0.9, 0.8, 0.4); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(166.0f,-15.0f);
		glVertex2f(166.0f, 17.0f);       
		glVertex2f(223.0f, 17.0f);       
		glVertex2f(223.0f,-15.0f);
	glEnd();

//Porta da Igreja 
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);	             		
		glVertex2f(172.0f,-15.5f);
		glVertex2f(172.0f, 12.0f);       
		glVertex2f(184.0f, 12.0f);       
		glVertex2f(184.0f,-15.5f);
	glEnd();

//"Torre" da Igreja	   		 
	glColor3f(0.9, 0.8, 0.4); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(166.0f,44.0f);
		glVertex2f(166.0f,17.0f);       
		glVertex2f(190.0f,17.0f);       
		glVertex2f(190.0f,44.0f);
	glEnd();

//Janela da "Torre" da Igreja 		
	glColor3f(0, 0.3, 0.7);    
	glBegin(GL_QUADS);  
		glVertex2f(172.0f,38.0f);
		glVertex2f(172.0f,24.0f);       
		glVertex2f(184.0f,24.0f);       
		glVertex2f(184.0f,38.0f);             
	glEnd();

//Janela da Igreja		
	glColor3f(0, 0.3, 0.7); 		      
	glBegin(GL_QUADS);
		glVertex2f(194.0f, 1.0f);
		glVertex2f(194.0f,12.0f);       
		glVertex2f(219.0f,12.0f);       
		glVertex2f(219.0f, 1.0f);             
	glEnd();

// Grades da Janela da Igreja  
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_LINES);
        glVertex2f(206.5f, 1.0f); //Vertical      
        glVertex2f(206.5f,12.0f);       
        glVertex2f(194.0f, 6.0f); //Horizontal   
        glVertex2f(219.0f, 6.0f);             
    glEnd();
    
//Teto da Igreja	   		 
	glColor3f(0.2, 0.1, 0); 		 		            
	glBegin(GL_QUADS);              
		glVertex2f(190.0f,39.0f);
		glVertex2f(190.0f,17.0f);       
		glVertex2f(223.0f,17.0f);       
		glVertex2f(223.0f,39.0f);
	glEnd();

//Teto da "Torre" da Igreja
	glColor3f(0.2, 0.1, 0); 	
	glBegin(GL_TRIANGLES);
		glVertex2f(163.0f,44.0f);
		glVertex2f(193.0f,44.0f);
		glVertex2f(178.0f,59.0f);
	glEnd();

//Círculo/Janela da "Torre" da Igreja
	float anguloA,raioA;
	int H,A,B,num_linesA;
	
	num_linesA = 100;
	A = 178;
	B = 50;
	raioA = 2; //modifica o tamanho do círculo
	

	// Habilita a alteração do estilo das linhas
	glEnable(GL_LINE_STIPPLE);

	// Altera a cor do desenho para vermelho
	glColor3f(1, 1, 1);

	//Posiciona o círculo
	//glTranslatef(50, 0, 0); 
	
	//Cria o círculo
	glBegin (GL_POLYGON); 
		for(H = 0; H < num_linesA ; H++) 
			{ 
				anguloA = H * 2 * M_PI /num_linesA; 
				glVertex2f (A+(cos(anguloA)*raioA),B+(sin(anguloA)*raioA));
			} 
	glEnd();
		
//Rua   
   	glColor3f(0, 0, 0);
	glBegin(GL_QUADS); 		       		
		glVertex2f(-150.0f, -50.0f);   
		glVertex2f(-150.0f, -15.0f);
		glVertex2f( 300.0f, -15.0f);    
		glVertex2f( 300.0f, -50.0f);       
	glEnd();

//-1ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(-170.0f, -32.0f);   
		glVertex2f(-170.0f, -30.0f);
		glVertex2f(-130.0f, -30.0f);    
		glVertex2f(-130.0f, -32.0f);       
	glEnd();

//0ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(-110.0f, -32.0f);   
		glVertex2f(-110.0f, -30.0f);
		glVertex2f(-70.0f, -30.0f);    
		glVertex2f(-70.0f, -32.0f);       
	glEnd();
	
//1ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(-50.0f, -32.0f);   
		glVertex2f(-50.0f, -30.0f);
		glVertex2f(-10.0f, -30.0f);    
		glVertex2f(-10.0f, -32.0f);       
	glEnd();

//2ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(10.0f, -32.0f);   
		glVertex2f(10.0f, -30.0f);
		glVertex2f(50.0f, -30.0f);    
		glVertex2f(50.0f, -32.0f);       
	glEnd();

//3ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f( 70.0f, -32.0f);   
		glVertex2f( 70.0f, -30.0f);
		glVertex2f(110.0f, -30.0f);    
		glVertex2f(110.0f, -32.0f);       
	glEnd();

//4ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(130.0f, -32.0f);   
		glVertex2f(130.0f, -30.0f);
		glVertex2f(170.0f, -30.0f);    
		glVertex2f(170.0f, -32.0f);       
	glEnd();

//5ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(190.0f, -32.0f);   
		glVertex2f(190.0f, -30.0f);
		glVertex2f(230.0f, -30.0f);    
		glVertex2f(230.0f, -32.0f);       
	glEnd();

//6ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(250.0f, -32.0f);   
		glVertex2f(250.0f, -30.0f);
		glVertex2f(290.0f, -30.0f);    
		glVertex2f(290.0f, -32.0f);       
	glEnd();

//7ºTraçado da Rua   
   	glColor3f(1, 1, 1);
	glBegin(GL_QUADS); 		       		
		glVertex2f(310.0f, -32.0f);   
		glVertex2f(310.0f, -30.0f);
		glVertex2f(350.0f, -30.0f);    
		glVertex2f(350.0f, -32.0f);       
	glEnd();

//Repartição/Mureta da Rua   
   	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS); 		       		
		glVertex2f(-150.0f, -50.0f);   
		glVertex2f(-150.0f, -55.0f);
		glVertex2f( 300.0f, -55.0f);    
		glVertex2f( 300.0f, -50.0f);       
	glEnd();
	
//Grama   
   	glColor3f(0, 1, 0);
	glBegin(GL_QUADS); 		       		
		glVertex2f(-150.0f, -100.0f);   
		glVertex2f(-150.0f, -55.0f);
		glVertex2f( 300.0f, -55.0f);    
		glVertex2f( 300.0f, -100.0f);       
	glEnd();
	
//SOL	
	float angulo_2,raio_2;
	int j,xx,yy,num_liness;
	
	num_liness = 100;
	xx = 10;
	yy = 140;
	raio_2 = 13; //modifica o tamanho do círculo
	

	// Habilita a alteração do estilo das linhas
	glEnable(GL_LINE_STIPPLE);

	// Altera a cor do desenho para vermelho
	glColor3f(0.9, 0.9, 0);

	//Posiciona o círculo
	glTranslatef(180, 0, 0); 
	
	//Cria o círculo
	glBegin (GL_POLYGON); 
		for(j = 0; j < num_liness ; j++) 
			{ 
				angulo_2 = j * 2 * M_PI /num_liness; 
				glVertex2f (xx+(cos(angulo_2)*raio_2),yy+(sin(angulo_2)*raio_2));
			} 
	glEnd();

	glPushMatrix();

    glTranslatef(tx,0.0f,0.0f);
	glTranslated(0.0f,ty,0.0f);
    glPushMatrix();
    glScalef(1.0f,1.0f,1.0f);
    glColor3f(1.0f,0.0f,0.0f);
    DesenhaCarro();	
	
	glFlush();
}

void TeclasEspeciais(int key, int x, int y)
{
	// Move a base
	if(key == GLUT_KEY_LEFT)
	{
		tx-=2;
		if ( tx < -300 )
			tx = -300; 
	}
	if(key == GLUT_KEY_RIGHT)
	{
		tx+=2;
		if ( tx > 140 )
			tx = 140; 
	}
	if(key == GLUT_KEY_DOWN)
	{
		ty -= 2;
		if(ty < -20)
			ty = -20;
	}     
	if(key == GLUT_KEY_UP)
	{
		ty += 2;
		if(ty > 0)
			ty = 0;
	}     
	glutPostRedisplay();
}
																				
// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;
                   
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;
                                              
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura) 
        gluOrtho2D (-90.0f, 140.0f, -90.0f*altura/largura, 200.0f*altura/largura);
    else 
        gluOrtho2D (-90.0f*largura/altura, 140.0f*largura/altura, -90.0f, 200.0f);
}

//Função Callback p/ gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y){
	if(key==27);
	exit(0);
//Pra fechar com Esc
}

//Função para inicializar parametros

void Inicializa(void){
	//Define a janela de visualização 2d
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-90,140,-90,200);
	glMatrixMode(GL_MODELVIEW);
}

//Programa Principal
int main(void){
	//Define modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	
	//Especifica o tam inic da janela em px
	glutInitWindowSize(500,500);
	
	//Especifica onde a janela será criada
	glutInitWindowPosition(500,0);
	
	//cria a janela
	glutCreateWindow("Trabalho");
	
	//Registra funç callback
	glutDisplayFunc(Casa_Desenho);
	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);
	glutKeyboardFunc(Teclado);
	
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);
	
	//chama func p/ fz as inicializações
	Inicializa();
	
	//Inicia e aguarda int do usuario
	glutMainLoop();
	
	return 0;
}