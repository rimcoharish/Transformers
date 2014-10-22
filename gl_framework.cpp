#include "gl_framework.hpp"
#include "transformers.hpp"
#include <math.h>
#include <stdlib.h>

namespace csX75
{
	int win_width;
	int win_height;
	double angle_x = 0, angle_y = 0;
	double translate_x = 0, translate_y = 0, translate_z = 0;
	double left_knee_angle = 0, right_knee_angle = 0;
	double left_leg_hip_angle = 0, right_leg_hip_angle = 0;
	double left_leg_hip_z_angle = 0, right_leg_hip_z_angle = 0;
	double left_leg_angle = 0, right_leg_angle = 0;
	double hip_center_z = 0, hip_center_angle = 0;
	double left_upper_arm_x_angle = 330, left_upper_arm_z_angle = 30;
	double right_upper_arm_x_angle = 30, right_upper_arm_z_angle = -30;
	double left_elbow_angle = -30, right_elbow_angle = -30;
	double upper_arm_z_angle = 0.5;
	double head_x_angle = 0, head_y_angle = 0, head_z_angle = 0;
	double neck_translate = torso_y;
	double tyre_x_angle = 0, front_tyre_y_angle = 0;

	const double leg_x = 0.35, leg_y = - 0.5;
	double leg_z = 0;

	const double knee_joint_length = 0.1;
	const double thigh_x = 0.2, thigh_y = 0.8, thigh_z = 0.2;
	const double shin_x = 0.45, shin_y = 0.7, shin_z = 0.45;
	const double foot_x = 0.45, foot_y = 0.1, foot_z = 0.55;
	const double tyre_x = 0.175, tyre_y = 0.225, tyre_z = 0.175;
	const double hip_x = 1.4, hip_y = 0.5, hip_z = 1;
	const double torso_x = 1.4, torso_y = 1.4, torso_z = 1;
	const double upper_arm_x = 0.2, upper_arm_y = 0.8, upper_arm_z = 0.2;
	const double lower_arm_x = 0.41, lower_arm_y = 0.8, lower_arm_z = 0.41;
	const double head_x = 0.5, head_y = 0.5, head_z = 0.5;
	const double neck_x = 0.1, neck_y = 0.3, neck_z = 0.1;
	const double neck_joint_x = 0.1, neck_joint_y = 0.1, neck_joint_z = 0.1;
	const double eye_x = 0.05, eye_y = 0.05, eye_z = 0.05;

	bool transformed = false;
	const double leg_z_increment = 0.005, leg_angle_increment = 1, hip_z_increment = 0.01, hip_angle_increment = 0.5;
	const double neck_translate_increment = 0.01;

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

