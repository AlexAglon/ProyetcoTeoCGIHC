/*
Semestre 2023-1
Animación:
1.- Simple o básica:Por banderas y condicionales
2.- Compleja: Por medio de funciones y algoritmos,Textura Animada.
4.- Técnicas de Animación: Por Keyframes
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION




#include <stdio.h>
#include <string.h>
#include <cmath>r
#include <vector>
#include <math.h>
////////////////////////////////////////AUDIO
#include<irrKlang.h>
#include<irrklang.h>
using namespace irrklang;

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <chrono>  // for high_resolution_clock
#include "addons.h"

// Models
#include "Tux_M.h"
#include "TuxFather.h"

//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include "Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;
const float FLOOR_SIZE = 60.0f;

// PROJECT SETUP
const int DAY_DURATION = 5; // Seconds
std::chrono::steady_clock::time_point start_time;

float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float toffsetu = 0.0f;
float toffsetv = 0.0f;
//float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;
float reproduciranimacion, habilitaranimacion,guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;
float reproduciranimaciontux, habilitaranimaciontux;
float reproduciranimacionHollow, habilitaranimacionHollow;

Window mainWindow;
Camera camera;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture sign2x1Texture;
Texture signDescuentoTexture;

Mesh* pisoMesh;
Mesh* signMesh;

/////////////////////////////////////////CASA PHINEAS////////////////////////////////////////////7
Model Casa;
Model Piso;
Model Ventanas;
Model Vidrios;
Model Alfombra;
Model Lampara;
Model BaseLamapara;
Model Comedor;
Model Libros;
Model MesaC;
Model Sala;
Model Sillas;
Model Puerta;
Model Puerta2;
Model BaseVentilador;
Model Ventilador;
Model Calendar;
Model Cuadro;
Model Arbol;
Model Pasto;
Model Cerca;
Model Logo;
Model Sabana;
Model Ser;
Model Phineas;
Model BrazoD;
Model BrazoI;
Model Calle;
/////////////////////////////////////////////////////////////////////////////////////////////////

//---------------------------Modelo para animaion de keyframe hollow K 
Model Hollow_K;
Model Energia;

//food trucks :
Model ItalianTruck;
Model AssiaticTruck;
Model AmericanTruck;
Model ArabicTruck;

//Comida Mexicana :
Model tortas; 
Model tacos;
Model puesto_garnachas;
Model puesto_aguas;

//Modelos extra
Model mesa;
Model banio;
Model lampara;
Model cartel;
Model botes;
Model tamales;

Model Stage_M;
Model StageLight_M;  // Reused 3 times 

// TuxFather
Model Desk_M;
Model MonitoOn_M;
Model MonitorOff_M;

Skybox skybox;
std::vector<std::string> skyboxDayFaces, skyboxNightFaces;


//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight sunLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

//PARA INPUT CON KEYFRAMES 
void inputKeyframes(bool* keys);
void inputTuxKeyframes(bool* keys);
void DoMovement();
bool anim = false;
bool anim2 = false;

//PARA INPUT CON KEYFRAMES hollow
void inputhollowKeyframes(bool* keys);
float rot1 = 0;
float rot3 = 0;
float rot = 0;
float trans = 0;

void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	/* |===========|
	*  |    TEXT   |
	*  |===========|
	*/
	unsigned int letreroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat letreroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,	// 0
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,  // 1
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,  // 2
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,  // 3
	};

	pisoMesh = new Mesh();
	pisoMesh->CreateMesh(floorVertices, floorIndices, 32, 6);

	signMesh = new Mesh();
	signMesh->CreateMesh(letreroVertices, letreroIndices, 32, 6);
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


///////////////////////////////KEYFRAMES/////////////////////
#define MAX_FRAMES 30
// Tux KeyFrames
glm::vec3 tuxFatherPos = glm::vec3(-415.0f, 1.0f, 80.0f);
glm::vec3 tuxFatherMov = tuxFatherPos;
float giroTuxFather = 180.0f;
int i_max_steps_tux = 90;
int i_curr_steps_tux = 0;

//para animaciones hollow

int i_max_steps_hollow = 90;
int i_curr_steps_hollow = 14;

typedef struct _tuxframe
{
	//Variables para GUARDAR Key Frames
	float movTux_x;		//Variable para PosicionX
	float movTux_z;		//Variable para PosicionY
	float movTux_xInc;		//Variable para IncrementoX
	float movTux_zInc;		//Variable para IncrementoY
	float giroTux;
	float giroTuxInc;
} TUX_FRAME;

TUX_FRAME TuxKeyFrame[MAX_FRAMES];
int TuxFrameIndex = 4;			//introducir datos
bool tuxPlay = false;
int tuxPlayIndex = 0;


//-----------------Animacion de energia de Hollow--------------------------------------------
float posEnergy = 0.0;//Posicion inicial
float movEnergy = 0.0f;//para movimiento
float energySize = 0.0;

//------------------------------------------Para hollow
typedef struct _hollowframe
{
	float energiat;
	float energyMov;

	float energiaT;
	float energyINC;
} HOLLOW_FRAME;

HOLLOW_FRAME HOLLOWKeyFrame[MAX_FRAMES];
int hollowFrameIndex = 11;			//introducir datos
bool hollowPlay = false;
int hollowPlayIndex = 0;


void saveTuxFrame(void)
{

	printf("frameindex %d\n", TuxFrameIndex);
	TuxKeyFrame[TuxFrameIndex].movTux_x = tuxFatherMov.x;
	TuxKeyFrame[TuxFrameIndex].movTux_z = tuxFatherMov.z;
	TuxKeyFrame[TuxFrameIndex].giroTux = giroTuxFather;

	TuxFrameIndex++;
}

void tuxResetElements(void)
{
	tuxFatherMov.x = TuxKeyFrame[0].movTux_x;
	tuxFatherMov.z = TuxKeyFrame[0].movTux_z;
	giroTuxFather = TuxKeyFrame[0].giroTux;
}

