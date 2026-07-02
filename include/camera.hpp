#pragma once
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

class Camera{
    public:
        glm::vec3 pos;
        glm::vec3 front;
        glm::vec3 up;

        float yaw;
        float pitch;

        float speed;
        float sensitivity;
        float fov;

        Camera(glm::vec3 startPos = glm::vec3(0.0f,0.0f,3.0f))
        :
            pos(startPos ),
            front(glm::vec3(0.0f,0.0f,-1.0f)),
            up(glm::vec3(0.0f,1.0f,0.0f)),
            yaw(-90.f),
            pitch(0.f),
            speed(2.5f),
            sensitivity(0.1f),
            fov(45.f)
            {}
        glm::mat4 getview() const {
            return glm::lookAt(pos, pos + front,up);
        }
        glm::mat4 getProjection(float aspectRatio) const {
            return glm::perspective(glm::radians(fov),aspectRatio,0.1f,100.f);
        }

        void processKeyboard(GLFWwindow* window, float deltatime){
            float velocity = speed * deltatime;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                pos += front * velocity;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                pos -= front * velocity;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                    pos -= glm::normalize(glm::cross(front, up)) * velocity;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                    pos += glm::normalize(glm::cross(front, up)) * velocity;
        }

        void processMouse(GLFWwindow* window,float xOffset, float yOffset){
            xOffset *= sensitivity;
            yOffset *= sensitivity;

            yaw += xOffset;
            pitch -= yOffset;

            if (pitch > 89.f) pitch = 89.f;
            if (pitch < -89.f) pitch = -89.f;

            glm::vec3 direction;
                direction.x = cos(glm::radians(yaw))* cos(glm::radians(pitch));
                direction.y = sin(glm::radians(pitch));
                direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                front = glm::normalize(direction);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


        }
};
