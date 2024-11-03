#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream> 

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 700;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Structure_19101037", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Build and compile shader
    Shader shader("vertexShader.vs", "fragmentShader.fs");

    float outerRectVertices[] = {
        -0.4f,  0.2f, 0.0f,   1.0f, 1.0f, 1.0f,  
         0.4f,  0.2f, 0.0f,   1.0f, 1.0f, 1.0f,  
         0.4f,  -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  
        -0.4f,  -0.5f, 0.0f,   1.0f, 1.0f, 1.0f   
    };

    float innerRectVertices[] = {
        -0.3f,   0.1f, 0.0f,   0.1f, 0.1f, 0.1f, 
         0.3f,   0.1f, 0.0f,   0.1f, 0.1f, 0.1f, 
         0.3f,  -0.4f, 0.0f,   0.1f, 0.1f, 0.1f,  
        -0.3f,  -0.4f, 0.0f,   0.1f, 0.1f, 0.1f
    };


    float triangleVertices[] = {
         0.0f, 0.6f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.4f, 0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
         0.4f, 0.2f, 0.0f,   1.0f, 0.0f, 0.0f  
    };


    float greenRectVertices[] = {

        -0.35f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.24f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.24f,  -0.1f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.35f,  -0.1f, 0.0f, 0.0f, 1.0f, 0.0f
    };



    unsigned int VBOs[4], VAOs[4];
    glGenVertexArrays(4, VAOs);
    glGenBuffers(4, VBOs);


    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(outerRectVertices), outerRectVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(innerRectVertices), innerRectVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(greenRectVertices), greenRectVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glm::mat4 transform = glm::mat4(1.0f);
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


        glBindVertexArray(VAOs[2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);


        glm::mat4 greenTransform = glm::mat4(1.0f);
        greenTransform = glm::translate(greenTransform, glm::vec3(0.0f, -0.05f, 0.0f));
        greenTransform = glm::rotate(greenTransform, glm::radians(35.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        greenTransform = glm::scale(greenTransform, glm::vec3(1.1f, 0.3f, 1.0f));

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(greenTransform));
        glBindVertexArray(VAOs[3]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(4, VAOs);
    glDeleteBuffers(4, VBOs);

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}