void tuxInterpolation(void)
{
	TuxKeyFrame[tuxPlayIndex].movTux_xInc = (TuxKeyFrame[tuxPlayIndex + 1].movTux_x - TuxKeyFrame[tuxPlayIndex].movTux_x) / i_max_steps_tux;
	TuxKeyFrame[tuxPlayIndex].movTux_zInc = (TuxKeyFrame[tuxPlayIndex + 1].movTux_z - TuxKeyFrame[tuxPlayIndex].movTux_z) / i_max_steps_tux;
	TuxKeyFrame[tuxPlayIndex].giroTuxInc = (TuxKeyFrame[tuxPlayIndex + 1].giroTux - TuxKeyFrame[tuxPlayIndex].giroTux) / i_max_steps_tux;
}

void tuxAnimate(void)
{
	//Movimiento del objeto
	if (tuxPlay)
	{
		if (i_curr_steps_tux >= i_max_steps_tux) //end of animation between frames?
		{
			tuxPlayIndex++;
			printf("playindex : %d\n", tuxPlayIndex);
			if (tuxPlayIndex > TuxFrameIndex - 2)	//end of total animation?
			{
				printf("Frame index= %d\n", TuxFrameIndex);
				printf("termina anim\n");
				tuxPlayIndex = 0;
				tuxPlay = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps_tux = 0; //Reset counter
				//Interpolation
				tuxInterpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			tuxFatherMov.x += TuxKeyFrame[tuxPlayIndex].movTux_xInc;
			tuxFatherMov.z += TuxKeyFrame[tuxPlayIndex].movTux_zInc;
			giroTuxFather += TuxKeyFrame[tuxPlayIndex].giroTuxInc;
			i_curr_steps_tux++;
		}

	}
}

//Para hollow
void saveHollowFrame(void)
{

	printf("frameindex %d\n", hollowFrameIndex);
	HOLLOWKeyFrame[hollowFrameIndex].energiat = energySize;//crecimiento
	HOLLOWKeyFrame[hollowFrameIndex].energyMov = movEnergy;//movimiento

	hollowFrameIndex++;
}

void hollowResetElements(void)
{
	energySize = HOLLOWKeyFrame[0].energiat;//crecimiento
	movEnergy = HOLLOWKeyFrame[0].energyMov;//MOvimiento
}

void hollowInterpolation(void)
{
	HOLLOWKeyFrame[hollowPlayIndex].energiaT = (HOLLOWKeyFrame[hollowPlayIndex + 1].energiat - HOLLOWKeyFrame[hollowPlayIndex].energiat) / i_max_steps_hollow;//crecimiento
	HOLLOWKeyFrame[hollowPlayIndex].energyINC = (HOLLOWKeyFrame[hollowPlayIndex + 1].energyMov - HOLLOWKeyFrame[hollowPlayIndex].energyMov) / i_max_steps_hollow;
}

void hollowAnimate(void)
{
	//Movimiento del objeto
	if (hollowPlay)
	{
		if (i_curr_steps_hollow >= i_max_steps_hollow) //end of animation between frames?
		{
			hollowPlayIndex++;
			printf("playindex : %d\n", hollowPlayIndex);
			if (hollowPlayIndex > hollowFrameIndex - 2)	//end of total animation?
			{
				printf("Frame index= %d\n", hollowFrameIndex);
				printf("termina anim\n");
				hollowPlayIndex = 0;
				hollowPlay = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps_hollow = 0; //Reset counter
				//Interpolation
				hollowInterpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation

			energySize += HOLLOWKeyFrame[hollowPlayIndex].energiaT;
			movEnergy += HOLLOWKeyFrame[hollowPlayIndex].energyINC;

			i_curr_steps_hollow++;
		}

	}
}


// Puesto KeyFrames
bool animacion = false;
float posXtamales = 100.0, posYtamales = 0.0, posZtamales = -350.0;
float movtamales_x = 0.0f, movtamales_z = 0.0f;
float giroTamales = 0;


int i_max_steps = 90;
int i_curr_steps = 14;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movTamales_x;		//Variable para PosicionX
	float movTamales_z;		//Variable para PosicionY
	float movTamales_xInc;		//Variable para IncrementoX
	float movTamales_zInc;		//Variable para IncrementoY
	float giroTamales;
	float giroTamalesInc;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 14;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].movTamales_x = movtamales_x;
	KeyFrame[FrameIndex].movTamales_z = movtamales_z;
	KeyFrame[FrameIndex].giroTamales = giroTamales;

	FrameIndex++;
}

void resetElements(void)
{
	movtamales_x = KeyFrame[0].movTamales_x;
	movtamales_z = KeyFrame[0].movTamales_z;
	giroTamales = KeyFrame[0].giroTamales;
	
}

void interpolation(void)
{
	KeyFrame[playIndex].movTamales_xInc = (KeyFrame[playIndex + 1].movTamales_x - KeyFrame[playIndex].movTamales_x) / i_max_steps;
	KeyFrame[playIndex].movTamales_zInc = (KeyFrame[playIndex + 1].movTamales_z - KeyFrame[playIndex].movTamales_z) / i_max_steps;
	KeyFrame[playIndex].giroTamalesInc = (KeyFrame[playIndex + 1].giroTamales - KeyFrame[playIndex].giroTamales) / i_max_steps;

}


void animate(void)
{
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			movtamales_x += KeyFrame[playIndex].movTamales_xInc;
			movtamales_z += KeyFrame[playIndex].movTamales_zInc;
			giroTamales += KeyFrame[playIndex].giroTamalesInc;

			i_curr_steps++;
		}

	}
}

/* FIN KEYFRAMES*/

//contador de luces puntuales lo declaramos aqui para que podamos prenderlas y apagarlas con el ciclod de los skybox
unsigned int pointLightCount = 0;

bool checkTime(std::chrono::steady_clock::time_point start, bool day_state) {
	// Revisamos si el número de segundos ya supero el limite
	float diff = getSecondsDiff(start);
	//printf("The diff is %i\n", diff);

	if (diff >= DAY_DURATION)
	{
		if (day_state)
		{
			//skybox = Skybox(skyboxNightFaces);
			pointLightCount += 3;//si es de noche encendemos las 3 
		}
		else {
			//skybox = Skybox(skyboxDayFaces);
			pointLightCount = 0;//si es de dia las apagamos
		}
		return true;
	}
	return false;
}

void checkForLightThreeshold(SpotLight lights[], glm::vec3 COLORS[], std::chrono::steady_clock::time_point& start) {

	// Revisar el limite de tiempo
	float diff = getSecondsDiff(start);

	if (diff >= 2) {
		for (int i = 0; i < 3; i++) {
			int index = rand() % 3 + 0;
			lights[i].setColor(COLORS[index].x, COLORS[index].y, COLORS[index].z);
		}
	}

	start = std::chrono::high_resolution_clock::now();
}


