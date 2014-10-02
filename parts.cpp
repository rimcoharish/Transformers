#include "parts.hpp"

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
			glCallList(cube);

		glPopMatrix();

		glPushMatrix();

			glColor3f(1, 0.2, 0);
			glTranslatef(- csX75::shin_x / 2, - csX75::shin_y - csX75::foot_y - csX75::thigh_y / 2, - csX75::shin_z / 2);
			glScalef(csX75::foot_x, csX75::foot_y, csX75::foot_z);
			glCallList(cube);

		glPopMatrix();

		glPushMatrix();

			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0, - csX75::thigh_y / 2 - csX75::tyre_x, - (csX75::shin_z / 2 + (0.05 * csX75::hip_z)));
			glRotatef(90, 0, 0, 1);
			glScalef(csX75::tyre_x, csX75::tyre_y, csX75::tyre_z);
			glCallList(cylinder);

		glPopMatrix();

		glPushMatrix();

			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(0, - csX75::thigh_y / 2 - csX75::shin_y - csX75::foot_y + csX75::tyre_x, - (csX75::shin_z / 2 + (0.05 * csX75::hip_z)));
			glRotatef(90, 0, 0, 1);
			glScalef(csX75::tyre_x, csX75::tyre_y, csX75::tyre_z);
			glCallList(cylinder);

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

			glColor3f(0.5, 0.5, 0.5);
			glScalef(csX75::upper_arm_x, csX75::upper_arm_y, csX75::upper_arm_z);	
			glCallList(cylinder);

		glPopMatrix();

	glEndList();
}

void struct_lower_arm(){

	glNewList(lower_arm, GL_COMPILE);

		glPushMatrix();

			glColor3f(1, 1, 1);
			glScalef(csX75::lower_arm_x, csX75::lower_arm_y, csX75::lower_arm_z);	
			glCallList(cube);

		glPopMatrix();

		glPushMatrix();

			glCallList(front_tyres);

		glPopMatrix();

	glEndList();
}

/*void struct_hand(){

	glNewList(hand, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.5, 0.5, 0.5);
			glTranslatef(csX75::hand_x / 2, csX75::hand_y / 2, csX75::hand_z / 2);
			glTranslatef(0, - (csX75::upper_arm_y / 2 + ))
}*/

void struct_front_tyres(){

	glNewList(front_tyres, GL_COMPILE);

		glPushMatrix();

			glColor3f(0.1, 0.1, 0.1);
			glTranslatef(csX75::lower_arm_x / 2, 0, 0);
			glRotatef(90, 0, 0, 1);
			glScalef(csX75::tyre_x, csX75::tyre_y, csX75::tyre_z);
			glCallList(cylinder);

		glPopMatrix();

	glEndList();
}