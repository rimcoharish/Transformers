#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "parts.hpp"

double offset=0.005;
GLuint TyreTex,ArmTex,LegTex,TorsoSideTex,TorsoFrontTex,HeadFrontTex;

GLuint getTexture(const char * imagepath){
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	unsigned char * data;
	FILE * file = fopen(imagepath,"rb");
	fread(header, 1, 54, file);
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	data = new unsigned char [imageSize];
	fread(data,1,imageSize,file);
	fclose(file);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	delete[] data;
	return textureID;
}

void initTextures(){
	TyreTex  = getTexture("./images/Tyre.bmp");
	ArmTex  = getTexture("./images/Hand.bmp");
	LegTex  = getTexture("./images/Leg.bmp");
	TorsoSideTex  = getTexture("./images/TorsoSide.bmp");
	TorsoFrontTex  = getTexture("./images/TorsoFront.bmp");
	HeadFrontTex  = getTexture("./images/Head.bmp");
}



void struct_cube()
{
	glNewList(cube,GL_COMPILE);

		glPushMatrix();
		/*glColor3f(0,0,0.4);*/
		glBegin(GL_POLYGON); //front face at z=1.0
			glVertex3f(0,1,1);
			glVertex3f(0,0,1);
			glVertex3f(1,0,1);
			glVertex3f(1,1,1);
		glEnd();

		/*glColor3f(0.1,0,0.8);*/
		glBegin(GL_POLYGON); //back face at z=0.0
			glVertex3f(0,0,0);
			glVertex3f(0,1,0);
			glVertex3f(1,1,0);
			glVertex3f(1,0,0);
		glEnd();

		/*glColor3f(0.2,0.6,0.2);*/
		glBegin(GL_POLYGON); //top face at y=1.0
			glVertex3f(0,1,0);
			glVertex3f(0,1,1);
			glVertex3f(1,1,1);
			glVertex3f(1,1,0);
		glEnd();

		/*glColor3f(0.2,0.1,0.2);*/
		glBegin(GL_POLYGON); //bottom face at y=0.0
			glVertex3f(0,0,0);
			glVertex3f(1,0,0);
			glVertex3f(1,0,1);
			glVertex3f(0,0,1);  	
		glEnd();

		/*glColor3f(0.6,0.1,0.9);*/
		glBegin(GL_POLYGON); //right face at x=1.0
			glVertex3f(1,1,0);
			glVertex3f(1,1,1);
			glVertex3f(1,0,1);
			glVertex3f(1,0,0);
		glEnd();

		/*glColor3f(0.6,0.9,0.1);*/
		glBegin(GL_POLYGON); //left face at x=0.0
			glVertex3f(0,1,0);
			glVertex3f(0,0,0);
			glVertex3f(0,0,1);
			glVertex3f(0,1,1);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		double offset = 0.0005;
		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(0 - offset,1 + offset,1 + offset);
			glVertex3f(0 - offset,0 - offset,1 + offset);
			glVertex3f(1 + offset,0 - offset,1 + offset);
			glVertex3f(1 + offset,1 + offset,1 + offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(0 - offset,0 - offset,0 - offset);
			glVertex3f(0 - offset,1 + offset,0 - offset);
			glVertex3f(1 + offset,1 + offset,0 - offset);
			glVertex3f(1 + offset,0 - offset,0 - offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(0 - offset,1 + offset,0 - offset);
			glVertex3f(0 - offset,1 + offset,1 + offset);
			glVertex3f(1 + offset,1 + offset,1 + offset);
			glVertex3f(1 + offset,1 + offset,0 - offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(0 - offset,0 - offset,0 - offset);
			glVertex3f(1 + offset,0 - offset,0 - offset);
			glVertex3f(1 + offset,0 - offset,1 + offset);
			glVertex3f(0 - offset,0 - offset,1 + offset);  	
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(1 + offset,1 + offset,0 - offset);
			glVertex3f(1 + offset,1 + offset,1 + offset);
			glVertex3f(1 + offset,0 - offset,1 + offset);
			glVertex3f(1 + offset,0 - offset,0 - offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(0 - offset,1 + offset,0 - offset);
			glVertex3f(0 - offset,0 - offset,0 - offset);
			glVertex3f(0 - offset,0 - offset,1 + offset);
			glVertex3f(0 - offset,1 + offset,1 + offset);
		glEnd();
		glPopMatrix();

	glEndList();
}

void struct_trapezium()
{
	glNewList(trapezium,GL_COMPILE);

		double down = 0.4;

		glPushMatrix();
		/*glColor3f(0,0,0.4);*/
		glBegin(GL_POLYGON); //front face at z=1.0
			glVertex3f(-0.5,0.5,0.5);
			glVertex3f(-down,-0.5,down);
			glVertex3f(down,-0.5,down);
			glVertex3f(0.5,0.5,0.5);
		glEnd();

		/*glColor3f(0.1,0,0.8);*/
		glBegin(GL_POLYGON); //back face at z=0.0
			glVertex3f(-0.5,0.5,-0.5);
			glVertex3f(0.5,0.5,-0.5);
			glVertex3f(down,-0.5,-down);
			glVertex3f(-down,-0.5,-down);
		glEnd();

		/*glColor3f(0.2,0.6,0.2);*/
		glBegin(GL_POLYGON); //top face at y=1.0
			glVertex3f(0.5,0.5,0.5);
			glVertex3f(down,-0.5,down);
			glVertex3f(down,-0.5,-down);
			glVertex3f(0.5,0.5,-0.5);
		glEnd();

		/*glColor3f(0.2,0.1,0.2);*/
		glBegin(GL_POLYGON); //bottom face at y=0.0
			glVertex3f(-0.5,0.5,0.5);
			glVertex3f(-0.5,0.5,-0.5);
			glVertex3f(-down,-0.5,-down);
			glVertex3f(-down,-0.5,down);
		glEnd();

		/*glColor3f(0.6,0.1,0.9);*/
		glBegin(GL_POLYGON); //right face at x=1.0
			glVertex3f(-0.5,0.5,0.5);
			glVertex3f(0.5,0.5,0.5);
			glVertex3f(0.5,0.5,-0.5);
			glVertex3f(-0.5,0.5,-0.5);
		glEnd();

		/*glColor3f(0.6,0.9,0.1);*/
		glBegin(GL_POLYGON); //left face at x=0.0
			glVertex3f(-down,-0.5,down);
			glVertex3f(-down,-0.5,-down);
			glVertex3f(down,-0.5,-down);
			glVertex3f(down,-0.5,down);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		double offset = 0.0005;
		glBegin(GL_LINE_LOOP);
			glVertex3f(- 0.5 - offset,0.5 + offset,0.5 + offset);
			glVertex3f(- down - offset,- 0.5 - offset,down + offset);
			glVertex3f(down + offset,- 0.5 - offset,down + offset);
			glVertex3f(0.5 + offset,0.5 + offset,0.5 + offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(- 0.5 - offset,0.5 + offset,- 0.5 - offset);
			glVertex3f(0.5 + offset,0.5 + offset,- 0.5 - offset);
			glVertex3f(down + offset,- 0.5 - offset,- down - offset);
			glVertex3f(- down - offset,- 0.5 - offset,- down - offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(0.5 + offset,0.5 + offset,0.5 + offset);
			glVertex3f(down + offset,- 0.5 - offset,down + offset);
			glVertex3f(down + offset,- 0.5 - offset,- down - offset);
			glVertex3f(0.5 + offset,0.5 + offset,- 0.5 - offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(- 0.5 - offset,0.5 + offset,0.5 + offset);
			glVertex3f(- 0.5 - offset,0.5 + offset,- 0.5 - offset);
			glVertex3f(- down - offset,- 0.5 - offset,- down - offset);
			glVertex3f(- down - offset,- 0.5 - offset,down + offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(- 0.5 - offset,0.5 + offset,0.5 + offset);
			glVertex3f(0.5 + offset,0.5 + offset,0.5 + offset);
			glVertex3f(0.5 + offset,0.5 + offset,- 0.5 - offset);
			glVertex3f(- 0.5 - offset,0.5 + offset,- 0.5 - offset);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(- down - offset,- 0.5 - offset,down + offset);
			glVertex3f(- down - offset,- 0.5 - offset,- down - offset);
			glVertex3f(down + offset,- 0.5 - offset,- down - offset);
			glVertex3f(down + offset,- 0.5 - offset,down + offset);
		glEnd();
		glPopMatrix();

	glEndList();
}

void struct_cylinder(){
	double r = 1.0, h = 1.0;
	glNewList(cylinder, GL_COMPILE);
		glPushMatrix();
		/*glColor3f(0.2,0.1,0.2);*/
		glBegin(GL_POLYGON);
			for(int i = 0; i < 360; i++){
				glVertex3f(r * cos((i * M_PI) / 180), h / 2, r * sin((i * M_PI) / 180));
			}
		glEnd();
		glBegin(GL_POLYGON);
			for(int i = 0; i < 360; i++){
				glVertex3f(r * cos((i * M_PI) / 180), - h / 2, r * sin((i * M_PI) / 180));
			}
		glEnd();
		/*glColor3f(0.6,0.9,0.1);*/
		for(int i = 0; i < 360; i++){
			glBegin(GL_POLYGON);
					glVertex3f(r * cos((i * M_PI) / 180), h / 2, r * sin((i * M_PI) / 180));
					glVertex3f(r * cos((i * M_PI) / 180), - h / 2, r * sin((i * M_PI) / 180));
					glVertex3f(r * cos(((i + 1) * M_PI) / 180), - h / 2, r * sin(((i + 1) * M_PI) / 180));
					glVertex3f(r * cos(((i + 1) * M_PI) / 180), h / 2, r * sin(((i + 1) * M_PI) / 180));
			glEnd();
		}
		glPopMatrix();
	glEndList();
}

void struct_thigh(){

	glNewList(thigh, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.2,0.1,0.2);
			glScalef(csX75::thigh_x, csX75::thigh_y, csX75::thigh_z);
			glCallList(cylinder);

		glPopMatrix();

	glEndList();
}

void struct_knee_joint(){

	glNewList(knee_joint, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.2,0.1,0.2);
			glTranslatef(0, - csX75::thigh_y / 2 - csX75::knee_joint_length / 2, 0);
			glScalef(csX75::thigh_x, csX75::knee_joint_length, csX75::thigh_z);
			glCallList(cylinder);

		glPopMatrix();

	glEndList();
}

void struct_leg(){

	glNewList(leg, GL_COMPILE);

		glPushMatrix();

			glColor3f(0, 0, 1);
			glTranslatef(- csX75::shin_x / 2, - csX75::shin_y - csX75::thigh_y / 2, - csX75::shin_z / 2);
			glScalef(csX75::shin_x, csX75::shin_y, csX75::shin_z);

			glEnable(GL_TEXTURE_2D);//right side
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, LegTex);
				glPushMatrix();
					glBegin(GL_QUADS);
						glTexCoord2f(0,0);glVertex3f(1 + offset,0 - offset,1 + offset);
						glTexCoord2f(1,0);glVertex3f(1 + offset,0 - offset,0 - offset);
						glTexCoord2f(1,1);glVertex3f(1 + offset,1 + offset,0 - offset);
						glTexCoord2f(0,1);glVertex3f(1 + offset,1 + offset,1 + offset);
					glEnd();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);//left side
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, LegTex);
				glPushMatrix();
					glBegin(GL_QUADS);
						glTexCoord2f(0,0);glVertex3f(0 - offset,0 - offset,1 + offset);
						glTexCoord2f(1,0);glVertex3f(0 - offset,0 - offset,0 - offset);
						glTexCoord2f(1,1);glVertex3f(0 - offset,1 + offset,0 - offset);
						glTexCoord2f(0,1);glVertex3f(0 - offset,1 + offset,1 + offset);
					glEnd();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);//front
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, LegTex);
				glPushMatrix();
					glBegin(GL_QUADS);
						glTexCoord2f(0,0);glVertex3f(0 - offset,0 - offset,1 + offset);
						glTexCoord2f(1,0);glVertex3f(1 + offset,0 - offset,1 + offset);
						glTexCoord2f(1,1);glVertex3f(1 + offset,1 + offset,1 + offset);
						glTexCoord2f(0,1);glVertex3f(0 - offset,1 + offset,1 + offset);
					glEnd();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glCallList(cube);

		glPopMatrix();

		glPushMatrix();

			glColor3f(1, 0.2, 0);
			glTranslatef(- csX75::shin_x / 2, - csX75::shin_y - csX75::foot_y - csX75::thigh_y / 2, - csX75::shin_z / 2);
			glScalef(csX75::foot_x, csX75::foot_y, csX75::foot_z);
			glCallList(cube);

		glPopMatrix();

	glEndList();
}

void struct_hip(){

	glNewList(hip, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.2, 0.2, 0.2);
			glScalef(csX75::hip_x, csX75::hip_y, csX75::hip_z);
			glCallList(trapezium);

		glPopMatrix();

	glEndList();

}

void struct_upper_arm(){

	glNewList(upper_arm, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.2,0.1,0.2);
			glScalef(csX75::upper_arm_x, csX75::upper_arm_y, csX75::upper_arm_z);	
			glCallList(cylinder);

		glPopMatrix();

	glEndList();
}

void struct_lower_arm(){

	glNewList(lower_arm, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.133, 0.184, 0.361);
			glScalef(csX75::lower_arm_x, csX75::lower_arm_y, csX75::lower_arm_z);

			glEnable(GL_TEXTURE_2D);//right side
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, ArmTex);
				glPushMatrix();
					glBegin(GL_QUADS);
						glTexCoord2f(0,0);glVertex3f(1 + offset,0 - offset,1 + offset);
						glTexCoord2f(1,0);glVertex3f(1 + offset,0 - offset,0 - offset);
						glTexCoord2f(1,1);glVertex3f(1 + offset,1 + offset,0 - offset);
						glTexCoord2f(0,1);glVertex3f(1 + offset,1 + offset,1 + offset);
					glEnd();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);//left side
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, ArmTex);
				glPushMatrix();
					glBegin(GL_QUADS);
						glTexCoord2f(0,0);glVertex3f(0 - offset,0 - offset,1 + offset);
						glTexCoord2f(1,0);glVertex3f(0 - offset,0 - offset,0 - offset);
						glTexCoord2f(1,1);glVertex3f(0 - offset,1 + offset,0 - offset);
						glTexCoord2f(0,1);glVertex3f(0 - offset,1 + offset,1 + offset);
					glEnd();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);//front
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glBindTexture(GL_TEXTURE_2D, ArmTex);
				glPushMatrix();
					glBegin(GL_QUADS);
						glTexCoord2f(0,0);glVertex3f(0 - offset,0 - offset,1 + offset);
						glTexCoord2f(1,0);glVertex3f(1 + offset,0 - offset,1 + offset);
						glTexCoord2f(1,1);glVertex3f(1 + offset,1 + offset,1 + offset);
						glTexCoord2f(0,1);glVertex3f(0 - offset,1 + offset,1 + offset);
					glEnd();
				glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glCallList(cube);

		glPopMatrix();

	glEndList();
}