int main()

//////////////////////////////////////////////////////////AUDIO//////////////////////////////////////////////////////////////////////////
{

	irrklang::ISoundEngine* audio = irrklang::createIrrKlangDevice();
	irrklang::ISoundEngine* audio2 = irrklang::createIrrKlangDevice();

	if (!audio)
	{
		printf("No inicia melodia");
		return 0;
	}
	if (!audio2)
	{
		printf("No inicia melodia");
		return 0;
	}
	audio->play2D("melodia1.mp3", true);
	audio->setSoundVolume(0.5f);//volumen 

	

	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	pisoTexture = Texture("Textures/piso_pasto_skybox2.tga");
	pisoTexture.LoadTextureA();

	sign2x1Texture = Texture("Textures/letrero_2x1.tga");
	sign2x1Texture.LoadTextureA();

	signDescuentoTexture = Texture("Textures/letrero_descuento.tga");
	signDescuentoTexture.LoadTextureA();


	//--------------------------------------------------Cargando Modelos----------------------------------------------------------------------------

	//////////////////////////////////////////////////////CASA PHINEAS/////////////////////////////////////////////////////
	Casa = Model();
	Casa.LoadModel("Models/Casa1/casa.obj");
	
	Piso= Model();
	Piso.LoadModel("Models/Piso/piso.obj");

	Ventanas = Model();
	Ventanas.LoadModel("Models/Ventanas/ventanas.obj");

	Vidrios = Model();
	Vidrios.LoadModel("Models/Vidrios/vidrios.obj");
	
	Vidrios = Model();
	Vidrios.LoadModel("Models/Vidrios/vidrios.obj");

	Alfombra = Model();
	Alfombra.LoadModel("Models/Alfombra/alfombra.obj");
	
	Lampara = Model();

	Lampara = Model();
	Lampara.LoadModel("Models/Lampara/lamp.obj");

	BaseLamapara = Model();
	BaseLamapara.LoadModel("Models/Lampara/baselamp.obj");

	Comedor = Model();
	Comedor.LoadModel("Models/Mesa/comedor.obj");

	Libros = Model();
	Libros.LoadModel("Models/Libros/libros.obj");

	MesaC = Model();
	MesaC.LoadModel("Models/MesaCentro/mesa.obj");

	Sala = Model();
	Sala.LoadModel("Models/Sala/sala.obj");

	Sillas = Model();
	Sillas.LoadModel("Models/Silla/silla.obj");

	Puerta = Model();
	Puerta.LoadModel("Models/PuertaA/puerta.obj");

	Puerta2 = Model();
	Puerta2.LoadModel("Models/PuertaB/puerta.obj");

	BaseVentilador = Model();
	BaseVentilador.LoadModel("Models/Ventilador/base.obj");

	Ventilador = Model();
	Ventilador.LoadModel("Models/Ventilador/ventilador.obj");
	
	Calendar = Model();
	Calendar.LoadModel("Models/Calendario/calendar.obj");

	Cuadro = Model();
	Cuadro.LoadModel("Models/Cuadro/cuadro.obj");

	Arbol = Model();
	Arbol.LoadModel("Models/Arbol/arbol.obj");

	Pasto = Model();
	Pasto.LoadModel("Models/Pasto/pasto.obj");

	Cerca = Model();
	Cerca.LoadModel("Models/Cerca/cerca.obj");

	Logo = Model();
	Logo.LoadModel("Models/Logo/logo.obj");

	Sabana = Model();
	Sabana.LoadModel("Models/Sabana/sabana.obj");

	Ser = Model();
	Ser.LoadModel("Models/Serinexistente/serinexistente.obj");

	Phineas = Model();
	Phineas.LoadModel("Models/Phineas/phineas.obj");

	BrazoD = Model();
	BrazoD.LoadModel("Models/BrazoDer/brazoder.obj");

	BrazoI = Model();
	BrazoI.LoadModel("Models/BrazoIzq/brazoizq.obj");

	Calle = Model();
	Calle.LoadModel("Models/Calle/calle.obj");
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//---------------------------Modelo de animacion para hollow K
	Hollow_K = Model();
	Hollow_K.LoadModel("Models/hollow/prueba_v4.obj");

	Energia = Model();
	Energia.LoadModel("Models/hollow/esfera_h.obj");

	//---------------------------Modelo de animacion para hollow K


	AssiaticTruck = Model();
	AssiaticTruck.LoadModel("Models/asian/asian_truck.obj");

	AmericanTruck = Model();
	AmericanTruck.LoadModel("Models/hotdog/hotdog_ham.obj");

	ItalianTruck = Model();
	ItalianTruck.LoadModel("Models/italiana/italian_truck.obj");

	ArabicTruck = Model();
	ArabicTruck.LoadModel("Models/arabic/arabic.obj");

	//Para puestos de comida reginal
	tacos = Model();
	tacos.LoadModel("Models/Puesto_tacos_pastor/puesto_tacos_pastor.obj");

	tortas = Model();
	tortas.LoadModel("Models/Puesto_tortas/Puesto_tortas_textura.obj");

	puesto_garnachas = Model();
	puesto_garnachas.LoadModel("Models/puesto_garnachas/puesto_garanachas.obj");

	puesto_aguas = Model();
	puesto_aguas.LoadModel("Models/puesto_Aguas_Frescas/puesto_aguas_frescas_v2.obj");

	mesa = Model();
	mesa.LoadModel("Models/mesas/mesa.obj");


	banio = Model();
	banio.LoadModel("Models/banio/banio3.obj");


	Stage_M = Model();
	Stage_M.LoadModel("Models/stage_clean.obj");
	StageLight_M = Model();
	StageLight_M.LoadModel("Models/stage_light_2.obj");


	lampara = Model();
	lampara.LoadModel("Models/lampara/lampara.obj");

	cartel = Model();
	cartel.LoadModel("Models/cartel/Anuncion_neon.obj");

	botes = Model();
	botes.LoadModel("Models/bote_Basura/trashcan1.obj");

	tamales = Model();
	tamales.LoadModel("Models/carrito/carrito.obj");

	Desk_M = Model();
	Desk_M.LoadModel("Models/desk/desk.obj");
	MonitoOn_M = Model();
	MonitoOn_M.LoadModel("Models/desk/monitor_on.obj");
	MonitorOff_M = Model();
	MonitorOff_M.LoadModel("Models/desk/monitor_off.obj");

	Tux_M tux = Tux_M(
		glm::vec3(0.0f),
		"Models/tux_v2/Cuerpo.obj",
		"Models/tux_v2/brazo_i.obj",
		"Models/tux_v2/brazo_d.obj",
		"Models/tux_v2/pie_i.obj",
		"Models/tux_v2/pie_d.obj"
	);

	TuxFather_M tuxFather = TuxFather_M(
		glm::vec3(-415.0f, 1.0f, 80.0f),
		"Models/tux_v2/Cuerpo.obj",
		"Models/tux_v2/brazo_i.obj",
		"Models/tux_v2/brazo_d.obj",
		"Models/tux_v2/pie_i.obj",
		"Models/tux_v2/pie_d.obj"
	);

	skyboxDayFaces.push_back("Textures/Skybox/dia/dia_lt.tga");
	skyboxDayFaces.push_back("Textures/Skybox/dia/dia_rt.tga");
	skyboxDayFaces.push_back("Textures/Skybox/dia/dia_dn.tga");
	skyboxDayFaces.push_back("Textures/Skybox/dia/dia_up.tga");
	skyboxDayFaces.push_back("Textures/Skybox/dia/dia_bk.tga");
	skyboxDayFaces.push_back("Textures/Skybox/dia/dia_ft.tga");

	skyboxNightFaces.push_back("Textures/Skybox/noche/lt.tga");
	skyboxNightFaces.push_back("Textures/Skybox/noche/rt.tga");
	skyboxNightFaces.push_back("Textures/Skybox/noche/down.tga");
	skyboxNightFaces.push_back("Textures/Skybox/noche/up.tga");
	skyboxNightFaces.push_back("Textures/Skybox/noche/back.tga");
	skyboxNightFaces.push_back("Textures/Skybox/noche/front.tga");

	skybox = Skybox(skyboxDayFaces);
	///VALORES DE MATERIALES //////////////////////////////////////////////
	Material_brillante = Material(0.1f, 16);
	Material_opaco = Material(0.3f, 4);

	glm::vec3 COLORS[4];
	COLORS[0] = glm::vec3(1.0f, 0.0f, 0.0f);  // RED
	COLORS[1] = glm::vec3(0.0f, 1.0f, 0.0f);  // GREEN
	COLORS[2] = glm::vec3(0.0f, 0.0f, 1.0f);  // BLUE
	COLORS[3] = glm::vec3(1.0f, 1.0f, 0.0f);  // RED + GREEN

	glm::vec2 CIRCLE[4];
	CIRCLE[0] = glm::vec2(1.0f, 0.0f);
	CIRCLE[1] = glm::vec2(0.0f, 1.0f);
	CIRCLE[2] = glm::vec2(-1.0f, 0.0f);
	CIRCLE[3] = glm::vec2(0.0f, -1.0f);

	float stageRot = 45.0f;
	int circleIndex = 0;

	//luz direccional, sólo 1 y siempre debe de existir
	// ### SUN Light ###
	sunLight = DirectionalLight(
		1.0f, 1.0f, 1.0f,	// COLOR
		0.8f, 0.3f,			// AmbientIntensity / DifusseIntensity
		0.0f, 0.0f, -1.0f); // Direction


	/* TODO: Cada farola tendra un pointLight que debera encender y apagarse*/
	//float aIntensity = getAttenuationValue(1.0f, 0.014f, 0.0007f, 325.0f);

	unsigned int pointLightCount = 0;
	// Farola de sushi y hotdog
	pointLights[0] = PointLight(
		1.0f, 1.0f, 0.4f,	// R G B
		//1.0f, 0.0f, 0.0f,
		100.0f, 1.0f,	// AmbientIntenssity / diffuseIntensity
		100.0f, 6.0f, 140.0f,	// Position
		0.5f, 0.7f, 0.1f);	// Contant, linar, exponent
	pointLightCount++;

	// Farola de italiana y arabe
	pointLights[1] = PointLight(
		1.0f, 1.0f, 0.4f,	// R G B
		100.0f, 1.0f,	// AmbientIntenssity / diffuseIntensity
		100.0f, 6.0f, -150.0f,	// Position
		0.5f, 0.7f, 0.1f);	// Contant, linar, exponent
	pointLightCount++;

	// Farola de tacos y aguas
	pointLights[2] = PointLight(
		1.0f, 1.0f, 0.4f,	// R G B
		100.0f, 1.0f,	// AmbientIntenssity / diffuseIntensity
		-100.0f, 6.0f, -60.0f,	// Position
		0.5f, 0.7f, 0.1f);	// Contant, linar, exponent
	pointLightCount++;


	unsigned int spotLightCount = 0;
	
	// STAGE LIGHT
	spotLights[0] = SpotLight(
		COLORS[0].x, COLORS[0].y, COLORS[0].z,	// R G B
		1000.0f, 10.0f,							// aIntensity dIntensity
		0.0f, 50.0f, 0.0f,						// XPos, yPos, zPos
		0.0f, -1.0f, 0.0f,						// Direction vector
		1.0f, 0.7f, 0.1f,						// What is this?			
		50.0f);									// Edge
	spotLightCount++;

	spotLights[1] = SpotLight(
		COLORS[2].x, COLORS[2].y, COLORS[2].z,	// R G B
		1000.0f, 10.0f,							// aIntensity dIntensity
		0.0f, 50.0f, 0.0f,						// XPos, yPos, zPos
		0.0f, -1.0f, 0.0f,						// Direction vector
		1.0f, 0.7f, 0.1f,						// What is this?			
		50.0f);									// Edge
	spotLightCount++;

	spotLights[2] = SpotLight(
		COLORS[3].x, COLORS[3].y, COLORS[3].z,	// R G B
		1000.0f, 10.0f,							// aIntensity dIntensity
		0.0f, 50.0f, 0.0f,						// XPos, yPos, zPos
		0.0f, -1.0f, 0.0f,						// Direction vector
		1.0f, 0.7f, 0.1f,						// What is this?			
		50.0f);									// Edge
	spotLightCount++;


	//PUESTO DE TORTAS
	spotLights[4] = SpotLight(1.0f, 0.5f, 0.0f,//color de la luz
		50.0f, 1.0f, //En esta si es importante el segundo valor porque nos da la intesidad de la luz  el primero no importa
		-120.0f, 40.0f, 150.0f,//Poscion, 
		10.0f, -1.0f, 0.0f,//Valores de direccion 
		0.5f, 0.7f, 0.1f,//valores de la ecuacion de segundo grado, no puede dar 0 este es que tanto se agranda o hace peque�a la luz
		200.0f);//Apertura de cono
	spotLightCount++;

	//PUESTO DE HOTDOGS
	spotLights[5] = SpotLight(1.0f, 0.5f, 0.0f,//color de la luz
		50.0f, 1.0f, //En esta si es importante el segundo valor porque nos da la intesidad de la luz  el primero no importa
		120.0f, 40.0f, 50.0f,//Poscion, 
		10.0f, -1.0f, 0.0f,//Valores de direccion 
		0.5f, 0.7f, 0.1f,//valores de la ecuacion de segundo grado, no puede dar 0 este es que tanto se agranda o hace peque�a la luz
		200.0f);//Apertura de cono
	spotLightCount++;

	//PUESTO ITALIANO
	spotLights[6] = SpotLight(1.0f, 0.5f, 0.0f,//color de la luz
		50.0f, 1.0f, //En esta si es importante el segundo valor porque nos da la intesidad de la luz  el primero no importa
		120.0f, 40.0f, -80.0f,//Poscion, 
		10.0f, -1.0f, 0.0f,//Valores de direccion 
		0.5f, 0.7f, 0.1f,//valores de la ecuacion de segundo grado, no puede dar 0 este es que tanto se agranda o hace peque�a la luz
		200.0f);//Apertura de cono
	spotLightCount++;

	//PUESTO ARABE
	spotLights[7] = SpotLight(1.0f, 0.5f, 0.0f,//color de la luz
		50.0f, 1.0f, //En esta si es importante el segundo valor porque nos da la intesidad de la luz  el primero no importa
		120.0f, 30.0f, -240.0f,//Poscion, 
		10.0f, -1.0f, 0.0f,//Valores de direccion 
		0.5f, 0.7f, 0.1f,//valores de la ecuacion de segundo grado, no puede dar 0 este es que tanto se agranda o hace peque�a la luz
		200.0f);//Apertura de cono
	spotLightCount++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;

	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)(mainWindow.getBufferWidth() / mainWindow.getBufferHeight()), 0.1f, 1000.0f);

	start_time = std::chrono::high_resolution_clock::now();
	//******************************************FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF******************************************/
	glm::vec3 posblackhawk = glm::vec3(2.0f, 0.0f, 0.0f);  //VARIABLE MAT PARA DECLARA DATOS DE X,Y,Z INICILES PARA EL AVION 
	
	//---------------------Animacion Hollow
	glm::vec3 posEner = glm::vec3(0.0f, 0.0f, 0.0f);//Para poder mover la bola de energia
	//KEYFRAMES DECLARADOS INICIALES

	// TUX KeyFrames
	TuxKeyFrame[0].movTux_x = -415.0f;
	TuxKeyFrame[0].movTux_z = 80.0f;
	TuxKeyFrame[0].giroTux = 180.0f;

	TuxKeyFrame[1].movTux_x = -415.0f;
	TuxKeyFrame[1].movTux_z = 63.0f;
	TuxKeyFrame[1].giroTux = 180.0f;

	TuxKeyFrame[2].movTux_x = -415.0f;
	TuxKeyFrame[2].movTux_z = 56.0f;
	TuxKeyFrame[2].giroTux = 180.0f;

	TuxFrameIndex++;
	TuxKeyFrame[3].movTux_x = -415.0f;
	TuxKeyFrame[3].movTux_z = 50.0f;
	TuxKeyFrame[3].giroTux = 180.0f;

	TuxFrameIndex++;
	TuxKeyFrame[4].movTux_x = -415.0f;
	TuxKeyFrame[4].movTux_z = 45.0f;
	TuxKeyFrame[4].giroTux = 240.0f;

	TuxFrameIndex++;
	TuxKeyFrame[5].movTux_x = -430.0f;
	TuxKeyFrame[5].movTux_z = 45.0f;
	TuxKeyFrame[5].giroTux = 240.0f;

	TuxFrameIndex++;
	TuxKeyFrame[6].movTux_x = -430.0f;
	TuxKeyFrame[6].movTux_z = 45.0f;
	TuxKeyFrame[6].giroTux = 270.0f;

	TuxFrameIndex++;
	TuxKeyFrame[7].movTux_x = -445.0f;
	TuxKeyFrame[7].movTux_z = 45.0f;
	TuxKeyFrame[7].giroTux = 270.0f;

	TuxFrameIndex++;
	TuxKeyFrame[8].movTux_x = -460.0f;
	TuxKeyFrame[8].movTux_z = 45.0f;
	TuxKeyFrame[8].giroTux = 270.0f;

	TuxFrameIndex++;
	TuxKeyFrame[9].movTux_x = -460.0f;
	TuxKeyFrame[9].movTux_z = 45.0f;
	TuxKeyFrame[9].giroTux = 303.1f;

	TuxFrameIndex++;
	TuxKeyFrame[10].movTux_x = -460.0f;
	TuxKeyFrame[10].movTux_z = 45.0f;
	TuxKeyFrame[10].giroTux = 360.0f;

	TuxFrameIndex++;
	TuxKeyFrame[11].movTux_x = -460.0f;
	TuxKeyFrame[11].movTux_z = 53.0f;
	TuxKeyFrame[11].giroTux = 360.0f;

	TuxFrameIndex++;
	TuxKeyFrame[12].movTux_x = -460.0f;
	TuxKeyFrame[12].movTux_z = 56.0f;
	TuxKeyFrame[12].giroTux = 360.0f;

	//TuxFrameIndex++;
	TuxKeyFrame[13].movTux_x = -460.0f;
	TuxKeyFrame[13].movTux_z = 62.0f;
	TuxKeyFrame[13].giroTux = 360.0f;



	KeyFrame[0].movTamales_x = -10.0f;
	KeyFrame[0].movTamales_z = 0.0f;
	KeyFrame[0].giroTamales = 90;

	KeyFrame[1].movTamales_x = -10.0f;
	KeyFrame[1].movTamales_z = 200.0f;
	KeyFrame[1].giroTamales = 90;

	KeyFrame[2].movTamales_x = -10.0f;
	KeyFrame[2].movTamales_z = 400.0f;
	KeyFrame[2].giroTamales = 90;

	KeyFrame[3].movTamales_x = -50.0f;
	KeyFrame[3].movTamales_z = 400.0f;
	KeyFrame[3].giroTamales = 0;

	KeyFrame[4].movTamales_x = -100.0f;
	KeyFrame[4].movTamales_z = 400.0f;
	KeyFrame[4].giroTamales = 0;

	KeyFrame[5].movTamales_x = -175.0f;
	KeyFrame[5].movTamales_z = 400.0f;
	KeyFrame[5].giroTamales = 0;

	KeyFrame[6].movTamales_x = -175.0f;
	KeyFrame[6].movTamales_z = 400.0f;
	KeyFrame[6].giroTamales = -90;

	KeyFrame[7].movTamales_x = -175.0f;
	KeyFrame[7].movTamales_z = 200.0f;
	KeyFrame[7].giroTamales = -90;

	KeyFrame[8].movTamales_x = -175.0f;
	KeyFrame[8].movTamales_z = -25.0f;
	KeyFrame[8].giroTamales = -90;

	KeyFrame[9].movTamales_x = -175.0f;
	KeyFrame[9].movTamales_z = -10.0f;
	KeyFrame[9].giroTamales = -180;
	//
	KeyFrame[10].movTamales_x = 20.0f;
	KeyFrame[10].movTamales_z = -1.0f;
	KeyFrame[10].giroTamales = -180;

	KeyFrame[11].movTamales_x = 20.0f;
	KeyFrame[11].movTamales_z = -1.0f;
	KeyFrame[11].giroTamales = -180;


	//Frames para hollow K
	
	HOLLOWKeyFrame[0].energiat = 0.0f;
	HOLLOWKeyFrame[0].energyMov = 0.0f;

	HOLLOWKeyFrame[1].energiat = 1.0f;
	HOLLOWKeyFrame[1].energyMov = 0.0f;

	HOLLOWKeyFrame[2].energiat = 2.0f;
	HOLLOWKeyFrame[2].energyMov = 0.0f;

	HOLLOWKeyFrame[3].energiat = 3.0f;
	HOLLOWKeyFrame[3].energyMov = 0.0f;

	HOLLOWKeyFrame[4].energiat = 4.0f;
	HOLLOWKeyFrame[4].energyMov = 0.0f;

	HOLLOWKeyFrame[5].energiat = 5.0f;
	HOLLOWKeyFrame[5].energyMov = 0.0f;

	HOLLOWKeyFrame[6].energiat = 6.0f;
	HOLLOWKeyFrame[6].energyMov = 0.0f;

	HOLLOWKeyFrame[7].energiat = 7.0f;
	HOLLOWKeyFrame[7].energyMov = 0.0f;

	HOLLOWKeyFrame[8].energiat = 8.0f;
	HOLLOWKeyFrame[8].energyMov = 0.0f;

	HOLLOWKeyFrame[9].energiat = 9.0f;
	HOLLOWKeyFrame[9].energyMov = 5.0f;

	HOLLOWKeyFrame[10].energiat = 4.0f;
	HOLLOWKeyFrame[10].energyMov = 10.0f;

	HOLLOWKeyFrame[11].energiat = 0.0f;
	HOLLOWKeyFrame[11].energyMov = 50.0f;

	HOLLOWKeyFrame[12].energiat = 0.0f;
	HOLLOWKeyFrame[12].energyMov = 60.0f;


	bool prev_day_state = true;
	bool is_day = true;
	bool animateStage = false;

	// Stage Lights
	glm::vec3 l1, l2, l3;


	//Loop mientras no se cierra la ventana
	

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		
		prev_day_state = mainWindow.isDay();
		
		//PARA EL ENCENDIDO / APAGADO DE LUCES TIPO SPOTLIGTH
		//spotLights[0].SetIntensity(mainWindow.EnciendeApagaLuces());//Agregando el valor de la intensidad
		spotLights[4].SetIntensity(mainWindow.EnciendeApagaLucesdifusa());
		spotLights[4].SetAmbientIntensity(mainWindow.EnciendeApagaLucesAmbiente());

		spotLights[5].SetIntensity(mainWindow.EnciendeApagaLucesdifusa());
		spotLights[5].SetAmbientIntensity(mainWindow.EnciendeApagaLucesAmbiente());

		spotLights[6].SetIntensity(mainWindow.EnciendeApagaLucesdifusa());
		spotLights[6].SetAmbientIntensity(mainWindow.EnciendeApagaLucesAmbiente());

		spotLights[7].SetIntensity(mainWindow.EnciendeApagaLucesdifusa());
		spotLights[7].SetAmbientIntensity(mainWindow.EnciendeApagaLucesAmbiente());


		if (checkTime(start_time, mainWindow.isDay()))
		{
			start_time = std::chrono::high_resolution_clock::now();
			mainWindow.toggleDay();
		}

		is_day = mainWindow.isDay();

		// ### Day && Night Mode ###
		if (mainWindow.isDay())
		{
			sunLight.setAmbientIntenssity(0.8f);
			//skybox = Skybox(skyboxDayFaces);  // NOTE: Enabling this lags the simulation

			if (prev_day_state != is_day) {
				skybox = Skybox(skyboxDayFaces);
			}

			// TODO: Solo cambiarlas cuando se hace el cambio de dia a noche
			// Enable lamps
			for (auto& light : pointLights) {
				light.setIntensity(0.0f);
			}
		}
		else {
			sunLight.setAmbientIntenssity(0.35f);
			
			if (prev_day_state != is_day) {
				skybox = Skybox(skyboxNightFaces);
			}

			// Disable lamps
			for (auto& light : pointLights) {
				light.setIntensity(100.0f);
			}

		}

		bool* keys = mainWindow.getsKeys();
		bool prev_key_nine = keys[GLFW_KEY_9];
		//Recibir eventos del usuario
		glfwPollEvents();
		keys = mainWindow.getsKeys();
		
		if (mainWindow.getCameraMode()) {
			// 3rd Person Mode
			tux.keyControl(mainWindow.getsKeys(), deltaTime);
			tux.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			camera.adjustCamera(tux.getPos(), tux.getDir(), tux.getWorldUp(), tux.getCAMERA_SCALE());
		}
		else {
			// Aero Mode
			tux.keyControl(mainWindow.getsKeys(), deltaTime);
			tux.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
			camera.adjustAeroCamera(tux.getPos(), tux.getDir());
		}

		// ### Luz de las Farolas ###
		if (keys[GLFW_KEY_B])  // Disable nearest pointlight
		{
			int nearestIndex = getNearestLightIndex(pointLights, pointLightCount, tux.getPos());
			printf("DISABLE LIGHT: Nearest index is: %d\n", nearestIndex);

			if (pointLights[nearestIndex].getIntensity() > 0.0f) {
				pointLights[nearestIndex].setIntensity(0.0f);
			}
		}
		if (keys[GLFW_KEY_7])
		{
			anim2 = false;
		}
		if (keys[GLFW_KEY_5])
		{
			anim2 =true;
		}
		
		if (anim2==true)
		{
			rot3 += 6;
			
		}
		
		if (keys[GLFW_KEY_6])
		{

			anim =true;

		}
		if (anim==true)
		{
			


			if (rot < 30.0f) {
				rot += 0.09f;
				trans -= 0.009f;
				if (rot1 < 80)
					rot1 += 1.0f;
				else
					rot1 = 80;
			}
			else {
				
				anim = false;

			}
		}

		if (keys[GLFW_KEY_V])  // Enable nearest pointlight
		{
			int nearestIndex = getNearestLightIndex(pointLights, pointLightCount, tux.getPos());
			printf("ENABLE LIGHT: Nearest index is: %d\n", nearestIndex);

			if (pointLights[nearestIndex].getIntensity() <= 0.0f) {
				pointLights[nearestIndex].setIntensity(1.0f);
			}
		}


		if (keys[GLFW_KEY_9])  // Enable stage animation
		{
			
			if (prev_key_nine != keys[GLFW_KEY_9]) { 
				animateStage = true;
				printf("CHANGING STAGE LIGHTS\n");
			}
		}


		if (keys[GLFW_KEY_8])  // Disable state animation
		{
			
			if (prev_key_nine != keys[GLFW_KEY_8]) {
				animateStage = false;
				printf("CHANGING STAGE LIGHTS\n");
			}
		}

		// para keyframes
		inputKeyframes(mainWindow.getsKeys());
		inputTuxKeyframes(mainWindow.getsKeys());
		inputhollowKeyframes(mainWindow.getsKeys());

		animate();
		tuxAnimate();
		hollowAnimate();


		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&sunLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		/* 
		*	--------------------------------------------------
		*		CARGA DE MODELOS
		*	--------------------------------------------------
		*/ 

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		// Make plane bigger
		model = glm::scale(model, glm::vec3(FLOOR_SIZE, 1.0f, FLOOR_SIZE));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		pisoMesh->RenderMesh();

		model = glm::mat4(1.0);
		glm::vec3 stagePos = glm::vec3(5.0f, 30.0f, 220.0f);
		model = glm::translate(model, glm::vec3(5.0f, -5.0f, 220.0f));
		model = glm::scale(model, glm::vec3(7.0f, 10.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Stage_M.RenderModel();
		
		if (animateStage) {
			int index;

			stageRot += 1.0f;

			// Enable Lights

			spotLights[0].setIntensity(100.0);
			spotLights[1].setIntensity(100.0);
			spotLights[2].setIntensity(100.0);

			spotLights[0].SetPos(stagePos);
			spotLights[1].SetPos(stagePos);
			spotLights[2].SetPos(stagePos);


			l1 = glm::vec3(
				1 * glm::sin(-stageRot * toRadians) * stagePos.x,
				glm::sin(-stageRot * toRadians) - stagePos.y,
				1 * glm::cos(stageRot * toRadians) * stagePos.z
			);

			l2 = glm::vec3(
				1000 * glm::sin(stageRot * toRadians) * stagePos.x + 50,
				glm::sin(stageRot * toRadians) - stagePos.y,
				glm::cos(stageRot * toRadians) * stagePos.z + 50
			);

			l3 = glm::vec3(
				500 * glm::sin(-stageRot * toRadians) * stagePos.x - 75,
				glm::sin(-stageRot * toRadians) - stagePos.y,
				glm::cos(-stageRot * toRadians) * stagePos.z - 75
			);

			l1 = glm::normalize(l1);
			l2 = glm::normalize(l2);
			l3 = glm::normalize(l3);

			spotLights[0].setDirection(l1);
			spotLights[1].setDirection(l2);
			spotLights[2].setDirection(l3);

			for (auto& light : spotLights) {
				index = rand() % 3 + 0;
				// TODO: Check if color is asssigned already, if it is, choose another one 

				light.setColor(COLORS[index].x, COLORS[index].y, COLORS[index].z);
				
			}
		}
		else {
			// Turn off the lights!
			spotLights[0].setIntensity(0);
			spotLights[1].setIntensity(0);
			spotLights[2].setIntensity(0);
		}



		// Light 1
		glm::mat4 aux = model;
		model = glm::rotate(model, stageRot * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StageLight_M.RenderModel();

		// Light 2
		//model = glm::mat4(1.0);
		aux = model;
		model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, stageRot * toRadians + 50, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(100.0f, 100.f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StageLight_M.RenderModel();

		// Light 3
		model = aux;
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, stageRot * toRadians + 10, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(100.0f, 100.f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		StageLight_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -5.0f, -600.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banio.RenderModel();

		

		//----------------------------------------------------------Areas de comida------------------------------------------------------------------
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f,1.0f,210.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AssiaticTruck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 1.0f, 70.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AmericanTruck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 1.0f, -70.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ItalianTruck.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 1.0f, -220.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArabicTruck.RenderModel();

		//----------------------------------------------------------Areas de comida------------------------------------------------------------------

		//Puesto de tortas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, -0.5f, 150.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tortas.RenderModel();

		//Puesto de tacos 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 5.0f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tacos.RenderModel();

		//////////////////////////////////////////////CASA PHINEAS///////////////////////////////////////////
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Casa.RenderModel();

		
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Alfombra.RenderModel();

		//--------------------------------------------------------------Hollow para keyframes
		model = glm::mat4(1.0);
		//posUFO = glm::vec3(posXUFO + movUFOx, posYUFO + movUFOy, posZUFO + movUFOz);
		//model = glm::translate(model, posUFO);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//model = glm::rotate(model, giroUFO * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Hollow_K.RenderModel();


		//Bola de energia
		model = glm::mat4(1.0);
		posEner = glm::vec3(0.0f, 0.0f, posEnergy + movEnergy);
		model = glm::translate(model, posEner);
		model = glm::scale(model, glm::vec3(energySize, energySize, energySize));
		//model = glm::rotate(model, giroUFO * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Energia.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BaseLamapara.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Comedor.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Libros.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		MesaC.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Sala.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Sillas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Piso.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ventanas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-511.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BaseVentilador.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-532.1f, 35.0f, 55.2f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, rot3 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ventilador.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Calendar.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuadro.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pasto.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cerca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Logo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::translate(model, glm::vec3(trans, trans * 8, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rot * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Sabana.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-490.0f, 0.0f, 50.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ser.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, 0.0f, 40.0f));
		model = glm::scale(model, glm::vec3(25.0f, 10.0f, 50.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Calle.RenderModel();

		

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-492.0f, 16.2f, 108.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-492.0f, 16.2f, 114.9f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, rot1 * toRadians, glm::vec3(0.0f, 0.1f, -0.1f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoD.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-492.0f, 16.2f, 108.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, rot1 * toRadians, glm::vec3(0.0f, -0.1f, -0.1f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		BrazoI.RenderModel();



		///////////////////////////////////////////////////////////////////////////////////////////////

		//Puesto de aguas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 0.0f, -130.0f));
		model = glm::scale(model, glm::vec3(2.5f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_aguas.RenderModel();

		//Puesto de garnachas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 0.0f, -250.0f));
		model = glm::scale(model, glm::vec3(5.0f, 10.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_garnachas.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, -140.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, -140.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mesa.RenderModel();



		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, -370.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banio.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -370.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banio.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -370.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		banio.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 10.0f, -400.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		botes.RenderModel();

		model = glm::mat4(1.0);
		posblackhawk = glm::vec3(posXtamales + movtamales_x, posYtamales , posZtamales + movtamales_z); //POS INICIAL+VALOR DE LA ANIMACION
		model = glm::translate(model, posblackhawk);
		model = glm::scale(model, glm::vec3(6.0f, 10.0f, 8.0f));
		model = glm::rotate(model, giroTamales * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tamales.RenderModel();


		//-----------------------------------------------------------------------Modelos de laparas----------------------
		//Lado de food trucks
		//Entre sushi y hot dog 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 0.0f, 140.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		//Entre hot dog e italiana 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		//Entre italiana y arabe
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		//Lado de comida mexicana 
		//Entre tortas y tacos 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 0.0f, 80.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		//Entre tacos y aguas 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 0.0f, -60.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		//Entre púesto de aguas y garnchas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		// TUX FATHER - A normal linux user
		// Desk
		float x_desk = -460.0f, z_desk = 80.0f;
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(x_desk, 0.0f, z_desk));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Desk_M.RenderModel();
		MonitorOff_M.RenderModel();
		// MonitoOn_M.RenderModel();
		tuxFather.move(uniformModel, tuxFatherMov, giroTuxFather);
		

		//Entre púesto de aguas y garnchas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara.RenderModel();

		//-------------------------------------PARA CARTELES
		//Entre púesto de aguas y garnchas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, -180.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cartel.RenderModel();

		//Entre foodtrucks
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cartel.RenderModel();

		tux.move(uniformModel);

		// Carteles
		toffsetu += 0.001;
		toffsetv += 0.0;

		if (toffsetu > 1.0)
			toffsetu = 0.0;

		toffset = glm::vec2(toffsetu, toffsetv);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-97.8f, 26.0f, -179.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 13.0f, 7.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sign2x1Texture.UseTexture();
		signMesh->RenderMesh();

		// Cartel FoodTrucks
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(95.0f, 26.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 13.0f, 7.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		signDescuentoTexture.UseTexture();
		signMesh->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

void inputTuxKeyframes(bool* keys) {
	if (keys[GLFW_KEY_SPACE] && keys[GLFW_KEY_2]) // init animation
	{
		if (reproduciranimaciontux < 1)
		{
			if (tuxPlay == false && (TuxFrameIndex > 1))
			{
				tuxResetElements();
				//First Interpolation				
				tuxInterpolation();
				tuxPlay = true;
				tuxPlayIndex = 0;
				i_curr_steps_tux = 0;
				reproduciranimaciontux++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimaciontux = 0;

			}
			else
			{
				tuxPlay = false;
			}
		}
	}
	if (keys[GLFW_KEY_0] && keys[GLFW_KEY_2])  // reset animation
	{
		if (habilitaranimaciontux < 1)
		{
			reproduciranimaciontux = 0;
		}
	}
}


void inputhollowKeyframes(bool* keys) {
	if (keys[GLFW_KEY_SPACE] && keys[GLFW_KEY_6]) // init animation
	{
		if (reproduciranimacionHollow < 1)
		{
			if (hollowPlay == false && (hollowFrameIndex > 1))
			{
				hollowResetElements();
				//First Interpolation				
				hollowInterpolation();
				hollowPlay = true;
				hollowPlayIndex = 0;
				i_curr_steps_hollow = 0;
				reproduciranimacionHollow++;
				printf("\n presiona 0 + 6 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacionHollow = 0;

			}
			else
			{
				hollowPlay = false;
			}
		}
	}
	if (keys[GLFW_KEY_0])  // reset animation
	{
		if (habilitaranimacionHollow < 1)
		{
			reproduciranimacionHollow = 0;
		}
	}
}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE] && keys[GLFW_KEY_1])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		}
	}
	if (keys[GLFW_KEY_0] && keys[GLFW_KEY_1])
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			//printf("movAvion_x es: %f\n", movtamales_x);
			//printf("movAvion_y es: %f\n", movAvion_y);
			printf(" \npresiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movtamales_x += 1.0f;
			printf("\n movAvion_x es: %f\n", movtamales_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_2])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}

}

void DoMovement() {
	if (anim)
	{

		if (rot < 360.0f ) {
			rot += 5.05f;
			
		}
		else {
			rot = false;

		}
	}
}
