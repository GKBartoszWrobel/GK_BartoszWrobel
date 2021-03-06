// GK_2c_Bartosz_Wróbel_7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include "colors.h"
#include "gltools_extracted.h"
#include "VectorMath.cpp"


// rozmiary bryły obcinania
const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near_ = 3.0;
const GLdouble far_ = 7.0;
// stałe do obsługi menu podręcznego
enum
{
	CUTTING_PLANE, // płaszczyzna przekroju
	POLYGON_OFFSET, // przesunięcie wartości głębi
	EXIT // wyjście
};
// kąt obrotu kuli
GLfloat angle = 0.0;
// kąty obrotu sześcianu
GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
// wskaźnik rysowania płaszczyzna przekroju
bool cutting_plane = true;
// wskaźnik przesunięcia wartości głębi
bool polygon_offset = true;
// wskaźnik naciśnięcia lewego przycisku myszki
int button_state = GLUT_UP;
// położenie kursora myszki
int button_x, button_y;

void Display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//czyszczenie bufora koloru i bufora głębokości
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// wybór macierzy modelowania
	glMatrixMode(GL_MODELVIEW);
	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();
	// przesunięcie układu współrzędnych sześcianu do środka bryły odcinania
	glTranslatef(0, 0, -(near_ + far_) / 2);
	// obroty sześcianu
	glRotatef(rotatex, 1.0, 0, 0);
	glRotatef(rotatey, 0, 1.0, 0);
	// niewielkie powiększenie sześcianu
	glScalef(1.0, 1.0, 1.0);

	// włączenie testu bufora głębokości
	glEnable(GL_DEPTH_TEST);

	// rysowanie kuli
	glPushMatrix();
	angle += 0.6;
	glRotatef(angle, 1.0, 1.0, 0.0);


	glColor3fv(Yellow);

	if (polygon_offset)
		glEnable(GL_POLYGON_OFFSET_FILL);


	glPolygonOffset(1.0, 1.0);
	glutSolidSphere(0.5, 10, 10);
	glColor3fv(Black);
	glutWireSphere(0.5, 10, 10);

	if (polygon_offset)
		glDisable(GL_POLYGON_OFFSET_FILL);

	glPopMatrix();


	// wnetrze ostroslupa
	GLTVector3 vNormal;
	GLTVector3 vCorners2[11] = { { 0.0f, 1.98f, 0.0f }, // Góra 0
	{ -0.50f, -0.98f, -1.22f }, // Skrajny tył lewy 1
	{ 0.50f, -0.98f, -1.22f }, // Skrajny tył prawy 2
	{ -1.26f, -0.98f, -0.52f } , // Tył lewy (za środkiem) 3
	{ 1.26f, -0.98f, -0.52f } ,// Tył prawy (za środkiem) 4
	{ -1.26f, -0.98f, 0.52f }, // Lewy przód (za środkiem) 5
	{ 1.26f, -0.98f, 0.52f }, // Prawy przód (za środkiem) 6
	{ -0.50f, -0.98f, 1.22f } , // Skrajny przód lewy 7
	{ 0.50f, -0.98f, 1.22f } , // Skrajny  przód prawy 8
	{ 0.0f, -0.98f, 0.70f } , // 9
	{ 0.00f, -0.98f, 0.00f } }; // Środek podstawy

								// Rysowanie piramidy
	glColor3f(0.0f, 0.0f, 1.0f);

	glEnable(GL_CULL_FACE);
	glBegin(GL_TRIANGLES);

	//Ściany boczne

	glColor3fv(Pink);
	gltGetNormalVector(vCorners2[1], vCorners2[2], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[1]);
	glVertex3fv(vCorners2[2]);
	glVertex3fv(vCorners2[0]);

	glColor3fv(Lime);
	gltGetNormalVector(vCorners2[2], vCorners2[4], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[2]);
	glVertex3fv(vCorners2[4]);
	glVertex3fv(vCorners2[0]);

	glColor3fv(Cyan);
	gltGetNormalVector(vCorners2[4], vCorners2[6], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[4]);
	glVertex3fv(vCorners2[6]);
	glVertex3fv(vCorners2[0]);

	glColor3fv(Green);
	gltGetNormalVector(vCorners2[6], vCorners2[8], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[6]);
	glVertex3fv(vCorners2[8]);
	glVertex3fv(vCorners2[0]);


	glColor3fv(Pink);
	gltGetNormalVector(vCorners2[8], vCorners2[9], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[8]);
	glVertex3fv(vCorners2[9]);
	glVertex3fv(vCorners2[0]);

	glColor3fv(Lime);
	gltGetNormalVector(vCorners2[9], vCorners2[7], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[9]);
	glVertex3fv(vCorners2[7]);
	glVertex3fv(vCorners2[0]);

	glColor3fv(Cyan);
	gltGetNormalVector(vCorners2[7], vCorners2[5], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[7]);
	glVertex3fv(vCorners2[5]);
	glVertex3fv(vCorners2[0]);

	glColor3fv(Green);
	gltGetNormalVector(vCorners2[5], vCorners2[3], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[5]);
	glVertex3fv(vCorners2[3]);
	glVertex3fv(vCorners2[0]);

	glColor3fv(Lime);
	gltGetNormalVector(vCorners2[3], vCorners2[1], vCorners2[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners2[3]);
	glVertex3fv(vCorners2[1]);
	glVertex3fv(vCorners2[0]);

	glEnd();
	glDisable(GL_CULL_FACE);


	//rysowanie płaszczyzny otworu w sześcianie
	if (cutting_plane)
	{
		//wyłączenie rysowania w buforze kolorów
		glDrawBuffer(GL_NONE);
		// rysowanie kwadratu częściowo odsłaniającego wnętrze sześcianu
		//(kwadrat jest położony o 0,001 jednostki nad bokiem sześcianu)
		glBegin(GL_QUADS);
		glVertex3f(-0.52f, -1.001f, 0.52f);
		glVertex3f(0.52f, -1.001f, 0.52f);
		glVertex3f(0.52f, -1.001f, -0.52f);
		glVertex3f(-0.52f, -1.001f, -0.52f);
		glEnd();
		// włączenie rysowania w buforze kolorów
		glDrawBuffer(GL_BACK);
	}
	// właściwy sześcian z obramowaniem, którego rysowanie wymusza brak oświetlenia
	if (polygon_offset)
		glEnable(GL_POLYGON_OFFSET_FILL);

	glPolygonOffset(1.0, 1.0);

	GLTVector3 vCorners[11] = { { 0.0f, 2.00f, 0.0f }, // Góra 0
	{ -0.52f, -1.0f, -1.24f }, // Skrajny tył lewy 1
	{ 0.52f, -1.0f, -1.24f }, // Skrajny tył prawy 2
	{ -1.28f, -1.0f, -0.54f } , // Tył lewy (za środkiem) 3
	{ 1.28f, -1.0f, -0.54f } ,// Tył prawy (za środkiem) 4
	{ -1.28f, -1.0f, 0.54f }, // Lewy przód (za środkiem) 5
	{ 1.28f, -1.0f, 0.54f }, // Prawy przód (za środkiem) 6
	{ -0.52f, -1.0f, 1.24f } , // Skrajny przód lewy 7
	{ 0.52f, -1.0f, 1.24f } , // Skrajny  przód prawy 8
	{ 0.0f, -1.0f, 1.40f } , // 9
	{ 0.0f, -1.0f, 0.0f } }; // Środek podstawy

							 // Rysowanie piramidy
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);

	//Rysowanie podstawy - 9 trójkątów:
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[9]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[9]);
	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[10]);

	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[10]);

	//Ściany boczne
	gltGetNormalVector(vCorners[1], vCorners[2], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[2], vCorners[4], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[2]);
	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[4], vCorners[6], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[4]);
	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[6], vCorners[8], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[6]);
	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[8], vCorners[9], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[8]);
	glVertex3fv(vCorners[9]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[9], vCorners[7], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[9]);
	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[7], vCorners[5], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[7]);
	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[5], vCorners[3], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[5]);
	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[0]);

	gltGetNormalVector(vCorners[3], vCorners[1], vCorners[0], vNormal);
	glNormal3fv(vNormal);
	glVertex3fv(vCorners[3]);
	glVertex3fv(vCorners[1]);
	glVertex3fv(vCorners[0]);

	glEnd();


	if (polygon_offset)
		glDisable(GL_POLYGON_OFFSET_FILL);

	//skierowanie poleceń do wykonania
	glFlush();
	// Zamiana buforów
	glutSwapBuffers();
}