		glMatrixMode(GL_PROJECTION);
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
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		win_width = width;
		win_height = height;
	}

	void reset_lower_body(){
		for(double i = left_knee_angle; i < 0; i+=upper_arm_z_angle){
			left_knee_angle+=upper_arm_z_angle;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		for(double i = right_knee_angle; i < 0; i+=upper_arm_z_angle){
			right_knee_angle+=upper_arm_z_angle;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		for(double i = left_leg_hip_z_angle; i > 0; i-=upper_arm_z_angle){
			left_leg_hip_z_angle -= upper_arm_z_angle;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		for(double i = right_leg_hip_z_angle; i < 0; i+=upper_arm_z_angle){
			right_leg_hip_z_angle += upper_arm_z_angle;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		while(left_leg_hip_angle != 0){
			left_leg_hip_angle += ((left_leg_hip_angle < 0) ? 1 : -1) * upper_arm_z_angle;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		while(right_leg_hip_angle != 0){
			right_leg_hip_angle += ((right_leg_hip_angle < 0) ? 1 : -1) * upper_arm_z_angle;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		while(head_x_angle != 0){
			int sign = ((head_x_angle < 0) ? 1 : -1);
			head_x_angle += sign * upper_arm_z_angle;
			//std::cout << head_x_angle << std::endl;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		while(head_y_angle != 0){
			int sign = ((head_y_angle < 180) ? -1 : 1);
			head_y_angle += sign * upper_arm_z_angle;
			if (head_y_angle == 360) head_y_angle = 0;
			//std::cout << head_y_angle << std::endl;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		while(head_z_angle != 0){
			int sign = ((head_z_angle < 0) ? 1 : -1);
			head_z_angle += sign * upper_arm_z_angle;
			//std::cout << head_z_angle << std::endl;
			renderGL(getWindow());
			glfwSwapBuffers(getWindow());
			glfwPollEvents();
		}
		//std::cout << left_knee_angle << " " << right_knee_angle << " " << left_leg_hip_angle << " " << right_leg_hip_angle << " " << std::endl;
	}

	//!GLFW keyboard callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		else if(key == GLFW_KEY_UP && mods == GLFW_MOD_SHIFT){
			translate_y += 0.05;
		}
		else if(key == GLFW_KEY_DOWN && mods == GLFW_MOD_SHIFT){
			translate_y -= 0.05;
		}
		else if(key == GLFW_KEY_LEFT && mods == GLFW_MOD_SHIFT){
			translate_x -= 0.05;
		}
		else if(key == GLFW_KEY_RIGHT && mods == GLFW_MOD_SHIFT){
			translate_x += 0.05;
		}
		else if (key == GLFW_KEY_LEFT){
			angle_y += 1;
			if (angle_y == 360) angle_y = 0;
		}
		else if (key == GLFW_KEY_RIGHT){
			angle_y -= 1;
			if (angle_y == -1) angle_y = 359;
		}
		else if (key == GLFW_KEY_UP){
			angle_x += 1;
			if (angle_x == 360) angle_x = 0;
		}
		else if (key == GLFW_KEY_DOWN){
			angle_x -= 1;
			if (angle_x == -1) angle_x = 359;
		}
		if(!transformed){
			int head_angle = 15;
			if(key == GLFW_KEY_R && mods == GLFW_MOD_CONTROL){
				reset_lower_body();
			}
			else if(key == GLFW_KEY_Q && mods == GLFW_MOD_SHIFT){
				if(left_knee_angle < 0 && left_knee_angle >= -34){
					left_knee_angle += 1;
				}	
			}
			else if (key == GLFW_KEY_Q){
				if (left_knee_angle <= 0 && left_knee_angle > -34){
					left_knee_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_W && mods == GLFW_MOD_SHIFT){
				if(right_knee_angle < 0 && right_knee_angle >= -34){
					right_knee_angle += 1;
				}	
			}
			else if (key == GLFW_KEY_W){
				if (right_knee_angle <= 0 && right_knee_angle > -34){
					right_knee_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_E && mods == GLFW_MOD_SHIFT){
				if(left_leg_hip_angle > -90 && left_leg_hip_angle <= 90){
					left_leg_hip_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_E){
				if(left_leg_hip_angle >= -90 && left_leg_hip_angle < 90){
					left_leg_hip_angle += 1;
				}
			}
			else if(key == GLFW_KEY_R && mods == GLFW_MOD_SHIFT){
				if(right_leg_hip_angle > -90 && right_leg_hip_angle <= 90){
					right_leg_hip_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_R){
				if(right_leg_hip_angle >= -90 && right_leg_hip_angle < 90){
					right_leg_hip_angle += 1;
				}
			}
			else if(key == GLFW_KEY_Y && mods == GLFW_MOD_SHIFT){
				if(left_leg_hip_z_angle > 0 && left_leg_hip_z_angle <= 45){
					left_leg_hip_z_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_Y){
				if(left_leg_hip_z_angle >= 0 && left_leg_hip_z_angle < 45){
					left_leg_hip_z_angle += 1;
				}
			}
			else if(key == GLFW_KEY_U && mods == GLFW_MOD_SHIFT){
				if(right_leg_hip_z_angle < 0 && right_leg_hip_z_angle >= -45){
					right_leg_hip_z_angle += 1;
				}
			}
			else if(key == GLFW_KEY_U){
				if(right_leg_hip_z_angle <= 0 && right_leg_hip_z_angle > -45){
					right_leg_hip_z_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_I && mods == GLFW_MOD_SHIFT){
				head_y_angle -= 1;
				if(head_y_angle == -1) head_y_angle = 359;
			}
			else if(key == GLFW_KEY_I){
				head_y_angle += 1;
				if(head_y_angle == 360) head_y_angle = 0;
			}
			else if(key == GLFW_KEY_O && mods == GLFW_MOD_SHIFT){
				if(head_z_angle > -head_angle && head_z_angle <= head_angle){
					head_z_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_O){
				if(head_z_angle >= -head_angle && head_z_angle < head_angle){
					head_z_angle += 1;
				};
			}
			else if(key == GLFW_KEY_P && mods == GLFW_MOD_SHIFT){
				if(head_x_angle > -head_angle && head_x_angle <= head_angle){
					head_x_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_P){
				if(head_x_angle >= -head_angle && head_x_angle < head_angle){
					head_x_angle += 1;
				}
			}
			else if(key == GLFW_KEY_A && mods == GLFW_MOD_SHIFT){
				left_upper_arm_x_angle += 1;
				if (left_upper_arm_x_angle == 0) left_upper_arm_x_angle = 0;
			}
			else if(key == GLFW_KEY_A){
				left_upper_arm_x_angle -= 1;
				if (left_upper_arm_x_angle == -1) left_upper_arm_x_angle = 359;
			}
			else if(key == GLFW_KEY_D && mods == GLFW_MOD_SHIFT){
				if(left_upper_arm_z_angle <= 90 && left_upper_arm_z_angle > 0){
					left_upper_arm_z_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_D){
				if(left_upper_arm_z_angle < 90 && left_upper_arm_z_angle >= 0){
					left_upper_arm_z_angle += 1;
				}
			}
			else if(key == GLFW_KEY_G && mods == GLFW_MOD_SHIFT){
				if(left_elbow_angle < 0 && left_elbow_angle >= -89){
					left_elbow_angle += 1;
				}
			}
			else if(key == GLFW_KEY_G){
				if(left_elbow_angle <= 0 && left_elbow_angle > -89){
					left_elbow_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT){
				right_upper_arm_x_angle += 1;
				if (right_upper_arm_x_angle == 0) right_upper_arm_x_angle = 0;
			}
			else if(key == GLFW_KEY_S){
				right_upper_arm_x_angle -= 1;
				if (right_upper_arm_x_angle == -1) right_upper_arm_x_angle = 359;
			}
			else if(key == GLFW_KEY_F && mods == GLFW_MOD_SHIFT){
				if(right_upper_arm_z_angle >= -90 && right_upper_arm_z_angle < 0){
					right_upper_arm_z_angle += 1;
				}
			}
			else if(key == GLFW_KEY_F){
				if(right_upper_arm_z_angle > -90 && right_upper_arm_z_angle <= 0){
					right_upper_arm_z_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_H && mods == GLFW_MOD_SHIFT){
				if(right_elbow_angle < 0 && right_elbow_angle >= -89){
					right_elbow_angle += 1;
				}
			}
			else if(key == GLFW_KEY_H){
				if(right_elbow_angle <= 0 && right_elbow_angle > -89){
					right_elbow_angle -= 1;
				}
			}
			else if(key == GLFW_KEY_J){
				tyre_x_angle--;
				if(tyre_x_angle < 0) tyre_x_angle = 359;
			}
			else if(key == GLFW_KEY_J && mods == GLFW_MOD_SHIFT){
				tyre_x_angle++;
				if(tyre_x_angle == 360) tyre_x_angle = 0;
			}
			else if(key == GLFW_KEY_K){
				front_tyre_y_angle--;
				if(front_tyre_y_angle < 0) front_tyre_y_angle = 359;
			}
			else if(key == GLFW_KEY_K && mods == GLFW_MOD_SHIFT){
				front_tyre_y_angle++;
				if(front_tyre_y_angle == 360) front_tyre_y_angle = 0;
			}
			else if(key == GLFW_KEY_T && action == GLFW_PRESS){
				transformed = true;
				reset_lower_body();
				for(double i = 0; i > - (csX75::torso_z); i-=hip_z_increment){
					csX75::hip_center_z -= hip_z_increment;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = 0; i < 90; i+=hip_angle_increment){
					csX75::hip_center_angle += hip_angle_increment;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = 0; i < 180; i+=leg_angle_increment){
					right_leg_angle += leg_angle_increment;
					left_leg_angle -= leg_angle_increment;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = 0; i < csX75::hip_z * 0.4 - csX75::thigh_z; i+=leg_z_increment){
					csX75::leg_z += leg_z_increment;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = left_upper_arm_z_angle; i > 0; i-=upper_arm_z_angle){
					csX75::left_upper_arm_z_angle -= upper_arm_z_angle;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = right_upper_arm_z_angle; i < 0; i+=upper_arm_z_angle){
					csX75::right_upper_arm_z_angle += upper_arm_z_angle;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				double angle_req = acos((torso_y / 2) / upper_arm_y) * 180 / M_PI - 4.5;
				while(left_upper_arm_x_angle != angle_req){
					int sign;
					if (left_upper_arm_x_angle < 180 && left_upper_arm_x_angle > angle_req) sign = -1;
					else sign = 1;
					if (left_upper_arm_x_angle >= 360) left_upper_arm_x_angle-= 360;
					if (abs(left_upper_arm_x_angle - angle_req) <= upper_arm_z_angle){
						left_upper_arm_x_angle = angle_req;
					}
					else left_upper_arm_x_angle += sign * upper_arm_z_angle;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				while(right_upper_arm_x_angle != angle_req){
					int sign;
					if (right_upper_arm_x_angle < 180 && right_upper_arm_x_angle > angle_req) sign = -1;
					else sign = 1;
					if (right_upper_arm_x_angle >= 360) right_upper_arm_x_angle-= 360;
					if (abs(right_upper_arm_x_angle - angle_req) <= upper_arm_z_angle){
						right_upper_arm_x_angle = angle_req;
					}
					else right_upper_arm_x_angle += sign * upper_arm_z_angle;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				while(left_elbow_angle != - 2 * angle_req){
					int sign;
					if (left_elbow_angle < - 2 * angle_req) sign = 1;
					else sign = -1;
					if (abs(- left_elbow_angle - 2 * angle_req) < upper_arm_z_angle) left_elbow_angle = - 2 * angle_req;
					else left_elbow_angle += sign * upper_arm_z_angle;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				while(right_elbow_angle != - 2 * angle_req){
					int sign;
					if (right_elbow_angle < - 2 * angle_req) sign = 1;
					else sign = -1;
					if (abs(- right_elbow_angle - 2 * angle_req) < upper_arm_z_angle) right_elbow_angle = - 2 * angle_req;
					else right_elbow_angle += sign * upper_arm_z_angle;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = neck_translate; i > torso_y / 2; i-=neck_translate_increment){
					neck_translate -= neck_translate_increment;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				std::cout << "Vehicle mode entered" << std::endl;
				std::cout << "Left x angle - " << left_upper_arm_x_angle << std::endl;
				std::cout << "Left z angle - " << left_upper_arm_z_angle << std::endl;
				std::cout << "Right x angle - " << right_upper_arm_x_angle << std::endl;
				std::cout << "Right z angle - " << right_upper_arm_z_angle << std::endl;
				std::cout << "Left elbow angle - " << left_elbow_angle << std::endl;
				std::cout << "Right elbow angle - " << right_elbow_angle << std::endl;
				std::cout << "Left leg hip angle - " << left_leg_hip_angle << std::endl;
				std::cout << "Right leg hip angle - " << right_leg_hip_angle << std::endl;
				std::cout << "Left leg hip z angle - " << left_leg_hip_z_angle << std::endl;
				std::cout << "Right leg hip z angle - " << right_leg_hip_z_angle << std::endl;
				std::cout << "Left leg angle - " << left_leg_angle << std::endl;
				std::cout << "Right leg angle - " << right_leg_angle << std::endl;
				std::cout << "Left leg knee angle - " << left_knee_angle << std::endl;
				std::cout << "Right leg knee angle - " << right_knee_angle << std::endl;
				std::cout << "Head x angle - " << head_x_angle << std::endl;
				std::cout << "Head y angle - " << head_y_angle << std::endl;
				std::cout << "Head z angle - " << head_z_angle << std::endl;
				std::cout << "Neck Height - " << neck_translate << std::endl << std::endl;
			}
		}
		else if(key == GLFW_KEY_T && mods == GLFW_MOD_SHIFT && action == GLFW_PRESS && transformed){
			transformed = false;
			for(double i = 0; i < csX75::hip_z * 0.4 - csX75::thigh_z; i+=leg_z_increment){
				csX75::leg_z -= leg_z_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			for(double i = 0; i < 180; i+=leg_angle_increment){
				right_leg_angle -= leg_angle_increment;
				left_leg_angle += leg_angle_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			for(double i = 0; i < 90; i+=hip_angle_increment){
				csX75::hip_center_angle -= hip_angle_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			for(double i = 0; i > - (csX75::torso_z); i-=hip_z_increment){
				csX75::hip_center_z += hip_z_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			for(double i = 0; i < 30; i+=upper_arm_z_angle){
				left_upper_arm_z_angle += upper_arm_z_angle;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			for(double i = 0; i > -30; i-=upper_arm_z_angle){
				right_upper_arm_z_angle -= upper_arm_z_angle;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			for(double i = neck_translate; i < torso_y; i+=neck_translate_increment){
				neck_translate += neck_translate_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			std::cout << "Robot mode entered" << std::endl;
			std::cout << "Left x angle - " << left_upper_arm_x_angle << std::endl;
			std::cout << "Left z angle - " << left_upper_arm_z_angle << std::endl;
			std::cout << "Right x angle - " << right_upper_arm_x_angle << std::endl;
			std::cout << "Right z angle - " << right_upper_arm_z_angle << std::endl;
			std::cout << "Left elbow angle - " << left_elbow_angle << std::endl;
			std::cout << "Right elbow angle - " << right_elbow_angle << std::endl;
			std::cout << "Left leg hip angle - " << left_leg_hip_angle << std::endl;
			std::cout << "Right leg hip angle - " << right_leg_hip_angle << std::endl;
			std::cout << "Left leg hip z angle - " << left_leg_hip_z_angle << std::endl;
			std::cout << "Right leg hip z angle - " << right_leg_hip_z_angle << std::endl;
			std::cout << "Left leg angle - " << left_leg_angle << std::endl;
			std::cout << "Right leg angle - " << right_leg_angle << std::endl;
			std::cout << "Left leg knee angle - " << left_knee_angle << std::endl;
			std::cout << "Right leg knee angle - " << right_knee_angle << std::endl;
			std::cout << "Head x angle - " << head_x_angle << std::endl;
			std::cout << "Head y angle - " << head_y_angle << std::endl;
			std::cout << "Head z angle - " << head_z_angle << std::endl;
			std::cout << "Neck Height - " << neck_translate << std::endl << std::endl;
		}
		else if(key == GLFW_KEY_J){
			tyre_x_angle--;
			if(tyre_x_angle < 0) tyre_x_angle = 359;
		}
		else if(key == GLFW_KEY_J && mods == GLFW_MOD_SHIFT){
			tyre_x_angle++;
			if(tyre_x_angle == 360) tyre_x_angle = 0;
		}
		else if(key == GLFW_KEY_K){
			front_tyre_y_angle--;
			if(front_tyre_y_angle < 0) front_tyre_y_angle = 359;
		}
		else if(key == GLFW_KEY_K && mods == GLFW_MOD_SHIFT){
			front_tyre_y_angle++;
			if(front_tyre_y_angle == 360) front_tyre_y_angle = 0;
		}
	}
};
