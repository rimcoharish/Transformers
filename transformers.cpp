#include <iostream>
#include "gl_framework.hpp"
#include "parts.hpp"

using namespace std;

//! The pointer to the GLFW window
GLFWwindow* window;

void init_structures(){
	struct_cylinder();
	struct_cube();
	struct_thigh();
	struct_leg();
	struct_knee_joint();
	struct_trapezium();
	struct_hip();
	struct_upper_arm();
	struct_lower_arm();
}

GLFWwindow* getWindow(){
	return window;
}

void renderGL(GLFWwindow* window){
	//rendering the transformerglLoadIdentity();
	//Set framebuffer clear color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//Set depth buffer furthest depth
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glScalef(0.35, 0.35, 0.35);

	glRotatef(csX75::angle_y, 0, 1, 0);
	glRotatef(csX75::angle_x, 1, 0, 0);

	glPushMatrix();

		glColor3f(1, 0, 0);
		glTranslatef(- csX75::torso_x / 2, 0, - csX75::torso_z / 2);
		glTranslatef(0, csX75::hip_y / 2, 0);
		glScalef(csX75::torso_x, csX75::torso_y, csX75::torso_z);
		glCallList(cube);

		//left hand
		/*glPushMatrix();

			glCallList(upper_arm);
			glTranslatef(0, - csX75::upper_arm_y / 2, 0);
			glRotatef(csX75::right_elbow_angle, 1, 0, 0);
			glTranslatef(- csX75::lower_arm_x / 2, - csX75::lower_arm_y / 2, - csX75::lower_arm_z / 2);
			glCallList(lower_arm);

		glPopMatrix();

		//right hand
		glPushMatrix();

		glPopMatrix();*/

	glPopMatrix();

	/*glPushMatrix();*/

		glTranslatef(0, 0, - csX75::hip_center_z);
		glTranslatef(0, csX75::hip_y / 2, - csX75::torso_z / 2);
		glRotatef(csX75::hip_center_angle, 1, 0, 0);
		glTranslatef(0, - csX75::hip_y / 2, csX75::torso_z / 2);

		glCallList(hip);

		//left leg
		glPushMatrix();

			glTranslatef(csX75::leg_x, csX75::leg_y, csX75::leg_z);
			glTranslatef(0, csX75::thigh_y / 2, 0);
			glRotatef(- csX75::left_leg_hip_angle, 1, 0, 0);
			glRotatef(csX75::left_leg_angle, 0, 1, 0);
			glTranslatef(0, - csX75::thigh_y / 2, 0);
			glCallList(thigh);
			glCallList(knee_joint);
			glTranslatef(0, - csX75::thigh_y/ 2, 0);
			glRotatef(- csX75::left_knee_angle, 1, 0, 0);
			glTranslatef(0, csX75::thigh_y / 2, 0);
			glCallList(leg);

		glPopMatrix();

		//right leg
		glPushMatrix();

			glTranslatef(- csX75::leg_x, csX75::leg_y, csX75::leg_z);
			glTranslatef(0, csX75::thigh_y / 2, 0);
			glRotatef(- csX75::right_leg_hip_angle, 1, 0, 0);
			glRotatef(csX75::right_leg_angle, 0, 1, 0);
			glTranslatef(0, - csX75::thigh_y / 2, 0);
			glCallList(thigh);
			glCallList(knee_joint);
			glTranslatef(0, - csX75::thigh_y / 2, 0);
			glRotatef(- csX75::right_knee_angle, 1, 0, 0);
			glTranslatef(0, csX75::thigh_y / 2, 0);
			glCallList(leg);

		glPopMatrix();

	/*glPopMatrix();*/
	/*glTranslatef(-0.5, -0.5, -0.5);*/
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