void struct_front_tyres(){

	glNewList(front_tyres, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(csX75::lower_arm_x / 2, 0, 0);
			glRotatef(csX75::tyre_x_angle, 1, 0, 0);
			glRotatef(csX75::front_tyre_y_angle, 0, 1, 0);
			glRotatef(90, 0, 0, 1);
			glScalef(csX75::tyre_x, csX75::tyre_y, csX75::tyre_z);
			glCallList(cylinder);

		glPopMatrix();

	glEndList();
}

void struct_cone(){

	glNewList(cone, GL_COMPILE);

		double r = 1, h = 1;

		glPushMatrix();
	
		for(int i = 0; i < 360; i++){
			glBegin(GL_POLYGON);
					glVertex3f(r * cos((i * M_PI) / 180), 0, r * sin((i * M_PI) / 180));
					glVertex3f(r * cos((i + 1) * M_PI / 180), 0, r * sin((i + 1) * M_PI / 180));
					glVertex3f(0, h, 0);
			glEnd();
		}

		glPopMatrix();

	glEndList();
}

void struct_neck(){

	glNewList(neck, GL_COMPILE);

		glColor3f(0.6, 0.2, 0.1);

		glPushMatrix();

			glScalef(csX75::neck_x, csX75::neck_y, csX75::neck_z);
			glCallList(cylinder);

		glPopMatrix();

	glEndList();

}

void struct_back_tyres(){

	double q = 1.0/sqrt(2);

	glNewList(back_tyres, GL_COMPILE);

		glColor3f(0, 0, 0);
		glRotatef(90, 0, 0, 1);
		glScalef(csX75::tyre_x, csX75::tyre_y, csX75::tyre_z);

		glEnable(GL_TEXTURE_2D);//tyre right
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, TyreTex);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0);glVertex3f(-q-offset,0.5+offset,q+offset);
					glTexCoord2f(1,0);glVertex3f(q+offset,0.5+offset,q+offset);
					glTexCoord2f(1,1);glVertex3f(q+offset,0.5+offset,-q-offset);
					glTexCoord2f(0,1);glVertex3f(-q-offset,0.5+offset,-q-offset);
				glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);//tyre right
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, TyreTex);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0);glVertex3f(-q-offset,-0.5-offset,q+offset);
					glTexCoord2f(1,0);glVertex3f(q+offset,-0.5-offset,q+offset);
					glTexCoord2f(1,1);glVertex3f(q+offset,-0.5-offset,-q-offset);
					glTexCoord2f(0,1);glVertex3f(-q-offset,-0.5-offset,-q-offset);
				glEnd();
			glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		
		glCallList(cylinder);

	glEndList();

}

