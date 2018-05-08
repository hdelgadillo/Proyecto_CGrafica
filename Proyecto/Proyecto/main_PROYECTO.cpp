//Semestre 2018-2
//************************************************************//
//************************************************************//
//************** Alumno (s):Delgadillo Cortez Hugo*********************************//
//*************				Leonel Macario Falcon							******//
//*************		Version de Visual studio 2017									******//
//************************************************************//
//************************************************************//

#include "texture.h"
#include "figuras.h"
#include "Camera.h"

#include "cmodel/CModel.h"

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
static GLuint ciudad_display_list;	//Display List for the Monito


									//NEW// Keyframes
									//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0, rotBrIzq = 0, rotBrDer = 0, rotRodDer = 0;
float giroMonito = 0;

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float rotBrIzq;
	float rotInc2;
	float rotBrDer;
	float rotRodDer;
	float rotInc4;
	float rotInc3;

	float giroMonito;
	float giroMonitoInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;


//GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };

CTexture text1;
CTexture text2;
CTexture text3;	//Flecha
CTexture text4;	//Pavimento
CTexture text5;	//Pasto01
CTexture text6;	//Casa01
CTexture text7;//torre roja
CTexture text8;//torre blanca
CTexture text9;//torre azul


				//NEW///////////////////////////7








float abrirPuerta = 0;
//END NEW//////////////////////////////////////////

CFiguras fig1;
CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito
CFiguras fig8;//torre roja
CFiguras fig9;//torre blanca
CFiguras fig10;//torre azul


void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].rotBrIzq = rotBrIzq;
	KeyFrame[FrameIndex].rotBrDer = rotBrDer;
	KeyFrame[FrameIndex].rotRodDer = rotBrDer;
	KeyFrame[FrameIndex].giroMonito = giroMonito;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotBrIzq = KeyFrame[0].rotBrIzq;
	rotBrDer = KeyFrame[0].rotBrDer;
	rotRodDer = KeyFrame[0].rotRodDer;
	giroMonito = KeyFrame[0].giroMonito;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotBrIzq - KeyFrame[playIndex].rotBrIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBrDer - KeyFrame[playIndex].rotBrDer) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}

void torreroja(void) {

	glPushMatrix();
glPushMatrix();
	glTranslatef(0.0, 1.85, 0.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
	glTranslatef(0.0, 1.25, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.0, 1.85, 0.75);
	glRotatef(0, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
	glTranslatef(0.0, 2.475, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.635, 1.25, 0.75);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.635, 1.25, 0.0);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
	glTranslatef(1.25, 1.25, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
	glTranslatef(1.25, 1.85, 0.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
	glTranslatef(1.25, 1.85, 0.75);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
	glTranslatef(1.25, 2.475, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.635,2.475, 0.0);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.635, 2.475, 0.75);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();

glPushMatrix();
glTranslatef(0.635, 1.80, 0.75);
glRotatef(45, 0, 0, 1);
glScalef(0.25, 1.45, .25);
glDisable(GL_LIGHTING);
fig3.prisma2(text7.GLindex, text7.GLindex);
glEnable(GL_LIGHTING);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.635,1.80, 0.0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.25, 1.45, .25);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text7.GLindex, text7.GLindex);
	glEnable(GL_LIGHTING);
glPopMatrix();
	glPopMatrix();

}

void torreblanca(void) {

	glPushMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.85, 0.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.25, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.85, 0.75);
	glRotatef(0, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 2.475, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 1.25, 0.75);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);;
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 1.25, 0.0);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 1.25, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 1.85, 0.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 1.85, 0.75);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 2.475, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 2.475, 0.0);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 2.475, 0.75);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.635, 1.80, 0.75);
	glRotatef(45, 0, 0, 1);
	glScalef(0.25, 1.45, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 1.80, 0.0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.25, 1.45, .25);
	glDisable(GL_LIGHTING);
	fig8.prisma2(text8.GLindex, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopMatrix();

}
void torreazul(void) {

	glPushMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.85, 0.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.25, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.85, 0.75);
	glRotatef(0, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 2.475, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 1.25, 0.75);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 1.25, 0.0);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 1.25, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 1.85, 0.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 1.85, 0.75);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.25, 2.475, 0.38);
	glRotatef(180, 0.0, 1.0, 1.0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 2.475, 0.0);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 2.475, 0.75);
	glRotatef(180, 1, 1, 0);
	glScalef(0.25, 1, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.635, 1.80, 0.75);
	glRotatef(45, 0, 0, 1);
	glScalef(0.25, 1.45, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.635, 1.80, 0.0);
	glRotatef(45, 0, 0, 1);
	glScalef(0.25, 1.45, .25);
	glDisable(GL_LIGHTING);
	fig10.prisma2(text9.GLindex, text9.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopMatrix();

}

void parque()
{

	glPushMatrix(); //Camino1
	glTranslatef(0, 0.0, 0.0);
	glScalef(200, 0.1, 200);
	glDisable(GL_LIGHTING);
	fig3.prisma2(text5.GLindex, 0);
	glEnable(GL_LIGHTING);
	glPopMatrix();





}








