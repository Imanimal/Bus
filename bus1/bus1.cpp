#include "stdafx.h"
#include <glut.h>

const int str=10, v1=306, f1=608, v2=144, f2=284, v3=144, f3=284;
float mainbox[v1][3], frontwheels[v2][3], backwheels[v3][3];
int f_mainbox[f1][4], f_frontwheels[f2][3], f_backwheels[f3][3];
char f[str];
float width=1000, height=500;
int angle=0, angle_w=0;
float min_x_v2, min_y_v2, max_x_v2, max_y_v2, sm_x_v2, sm_y_v2;
float min_x_v3, min_y_v3, max_x_v3, max_y_v3, sm_x_v3, sm_y_v3;

void Initialize(){
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-width/2, width/2, -height/2, height/2, -1000, 1000);
	glScalef(6,6,6);
}
 
void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glTranslatef(sm_x_v2, sm_y_v2, 0);
	glRotatef(angle_w, 0.0, 0.0, 1.0);
	glTranslatef(-sm_x_v2, -sm_y_v2, 0);
	glColor3f(0.0,0.0,0.0);
	for(int i=0; i<f2; i++) {
		glBegin(GL_LINE_LOOP);
			glVertex3f(frontwheels[f_frontwheels[i][0]][0], frontwheels[f_frontwheels[i][0]][1], frontwheels[f_frontwheels[i][0]][2]);
			glVertex3f(frontwheels[f_frontwheels[i][1]][0], frontwheels[f_frontwheels[i][1]][1], frontwheels[f_frontwheels[i][1]][2]);
			glVertex3f(frontwheels[f_frontwheels[i][2]][0], frontwheels[f_frontwheels[i][2]][1], frontwheels[f_frontwheels[i][2]][2]);
		glEnd();
	}

	glPopMatrix();
	glPushMatrix();

	glTranslatef(sm_x_v3, sm_y_v3, 0);
	glRotatef(angle_w, 0.0, 0.0, 1.0);
	glTranslatef(-sm_x_v3, -sm_y_v3, 0);
	for(int i=0; i<f3; i++) {
		glBegin(GL_LINE_LOOP);
			glVertex3f(backwheels[f_backwheels[i][0]][0], backwheels[f_backwheels[i][0]][1], backwheels[f_backwheels[i][0]][2]);
			glVertex3f(backwheels[f_backwheels[i][1]][0], backwheels[f_backwheels[i][1]][1], backwheels[f_backwheels[i][1]][2]);
			glVertex3f(backwheels[f_backwheels[i][2]][0], backwheels[f_backwheels[i][2]][1], backwheels[f_backwheels[i][2]][2]);
		glEnd();
	}
	glPopMatrix();

	glColor3f(0.5,0.0,0.0);
	for(int i=0; i<f1; i++) {
		glBegin(GL_LINE_LOOP);
			glVertex3f(mainbox[f_mainbox[i][0]][0], mainbox[f_mainbox[i][0]][1], mainbox[f_mainbox[i][0]][2]);
			glVertex3f(mainbox[f_mainbox[i][1]][0], mainbox[f_mainbox[i][1]][1], mainbox[f_mainbox[i][1]][2]); 
			glVertex3f(mainbox[f_mainbox[i][2]][0], mainbox[f_mainbox[i][2]][1], mainbox[f_mainbox[i][2]][2]);
		glEnd();
	}

	glutSwapBuffers();
}

void Timer(int){
	glRotatef(angle, 0.0, 1.0, 0.0);
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}

