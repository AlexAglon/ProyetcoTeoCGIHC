#pragma once
#pragma once
#include <string>
#include <glm.hpp>
#include "Model.h"

/*
Handle Tux animation, thats all.
*/

//const float STEP_INC = 3.0f;


class TuxFather_M
{
private:

	// ### MOVEMENT ###
	glm::vec3 pos; // Donde est�

	GLfloat moveSpeed;
	GLfloat rotation_angle;

	Model body_M, larm_M, rarm_M, lfoot_M, rfoot_M;

	// limit these to certain values
	float left_arm_ang;
	float right_arm_ang;
	float left_foot_ang;
	float right_foot_ang;

	bool larm_d, rfoot_d;
	bool moveHandsAndFeet;

	//void update();

public:
	TuxFather_M(
		glm::vec3 startingPosition,
		std::string body_model,
		std::string left_arm_model,
		std::string right_arm_model,
		std::string left_foot_model,
		std::string right_foot_model
	);
	TuxFather_M();

	glm::vec3 getPos() { return pos; };

	void walkAnimation();
	void typingAnimation();
	void moveTypingHands();

	void shouldMoveHandsAndFeet(bool state);

	void setPos(glm::vec3 newPos);
	void move(GLuint& uniformModel, glm::vec3 newPos, float rotAngle);
};

