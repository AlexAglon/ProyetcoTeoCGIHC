#include "TuxFather.h"
#include <string>
#include <glew.h>
#include <glfw3.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "iostream"

const float arm_angle_limit = 24.0f;
const float foot_angle_limit = 20.0f;

float armUpperAngleTypingLimit = 290.0f;
float armLowerAngleTypingLimit = 240.0f;


const float TUX_SCALE = 2.0f;
float typyingStep = 0.0f;

/*
TODO:

Tux debe manejar su pocisi�n en XYZ en el plano en todo momento, ya que a partir del tux
se �ra moviendo la camara haciendo uso de LookAt(), el cual nos permitira siempre tener
al tux en el foco de la camara sin importar a donde nos movemos.

*/

TuxFather_M::TuxFather_M(
	glm::vec3 startingPos,
	std::string body_model,
	std::string left_arm_model,
	std::string right_arm_model,
	std::string left_foot_model,
	std::string right_foot_model
) {
	// ### Pocision y direccion tux ###
	/*
		-460.0f, 1.0f, 60.0f   In front of the desk
	*/
	pos = startingPos;

	// Limit arms and foot movement
	larm_d = true; // front
	rfoot_d = true; // back
	left_arm_ang = 0.0f;
	right_arm_ang = 0.0f;

	right_foot_ang = 0.0f;
	left_foot_ang = 0.0f;

	//update();

	// ### Carga de modelos ### 
	body_M = Model();
	larm_M = Model();
	rarm_M = Model();
	lfoot_M = Model();
	rfoot_M = Model();

	rotation_angle = 0.0f;

	body_M.LoadModel(body_model);
	larm_M.LoadModel(left_arm_model);
	rarm_M.LoadModel(right_arm_model);
	rfoot_M.LoadModel(right_foot_model);
	lfoot_M.LoadModel(left_foot_model);
}

void TuxFather_M::walkAnimation() {
	/* Animate arms and legs while walking*/
	float step = 0.2f;

	// Brazo izquierdo
	if (larm_d) { // front
		if (left_arm_ang < arm_angle_limit) {
			// it is in the acceptable range for movement
			left_arm_ang += step;
		}
		else if (left_arm_ang >= arm_angle_limit) {
			// Change direction
			larm_d = false;
			left_arm_ang -= step;
		}
	}
	else { // back
		if (left_arm_ang > -arm_angle_limit) {
			// it is in the acceptable range for movement
			left_arm_ang -= step;
		}
		else if (left_arm_ang <= arm_angle_limit) {
			// Change direction
			larm_d = true;
			left_arm_ang += step;
		}
	}

	right_arm_ang = left_arm_ang;

	// Pie Derecho
	if (rfoot_d) { // front
		if (left_foot_ang < foot_angle_limit) {
			// it is in the acceptable range for movement
			left_foot_ang += step;
		}
		else if (left_foot_ang >= foot_angle_limit) {
			// Change direction
			rfoot_d = false;
			left_foot_ang -= step;
		}
	}
	else { // back
		if (left_foot_ang > -foot_angle_limit) {
			// it is in the acceptable range for movement
			left_foot_ang -= step;
		}
		else if (left_foot_ang <= foot_angle_limit) {
			// Change direction
			rfoot_d = true;
			left_foot_ang += step;
		}
	}
}

float typingStepIncrement = 0.0f;
float rAngleArm = -270.0f;
bool rArmDirection = true; // true: front, false; back

float lAngleArm = 0.0f;

void TuxFather_M::typingAnimation() {
	/* Animate arms and legs typing*/
	
	rAngleArm = armLowerAngleTypingLimit + typingStepIncrement;
	if (rArmDirection) {
		typingStepIncrement += 2.0f;
	}
	else
	{
		typingStepIncrement -= 2.0f;
	}

	std::cout << "rArmAngle: " << rAngleArm << "\t";

	// lAngleArm = armUpperAngleTypingLimit;
	
	if ( rArmDirection && rAngleArm > armUpperAngleTypingLimit) {
		std::cout << "Changing direction to front\n";
		rArmDirection = false;
		typingStepIncrement = -typingStepIncrement;
	}
	else if (not rArmDirection && rAngleArm < armLowerAngleTypingLimit) {
		std::cout << "Changing direction to back\n";
		rArmDirection = true;
		typingStepIncrement = -typingStepIncrement;
	}

	right_arm_ang = rAngleArm;


	//if (larm_d) { // front
	//	if ( left_arm_ang < armAngleTypingLimit) {
	//		// it is in the acceptable range for movement
	//		left_arm_ang += typyingStep;
	//	}
	//	else if (left_arm_ang >= armAngleTypingLimit) {
	//		// Change direction
	//		larm_d = false;
	//		left_arm_ang -= typyingStep;
	//	}
	//}
	//else { // back
	//	if (left_arm_ang > -armAngleTypingLimit) {
	//		// it is in the acceptable range for movement
	//		left_arm_ang -= step;
	//	}
	//	else if (left_arm_ang <= armAngleTypingLimit) {
	//		// Change direction
	//		larm_d = true;
	//		left_arm_ang += step;
	//	}
	//}

	//float baseRotation = 90.0f;

	//left_arm_ang = baseRotation;
	////right_arm_ang += baseRotation;

	//right_arm_ang = left_arm_ang;
}

void TuxFather_M::shouldMoveHandsAndFeet(bool state) {
	moveHandsAndFeet = state;
}


void TuxFather_M::move(GLuint& uniformModel, glm::vec3 newPos, float rotAngle) {
	pos = newPos;
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 aux;

	if (moveHandsAndFeet) {
		walkAnimation();
	}

	
	//std::cout << "X: " << pos.x << " Y: " << pos.y << " Z: " << pos.z << "\n";
	model = glm::translate(model, glm::vec3(pos.x, pos.y, pos.z));
	model = glm::rotate(model, glm::radians(rotAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(TUX_SCALE));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	body_M.RenderModel();

	aux = model;
	model = glm::rotate(model, glm::radians(left_arm_ang), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	larm_M.RenderModel();

	// FIXME: if rarm_ang is -larm_ang, then why does it exist?
	model = aux;
	model = glm::rotate(model, glm::radians(right_arm_ang), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	rarm_M.RenderModel();

	model = aux;
	model = glm::rotate(model, glm::radians(right_foot_ang), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lfoot_M.RenderModel();
	model = aux;
	model = glm::rotate(model, glm::radians(-right_foot_ang), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	rfoot_M.RenderModel();

}