GLuint createDL()
{
	GLuint ciudadDL;
	//GLuint cieloDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);
	// call the function that contains 
	// the rendering commands
	parque();
	
	//monito();
	// endList
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);


	text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();



	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();

	text4.LoadTGA("city/pavimento.tga");
	text4.BuildGLTexture();
	text4.ReleaseImage();

	text5.LoadTGA("city/pasto01.tga");
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text6.LoadTGA("city/casa01.tga");
	text6.BuildGLTexture();
	text6.ReleaseImage();

	text7.LoadTGA("texturas/skyscreamer/fondorojo.tga");
	text7.BuildGLTexture();
	text7.ReleaseImage();

	text8.LoadTGA("texturas/skyscreamer/metalblanco.tga");
	text8.BuildGLTexture();
	text8.ReleaseImage();

	text9.LoadTGA("texturas/skyscreamer/metalazul.tga");
	text9.BuildGLTexture();
	text9.ReleaseImage();
	 

	//NEW////////////////////////////////////////////

	
	//END NEW//////////////////////////////

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for (int i = 0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].rotBrIzq = 0;
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotInc = 0;
		KeyFrame[i].rotBrDer = 0;
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].giroMonito = 0;
		KeyFrame[i].giroMonitoInc = 0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
							//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();


	glRotatef(g_lookupdown, 1.0f, 0, 0);

	gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
		objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
		objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);


	glPushMatrix();
	glPushMatrix(); //Creamos cielo
	glDisable(GL_LIGHTING);
	glTranslatef(0, 60, 0);
	fig1.skybox(200.0, 130.0, 200.0, text1.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
	

	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(1, 1, 1);
	//glScalef(0.5, 0.5, 0.5);
	//monito();
	
	
	glCallList(ciudad_display_list);
	glTranslatef(posX, posY, posZ);
	glRotatef(giroMonito, 0, 1, 0);

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glColor3f(1.0, 1.0, 1.0);

	//aqui empieza torre
	glPushMatrix();
	glPushMatrix();
	torreroja();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 1.2, 0.0);
	torreroja();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 2.4, 0.0);
	torreroja();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 3.6, 0.0);
	torreroja();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 4.8, 0.0);
	torreroja();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 6, 0.0);
	torreroja();
	glPopMatrix();
	//torre blanca
	glPushMatrix();
	glTranslatef(0.0, 7.5, 0.0);
	torreblanca();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 8.7, 0.0);
	torreblanca();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 9.9, 0.0);
	torreblanca();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 11.1, 0.0);
	torreblanca();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 12.3, 0.0);
	torreblanca();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 13.5, 0.0);
	torreblanca();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 14.7, 0.0);
	torreblanca();
	glPopMatrix();
	//torre azul

	glPushMatrix();
	glTranslatef(0.0, 16.2, 0.0);
	torreazul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 17.7, 0.0);
	torreazul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 19.2, 0.0);
	torreazul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 20.7, 0.0);
	torreazul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 22.2, 0.0);
	torreazul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 23.7, 0.0);
	torreazul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 25.2, 0.0);
	torreazul();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,23.7, 0.0);
	torreazul();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0,25.2, 0.0);
	torreazul();
	glPopMatrix();


	glPopMatrix();






	glPopMatrix();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "Six Flags");
	pintaTexto(-11, 8.5, -14, (void *)font, s);
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glutSwapBuffers();

}

void animacion()
{
	fig3.text_izq -= 0.001;
	fig3.text_der -= 0.001;
	if (fig3.text_izq<-1)
		fig3.text_izq = 0;
	if (fig3.text_der<0)
		fig3.text_der = 1;

	//Movimiento del monito
	if (play)
	{

		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex>FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();

			}
		}
		else
		{
			//Draw animation
			posX += KeyFrame[playIndex].incX;
			posY += KeyFrame[playIndex].incY;
			posZ += KeyFrame[playIndex].incZ;

			rotRodIzq += KeyFrame[playIndex].rotInc;
			rotBrIzq += KeyFrame[playIndex].rotInc2;
			rotBrDer += KeyFrame[playIndex].rotInc3;
			rotRodDer += KeyFrame[playIndex].rotInc4;
			giroMonito += KeyFrame[playIndex].giroMonitoInc;

			i_curr_steps++;
		}

	}


	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;

	case 'k':		//
	case 'K':
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}

		break;

	case 'l':
	case 'L':
		if (play == false && (FrameIndex>1))
		{

			resetElements();
			//First Interpolation				
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;

	case 'y':
	case 'Y':
		posZ++;
		printf("%f \n", posZ);
		break;

	case 'g':
	case 'G':
		posX--;
		printf("%f \n", posX);
		break;

	case 'h':
	case 'H':
		posZ--;
		printf("%f \n", posZ);
		break;

	case 'j':
	case 'J':
		posX++;
		printf("%f \n", posX);
		break;

	case 'b':
		rotRodIzq++;
		printf("%f \n", rotRodIzq);
		break;

	case 'B':
		rotRodIzq--;
		printf("%f \n", rotRodIzq);
		break;

	case 'n':
		rotRodDer++;
		printf("%f \n", rotRodIzq);
		break;

	case 'N':
		rotRodDer--;
		printf("%f \n", rotRodIzq);
		break;


	case 'p':
		giroMonito++;
		break;

	case 'P':
		giroMonito--;
		break;

	case 'i':
		rotBrIzq++;
		break;

	case 'I':
		rotBrIzq--;
		break;

	case 'o':
		rotBrDer++;
		break;

	case 'O':
		rotBrDer--;
		break;
	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void menuKeyFrame(int id)
{
	switch (id)
	{
	case 0:	//Save KeyFrame
		if (FrameIndex<MAX_FRAMES)
		{
			saveFrame();
		}
		break;

	case 1:	//Play animation
		if (play == false && FrameIndex >1)
		{

			resetElements();
			//First Interpolation
			interpolation();

			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
		break;


	}
}


void menu(int id)
{

}



int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Practica 11"); // Nombre de la Ventana
									 //glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);

	submenu = glutCreateMenu(menuKeyFrame);
	glutAddMenuEntry("Guardar KeyFrame", 0);
	glutAddMenuEntry("Reproducir Animacion", 1);
	glutCreateMenu(menu);
	glutAddSubMenu("Animacion Monito", submenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();          // 

	return 0;
}