void readfile(FILE * bus) {
	while(f[0]!='v')
			fscanf(bus, "%s", &f);
	fscanf(bus, "%s", &f);

	for(int i=0; i<v1; i++){
		while(f[0]!='v')
			fscanf(bus, "%s", &f);
		f[0]=0;
		fscanf(bus, "%f", &mainbox[i][0]);
		fscanf(bus, "%f", &mainbox[i][1]);
		fscanf(bus, "%f", &mainbox[i][2]);
	}
	for(int i=0; i<f1; i++){
		while(f[0]!='f')
			fscanf(bus, "%s", &f);
		f[0]=0;
		fscanf(bus, "%d", &f_mainbox[i][0]);
		f_mainbox[i][0]--;
		fscanf(bus, "%d", &f_mainbox[i][1]);
		f_mainbox[i][1]--;
		fscanf(bus, "%d", &f_mainbox[i][2]);
		f_mainbox[i][2]--;
	}

	for(int i=0; i<v3; i++){
		while(f[0]!='v')
			fscanf(bus, "%s", &f);
		f[0]=0;
		fscanf(bus, "%f", &backwheels[i][0]);
		fscanf(bus, "%f", &backwheels[i][1]);
		fscanf(bus, "%f", &backwheels[i][2]);
	}
	for(int i=0; i<f3; i++){
		while(f[0]!='f')
			fscanf(bus, "%s", &f);
		f[0]=0;
		fscanf(bus, "%d", &f_backwheels[i][0]);
		f_backwheels[i][0]=f_backwheels[i][0]-v1-1;
		fscanf(bus, "%d", &f_backwheels[i][1]);
		f_backwheels[i][1]=f_backwheels[i][1]-v1-1;
		fscanf(bus, "%d", &f_backwheels[i][2]);
		f_backwheels[i][2]=f_backwheels[i][2]-v1-1;
	}

	for(int i=0; i<v2; i++){
		while(f[0]!='v')
			fscanf(bus, "%s", &f);
		f[0]=0;
		fscanf(bus, "%f", &frontwheels[i][0]);
		fscanf(bus, "%f", &frontwheels[i][1]);
		fscanf(bus, "%f", &frontwheels[i][2]);
	}
	for(int i=0; i<f2; i++){
		while(f[0]!='f')
			fscanf(bus, "%s", &f);
		f[0]=0;
		fscanf(bus, "%d", &f_frontwheels[i][0]);
		f_frontwheels[i][0]=f_frontwheels[i][0]-v1-v2-1;
		fscanf(bus, "%d", &f_frontwheels[i][1]);
		f_frontwheels[i][1]=f_frontwheels[i][1]-v1-v2-1;
		fscanf(bus, "%d", &f_frontwheels[i][2]);
		f_frontwheels[i][2]=f_frontwheels[i][2]-v1-v2-1;
	}
	fclose(bus);

	min_x_v2=frontwheels[0][0];
	max_x_v2=frontwheels[0][0];
	min_y_v2=frontwheels[0][1];
	max_y_v2=frontwheels[0][1];

	min_x_v3=backwheels[0][0];
	max_x_v3=backwheels[0][0];
	min_y_v3=backwheels[0][1];
	max_y_v3=backwheels[0][1];

	for (int i=1; i<v2; i++) {
		if (frontwheels[i][0]>max_x_v2)
			max_x_v2=frontwheels[i][0];
		if (frontwheels[i][0]<min_x_v2)
			min_x_v2=frontwheels[i][0];
		if (frontwheels[i][1]>max_y_v2)
			max_y_v2=frontwheels[i][1];
		if (frontwheels[i][1]<min_y_v2)
			min_y_v2=frontwheels[i][1];
		if (backwheels[i][0]>max_x_v3)
			max_x_v3=backwheels[i][0];
		if (backwheels[i][0]<min_x_v3)
			min_x_v3=backwheels[i][0];
		if (backwheels[i][1]>max_y_v3)
			max_y_v3=backwheels[i][1];
		if (backwheels[i][1]<min_y_v3)
			min_y_v3=backwheels[i][1];
	}
	sm_x_v2=min_x_v2+((max_x_v2-min_x_v2)/2);
	sm_y_v2=min_y_v2+((max_y_v2-min_y_v2)/2);
	sm_x_v3=min_x_v3+((max_x_v3-min_x_v3)/2);
	sm_y_v3=min_y_v3+((max_y_v3-min_y_v3)/2);
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'a':
		angle++;
		break;
	case 'd':
		angle--;
		break;
	case 'w':
		angle_w-=5;
		break;
	case 's':
		angle_w+=5;
		break;
	}
}

int main(int argc, char **argv) {
	FILE * bus;
	bus = fopen ("bus5.obj","rt");
	if (bus==NULL) {
		printf("File not found.");
		return 0;
	}
	readfile(bus);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Автобус");
	glutDisplayFunc(Draw);
	glutTimerFunc(50, Timer, 0);
	glutKeyboardFunc(Keyboard);
	Initialize();
	glutMainLoop();
	return 0;
}