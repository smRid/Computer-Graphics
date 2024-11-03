#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.9f, 0.3f, 1.0f);\n"
"}\n\0";

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.87246, 0.56064   ,
        - 0.85541, 0.57323  ,
        - 0.83829, 0.57738  ,
        - 0.81139, 0.58148  ,
        - 0.78694, 0.58560  ,
        - 0.76980, 0.58553  ,
        - 0.75019, 0.58122  ,
        - 0.73303, 0.57693  ,
        - 0.70847, 0.56417  ,
        - 0.69123, 0.54722  ,
        - 0.67157, 0.53448  ,
        - 0.65925, 0.52177  ,
        - 0.63467, 0.50479  ,
        - 0.61498, 0.48783  ,
        - 0.59042, 0.47507  ,
        - 0.56339, 0.45807  ,
        - 0.54365, 0.43267  ,
        - 0.52146, 0.40726  ,
        - 0.49678, 0.37340  ,
        - 0.48214, 0.38178  ,
        - 0.46761, 0.40704  ,
        - 0.44573, 0.43226  ,
        - 0.42633, 0.46171  ,
        - 0.40932, 0.48274  ,
        - 0.39731, 0.52066  ,
        - 0.38530, 0.55859  ,
        - 0.36590, 0.58804  ,
        - 0.35634, 0.62598  ,
        - 0.34428, 0.65546  ,
        - 0.32972, 0.67650  ,
        - 0.31514, 0.69331  ,
        - 0.29563, 0.70589  ,
        - 0.28342, 0.71006  ,
        - 0.26875, 0.71421  ,
        - 0.24932, 0.73945  ,
        - 0.23474, 0.75626  ,
        - 0.21521, 0.76462  ,
        - 0.19812, 0.77299  ,
        - 0.18346, 0.77715  ,
        - 0.16390, 0.78128  ,
        - 0.14187, 0.78119  ,
        - 0.12958, 0.77270  ,
        - 0.10997, 0.76840  ,
        - 0.09036, 0.76409  ,
        - 0.06577, 0.74711  ,
        - 0.05116, 0.75971  ,
        - 0.03900, 0.77232  ,
        - 0.01707, 0.78910  ,
        0.00733, 0.80166    ,
        0.03181, 0.80155    ,
        0.05145, 0.79303    ,
        0.07103, 0.79295    ,
        0.09059, 0.79709    ,
        0.10778, 0.78857    ,
        0.12992, 0.77160    ,
        0.15695, 0.75461    ,
        0.17416, 0.74188    ,
        0.17926, 0.70810    ,
        0.19880, 0.71646    ,
        0.21833, 0.72482    ,
        0.23307, 0.71632    ,
        0.24781, 0.70782    ,
        0.26992, 0.69506    ,
        0.28226, 0.67813    ,
        0.30193, 0.66539    ,
        0.31916, 0.64844    ,
        0.33885, 0.63148    ,
        0.35120, 0.61455    ,
        0.36364, 0.58074    ,
        0.36872, 0.55119    ,
        0.38101, 0.54270    ,
        0.40307, 0.53838    ,
        0.42268, 0.53408    ,
        0.43013, 0.51717    ,
        0.43763, 0.49182    ,
        0.44997, 0.47489    ,
        0.46724, 0.45372    ,
        0.48445, 0.44099    ,
        0.49924, 0.42405    ,
        0.51406, 0.40289    ,
        0.52890, 0.37752    ,
        0.53877, 0.36482    ,
        0.54632, 0.33103    ,
        0.57101, 0.29717    ,
        0.58835, 0.26334    ,
        0.59098, 0.23379    ,
        0.60348, 0.19155    ,
        0.60861, 0.15355    ,
        0.62108, 0.11552    ,
        0.64074, 0.10278    ,
        0.65311, 0.08163    ,
        0.67032, 0.06890    ,
        0.68509, 0.05618    ,
        0.68038, 0.02667    ,
        0.67813, -0.00708   ,
        0.68563, -0.03243   ,
        0.69803, -0.05780   ,
        0.71529, -0.07897   ,
        0.72037, -0.10852   ,
        0.73527, -0.14234   ,
        0.74032, -0.16768   ,
        0.74789, -0.20569   ,
        0.75792, -0.24370   ,
        0.75810, -0.27324   ,
        0.75581, -0.29855   ,
        0.74338, -0.26896   ,
        0.72125, -0.25199   ,
        0.70393, -0.22238   ,
        0.68664, -0.19699   ,
        0.67677, -0.18429   ,
        0.66195, -0.16313   ,
        0.65448, -0.14200   ,
        0.63961, -0.11240   ,
        0.63502, -0.16302   ,
        0.63521, -0.19255   ,
        0.63044, -0.21363   ,
        0.62565, -0.23049   ,
        0.64291, -0.25166   ,
        0.66755, -0.27708   ,
        0.67986, -0.28979   ,
        0.69716, -0.31518   ,
        0.72176, -0.33638   ,
        0.74637, -0.35758   ,
        0.77841, -0.39147   ,
        0.79325, -0.41685   ,
        0.80330, -0.45909   ,
        0.81582, -0.50555   ,
        0.81850, -0.54354   ,
        0.81144, -0.58992   ,
        0.81170, -0.63212   ,
        0.80456, -0.66584   ,
        0.79735, -0.68691   ,
        0.78490, -0.65310   ,
        0.78235, -0.63621   ,
        0.76998, -0.61506   ,
        0.75772, -0.61079   ,
        0.75547, -0.64454   ,
        0.76053, -0.66988   ,
        0.76071, -0.69941   ,
        0.74860, -0.72046   ,
        0.73875, -0.71198   ,
        0.73365, -0.67820   ,
        0.73105, -0.65287   ,
        0.72612, -0.64863   ,
        0.71904, -0.69080   ,
        0.70932, -0.70341   ,
        0.69724, -0.72868   ,
        0.68484, -0.70331   ,
        0.68474, -0.68643   ,
        0.68464, -0.66956   ,
        0.68443, -0.63580   ,
        0.66982, -0.64840   ,
        0.66510, -0.67791   ,
        0.66041, -0.71165   ,
        0.65054, -0.69895   ,
        0.64305, -0.67360   ,
        0.63323, -0.66934   ,
        0.63111, -0.72418   ,
        0.62624, -0.72838   ,
        0.61138, -0.69878   ,
        0.60872, -0.66502   ,
        0.61099, -0.63549   ,
        0.62065, -0.61443   ,
        0.62302, -0.60178   ,
        0.61313, -0.58487   ,
        0.59586, -0.56370   ,
        0.57623, -0.55517   ,
        0.56388, -0.53824   ,
        0.54664, -0.52129   ,
        0.53435, -0.51280   ,
        0.52190, -0.47900   ,
        0.51198, -0.45786   ,
        0.50451, -0.43673   ,
        0.48732, -0.42822   ,
        0.48227, -0.40288   ,
        0.46745, -0.38172   ,
        0.45993, -0.35215   ,
        0.45240, -0.32258   ,
        0.43521, -0.31407   ,
        0.43063, -0.36469   ,
        0.43328, -0.39845   ,
        0.42607, -0.41952   ,
        0.41612, -0.39416   ,
        0.40620, -0.37302   ,
        0.40383, -0.38567   ,
        0.39664, -0.41096   ,
        0.39677, -0.43205   ,
        0.39677, -0.43205   ,
        0.38687, -0.41513   ,
        0.38187, -0.39824   ,
        0.37687, -0.38134   ,
        0.36961, -0.39396   ,
        0.36242, -0.41925   ,
        0.36257, -0.44457   ,
        0.34796, -0.45716   ,
        0.34786, -0.44029   ,
        0.33794, -0.41915   ,
        0.33309, -0.42757   ,
        0.32341, -0.44440   ,
        0.32088, -0.43173   ,
        0.31835, -0.41906   ,
        0.30841, -0.39371   ,
        0.30338, -0.37259   ,
        0.29591, -0.35146   ,
        0.29091, -0.33456   ,
        0.27869, -0.33873   ,
        0.26398, -0.33445   ,
        0.24195, -0.33435   ,
        0.22481, -0.33428   ,
        0.20031, -0.32996   ,
        0.18562, -0.32990   ,
        0.15866, -0.32556   ,
        0.14642, -0.32551   ,
        0.13173, -0.32545   ,
        0.10970, -0.32536   ,
        0.08514, -0.31260   ,
        0.05577, -0.31247   ,
        0.04108, -0.31241   ,
        0.00189, -0.30802   ,
        - 0.02504, -0.30791 ,
        - 0.04952, -0.30781 ,
        - 0.08624, -0.30765 ,
        - 0.11072, -0.30755 ,
        - 0.14745, -0.30739 ,
        - 0.17193, -0.30729 ,
        - 0.19156, -0.29877 ,
        - 0.21359, -0.29868 ,
        - 0.22836, -0.28596 ,
        - 0.25047, -0.27320 ,
        - 0.26518, -0.26892 ,
        - 0.27745, -0.26465 ,
        - 0.28977, -0.25194 ,
        - 0.31188, -0.23919 ,
        - 0.30438, -0.26454 ,
        - 0.29930, -0.29410 ,
        - 0.29425, -0.31943 ,
        - 0.28675, -0.34478 ,
        - 0.27673, -0.38280 ,
        - 0.27170, -0.40392 ,
        - 0.25683, -0.43352 ,
        - 0.24926, -0.47152 ,
        - 0.24418, -0.50108 ,
        - 0.23908, -0.53486 ,
        - 0.23890, -0.56439 ,
        - 0.24856, -0.58545 ,
        - 0.25083, -0.61498 ,
        - 0.26046, -0.64025 ,
        - 0.27510, -0.64863 ,
        - 0.29948, -0.66540 ,
        - 0.30922, -0.67380 ,
        - 0.33122, -0.67793 ,
        - 0.33349, -0.70745 ,
        - 0.35789, -0.72001 ,
        - 0.35560, -0.69470 ,
        - 0.35583, -0.65673 ,
        - 0.37032, -0.69042 ,
        - 0.37513, -0.70306 ,
        - 0.38480, -0.72411 ,
        - 0.40188, -0.73248 ,
        - 0.41678, -0.69866 ,
        - 0.40709, -0.68183 ,
        - 0.40729, -0.64807 ,
        - 0.41953, -0.64802 ,
        - 0.42667, -0.68174 ,
        - 0.42902, -0.69861 ,
        - 0.44355, -0.72387 ,
        - 0.46321, -0.71113 ,
        - 0.46337, -0.68581 ,
        - 0.45128, -0.66054 ,
        - 0.45141, -0.63945 ,
        - 0.47079, -0.67312 ,
        - 0.48543, -0.68150 ,
        - 0.49522, -0.68145 ,
        - 0.48318, -0.64775 ,
        - 0.46615, -0.63094 ,
        - 0.44909, -0.61836 ,
        - 0.45646, -0.61411 ,
        - 0.47610, -0.60559 ,
        - 0.46881, -0.59718 ,
        - 0.44443, -0.58040 ,
        - 0.43466, -0.57623 ,
        - 0.42250, -0.56362 ,
        - 0.41278, -0.55100 ,
        - 0.41054, -0.51726 ,
        - 0.41565, -0.48348 ,
        - 0.42070, -0.45814 ,
        - 0.43557, -0.42854 ,
        - 0.44059, -0.40742 ,
        - 0.44801, -0.39473 ,
        - 0.45799, -0.36516 ,
        - 0.46056, -0.34405 ,
        - 0.46567, -0.31027 ,
        - 0.47066, -0.29337 ,
        - 0.47327, -0.26805 ,
        - 0.48301, -0.27644 ,
        - 0.49262, -0.30594 ,
        - 0.50476, -0.32276 ,
        - 0.51202, -0.33539 ,
        - 0.52163, -0.36489 ,
        - 0.53375, -0.38593 ,
        - 0.53854, -0.40279 ,
        - 0.54328, -0.42809 ,
        - 0.55299, -0.44070 ,
        - 0.56286, -0.42800 ,
        - 0.56299, -0.40691 ,
        - 0.55823, -0.38583 ,
        - 0.55841, -0.35629 ,
        - 0.57044, -0.39000 ,
        - 0.57276, -0.41109 ,
        - 0.58247, -0.42370 ,
        - 0.58500, -0.41103 ,
        - 0.58510, -0.39416 ,
        - 0.57789, -0.37309 ,
        - 0.57804, -0.34777 ,
        - 0.59502, -0.37302 ,
        - 0.59987, -0.38144 ,
        - 0.61195, -0.40670 ,
        - 0.61693, -0.39402 ,
        - 0.61466, -0.36450 ,
        - 0.61229, -0.35185 ,
        - 0.61961, -0.35604 ,
        - 0.62677, -0.38554 ,
        - 0.63891, -0.40237 ,
        - 0.64375, -0.41079 ,
        - 0.63899, -0.38971 ,
        - 0.63911, -0.36861 ,
        - 0.63437, -0.34331 ,
        - 0.62721, -0.31381 ,
        - 0.62239, -0.30117 ,
        - 0.61038, -0.26325 ,
        - 0.60314, -0.24640 ,
        - 0.59345, -0.22956 ,
        - 0.58869, -0.20849 ,
        - 0.58392, -0.18741 ,
        - 0.57926, -0.14945 ,
        - 0.57691, -0.13259 ,
        - 0.57707, -0.10727 ,
        - 0.57730, -0.06929 ,
        - 0.57748, -0.03976 ,
        - 0.58011, -0.01021 ,
        - 0.58024, 0.01089  ,
        - 0.58526, 0.03201  ,
        - 0.59037, 0.06578  ,
        - 0.60508, 0.07006  ,
        - 0.61985, 0.08278  ,
        - 0.63214, 0.09127  ,
        - 0.65180, 0.10402  ,
        - 0.66901, 0.11675  ,
        - 0.68620, 0.12526  ,
        - 0.69849, 0.13375  ,
        - 0.71818, 0.15071  ,
        - 0.72552, 0.15074  ,
        - 0.74274, 0.16347  ,
        - 0.75753, 0.18041  ,
        - 0.77724, 0.20159  ,
        - 0.78464, 0.21006  ,
        - 0.79451, 0.22276  ,
        - 0.80443, 0.24390  ,
        - 0.81433, 0.26082  ,
        - 0.82177, 0.27773  ,
        - 0.82672, 0.28619  ,
        - 0.83917, 0.32000  ,
        - 0.85386, 0.32006  ,
        - 0.86615, 0.32855  ,
        - 0.86878, 0.35810  ,
        - 0.87135, 0.37920  ,
        - 0.87403, 0.41719  ,
        - 0.87659, 0.43408  ,
        - 0.88164, 0.45942  ,
        - 0.88427, 0.48896  ,
        - 0.88445, 0.51850  ,
        - 0.87973, 0.54802


    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // -----
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_LINE_LOOP, 0, 372);
        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
