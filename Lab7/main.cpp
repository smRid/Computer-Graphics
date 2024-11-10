#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// fan properties
float fanRotation = 0.0f;
bool isFanRotating = false;
float rotationSpeed = 10000.0f;  // Degrees per second

int main()
{
    // [Previous initialization code remains the same...]
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Table Fan", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // Center cube vertices (now in 3D)
    float centerCube[] = {
        // Front face
        -0.2f, -0.2f, 0.2f,   1.0f, 0.0f, 0.0f,  // red
        0.2f, -0.2f, 0.2f,    1.0f, 0.0f, 0.0f,
        0.2f, 0.2f, 0.2f,     1.0f, 0.0f, 0.0f,
        -0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,
        // Back face
        -0.2f, -0.2f, -0.2f,  1.0f, 0.0f, 0.0f,
        0.2f, -0.2f, -0.2f,   1.0f, 0.0f, 0.0f,
        0.2f, 0.2f, -0.2f,    1.0f, 0.0f, 0.0f,
        -0.2f, 0.2f, -0.2f,   1.0f, 0.0f, 0.0f
    };


    // Fan blade vertices (taller and 3D)
    float blade[] = {
        // Front face
        -0.1f, 0.0f, 0.05f,    0.0f, 0.8f, 0.0f,  // green
        0.1f, 0.0f, 0.05f,     0.0f, 0.8f, 0.0f,
        0.1f, 1.0f, 0.05f,     0.0f, 0.8f, 0.0f,
        -0.1f, 1.0f, 0.05f,    0.0f, 0.8f, 0.0f,
        // Back face
        -0.1f, 0.0f, -0.05f,   0.0f, 0.8f, 0.0f,
        0.1f, 0.0f, -0.05f,    0.0f, 0.8f, 0.0f,
        0.1f, 1.0f, -0.05f,    0.0f, 0.8f, 0.0f,
        -0.1f, 1.0f, -0.05f,   0.0f, 0.8f, 0.0f
    };

    // Stand vertices (3D rectangle)
    float stand[] = {
        // Front face
        -0.1f, -2.0f, 0.1f,    0.3f, 0.3f, 0.3f,  // dark gray
        0.1f, -2.0f, 0.1f,     0.3f, 0.3f, 0.3f,
        0.1f, 0.0f, 0.1f,      0.3f, 0.3f, 0.3f,
        -0.1f, 0.0f, 0.1f,     0.3f, 0.3f, 0.3f,
        // Back face
        -0.1f, -2.0f, -0.1f,   0.3f, 0.3f, 0.3f,
        0.1f, -2.0f, -0.1f,    0.3f, 0.3f, 0.3f,
        0.1f, 0.0f, -0.1f,     0.3f, 0.3f, 0.3f,
        -0.1f, 0.0f, -0.1f,    0.3f, 0.3f, 0.3f
    };

    // Table vertices (larger rectangle positioned below the stand)
    float table[] = {
        // Front face
        -1.5f, -2.1f, 0.75f,   0.6f, 0.3f, 0.0f,  // brown
        1.5f, -2.1f, 0.75f,    0.6f, 0.3f, 0.0f,
        1.5f, -2.0f, 0.75f,    0.6f, 0.3f, 0.0f,
        -1.5f, -2.0f, 0.75f,   0.6f, 0.3f, 0.0f,
        // Back face
        -1.5f, -2.1f, -0.75f,  0.6f, 0.3f, 0.0f,
        1.5f, -2.1f, -0.75f,   0.6f, 0.3f, 0.0f,
        1.5f, -2.0f, -0.75f,   0.6f, 0.3f, 0.0f,
        -1.5f, -2.0f, -0.75f,  0.6f, 0.3f, 0.0f
    };

    // Indices for drawing 3D objects
    unsigned int indices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,
        // Right face
        1, 5, 6,
        6, 2, 1,
        // Back face
        5, 4, 7,
        7, 6, 5,
        // Left face
        4, 0, 3,
        3, 7, 4,
        // Top face
        3, 2, 6,
        6, 7, 3,
        // Bottom face
        4, 5, 1,
        1, 0, 4
    };

    // Set up VAOs and VBOs for each component
    unsigned int centerVAO, centerVBO, centerEBO;
    glGenVertexArrays(1, &centerVAO);
    glGenBuffers(1, &centerVBO);
    glGenBuffers(1, &centerEBO);

    glBindVertexArray(centerVAO);
    glBindBuffer(GL_ARRAY_BUFFER, centerVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(centerCube), centerCube, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, centerEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Blade VAO setup
    unsigned int bladeVAO, bladeVBO, bladeEBO;
    glGenVertexArrays(1, &bladeVAO);
    glGenBuffers(1, &bladeVBO);
    glGenBuffers(1, &bladeEBO);

    glBindVertexArray(bladeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, bladeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blade), blade, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bladeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Stand VAO setup
    unsigned int standVAO, standVBO, standEBO;
    glGenVertexArrays(1, &standVAO);
    glGenBuffers(1, &standVBO);
    glGenBuffers(1, &standEBO);

    glBindVertexArray(standVAO);
    glBindBuffer(GL_ARRAY_BUFFER, standVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(stand), stand, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, standEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Table VAO setup
    unsigned int tableVAO, tableVBO, tableEBO;
    glGenVertexArrays(1, &tableVAO);
    glGenBuffers(1, &tableVBO);
    glGenBuffers(1, &tableEBO);

    glBindVertexArray(tableVAO);
    glBindBuffer(GL_ARRAY_BUFFER, tableVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(table), table, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tableEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // Update fan rotation
        if (isFanRotating)
        {
            fanRotation += rotationSpeed * deltaTime;
            if (fanRotation >= 360.0f)
                fanRotation -= 360.0f;
        }

        // Draw stand (at bottom)
        glm::mat4 model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        glBindVertexArray(standVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Draw table (at bottom of the scene)
        model = glm::mat4(1.0f);
        ourShader.setMat4("model", model);
        glBindVertexArray(tableVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Draw center cube (elevated)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));  // Already elevated in vertices
        ourShader.setMat4("model", model);
        glBindVertexArray(centerVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Draw the four blades
        glBindVertexArray(bladeVAO);
        for (int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::rotate(model, glm::radians(fanRotation + (i * 90.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
            ourShader.setMat4("model", model);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glDeleteVertexArrays(1, &centerVAO);
    glDeleteVertexArrays(1, &bladeVAO);
    glDeleteVertexArrays(1, &standVAO);
    glDeleteVertexArrays(1, &tableVAO);
    glDeleteBuffers(1, &centerVBO);
    glDeleteBuffers(1, &bladeVBO);
    glDeleteBuffers(1, &standVBO);
    glDeleteBuffers(1, &centerEBO);
    glDeleteBuffers(1, &bladeEBO);
    glDeleteBuffers(1, &standEBO);
    glDeleteBuffers(1, &tableVBO);
    glDeleteBuffers(1, &tableEBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    static bool sKeyPressed = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }


    // F key now toggles fan rotation
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if (!sKeyPressed) {
            isFanRotating = !isFanRotating;
            sKeyPressed = true;
        }
    }
    else {
        sKeyPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Add these callback function implementations at the end of the file

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}




void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}