// zmiana wielkości okna
void Reshape(int width, int height)
{
	// obszar renderingu - całe okno
	glViewport(0, 0, width, height);
	// wybór macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();
	// parametry bryły obcinania
	glFrustum(left, right, bottom, top, near_, far_);
	// generowanie sceny 3D
	Display();
}
// obsługa klawiszy funkcyjnych i klawiszy kursora
void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
		// kursor w lewo
	case GLUT_KEY_LEFT:
		rotatey -= 1;
		break;
		// kursor w górę
	case GLUT_KEY_UP:
		rotatex -= 1;
		break;
		// kursor w prawo
	case GLUT_KEY_RIGHT:
		rotatey += 1;
		break;
		// kursor w dół
	case GLUT_KEY_DOWN:
		rotatex += 1;
		break;
	}
	// odrysowanie okna
	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}
// obsługa przycisków myszki
void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapamiętanie stanu lewego przycisku myszki
		button_state = state;
		// zapamiętanie położenia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}
// obsługa ruchu kursora myszki
void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}
// obsługa menu podręcznego
void Menu(int value)
{
	switch (value)
	{
		// płaszczyzna przekroju
	case CUTTING_PLANE:
		cutting_plane = !cutting_plane;
		Display();
		break;
		// przesunięcie wartości głębi
	case POLYGON_OFFSET:
		polygon_offset = !polygon_offset;
		Display();
		break;
		// wyjście
	case EXIT:
		exit(0);
	}
}
int main(int argc, char * argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// rozmiary głównego okna programu
	glutInitWindowSize(500, 500);
	// utworzenie głównego okna programu
	glutCreateWindow("Z-bufor");
	// dołączenie funkcji generującej scenę 3D
	glutDisplayFunc(Display);
	// dołączenie funkcji wywoływanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);
	// dołączenie funkcji obsługi klawiszy funkcyjnych i klawiszy kursora
	glutSpecialFunc(SpecialKeys);
	// obsługa przycisków myszki
	glutMouseFunc(MouseButton);
	// obsługa ruchu kursora myszki
	glutMotionFunc(MouseMotion);
	// utworzenie menu podręcznego
	glutCreateMenu(Menu);
	// menu główne
	glutCreateMenu(Menu);
#ifdef WIN32
	glutAddMenuEntry("Plaszczyzna przekroju: rysowana/nierysowana", CUTTING_PLANE);
	glutAddMenuEntry("Przesuniecie wartosci glebi: wlacz/wylacz", POLYGON_OFFSET);
	glutAddMenuEntry("Wyjscie", EXIT);
#else
	glutAddMenuEntry("Plaszczyzna przekroju: rysowana/nierysowana", CUTTING_PLANE);
	glutAddMenuEntry("Przesuniecie wartosci glebi: wlacz/wylacz", POLYGON_OFFSET);
	glutAddMenuEntry("Wyjscie", EXIT);
#endif
	// określenie przycisku myszki obsługującej menu podręczne
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// dołączenie funkcji wywoływanej podczas "bezczynności" systemu
	glutIdleFunc(Display);
	// wprowadzenie programu do obsługi pętli komunikatów
	glutMainLoop();
	return 0;
}