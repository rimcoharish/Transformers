#include "gl_framework.hpp"
#include "transformers.hpp"

namespace csX75
{
	int win_width;
	int win_height;
	double angle_x = 0;
	double angle_y = 0;
	double left_knee_angle = 0;
	double right_knee_angle = 0;
	double left_leg_hip_angle = 0;
	double right_leg_hip_angle = 0;
	double left_leg_angle = 0, right_leg_angle = 0;
	double hip_center_z = 0, hip_center_angle = 0;
	double left_upper_arm_x_angle = 0, left_upper_arm_z_angle = 0;
	double right_upper_arm_x_angle = 0, right_upper_arm_z_angle = 0;
	double left_elbow_angle = 0, right_elbow_angle = 0;

	const double leg_x = 0.35, leg_y = - 0.5;
	double leg_z = 0;

	const double knee_joint_length = 0.1;
	const double thigh_x = 0.2, thigh_y = 0.8, thigh_z = 0.2;
	const double shin_x = 0.45, shin_y = 0.7, shin_z = 0.45;
	const double foot_x = 0.45, foot_y = 0.1, foot_z = 0.55;
	const double tyre_x = 0.175, tyre_y = 0.225, tyre_z = 0.175;
	const double hip_x = 1.4, hip_y = 0.5, hip_z = 1;
	const double torso_x = 1.4, torso_y = 1.4, torso_z = 1;
	const double upper_arm_x = 0.45, upper_arm_y = 0.7, upper_arm_z = 0.45;
	const double lower_arm_x = 0.2, lower_arm_y = 0.7, lower_arm_z = 0.2;

	bool transformed = false;
	const double leg_z_increment = 0.005, leg_angle_increment = 0.7, hip_z_increment = 0.01, hip_angle_increment = 0.5;

	//! Initialize GL State
	void initGL(void)
	{
		glLoadIdentity();
		//Set framebuffer clear color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//Set depth buffer furthest depth
		glClearDepth(1.0);

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glMatrixMode(GL_PROJECTION);
		glOrtho(-1, 1, -1, 1, -1, 1);
	}

	//!GLFW Error Callback
	void error_callback(int error, const char* description)
	{
		std::cerr<<description<<std::endl;
	}

	//!GLFW framebuffer resize callback
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		if(height == 0) height = 1;

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();

		//Draw to the whole window
		glViewport( 0, 0, width, height );

		//Keep the aspect ratio fixed
		double aspect;
		if (width > height)
		{
			aspect = (double)width/(double)height;
			glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
		}
		else
		{
			aspect = (double)height/(double)width;
			glOrtho(-1.0, 1.0, -aspect, aspect, -1.0, 1.0);
		}
		win_width = width;
		win_height = height;
	}

	//!GLFW keyboard callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		else if (key == GLFW_KEY_LEFT)
			angle_y += 1;
		else if (key == GLFW_KEY_RIGHT)
			angle_y -= 1;
		else if (key == GLFW_KEY_UP)
			angle_x += 1;
		else if (key == GLFW_KEY_DOWN)
			angle_x -= 1;
		else if (key == GLFW_KEY_Q){
			if (left_knee_angle >= 0 && left_knee_angle <34){
				left_knee_angle += 1;
			}
		}
		else if(key == GLFW_KEY_W){
			if(left_knee_angle >=1 && left_knee_angle <= 34){
				left_knee_angle -= 1;
			}	
		}
		else if (key == GLFW_KEY_E){
			if (right_knee_angle >= 0 && right_knee_angle <34){
				right_knee_angle += 1;
			}
		}
		else if(key == GLFW_KEY_R){
			if(right_knee_angle >=1 && right_knee_angle <= 34){
				right_knee_angle -= 1;
			}	
		}
		else if(key == GLFW_KEY_T){
			if(left_leg_hip_angle >= 0 && left_leg_hip_angle < 90){
				left_leg_hip_angle += 1;
			}
		}
		else if(key == GLFW_KEY_Y){
			if(left_leg_hip_angle >= 1 && left_leg_hip_angle <= 90){
				left_leg_hip_angle -= 1;
			}
		}
		else if(key == GLFW_KEY_U){
			if(right_leg_hip_angle >= 0 && right_leg_hip_angle < 90){
				right_leg_hip_angle += 1;
			}
		}
		else if(key == GLFW_KEY_I){
			if(right_leg_hip_angle >= 1 && right_leg_hip_angle <= 90){
				right_leg_hip_angle -= 1;
			}
		}
		else if(key == GLFW_KEY_A){
			right_upper_arm_x_angle -= 1;
		}
		else if(key == GLFW_KEY_S){
			right_upper_arm_x_angle += 1;
		}
		else if(key == GLFW_KEY_D){
			right_upper_arm_x_angle -= 1;
		}
		else if(key == GLFW_KEY_F){
			right_upper_arm_x_angle += 1;
		}
		else if(key == GLFW_KEY_O && action == GLFW_PRESS && !transformed){
			transformed = true;
			for(double i = 0; i > - (csX75::torso_z); i-=hip_z_increment){
				csX75::hip_center_z -= hip_z_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
			for(double i = 0; i < 90; i+=hip_angle_increment){
				csX75::hip_center_angle -= hip_angle_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
			for(double i = 0; i < 180; i+=leg_angle_increment){
				right_leg_angle -= leg_angle_increment;
				left_leg_angle += leg_angle_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
			for(double i = 0; i < csX75::hip_z * 0.4 - csX75::thigh_z; i+=leg_z_increment){
				csX75::leg_z -= leg_z_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
		}
		else if(key == GLFW_KEY_P && action == GLFW_PRESS && transformed){
			transformed = false;
			for(double i = 0; i < csX75::hip_z * 0.4 - csX75::thigh_z; i+=leg_z_increment){
				csX75::leg_z += leg_z_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
			for(double i = 0; i < 180; i+=leg_angle_increment){
				right_leg_angle += leg_angle_increment;
				left_leg_angle -= leg_angle_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
			for(double i = 0; i < 90; i+=hip_angle_increment){
				csX75::hip_center_angle += hip_angle_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
			for(double i = 0; i > - (csX75::torso_z); i-=hip_z_increment){
				csX75::hip_center_z += hip_z_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
			}
		}
	}
};
