#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 7.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


//change speed
float translateSpeed = 1.0f;
float rotationSpeed = 0.2f;

//changes of cube
float fan_translate_X = 0;
float fan_translate_Y = 0;
float fan_translate_Z = 0;

bool isCubeRotating = false;
bool isCeelingFanRotating = false;
float cube_rotate_Z = 0;
float cube_rotate_Y = 0;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab 7 (Camera and 3D Object)", NULL, NULL);
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

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //----------------------------------------------------------------------------Triangle
    

    //----------------------------------------------------------------------------Cube

    float cube_vertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,

        0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.5f, 1.0f, 0.0f, 1.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cube_VAO, cube_VBO, cube_EBO;
    glGenVertexArrays(1, &cube_VAO);
    glGenBuffers(1, &cube_VBO);
    glGenBuffers(1, &cube_EBO);

    glBindVertexArray(cube_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);


    //Enabling opacity changing capability
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);

        

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
        ourShader.use();


        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);



        //initialization
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, translateToCenter, translateToPivot, translateWholeFan, rotateBladeMatrix;
        float translate_X, translate_Y, translate_Z, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, scale_X, scale_Y, scale_Z;
        float pivotX, pivotY, pivotZ;

        //-----------------------------------------------------------------------------------------cube
        translate_X = translate_Y = translate_Z = rotateAngle_X = rotateAngle_Y = rotateAngle_Z = 0;
        scale_X = scale_Y = scale_Z = 1.0;

        if (isCubeRotating)
            cube_rotate_Z = (cube_rotate_Z + rotationSpeed);
        if (isCeelingFanRotating)
            cube_rotate_Y = (cube_rotate_Y + rotationSpeed);



        translateWholeFan = glm::translate(identityMatrix, glm::vec3(fan_translate_X, fan_translate_Y, fan_translate_Z));

        //----------------------------------------------------------------------------------------Rotation around pivot
        pivotX = 0.25f;
        pivotY = 0.25f;
        translateToCenter = glm::translate(identityMatrix, glm::vec3(-pivotX, -pivotY, 0.0f));
        translateToPivot = glm::translate(identityMatrix, glm::vec3(pivotX, pivotY, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(cube_rotate_Z), glm::vec3(0.0f, 0.0f, 1.0f));


        //-----------------------------------------------------------------------------------------Center
        model = translateWholeFan * translateToPivot * rotateZMatrix * translateToCenter;
        ourShader.setMat4("model", model);

        glm::vec4 newColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        ourShader.setBool("changeColorFromMain", false);

        //-----------------------------------------------------------------------------------------Right Hand
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25f, 0.1f, 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.6f, 0.6f));
        model = translateWholeFan * translateToPivot * rotateZMatrix * translateToCenter * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.7f, 0.8f, 0.9f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //-----------------------------------------------------------------------------------------Left Hand
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 0.1f, 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.6f, 0.6f));
        model = translateWholeFan * translateToPivot * rotateZMatrix * translateToCenter * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.7f, 0.8f, 0.9f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //-----------------------------------------------------------------------------------------Upper Hand
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.12f, 0.25f, 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 2.5f, 0.6f));
        model = translateWholeFan * translateToPivot * rotateZMatrix * translateToCenter * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.7f, 0.8f, 0.9f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //-----------------------------------------------------------------------------------------Bottom Hand
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.12f, -1.0f, 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 2.5f, 0.6f));
        model = translateWholeFan * translateToPivot * rotateZMatrix * translateToCenter * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.7f, 0.8f, 0.9f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);


        //----------------------------------------------------------------------------------------Stand

        //a
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, -1.6f, -0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 4.0f, 0.3f));
        model = translateWholeFan * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //b
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.2f, -0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.3f, 1.0f));
        model = translateWholeFan * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.4f, 0.4f, 0.4, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //c
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.7, -1.6f, -1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.2f, 3.0f));
        model = translateWholeFan * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.9f, 0.8f, 0.7f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);


        //---------------------------------------------------------------------------------Ceiling Fan

        //----------------------------------------------------------------------------------------Rotation around pivot

        translateToCenter = glm::translate(identityMatrix, glm::vec3(-0.16f, -1.85f, -3.05f));
        translateToPivot = glm::translate(identityMatrix, glm::vec3(0.16f, 1.85f, 3.05f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(cube_rotate_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        



       //------------------------------------------------------------------------------------------- Center Stand

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.12f, 2.0f, 3.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.6f, 0.2f));
        model = translateWholeFan * translateMatrix * scaleMatrix;
       
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);


        //------------------------------------------------------------------------------------------- Center Cube

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.09, 1.6f, 2.8f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.6f, 1.0f));
        model = translateWholeFan * translateToPivot * rotateYMatrix * translateToCenter * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //--------------------------------------------------------------------------------------------------------------Left Blade
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.0f, 1.7f, 2.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.2f, 0.6f));
        model = translateWholeFan * translateToPivot * rotateYMatrix * translateToCenter * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //--------------------------------------------------------------------------------------------------------------Right Blade
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1f, 1.7f, 2.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.2f, 0.6f));
        model = translateWholeFan * translateToPivot * rotateYMatrix * translateToCenter * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);


        //--------------------------------------------------------------------------------------------------------------Back Blade
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.7f, 2.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.2f, 0.6f));
        float cube_blade_back = 90;
        rotateBladeMatrix = glm::rotate(identityMatrix, glm::radians(cube_blade_back), glm::vec3(0.0f, 1.0f, 0.0f));

        model = translateWholeFan * translateToPivot * rotateYMatrix * translateToCenter  * translateMatrix * rotateBladeMatrix * scaleMatrix ;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);

        //--------------------------------------------------------------------------------------------------------------Front Blade
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.32f, 1.7f, 2.9f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.2f, 0.6f));
        float cube_blade_front = -90;
        rotateBladeMatrix = glm::rotate(identityMatrix, glm::radians(cube_blade_front), glm::vec3(0.0f, 1.0f, 0.0f));

        model = translateWholeFan * translateToPivot * rotateYMatrix * translateToCenter * translateMatrix * rotateBladeMatrix * scaleMatrix;
        ourShader.setMat4("model", model);

        newColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        ourShader.setBool("changeColorFromMain", true);
        ourShader.setVec4("colorFromMain", newColor);
        glBindVertexArray(cube_VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        ourShader.setBool("changeColorFromMain", false);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cube_VAO);
    glDeleteBuffers(1, &cube_VAO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
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

    //changes of cube
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        fan_translate_Z -= translateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        fan_translate_Z += translateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        fan_translate_X -= translateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        fan_translate_X += translateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        fan_translate_Y += translateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        fan_translate_Y -= translateSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        isCubeRotating = !isCubeRotating;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        isCeelingFanRotating = !isCeelingFanRotating;
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
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
