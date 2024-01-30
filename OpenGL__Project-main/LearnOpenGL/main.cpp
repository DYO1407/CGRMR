#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include "Model.h"
#include "stb_image.h"
#include "Camerar.h"

#include "shader.h"

#include <iostream>

using namespace std;


// try to fix something  

// Vertex Shader Source 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // input of the vertex Shader (position)
"layout (location = 1) in vec3 aColor;\n" // the color variable has attribute position 1
"out vec3 ourColor;\n" // output of vertex Shader
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n" // aPos(x,y,z)
"   ourColor = aColor;\n" // vec4(0.5, 0.0, 0.0, 1.0)
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n" // output of the fragment shader 
"in vec3 ourColor;\n" // input for fragment shader (in keyword) // uniform vec4 ourColor
"void main()\n"
"{\n"
"    FragColor = vec4(ourColor,1.0);\n" // vec4(0.5, 0.0, 0.0, 1.0);
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;




// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
bool gamestarted = false;

float adjustmentX_user = 0.0f;
float adjustmentY_user = 15.0f;
float adjustmentZ_user = 0.0f;

bool goingRight = false;
bool goingLeft = false;

float startFrame = 0.0f;
int main(void)
{

    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    GLFWwindow* window;
     Assimp::Importer importer;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1600, 900, "Hello Dude From OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
   // Shader ourShader("3.3.shader.vs", "3.3.shader.fs"); // you can name your shader files however you like
    stbi_set_flip_vertically_on_load(true);
    Shader ourShader("shaders/model_loading.vs", "shaders/model_loading.fs");

    // load models
    // -----------
    Model Track_Model(("resources/models/Track/Track.obj"));
    Model Tank_Model(("resources/models/Tank/Tank.obj"));
    Model Container_Model(("resources/models/Container/Container.obj"));
    Model BurnedVehicle_Model(("resources/models/Burned_vehicle/Burned_Vehicle.obj"));
    Model Barrel_Model(("resources/models/Barrel/Barrel.obj"));
    Model WoodenBarrel_Model(("resources/models/Wooden_Barrel/Wooden_Barrel.obj"));
    Model RustWheel_Model(("resources/models/Rust_wheel/Rust_Wheel.obj"));

    Model TrashCan_Model(("resources/models/Trash_Can/Trash_Can.obj"));
    Model Soldier_Model(("resources/models/Soldier/soldier1_01.obj"));
    Model Monster_Model(("resources/models/monster/nanosuit.obj"));


    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };


    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    glEnable(GL_DEPTH_TEST);
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // we can tell OpenGL how it should interpret the vertex data (per vertex attribute)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // To draw the wirefram of the object 
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    ourShader.use(); // Aktivate the shader Program

    // passing the transformation matrix to the Vertex_shader 
    unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
 

    // Enabling Depth Testing
    glEnable(GL_DEPTH_TEST);


    glm::vec3 soldierPosition = glm::vec3(55.0f, 0.0f, -7.0f);
    float soldierSpeed = -6.0f;
    
   
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float currentFrame = static_cast<float>(glfwGetTime());
        if (gamestarted)
        {
            deltaTime = currentFrame - lastFrame - startFrame;
            lastFrame = currentFrame - startFrame;

            soldierPosition.x += soldierSpeed * deltaTime;
            glm::vec3 cameraPosition = glm::vec3(11.0f, 15.0f, -4.0f);
            cameraPosition += soldierPosition;

            camera.Position = cameraPosition;
            camera.Pitch = -40.0f;

            glm::vec3 direction = glm::normalize(soldierPosition - camera.Position);
            //camera.Yaw = glm::degrees(atan2(-direction.z, direction.x)) - 180.0f;
            camera.Yaw = -182.0f;
        }
        processInput(window);
        
        //  create transformations
        glm::mat4 trans = glm::mat4(1.0f);

        // Passing Projection Matrix to Vertex Shader
    

        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 track_model = glm::mat4(1.0f);
        track_model = glm::translate(track_model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        track_model = glm::scale(track_model, glm::vec3(1.0f, 1.0f, 2.0f));	// it's a bit too big for our scene, so scale it down

        ourShader.setMat4("model", track_model);
        Track_Model.Draw(ourShader);

        glm::mat4 tank_model = glm::mat4(1.0f);
        tank_model = glm::translate(tank_model, glm::vec3(5.0f, 0.0f, -6.0f)); // translate it down so it's at the center of the scene
        tank_model = glm::scale(tank_model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        tank_model = glm::rotate(tank_model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        ourShader.setMat4("model", tank_model);
        Tank_Model.Draw(ourShader);


        glm::mat4 container_model = glm::mat4(1.0f);
        container_model = glm::translate(container_model, glm::vec3(-45.0f, 0.0f, -7.0f)); // translate it down so it's at the center of the scene
        container_model = glm::scale(container_model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        container_model = glm::rotate(container_model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", container_model);
        Container_Model.Draw(ourShader);

        glm::mat4 burnedvehicle_model = glm::mat4(1.0f);
        burnedvehicle_model = glm::translate(burnedvehicle_model, glm::vec3(40.0f, 0.0f, -7.0f)); // translate it down so it's at the center of the scene
        burnedvehicle_model = glm::scale(burnedvehicle_model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        burnedvehicle_model = glm::rotate(burnedvehicle_model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        ourShader.setMat4("model", burnedvehicle_model);
        BurnedVehicle_Model.Draw(ourShader);


        glm::mat4 barrel_model = glm::mat4(1.0f);
        barrel_model = glm::translate(barrel_model, glm::vec3(45.0f, 0.0f, -5.0f)); // translate it down so it's at the center of the scene
        barrel_model = glm::scale(barrel_model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", barrel_model);
        Barrel_Model.Draw(ourShader);

        glm::mat4 woodenbarrel_model = glm::mat4(1.0f);
        woodenbarrel_model = glm::translate(woodenbarrel_model, glm::vec3(-20.0f, 0.0f, -7.0f)); // translate it down so it's at the center of the scene
        woodenbarrel_model = glm::scale(woodenbarrel_model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", woodenbarrel_model);
        WoodenBarrel_Model.Draw(ourShader);

        glm::mat4 rustwheel_model = glm::mat4(1.0f);
        rustwheel_model = glm::translate(rustwheel_model, glm::vec3(30.0f, 0.2f, -6.0f)); // translate it down so it's at the center of the scene
        rustwheel_model = glm::scale(rustwheel_model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", rustwheel_model);
        RustWheel_Model.Draw(ourShader);

        glm::mat4 trashcan_model = glm::mat4(1.0f);
        trashcan_model = glm::translate(trashcan_model, glm::vec3(20.0f, 0.0f, -7.0f)); // translate it down so it's at the center of the scene
        trashcan_model = glm::scale(trashcan_model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
        trashcan_model = glm::rotate(trashcan_model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        ourShader.setMat4("model", trashcan_model);
        TrashCan_Model.Draw(ourShader);

        float addX = 0.0f;
        if (goingRight)
            addX -= 3.0f;
        if (goingLeft)
            addX += 3.0f;
        glm::mat4 soldier_model = glm::mat4(1.0f);
        soldier_model = glm::translate(soldier_model, soldierPosition + glm::vec3(0.0f, 0.0f, addX)); // translate it down so it's at the center of the scene
        soldier_model = glm::scale(soldier_model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
        soldier_model = glm::rotate(soldier_model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        ourShader.setMat4("model", soldier_model);
        Soldier_Model.Draw(ourShader);

        glm::mat4 monster_model = glm::mat4(1.0f);
        monster_model = glm::translate(monster_model, glm::vec3(63.0f, 0.0f, -5.0f)); // translate it down so it's at the center of the scene
        monster_model = glm::scale(monster_model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        monster_model = glm::rotate(monster_model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        ourShader.setMat4("model", monster_model);
        Monster_Model.Draw(ourShader);
       

        glBindVertexArray(VAO);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;

  
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//process all input : query GLFW whether relevant keys are pressed / released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, 0.01);
       // adjustmentX_user++;
      
    }
      
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, 0.01);
        //adjustmentY_user++;
    }
        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, 0.01);
       // adjustmentZ_user++;
        if (goingRight)
            goingRight = false;
        else if (!goingLeft)
            goingLeft = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, 0.01);

        if (goingLeft)
            goingLeft = false;
        else if (!goingRight)
            goingRight = true;
    }
       
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        gamestarted = !gamestarted;
        startFrame = static_cast<float>(glfwGetTime());
    }
       
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
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

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
