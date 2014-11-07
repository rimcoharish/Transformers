#include "gl_framework.hpp"
#include "transformers.hpp"
#include <math.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

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
	double left_upper_arm_x_angle = 0, left_upper_arm_z_angle = 30;
	double right_upper_arm_x_angle = 0, right_upper_arm_z_angle = -30;
	double left_elbow_angle = -30, right_elbow_angle = -30;
	double upper_arm_z_angle = 0.5;
	double head_x_angle = 0, head_y_angle = 0, head_z_angle = 0;
	double neck_translate = torso_y;
	double tyre_x_angle = 0, front_tyre_y_angle = 0;
	bool head_light1 = false, head_light2 = false;

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
	const double head_x = 0.6, head_y = 0.6, head_z = 0.6;
	const double neck_x = 0.1, neck_y = 0.3, neck_z = 0.1;
	const double neck_joint_x = 0.1, neck_joint_y = 0.1, neck_joint_z = 0.1;
	const double eye_x = 0.1, eye_y = 0.1, eye_z = 0.1;

	bool transformed = false;
	const double leg_z_increment = 0.005, leg_angle_increment = 1, hip_z_increment = 0.01, hip_angle_increment = 0.5;
	const double neck_translate_increment = 0.01;

	double camera1[9]={0,4,12,0,4,11,0,1,0};

	double camera2[9]={0,4,1,0,4,3,0,1,0};
	double dum2[9]=   {0,4,1,0,4,3,0,1,0};

	double camera3[9]={0,4,-5,0,4,3,0,1,0};
	double dum3[9]=   {0,4,-5,0,4,3,0,1,0};

	double currentCamera[9]={0,4,10,0,3,3,0,1,0};

	double camera2_pos = 1;
	double camera2_look_at = 3;
	double camera3_pos = -5;
	double camera3_look_at = 3;

	int CurrentCameraNumber = 1;

	void initLights(){
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);

		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_NORMALIZE);
		glShadeModel(GL_SMOOTH);
	}

	void initLightPositions(){

		GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

		GLfloat lightDiff0[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat lightSpec0[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat lightPos0[] = {10.0f, 10.0f, 10.0f, 0.0f};
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

		GLfloat lightDiff1[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat lightSpec1[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat lightPos1[] = {-10.0f, 10.0f, -10.0f, 0.0f};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiff1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

		GLfloat mat_diffuse[] = {0.5, 0.5, 0.5, 1.0};
		GLfloat mat_specular[] = {0.2, 0.2, 0.2, 1.0};
		GLfloat mat_shininess[] = {128.0};
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	}

	void ChangeView(){
		if(CurrentCameraNumber==1){
			for(int i=0;i<9;i++){
				currentCamera[i]=camera1[i];
			}
		}
		else if(CurrentCameraNumber==2){
			for(int i=0;i<9;i++){
				currentCamera[i]=camera2[i];
			}
		}
		else if(CurrentCameraNumber==3){
			for(int i=0;i<9;i++){
				currentCamera[i]=camera3[i];
			}
		}

		glLoadIdentity();	

		gluLookAt(csX75::currentCamera[0],csX75::currentCamera[1],csX75::currentCamera[2],
				csX75::currentCamera[3],csX75::currentCamera[4],csX75::currentCamera[5],
					csX75::currentCamera[6],csX75::currentCamera[7],csX75::currentCamera[8]);
	}

	void printState(void){
		ofstream keyframes_file;
		keyframes_file.open("keyframes.txt", ios_base::app);
		keyframes_file << left_knee_angle << " ";
		keyframes_file << right_knee_angle << " ";
		keyframes_file << left_leg_angle << " ";
		keyframes_file << right_leg_angle << " ";
		keyframes_file << left_leg_hip_angle << " ";
		keyframes_file << right_leg_hip_angle << " ";
		keyframes_file << left_leg_hip_z_angle << " ";
		keyframes_file << right_leg_hip_z_angle << " ";
		keyframes_file << hip_center_z << " ";
		keyframes_file << hip_center_angle << " ";
		keyframes_file << left_upper_arm_x_angle << " ";
		keyframes_file << right_upper_arm_x_angle << " ";
		keyframes_file << left_upper_arm_z_angle << " ";
		keyframes_file << right_upper_arm_z_angle << " ";
		keyframes_file << left_elbow_angle << " ";
		keyframes_file << right_elbow_angle << " ";
		keyframes_file << translate_x << " ";
		keyframes_file << translate_y << " ";
		keyframes_file << translate_z << " ";
		keyframes_file << head_x << " ";
		keyframes_file << head_y << " ";
		keyframes_file << head_z << " ";
		keyframes_file << neck_translate << " ";
		keyframes_file << tyre_x_angle << " ";
		keyframes_file << front_tyre_y_angle << " ";
		keyframes_file << head_light1 << " ";
		keyframes_file << head_light2 << " ";
		keyframes_file << CurrentCameraNumber << " ";
		keyframes_file << currentCamera[0] << " ";
		keyframes_file << currentCamera[1] << " ";
		keyframes_file << currentCamera[2] << " ";
		keyframes_file << currentCamera[3] << " ";
		keyframes_file << currentCamera[4] << " ";
		keyframes_file << currentCamera[5] << " ";
		keyframes_file << currentCamera[6] << " ";
		keyframes_file << currentCamera[7] << " ";
		keyframes_file << currentCamera[8] << endl;
	}

	void render(){
		renderGL(getWindow());
		glfwSwapBuffers(getWindow());
		glfwPollEvents();
	}

	void transform(){
		transformed = true;

		//Part1 - Hip moves backwards, hands rotate about z

		double increment = 0.03;

		double left_upper_arm_z_angle_increment, right_upper_arm_z_angle_increment;
		left_upper_arm_z_angle_increment = -left_upper_arm_z_angle * increment;
		right_upper_arm_z_angle_increment = -right_upper_arm_z_angle * increment;

		if(left_leg_hip_angle > 180) left_leg_hip_angle -= 360;
		if(right_leg_hip_angle > 180) right_leg_hip_angle -= 360;

		double left_leg_hip_angle_increment = -left_leg_hip_angle * increment;
		double right_leg_hip_angle_increment = -right_leg_hip_angle * increment;

		double left_knee_angle_increment = -left_knee_angle * increment;
		double right_knee_angle_increment = -right_knee_angle * increment;

		double hip_center_z_increment = -torso_z * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			cout << i << endl;
			hip_center_z += hip_center_z_increment;
			left_upper_arm_z_angle += left_upper_arm_z_angle_increment;
			right_upper_arm_z_angle += right_upper_arm_z_angle_increment;
			left_leg_hip_angle += left_leg_hip_angle_increment;
			right_leg_hip_angle += right_leg_hip_angle_increment;
			left_knee_angle += left_knee_angle_increment;
			right_knee_angle += right_knee_angle_increment;
			render();
		}

		hip_center_z = -torso_z;
		left_upper_arm_z_angle = 0;
		right_upper_arm_z_angle = 0;
		left_leg_hip_angle = 0;
		right_leg_hip_angle = 0;
		left_knee_angle = 0;
		right_knee_angle = 0;
		printState();

		//Part1 - Complete

		//Part2 - Hip rotates, the legs rotate 180 degrees, the arms position themselves, the head lowers into torso

		double angle_req = acos((torso_y / 2) / upper_arm_y) * 180 / M_PI - 4.5;

		if(left_upper_arm_x_angle > 180) left_upper_arm_x_angle -= 360;
		if(right_upper_arm_x_angle > 180) right_upper_arm_x_angle -= 360;

		double left_upper_arm_x_angle_increment = (angle_req - left_upper_arm_x_angle) * increment;
		double right_upper_arm_x_angle_increment = (angle_req - right_upper_arm_x_angle) * increment;

		double left_elbow_angle_increment = (-left_elbow_angle - 2 * angle_req) * increment;
		double right_elbow_angle_increment = (-right_elbow_angle - 2 * angle_req) * increment;

		double hip_center_angle_increment = (90 - hip_center_angle) * increment;

		double left_leg_y_angle_increment = (-180 - left_leg_angle) * increment;
		double right_leg_y_angle_increment = (180 - right_leg_angle) * increment;

		double leg_z_increment1 = (hip_z * 0.4 - thigh_z - leg_z) * increment;

		double neck_translate_increment = ((torso_y - 0.4) / 2 - neck_translate) * increment;

		double descend = (1 - translate_y) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;
			right_elbow_angle += right_elbow_angle_increment;
			hip_center_angle += hip_center_angle_increment;
			left_leg_angle += left_leg_y_angle_increment;
			right_leg_angle += right_leg_y_angle_increment;
			leg_z += leg_z_increment1;
			neck_translate += neck_translate_increment;
			translate_y -= descend;
			render();
		}

		left_upper_arm_x_angle = angle_req;
		right_upper_arm_x_angle = angle_req;
		left_elbow_angle = - 2 * angle_req;
		right_elbow_angle = - 2 * angle_req;
		hip_center_angle = 90;
		left_leg_angle = -180;
		right_leg_angle = 180;
		leg_z = hip_z * 0.4 - thigh_z;
		neck_translate = (torso_y - 0.4) / 2;
		printState();
	}

	void transform_back(){
		transformed = false;

		double increment = 0.03;

		double angle_req = acos((torso_y / 2) / upper_arm_y) * 180 / M_PI - 4.5;

		if(left_upper_arm_x_angle > 180) left_upper_arm_x_angle -= 360;
		if(right_upper_arm_x_angle > 180) right_upper_arm_x_angle -= 360;

		double left_upper_arm_x_angle_increment = (- left_upper_arm_x_angle) * increment;
		double right_upper_arm_x_angle_increment = (- right_upper_arm_x_angle) * increment;

		double left_elbow_angle_increment = (-left_elbow_angle + 30) * increment;
		double right_elbow_angle_increment = (-right_elbow_angle + 30) * increment;

		double hip_center_angle_increment = (- hip_center_angle) * increment;

		double left_leg_y_angle_increment = (- left_leg_angle) * increment;
		double right_leg_y_angle_increment = (- right_leg_angle) * increment;

		double leg_z_increment1 = (- leg_z) * increment;

		double neck_translate_increment = (torso_y - neck_translate) * increment;

		double descend = (- translate_y) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;
			right_elbow_angle += right_elbow_angle_increment;
			hip_center_angle += hip_center_angle_increment;
			left_leg_angle += left_leg_y_angle_increment;
			right_leg_angle += right_leg_y_angle_increment;
			leg_z += leg_z_increment1;
			neck_translate += neck_translate_increment;
			translate_y += descend;
			render();
		}

		left_upper_arm_x_angle = 0;
		right_upper_arm_x_angle = 0;
		left_elbow_angle = -30;
		right_elbow_angle = -30;
		hip_center_angle = 0;
		left_leg_angle = 0;
		right_leg_angle = 0;
		leg_z = 0;
		neck_translate = torso_y;
		printState();

		double left_upper_arm_z_angle_increment, right_upper_arm_z_angle_increment;
		left_upper_arm_z_angle_increment = (-30 -left_upper_arm_z_angle) * increment;
		right_upper_arm_z_angle_increment = (30 -right_upper_arm_z_angle) * increment;

		if(left_leg_hip_angle > 180) left_leg_hip_angle -= 360;
		if(right_leg_hip_angle > 180) right_leg_hip_angle -= 360;

		double left_leg_hip_angle_increment = -left_leg_hip_angle * increment;
		double right_leg_hip_angle_increment = -right_leg_hip_angle * increment;

		double left_knee_angle_increment = -left_knee_angle * increment;
		double right_knee_angle_increment = -right_knee_angle * increment;

		double hip_center_z_increment = -torso_z * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			cout << i << endl;
			hip_center_z -= hip_center_z_increment;
			left_upper_arm_z_angle -= left_upper_arm_z_angle_increment;
			right_upper_arm_z_angle -= right_upper_arm_z_angle_increment;
			left_leg_hip_angle -= left_leg_hip_angle_increment;
			right_leg_hip_angle -= right_leg_hip_angle_increment;
			left_knee_angle -= left_knee_angle_increment;
			right_knee_angle -= right_knee_angle_increment;
			render();
		}

		hip_center_z = 0;
		left_upper_arm_z_angle = 30;
		right_upper_arm_z_angle = -30;
		left_leg_hip_angle = 0;
		right_leg_hip_angle = 0;
		left_knee_angle = 0;
		right_knee_angle = 0;
		printState();
	}

	void run_part1(double forward_len, double increment, double descend_len){
		//Left leg backwards, left hand forward, right leg forward, right hand backward

		if(left_upper_arm_x_angle > 180) left_upper_arm_x_angle -= 360;
		if(right_upper_arm_x_angle > 180) right_upper_arm_x_angle -= 360;

		double left_upper_arm_x_angle_increment = (-30 - left_upper_arm_x_angle) * increment;
		double right_upper_arm_x_angle_increment = (45 - right_upper_arm_x_angle) * increment;

		double left_leg_hip_angle_increment = (-30 - left_leg_hip_angle) * increment;
		double right_leg_hip_angle_increment = (30 - right_leg_hip_angle) * increment;

		double knee_joint_increment = (-30 - left_knee_angle) * increment;

		double descend = descend_len * increment;

		double forward = forward_len * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			left_leg_hip_angle += left_leg_hip_angle_increment;
			right_leg_hip_angle += right_leg_hip_angle_increment;
			left_knee_angle += knee_joint_increment;
			right_knee_angle+= knee_joint_increment;
			translate_y -= descend;
			translate_x += forward * sin((angle_y) * M_PI / 180);
			translate_z += forward * cos((angle_y) * M_PI / 180);
			render();
		}
		left_upper_arm_x_angle = -30;
		right_upper_arm_x_angle = 45;
		left_leg_hip_angle = -30;
		right_leg_hip_angle = 30;
		left_knee_angle = -30;
		right_knee_angle = -30;
		printState();
	}

	void run_part2(double forward_len, double increment, double descend_len){
		//Left leg backwards, left hand forward, right leg forward, right hand backward

		if(left_upper_arm_x_angle > 180) left_upper_arm_x_angle -= 360;
		if(right_upper_arm_x_angle > 180) right_upper_arm_x_angle -= 360;

		double left_upper_arm_x_angle_increment = (- left_upper_arm_x_angle) * increment;
		double right_upper_arm_x_angle_increment = (- right_upper_arm_x_angle) * increment;

		double left_leg_hip_angle_increment = (- left_leg_hip_angle) * increment;
		double right_leg_hip_angle_increment = (- right_leg_hip_angle) * increment;

		double knee_joint_increment = (- left_knee_angle) * increment;

		double descend = descend_len * increment;

		double forward = forward_len * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			left_leg_hip_angle += left_leg_hip_angle_increment;
			right_leg_hip_angle += right_leg_hip_angle_increment;
			left_knee_angle += knee_joint_increment;
			right_knee_angle+= knee_joint_increment;
			translate_y += descend;
			translate_x += forward * sin((angle_y) * M_PI / 180);
			translate_z += forward * cos((angle_y) * M_PI / 180);
			render();
		}
		left_upper_arm_x_angle = 0;
		right_upper_arm_x_angle = 0;
		left_leg_hip_angle = 0;
		right_leg_hip_angle = 0;
		left_knee_angle = 0;
		right_knee_angle = 0;
		printState();
	}

	void run_part3(double forward_len, double increment, double descend_len){
		//Left leg backwards, left hand forward, right leg forward, right hand backward

		if(left_upper_arm_x_angle > 180) left_upper_arm_x_angle -= 360;
		if(right_upper_arm_x_angle > 180) right_upper_arm_x_angle -= 360;

		double left_upper_arm_x_angle_increment = (45 - left_upper_arm_x_angle) * increment;
		double right_upper_arm_x_angle_increment = (-30 - right_upper_arm_x_angle) * increment;

		double left_leg_hip_angle_increment = (30 - left_leg_hip_angle) * increment;
		double right_leg_hip_angle_increment = (-30 - right_leg_hip_angle) * increment;

		double knee_joint_increment = (-30 - left_knee_angle) * increment;

		double descend = descend_len * increment;

		double forward = forward_len * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			left_leg_hip_angle += left_leg_hip_angle_increment;
			right_leg_hip_angle += right_leg_hip_angle_increment;
			left_knee_angle += knee_joint_increment;
			right_knee_angle+= knee_joint_increment;
			translate_y -= descend;
			translate_x += forward * sin((angle_y) * M_PI / 180);
			translate_z += forward * cos((angle_y) * M_PI / 180);
			render();
		}
		left_upper_arm_x_angle = 45;
		right_upper_arm_x_angle = -30;
		left_leg_hip_angle = 30;
		right_leg_hip_angle = -30;
		left_knee_angle = -30;
		right_knee_angle = -30;
		printState();
	}

	void run_part4(double forward_len, double increment, double descend_len){
		//Left leg backwards, left hand forward, right leg forward, right hand backward

		if(left_upper_arm_x_angle > 180) left_upper_arm_x_angle -= 360;
		if(right_upper_arm_x_angle > 180) right_upper_arm_x_angle -= 360;

		double left_upper_arm_x_angle_increment = (- left_upper_arm_x_angle) * increment;
		double right_upper_arm_x_angle_increment = (- right_upper_arm_x_angle) * increment;

		double left_leg_hip_angle_increment = (- left_leg_hip_angle) * increment;
		double right_leg_hip_angle_increment = (- right_leg_hip_angle) * increment;

		double knee_joint_increment = (- left_knee_angle) * increment;

		double descend = descend_len * increment;

		double forward = forward_len * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			left_leg_hip_angle += left_leg_hip_angle_increment;
			right_leg_hip_angle += right_leg_hip_angle_increment;
			left_knee_angle += knee_joint_increment;
			right_knee_angle+= knee_joint_increment;
			translate_y += descend;
			translate_x += forward * sin((angle_y) * M_PI / 180);
			translate_z += forward * cos((angle_y) * M_PI / 180);
			render();
		}
		left_upper_arm_x_angle = 0;
		right_upper_arm_x_angle = 0;
		left_leg_hip_angle = 0;
		right_leg_hip_angle = 0;
		left_knee_angle = 0;
		right_knee_angle = 0;
		printState();
	}

	void run(){
		int i = 0;
		while(i < 2){
			cout << i << endl;
			double increment = 0.03;
			double forward_len = 0.5;
			double descend_len = 0.2;
			run_part1(forward_len, increment, descend_len);
			run_part2(forward_len, increment, descend_len);
			run_part3(forward_len, increment, descend_len);
			run_part4(forward_len, increment, descend_len);
			i++;
		}
	}

	void position_right_arm_for_punch(){
		double increment = 0.03;

		double right_upper_arm_x_angle_increment = (-76 - right_upper_arm_x_angle) * increment;
		double right_upper_arm_z_angle_increment = (-59 - right_upper_arm_z_angle) * increment;
		double right_elbow_angle_increment = (-89 - right_elbow_angle) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			right_upper_arm_z_angle += right_upper_arm_z_angle_increment;
			right_elbow_angle += right_elbow_angle_increment;
			render();
		}
		printState();
	}

	void position_left_arm_for_punch(){
		double increment = 0.03;

		double left_upper_arm_x_angle_increment = (-76 - left_upper_arm_x_angle) * increment;
		double left_upper_arm_z_angle_increment = (59 - left_upper_arm_z_angle) * increment;
		double left_elbow_angle_increment = (-89 - left_elbow_angle) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			left_upper_arm_z_angle += left_upper_arm_z_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;
			render();
		}
		printState();
	}

	void punch_right(){
		double increment = 0.03;

		double left_upper_arm_x_angle_increment = (-76 - left_upper_arm_x_angle) * increment;
		double left_upper_arm_z_angle_increment = (59 - left_upper_arm_z_angle) * increment;
		double left_elbow_angle_increment = (-89 - left_elbow_angle) * increment;

		double right_upper_arm_x_angle_increment = (-100 - right_upper_arm_x_angle) * increment;
		double right_upper_arm_z_angle_increment = (-61 - right_upper_arm_z_angle) * increment;
		double right_elbow_angle_increment = (- right_elbow_angle) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			left_upper_arm_z_angle += left_upper_arm_z_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;

			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			right_upper_arm_z_angle += right_upper_arm_z_angle_increment;
			right_elbow_angle += right_elbow_angle_increment;
			render();
		}
		printState();
	}

	void punch_left(){
		double increment = 0.03;

		double right_upper_arm_x_angle_increment = (-76 - right_upper_arm_x_angle) * increment;
		double right_upper_arm_z_angle_increment = (-59 - right_upper_arm_z_angle) * increment;
		double right_elbow_angle_increment = (-89 - right_elbow_angle) * increment;

		double left_upper_arm_x_angle_increment = (-100 - left_upper_arm_x_angle) * increment;
		double left_upper_arm_z_angle_increment = (61 - left_upper_arm_z_angle) * increment;
		double left_elbow_angle_increment = (- left_elbow_angle) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			right_upper_arm_x_angle += right_upper_arm_x_angle_increment;
			right_upper_arm_z_angle += right_upper_arm_z_angle_increment;
			right_elbow_angle += right_elbow_angle_increment;
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			left_upper_arm_z_angle += left_upper_arm_z_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;
			render();
		}
		printState();
	}

	void position_for_taunt(){
		double increment = 0.03;

		double left_upper_arm_x_angle_increment = (-50 - left_upper_arm_x_angle) * increment;
		double left_upper_arm_z_angle_increment = (30 - left_upper_arm_z_angle) * increment;
		double left_elbow_angle_increment = (-89 - left_elbow_angle) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			left_upper_arm_z_angle += left_upper_arm_z_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;
			render();
		}
		printState();
	}

	void taunt_move_back(){
		double increment = 0.03;

		double left_upper_arm_x_angle_increment = (-10 - left_upper_arm_x_angle) * increment;
		double left_upper_arm_z_angle_increment = (30 - left_upper_arm_z_angle) * increment;
		double left_elbow_angle_increment = (-80 - left_elbow_angle) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			left_upper_arm_z_angle += left_upper_arm_z_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;
			render();
		}
		printState();
	}

	void taunt_move_forward(){
		double increment = 0.03;

		double left_upper_arm_x_angle_increment = (-30 - left_upper_arm_x_angle) * increment;
		double left_upper_arm_z_angle_increment = (30 - left_upper_arm_z_angle) * increment;
		double left_elbow_angle_increment = (-70 - left_elbow_angle) * increment;

		printState();
		for(double i = 0; i < 1; i+=increment){
			left_upper_arm_x_angle += left_upper_arm_x_angle_increment;
			left_upper_arm_z_angle += left_upper_arm_z_angle_increment;
			left_elbow_angle += left_elbow_angle_increment;
			render();
		}
		printState();
	}

	void taunt(){
		double increment = 0.03;
		for(int i = 0; i < 3; i++){
			position_for_taunt();
			taunt_move_back();
			taunt_move_forward();
		}

		// double 
	}

	void punch(){
		position_left_arm_for_punch();
		position_right_arm_for_punch();
		//taunt();
		for(int i = 0; i < 4; i++){
			punch_right();
			punch_left();
		}
	}


	void animate(){
		run();
		punch();
		taunt();
		punch();
		transform();
		transform_back();
	}

	void Animate(GLFWwindow* window){
		string line;
    	ifstream myfile ("keyframes.txt");
    	if(myfile.is_open()){
    		getline(myfile,line);//cout << line << endl;
    		getline(myfile,line);//cout << line << endl;
    		// myfile>>left_knee_angle;cout<<left_knee_angle<<endl;

    		// getline(myfile,line);
    		while(true){
    			if(myfile>>left_knee_angle){

	    			myfile>>right_knee_angle>>left_leg_angle>>right_leg_angle>>left_leg_hip_angle>>right_leg_hip_angle>>left_leg_hip_z_angle>>right_leg_hip_z_angle>>
	    					hip_center_z>>hip_center_angle>>left_upper_arm_x_angle>>right_upper_arm_x_angle>>left_upper_arm_z_angle>>right_upper_arm_z_angle>>left_elbow_angle>>
	    						right_elbow_angle>>translate_x>>translate_y>>translate_z>>head_x_angle>>head_y_angle>>head_z_angle>>tyre_x_angle>>front_tyre_y_angle>>head_light1>>head_light2;
					cout<< " " << right_knee_angle<< " " << left_leg_angle<< " " << right_leg_angle<< " " << left_leg_hip_angle<< " " << right_leg_hip_angle<< " " << left_leg_hip_z_angle
								<< " " << right_leg_hip_z_angle<< " " << hip_center_z<< " " << hip_center_angle<< " " << left_upper_arm_x_angle<< " " << right_upper_arm_x_angle<< " " << left_upper_arm_z_angle
	    						<< " " << right_upper_arm_z_angle<< " " << left_elbow_angle<< " " << right_elbow_angle<< " " << translate_x<< " " << translate_y<< " " << translate_z<< " " << head_x_angle
	    						<< " " << head_y_angle<< " " << head_z_angle<< " " << tyre_x_angle<< " " << front_tyre_y_angle<< " " << head_light1<< " " << head_light2 << " " << CurrentCameraNumber<< endl;


					renderGL(window);
					glfwSwapBuffers(window);
					glfwPollEvents();
					
				}
    		}
    		myfile.close();
    	}
	}

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
			gluPerspective(50,aspect,1,3000);
		}
		else
		{
			aspect = (double)height/(double)width;
			gluPerspective(50,aspect,1,3000);
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
		if (key == GLFW_KEY_4 && mods == GLFW_MOD_SHIFT){
			glDisable(GL_LIGHT0);
		}
		else if (key == GLFW_KEY_4){
			glEnable(GL_LIGHT0);
		}
		else if (key == GLFW_KEY_5 && mods == GLFW_MOD_SHIFT){
			glDisable(GL_LIGHT1);
		}
		else if (key == GLFW_KEY_5){
			glEnable(GL_LIGHT1);
		}
		else if (key == GLFW_KEY_6 && mods == GLFW_MOD_SHIFT){
			glDisable(GL_LIGHT2);
		}
		else if (key == GLFW_KEY_6){
			glEnable(GL_LIGHT2);
		}
		else if (key == GLFW_KEY_7 && mods == GLFW_MOD_SHIFT){
			glEnable(GL_LIGHT3);
		}
		else if (key == GLFW_KEY_7){
			glEnable(GL_LIGHT3);
		}
		else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
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
		else if (key == GLFW_KEY_LEFT && mods == GLFW_MOD_CONTROL){
			angle_y += 1;
			if (angle_y == 360) angle_y = 0;
			// camera_angle -= 1;
			// orientMe(camera_angle);
			// cout << "Right" << camera_angle << endl;
			// if(camera_angle < 0) camera_angle = 359;
		}
		else if (key == GLFW_KEY_RIGHT && mods == GLFW_MOD_CONTROL){
			angle_y -= 1;
			if (angle_y == -1) angle_y = 359;
			// camera_angle += 1;
			// orientMe(camera_angle);
			// cout << "Right" << camera_angle << endl;
			// if(camera_angle == 360) camera_angle = 0;
		}
		else if (key == GLFW_KEY_UP && mods == GLFW_MOD_CONTROL){
			angle_x += 1;
			if (angle_x == 360) angle_x = 0;
			// moveMeFlat(1);
		}
		else if (key == GLFW_KEY_DOWN && mods == GLFW_MOD_CONTROL){
			angle_x -= 1;
			if (angle_x == -1) angle_x = 359;
		// moveMeFlat(-1);
		}
		else if(key == GLFW_KEY_UP){

			translate_x += 0.1 * sin((angle_y) * M_PI / 180);
			translate_z += 0.1 * cos((angle_y) * M_PI / 180);

			camera2[0]+=0.1 * sin((angle_y) * M_PI / 180);
			camera2[2]+=0.1 * cos((angle_y) * M_PI / 180);

			camera3[0]+=0.1 * sin((angle_y) * M_PI / 180);
			camera3[2]+=0.1 * cos((angle_y) * M_PI / 180);

			camera2[3]+=0.1 * sin((angle_y) * M_PI / 180);
			camera2[5]+=0.1 * cos((angle_y) * M_PI / 180);

			camera3[3]+=0.1* sin((angle_y) * M_PI / 180);
			camera3[5]+=0.1 * cos((angle_y) * M_PI / 180);
			tyre_x_angle -= 5;
			// 
			// cout << "sdif" << endl;
		}
		else if(key == GLFW_KEY_DOWN){

			translate_x -= 0.1 * sin((angle_y) * M_PI / 180);
			translate_z -= 0.1 * cos((angle_y) * M_PI / 180);

			camera2[0]-=0.1 * sin((angle_y) * M_PI / 180);
			camera2[2]-=0.1 * cos((angle_y) * M_PI / 180);

			camera3[0]-=0.1 * sin((angle_y) * M_PI / 180);
			camera3[2]-=0.1 * cos((angle_y) * M_PI / 180);

			camera2[3]-=0.1 * sin((angle_y) * M_PI / 180);
			camera2[5]-=0.1 * cos((angle_y) * M_PI / 180);

			camera3[3]-=0.1 * sin((angle_y) * M_PI / 180);
			camera3[5]-=0.1 * cos((angle_y) * M_PI / 180);
			tyre_x_angle += 5;
			// ChangeView();
		}
		else if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
			front_tyre_y_angle = 0;
		}
		else if(key == GLFW_KEY_RIGHT){
			/*if(front_tyre_y_angle < 45) front_tyre_y_angle += 0.1;
			angle_y += front_tyre_y_angle;
			if(angle_x > 360) angle_x -= 360;*/

			front_tyre_y_angle = -25;
			angle_y -= 1;
			if(angle_y < 0) angle_y = angle_y + 360;
			translate_x += 0.05 * sin((angle_y) * M_PI / 180);
			translate_z += 0.05 * cos((angle_y) * M_PI / 180);
			
			camera2[0] = translate_x + camera2_pos * sin(angle_y * M_PI / 180);
			camera2[2] = translate_z + camera2_pos * cos(angle_y * M_PI / 180);

			camera2[3] = translate_x + camera2_look_at * sin(angle_y * M_PI / 180);
			camera2[5] = translate_z + camera2_look_at * cos(angle_y * M_PI / 180);

			camera3[0] = translate_x + camera3_pos * sin(angle_y * M_PI / 180);
			camera3[2] = translate_z + camera3_pos * cos(angle_y * M_PI / 180);

			camera3[3] = translate_x + camera3_look_at * sin(angle_y * M_PI / 180);
			camera3[5] = translate_z + camera3_look_at * cos(angle_y * M_PI / 180);
			tyre_x_angle -= 5;
			// ChangeView();
		}
		else if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE){
			front_tyre_y_angle = 0;
		}
		else if(key == GLFW_KEY_LEFT){
			/*if (front_tyre_y_angle > -45) front_tyre_y_angle -= 0.1;
			angle_y -= front_tyre_y_angle;
			if(angle_x < 0) angle_x += 360;*/

			front_tyre_y_angle = 25;
			angle_y += 1;
			if(angle_y >360) angle_y = angle_y - 360;
			translate_x += 0.05 * sin((angle_y) * M_PI / 180);
			translate_z += 0.05 * cos((angle_y) * M_PI / 180);
			
			camera2[0] = translate_x + camera2_pos * sin(angle_y * M_PI / 180);
			camera2[2] = translate_z + camera2_pos * cos(angle_y * M_PI / 180);

			camera2[3] = translate_x + camera2_look_at * sin(angle_y * M_PI / 180);
			camera2[5] = translate_z + camera2_look_at * cos(angle_y * M_PI / 180);

			camera3[0] = translate_x + camera3_pos * sin(angle_y * M_PI / 180);
			camera3[2] = translate_z + camera3_pos * cos(angle_y * M_PI / 180);

			camera3[3] = translate_x + camera3_look_at * sin(angle_y * M_PI / 180);
			camera3[5] = translate_z + camera3_look_at * cos(angle_y * M_PI / 180);
			tyre_x_angle -= 5;
			// ChangeView();
		}
		else if(key==GLFW_KEY_B && action == GLFW_PRESS) animate();
		else if(key==GLFW_KEY_L){
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

			ofstream keyframes_file;
			keyframes_file.open("keyframes.txt", ios_base::app);
			keyframes_file << left_knee_angle << " ";
			keyframes_file << right_knee_angle << " ";
			keyframes_file << left_leg_angle << " ";
			keyframes_file << right_leg_angle << " ";
			keyframes_file << left_leg_hip_angle << " ";
			keyframes_file << right_leg_hip_angle << " ";
			keyframes_file << left_leg_hip_z_angle << " ";
			keyframes_file << right_leg_hip_z_angle << " ";
			keyframes_file << hip_center_z << " ";
			keyframes_file << hip_center_angle << " ";
			keyframes_file << left_upper_arm_x_angle << " ";
			keyframes_file << right_upper_arm_x_angle << " ";
			keyframes_file << left_upper_arm_z_angle << " ";
			keyframes_file << right_upper_arm_z_angle << " ";
			keyframes_file << left_elbow_angle << " ";
			keyframes_file << right_elbow_angle << " ";
			keyframes_file << translate_x << " ";
			keyframes_file << translate_y << " ";
			keyframes_file << translate_z << " ";
			keyframes_file << head_x << " ";
			keyframes_file << head_y << " ";
			keyframes_file << head_z << " ";
			keyframes_file << tyre_x_angle << " ";
			keyframes_file << front_tyre_y_angle << " ";
			keyframes_file << head_light1 << " ";
			keyframes_file << head_light2 << endl;
		}
		if(!transformed){
			int head_angle = 15;
			if(key==GLFW_KEY_1 && CurrentCameraNumber != 1){
				CurrentCameraNumber=1;
				ChangeView();
			}
			else if(key==GLFW_KEY_2 && CurrentCameraNumber != 2){
				CurrentCameraNumber=2;
				ChangeView();
			}
			else if(key==GLFW_KEY_3 && CurrentCameraNumber != 3){
				CurrentCameraNumber=3;
				ChangeView();
			}
			else if(key == GLFW_KEY_R && mods == GLFW_MOD_CONTROL){
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
			else if(key == GLFW_KEY_J && mods == GLFW_MOD_SHIFT){
				tyre_x_angle++;
				if(tyre_x_angle == 360) tyre_x_angle = 0;
			}	
			else if(key == GLFW_KEY_J){
				tyre_x_angle--;
				if(tyre_x_angle < 0) tyre_x_angle = 359;
			}
			else if(key == GLFW_KEY_K && mods == GLFW_MOD_SHIFT){
				front_tyre_y_angle++;
				if(front_tyre_y_angle == 360) front_tyre_y_angle = 0;
			}
			else if(key == GLFW_KEY_K){
				front_tyre_y_angle--;
				if(front_tyre_y_angle < 0) front_tyre_y_angle = 359;
			}
			else if(key == GLFW_KEY_T && action == GLFW_PRESS){
				transformed = true;
				reset_lower_body();
				for(double i = 0; i > - (torso_z); i-=hip_z_increment){
					hip_center_z -= hip_z_increment;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = 0; i < 90; i+=hip_angle_increment){
					hip_center_angle += hip_angle_increment;
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
				for(double i = 0; i < hip_z * 0.4 - thigh_z; i+=leg_z_increment){
					leg_z += leg_z_increment;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = left_upper_arm_z_angle; i > 0; i-=upper_arm_z_angle){
					left_upper_arm_z_angle -= upper_arm_z_angle;
					renderGL(getWindow());
					glfwSwapBuffers(getWindow());
					glfwPollEvents();
				}
				for(double i = right_upper_arm_z_angle; i < 0; i+=upper_arm_z_angle){
					right_upper_arm_z_angle += upper_arm_z_angle;
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
				for(double i = neck_translate; i > (torso_y - 0.4) / 2; i-=neck_translate_increment){
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
			for(double i = 0; i < hip_z * 0.4 - thigh_z; i+=leg_z_increment){
				leg_z -= leg_z_increment;
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
				hip_center_angle -= hip_angle_increment;
				renderGL(getWindow());
				glfwSwapBuffers(getWindow());
				glfwPollEvents();
			}
			for(double i = 0; i > - (torso_z); i-=hip_z_increment){
				hip_center_z += hip_z_increment;
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
		else if(key == GLFW_KEY_J && mods == GLFW_MOD_SHIFT){
			tyre_x_angle++;
			if(tyre_x_angle == 360) tyre_x_angle = 0;
		}
		else if(key == GLFW_KEY_J){
			tyre_x_angle--;
			if(tyre_x_angle < 0) tyre_x_angle = 359;
		}
		else if(key == GLFW_KEY_K && mods == GLFW_MOD_SHIFT){
			front_tyre_y_angle++;
			if(front_tyre_y_angle == 360) front_tyre_y_angle = 0;
		}
		else if(key == GLFW_KEY_K){
			front_tyre_y_angle--;
			if(front_tyre_y_angle < 0) front_tyre_y_angle = 359;
		}
		else if(key==GLFW_KEY_1 && CurrentCameraNumber != 1){
			CurrentCameraNumber=1;
			ChangeView();
		}
		else if(key==GLFW_KEY_2 && CurrentCameraNumber != 2){
			CurrentCameraNumber=2;
			ChangeView();
		}
		else if(key==GLFW_KEY_3 && CurrentCameraNumber != 3){
			CurrentCameraNumber=3;
			ChangeView();
		}
	}
};