#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <iostream>

namespace csX75
{
	extern double angle_x, angle_y;
	extern double translate_x, translate_y, translate_z;
	extern double left_knee_angle, right_knee_angle;
	extern double left_leg_hip_angle, right_leg_hip_angle;
	extern double left_leg_angle, right_leg_angle;
	extern double left_leg_hip_z_angle, right_leg_hip_z_angle;
	extern double hip_center_z, hip_center_angle;
	extern double left_upper_arm_x_angle, left_upper_arm_z_angle;
	extern double right_upper_arm_x_angle, right_upper_arm_z_angle;
	extern double left_elbow_angle, right_elbow_angle;
	extern double head_x_angle, head_y_angle, head_z_angle;
	extern double neck_translate;
	extern double leg_z;
	extern double tyre_x_angle, front_tyre_y_angle;
	extern double camera_angle;
	const extern double leg_x, leg_y;
	const extern double knee_joint_length;
	const extern double thigh_x, thigh_y, thigh_z;
	const extern double shin_x, shin_y, shin_z;
	const extern double foot_x, foot_y, foot_z;
	const extern double tyre_x, tyre_y, tyre_z;
	const extern double hip_x, hip_y, hip_z;
	const extern double torso_x, torso_y, torso_z;
	const extern double upper_arm_x, upper_arm_y, upper_arm_z;
	const extern double lower_arm_x, lower_arm_y, lower_arm_z;
	const extern double head_x, head_y, head_z;
	const extern double neck_x, neck_y, neck_z;
	const extern double neck_joint_x, neck_joint_y, neck_joint_z;
	const extern double eye_x, eye_z, eye_y;

	extern double camera_angle;
	extern double camera1[9];
	extern double camera2[9];
	extern double camera3[9];
	extern double currentCamera[9];
	extern int CurrentCameraNumber;

	//! Initialize GL State
	void initGL(void);

	//!GLFW Error Callback
	void error_callback(int error, const char* description);
	//!GLFW framebuffer resize callback
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	//!GLFW keyboard callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void toggle_view(int i);
	bool gluInvertMatrix(GLfloat* m, GLfloat* invOut);
	// void changeOtherCameraCordinates();
	void ChangeView();
	// void viewer();

	void initLights();
	void initLightPositions();
	void printState();

	// void Animate(GLFWwindow* window);

};

#endif