void struct_torso(){

	glNewList(torso, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.133, 0.184, 0.361);

			glTranslatef(- csX75::torso_x / 2, 0, - csX75::torso_z / 2);
			glScalef(csX75::torso_x, csX75::torso_y, csX75::torso_z);

			glEnable(GL_TEXTURE_2D);//right
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
					glBindTexture(GL_TEXTURE_2D, TorsoSideTex);
					glPushMatrix();
						glBegin(GL_QUADS);
							glTexCoord2f(0,0);glVertex3f(1 + offset,0 - offset,1 + offset);
							glTexCoord2f(1,0);glVertex3f(1 + offset,0 - offset,0 - offset);
							glTexCoord2f(1,1);glVertex3f(1 + offset,1 + offset,0 - offset);
							glTexCoord2f(0,1);glVertex3f(1 + offset,1 + offset,1 + offset);
						glEnd();
					glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);//left
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
					glBindTexture(GL_TEXTURE_2D, TorsoSideTex);
					glPushMatrix();
						glBegin(GL_QUADS);
							glTexCoord2f(0,0);glVertex3f(0 - offset,0 - offset,1 + offset);
							glTexCoord2f(1,0);glVertex3f(0 - offset,0 - offset,0 - offset);
							glTexCoord2f(1,1);glVertex3f(0 - offset,1 + offset,0 - offset);
							glTexCoord2f(0,1);glVertex3f(0 - offset,1 + offset,1 + offset);
						glEnd();
					glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glEnable(GL_TEXTURE_2D);//front
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
					glBindTexture(GL_TEXTURE_2D, TorsoFrontTex);
					glPushMatrix();
						glBegin(GL_QUADS);
							glTexCoord2f(0,0);glVertex3f(0 - offset,0 - offset,1 + offset);
							glTexCoord2f(1,0);glVertex3f(1 + offset,0 - offset,1 + offset);
							glTexCoord2f(1,1);glVertex3f(1 + offset,1 + offset,1 + offset);
							glTexCoord2f(0,1);glVertex3f(0 - offset,1 + offset,1 + offset);
						glEnd();
					glPopMatrix();
			glDisable(GL_TEXTURE_2D);

			glCallList(cube);

		glPopMatrix();

	glEndList();

}

void struct_head(){

	glNewList(head, GL_COMPILE);

		glPushMatrix();

				glTranslatef(- csX75::head_x / 2, 0, -csX75::head_z / 2);
				glScalef(csX75::head_x, csX75::head_y, csX75::head_z);

				glEnable(GL_TEXTURE_2D);//front
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
					glBindTexture(GL_TEXTURE_2D, HeadFrontTex);
					glPushMatrix();
						glBegin(GL_QUADS);
							glTexCoord2f(0,0);glVertex3f(0 - offset,0 - offset,1 + offset);
							glTexCoord2f(1,0);glVertex3f(1 + offset,0 - offset,1 + offset);
							glTexCoord2f(1,1);glVertex3f(1 + offset,1 + offset,1 + offset);
							glTexCoord2f(0,1);glVertex3f(0 - offset,1 + offset,1 + offset);
						glEnd();
					glPopMatrix();
				glDisable(GL_TEXTURE_2D);

				glCallList(cube);

			glPopMatrix();

	glEndList();

}