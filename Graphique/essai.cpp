/* 1. environnement 3D avec la bonne perspective
2. apparaitre les pièces
3. faire tourner et descendre les pièces 
4. gérer les lignes*/

/* 1.*/

#include <gtk/gtk.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <Piece.h>
#include <PieceFactory.h>

struct glutWindow{
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
};

glutWindow win;

void initialize(){
    // select projection matrix
	glMatrixMode(GL_PROJECTION);

	// set the viewport
	glViewport(0, 0, win.width, win.height);

	// set matrix mode
	glMatrixMode(GL_PROJECTION);

	// reset projection matrix
	glLoadIdentity();
	GLfloat aspect = (GLfloat)win.width / win.height;

	// set up a perspective projection matrix
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);

	// specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);

	// specify the clear value for the depth buffer
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// specify implementation-specific hints
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat amb_light[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat diffuse[] = { 0.5, 0.5, 0.5, 1 };
	GLfloat specular[] = { 0.5, 0.5, 0.6, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
	float i;
	char scr[20];
	char scre[20];

	strcpy_s(scr, "S C O R E : ");
	sprintf_s(scre, "%d", score);
	strcat_s(scr, scre);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	printTxt(1.0f, 1.0f, scr);

	glLoadIdentity();
	gluLookAt(zoom, 2, 0, 0, 0, 0, 0, 1, 0);


	glPushMatrix();

	glColor3f(0, 1, 1);
	glTranslatef(0, 0, 0);
	glRotatef(leftRight_rotation, 0, 1, 0);
	glRotatef(upDown_x, 1, 0, 0);
	glRotatef(upDown_z, 0, 0, 1);


	glColor3f(0.7, 0.6, 0.9);
	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(i, N / 2, -N / 2);
		glVertex3f(i, -N / 2, -N / 2);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(N / 2, i, -N / 2);
		glVertex3f(-N / 2, i, -N / 2);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-N / 2, N / 2, i);
		glVertex3f(-N / 2, -N / 2, i);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(-N / 2, i, N / 2);
		glVertex3f(-N / 2, i, -N / 2);
		glEnd();
	}


	glColor3f(0.9, 0.9, 0.6);
	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(i, -N / 2, -N / 2);
		glVertex3f(i, -N / 2, N / 2);
		glEnd();
	}

	for (i = -N / 2; i <= N / 2; i++)
	{
		glBegin(GL_LINES);
		glVertex3f(N / 2, -N / 2, i);
		glVertex3f(-N / 2, -N / 2, i);
		glEnd();
	}

	glPopMatrix();

	if (!gameOver)
	{
		/*shp.drawShape(d, movex, down, movez, leftRight_rotation, upDown_x, upDown_z);*/

		putInBase();
	}
	else
	{
		strcpy_s(scr, "G A M E  O V E R");
		printTxt(4.0f, 5.0f, scr);
	}

	drawBase();

	if (!stop)
	{
		down -= down_speed;
	}

	glutSwapBuffers();
	glFlush();

}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
	int moires = 0;

	if (leftRight_rotation < 0)
		moires = leftRight_rotation % 360 + 360;
	else
		moires = leftRight_rotation % 360;


	switch (key)
	{
	case 's':
		if (stop)
			stop = false;
		else
			stop = true;

		break;

	case 'i':
		if (moires <= 45 || moires > 315)
		{
			upDown_z += r_speed;
		}
		else if (moires > 135 && moires <= 225)
		{
			upDown_z -= r_speed;
		}
		else if (moires > 45 && moires <= 135)
		{
			upDown_x -= r_speed;
		}
		else if (moires > 225 && moires <= 315)
		{
			upDown_x += r_speed;
		}

		break;

	case 'k':
		if (moires <= 45 || moires > 315)
		{
			upDown_z -= r_speed;
		}
		else if (moires > 135 && moires <= 225)
		{
			upDown_z += r_speed;
		}
		else if (moires > 45 && moires <= 135)
		{
			upDown_x += r_speed;
		}
		else if (moires > 225 && moires <= 315)
		{
			upDown_x -= r_speed;
		}

		break;

	case '-':
		if (down_speed > 0.01 && !stop)
			down_speed -= 0.005;
		break;

	case '=':
		if (down_speed <= 0.10 && !stop)
			down_speed += 0.005;
		break;

	case 'j':
		leftRight_rotation += r_speed;
		break;

	case 'l':
		leftRight_rotation -= r_speed;
		break;

	case 'x':
		if (!stop)
			Piece::RotateForward()
		break;

	case 'c':
		if (!stop)
			Piece::RotateBackward()
		break;

	case 'v':
		if (!stop)
			Piece::RotateCW();
		break;
    case 'b':
        if(!stop)
            Piece::RotateCCW();
        break;
	case KEY_ESCAPE:
		exit(0);
		break;

	default:
		break;
	}


    

int main(int argc, char **argv) {	
    // set window values
	win.width = 640;
	win.height = 480;
	win.title = "Tetris 3D";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	glutInit(&argc, argv);                           // Initialize glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  		// Display Mode
	glutInitWindowSize(win.width, win.height);                    // Set the window size
	glutCreateWindow("Tetris 3D");                 // Create the window with given title
	glutDisplayFunc(display);                       // Set the display function
	glutIdleFunc(display);
	glutKeyboardFunc(keyboard);                  // Set the normal keyboard function
	//glutSpecialFunc(special_keys);                  // Set the special keyboard function
//	glutMouseFunc(mouse_button);                    // Set the mouse button function
	initialize();
	glutMainLoop();                                 // Initialize main loop

	return 0;
}