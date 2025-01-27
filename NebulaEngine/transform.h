#pragma once


class Transform {
public:
	// Translate
	static glm::mat4 Translate(glm::mat4 model, glm::vec3 translation) {
		return glm::translate(model, translation);
	}

	static glm::mat4 TranslateX(glm::mat4 model, float translationX) {
		return glm::translate(model, glm::vec3(translationX, 0.0f, 0.0f));
	}

	static glm::mat4 TranslateY(glm::mat4 model, float translationY) {
		return glm::translate(model, glm::vec3(0.0f, translationY, 0.0f));
	}

	static glm::mat4 TranslateZ(glm::mat4 model, float translationZ) {
		return glm::translate(model, glm::vec3(0.0f, 0.0f, translationZ));
	}


	// Scale
	static glm::mat4 Scale(glm::mat4 model, glm::vec3 scaleFactor) {
		return glm::scale(model, scaleFactor);
	}

	static glm::mat4 ScaleX(glm::mat4 model, float scaleFactorX) {
		return glm::scale(model, glm::vec3(scaleFactorX, 1.0f, 1.0f));
	}

	static glm::mat4 ScaleY(glm::mat4 model, float scaleFactorY) {
		return glm::scale(model, glm::vec3(1.0f, scaleFactorY, 1.0f));
	}

	static glm::mat4 ScaleZ(glm::mat4 model, float scaleFactorZ) {
		return glm::scale(model, glm::vec3(1.0f, 1.0f, scaleFactorZ));
	}

	static glm::mat4 ScaleUniform(glm::mat4 model, float scaleFactor) {
		return glm::scale(model, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
	}


	// Rotate
	static glm::mat4 Rotate(glm::mat4 model, glm::vec3 axis, float angle) {
		return glm::rotate(model, glm::radians(angle), axis);
	}

	static glm::mat4 RotateX(glm::mat4 model, float angle) {
		return glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	static glm::mat4 RotateY(glm::mat4 model, float angle) {
		return glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	static glm::mat4 RotateZ(glm::mat4 model, float angle) {
		return glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	}


	// Others
	static glm::mat4 Reset() {
		return glm::mat4(1);
	}

	
	// Camera
	static glm::mat4 LookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up) {
		return glm::lookAt(position, target, up);
	}

	static glm::mat4 Perspective(float fov, float aspectRatio, float near, float far) {
		return glm::perspective(glm::radians(fov), aspectRatio, near, far);
	}

	static glm::mat4 Orthographic(float left, float right, float bottom, float top, float near, float far) {
		return glm::ortho(left, right, bottom, top, near, far);
	}
};