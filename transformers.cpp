#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "gl_framework.hpp"
#include "parts.hpp"

using namespace std;
// using namespace csX75;

//! The pointer to the GLFW window
GLFWwindow* window;

void init_structures(){
	initTextures();
	struct_cylinder();
	struct_cube();
	struct_thigh();
	struct_leg();
	struct_knee_joint();
	struct_trapezium();
	struct_hip();
	struct_upper_arm();
	struct_lower_arm();
	struct_front_tyres();
	struct_cone();
	struct_neck();
	struct_back_tyres();
	struct_head();
	struct_torso();
	struct_surrounding();
	csX75::ChangeView();
}

GLFWwindow* getWindow(){
	return window;
}

GLuint getTexture(const char * imagepath);


void renderRoom(GLFWwindow* window){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	gluLookAt(csX75::currentCamera[0],csX75::currentCamera[1],csX75::currentCamera[2],
				csX75::currentCamera[3],csX75::currentCamera[4],csX75::currentCamera[5],
					csX75::currentCamera[6],csX75::currentCamera[7],csX75::currentCamera[8]);

	csX75::ChangeView();
	// csX75::viewer();
	// csX75::changeOtherCameraCordinates();

	// for(int i=0;i<9;i++){cout<<csX75::currentCamera[i]<<" ";}cout<<endl;

	glCallList(surrounding);
}




void renderGL(GLFWwindow* window){

	renderRoom(window);

	double q = 1.0/sqrt(2);
	double offset = 0.01;

	
	glTranslatef(0,2,0);
	glTranslatef(csX75::translate_x, csX75::translate_y, csX75::translate_z);

	glRotatef(csX75::angle_y, 0, 1, 0);
	glRotatef(csX75::angle_x, 1, 0, 0);

	glPushMatrix();

		glColor3f(1, 0, 0);
		glTranslatef(0, csX75::hip_y / 2, 0);

		glPushMatrix();

			glCallList(torso);

			//left hand
			glPushMatrix();

				glTranslatef((csX75::upper_arm_x + csX75::torso_x / 2), csX75::torso_y - csX75::upper_arm_y / 2, 0);
				glTranslatef(- csX75::upper_arm_x, csX75::upper_arm_y / 2, 0);
				glRotatef(csX75::left_upper_arm_z_angle, 0, 0, 1);
				glTranslatef(csX75::upper_arm_x, 0, 0);
				glRotatef(csX75::left_upper_arm_x_angle, 1, 0, 0);
				glTranslatef(0, - csX75::upper_arm_y / 2, 0);
				glCallList(upper_arm);
				glTranslatef(0, - csX75::upper_arm_y / 2, - csX75::lower_arm_z / 2);
				glRotatef(csX75::left_elbow_angle, 1, 0, 0);
				glTranslatef(- csX75::lower_arm_x / 2, - csX75::lower_arm_y, 0);
				glCallList(lower_arm);

				glPushMatrix();

					glColor3f(0.1, 0.1, 0.1);
					glTranslatef(csX75::lower_arm_x / 2, 0, 0);
					glRotatef(- csX75::right_elbow_angle - csX75::right_upper_arm_x_angle, 1, 0, 0);
					glRotatef(csX75::front_tyre_y_angle, 0, 1, 0);
					glRotatef(-csX75::tyre_x_angle, 1, 0, 0);
					glRotatef(csX75::right_elbow_angle + csX75::right_upper_arm_x_angle, 1, 0, 0);
					glCallList(back_tyres);

				glPopMatrix();

			glPopMatrix();

			//right hand

			glPushMatrix();

				glTranslatef(- (csX75::upper_arm_x + csX75::torso_x / 2), csX75::torso_y - csX75::upper_arm_y / 2, 0);
				glTranslatef(csX75::upper_arm_x, csX75::upper_arm_y / 2, 0);
				glRotatef(csX75::right_upper_arm_z_angle, 0, 0, 1);
				glTranslatef(- csX75::upper_arm_x, 0, 0);
				glRotatef(csX75::right_upper_arm_x_angle, 1, 0, 0);
				glTranslatef(0, - csX75::upper_arm_y / 2, 0);
				glCallList(upper_arm);
				glTranslatef(0, - csX75::upper_arm_y / 2, - csX75::lower_arm_z / 2);
				glRotatef(csX75::right_elbow_angle, 1, 0, 0);
				glTranslatef(- csX75::lower_arm_x / 2, - csX75::lower_arm_y, 0);
				glCallList(lower_arm);

				glPushMatrix();

					glColor3f(0.1, 0.1, 0.1);
					glTranslatef(csX75::lower_arm_x / 2, 0, 0);
					glRotatef(- csX75::right_elbow_angle - csX75::right_upper_arm_x_angle, 1, 0, 0);
					glRotatef(csX75::front_tyre_y_angle, 0, 1, 0);
					glRotatef(-csX75::tyre_x_angle, 1, 0, 0);
					glRotatef(csX75::right_elbow_angle + csX75::right_upper_arm_x_angle, 1, 0, 0);
					glCallList(back_tyres);

				glPopMatrix();

			glPopMatrix();

			glPushMatrix();
			
				glTranslatef(0, csX75::neck_translate, 0);

				glCallList(neck);

				glPushMatrix();

					glTranslatef(0, csX75::neck_y / 2, 0);

					glPushMatrix();

						glScalef(csX75::neck_joint_x, csX75::neck_joint_y, csX75::neck_joint_z);
						glCallList(cone);

					glPopMatrix();

					glColor3f(0.133, 0.184, 0.361);

					glPushMatrix();

						glRotatef(csX75::head_x_angle, 1, 0, 0);
						glRotatef(csX75::head_y_angle, 0, 1, 0);
						glRotatef(csX75::head_z_angle, 0, 0, 1);
						glCallList(head);

					glPopMatrix();

				glPopMatrix();

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();

	glPushMatrix();

		glTranslatef(0, 0, csX75::hip_center_z);
		glTranslatef(0, csX75::hip_y / 2, csX75::torso_z / 2);
		glRotatef(csX75::hip_center_angle, 1, 0, 0);
		glTranslatef(0, - csX75::hip_y / 2, - csX75::torso_z / 2);

		glCallList(hip);

		//left leg
		glPushMatrix();

			glTranslatef(csX75::leg_x, csX75::leg_y, csX75::leg_z);
			glTranslatef(0, csX75::thigh_y / 2, 0);
			glRotatef(- csX75::left_leg_hip_angle, 1, 0, 0);
			glRotatef(csX75::left_leg_angle, 0, 1, 0);
			glRotatef(csX75::left_leg_hip_z_angle, 0, 0, 1);
			glTranslatef(0, - csX75::thigh_y / 2, 0);
			glCallList(thigh);
			glCallList(knee_joint);
			glTranslatef(0, - csX75::thigh_y/ 2, 0);
			glRotatef(- csX75::left_knee_angle, 1, 0, 0);
			glTranslatef(0, csX75::thigh_y / 2, 0);
			glCallList(leg);

			//tyres
			glPushMatrix();

				glColor3f(0.1, 0.1, 0.1);
				glTranslatef(0, - csX75::thigh_y / 2 - csX75::tyre_x, - (csX75::shin_z / 2 + (0.05 * csX75::hip_z)));
				glRotatef(csX75::tyre_x_angle, 1, 0, 0);
				glCallList(back_tyres);

			glPopMatrix();

			glPushMatrix();

				glColor3f(0.1, 0.1, 0.1);
				glTranslatef(0, - csX75::thigh_y / 2 - csX75::shin_y - csX75::foot_y + csX75::tyre_x, - (csX75::shin_z / 2 + (0.05 * csX75::hip_z)));
				glRotatef(csX75::tyre_x_angle, 1, 0, 0);
				glCallList(back_tyres);

			glPopMatrix();

		glPopMatrix();

		//right leg
		glPushMatrix();


			glTranslatef(- csX75::leg_x, csX75::leg_y, csX75::leg_z);
			glTranslatef(0, csX75::thigh_y / 2, 0);
			glRotatef(- csX75::right_leg_hip_angle, 1, 0, 0);
			glRotatef(csX75::right_leg_angle, 0, 1, 0);
			glRotatef(csX75::right_leg_hip_z_angle, 0, 0, 1);
			glTranslatef(0, - csX75::thigh_y / 2, 0);
			glCallList(thigh);
			glCallList(knee_joint);
			glTranslatef(0, - csX75::thigh_y / 2, 0);
			glRotatef(- csX75::right_knee_angle, 1, 0, 0);
			glTranslatef(0, csX75::thigh_y / 2, 0);

			glCallList(leg);

			//tyres
			glPushMatrix();

				glColor3f(0.1, 0.1, 0.1);
				glTranslatef(0, - csX75::thigh_y / 2 - csX75::tyre_x, - (csX75::shin_z / 2 + (0.05 * csX75::hip_z)));
				glRotatef(csX75::tyre_x_angle, 1, 0, 0);
				glCallList(back_tyres);

			glPopMatrix();

			glPushMatrix();

				glColor3f(0.1, 0.1, 0.1);
				glTranslatef(0, - csX75::thigh_y / 2 - csX75::shin_y - csX75::foot_y + csX75::tyre_x, - (csX75::shin_z / 2 + (0.05 * csX75::hip_z)));
				glRotatef(csX75::tyre_x_angle, 1, 0, 0);
				glCallList(back_tyres);

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}

int main(int argc, char *argv[]){
	//progname=argv[0];

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
	return -1;

	int win_width=512;
	int win_height=512;

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(win_width, win_height, "Transformer", NULL, NULL);
	if(!window){
		glfwTerminate();
		return -1;
	}

	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwGetFramebufferSize(window, &win_width, &win_height);
	csX75::framebuffer_size_callback(window, win_width, win_height);
	//Initialize GL state
	
	csX75::initGL();
	init_structures();

	// Loop until the user closes the window
	while(glfwWindowShouldClose(window) == 0){

		// Render here
		// renderRoom(window);
		
		renderGL(window);
		// Swap front and back buffers
		glfwSwapBuffers(window);
		// Poll for and process events
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
