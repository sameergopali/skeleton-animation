#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include "Model.hpp"
#include "Shader.h"
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);


bool firstMouse = true;

float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

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
    stbi_set_flip_vertically_on_load(true);

    //Model model("/Users/logpoint/Documents/ogl/ogl/resource/backpack/backpack.obj",1);
     Model model("/Users/logpoint/Downloads/ogldev-source/Content/boblampclean.md5mesh",1);
    //  Model model("/Users/logpoint/ogl/resource/snake.dae",1);
   // Animator anim("/Users/logpoint/ogl/resource/animX.dae");
   
   
    
  //  anim.loadAnimationTransform((float)glfwGetTime(),transformations);

    Shader sp("/Users/logpoint/Documents/ogl/ogl/vertex.glsl","/Users/logpoint/Documents/ogl/ogl/fragment.glsl");
    // render loop
    // -----------
    glm::mat4 transM= glm::mat4(1.0f);
    transM= glm::translate(transM, glm::vec3(0.0f,3.33f,0.0f)  );
    cout << glm::to_string(transM);
    for(int k = 0; k<4;k++){
        for(int j=0; j<4; j++){
            cout <<"a["<<k <<"]"<<"["<<j<<"]" << transM[k][j]<< endl;
        }
    }
    
    glm::mat4 mvp[3];
    mvp[0]=glm::perspective(glm::radians(30.0f), (float)SCR_WIDTH /(float)SCR_HEIGHT, 0.1f, 100.0f);
    mvp[1]=glm::mat4(1.0f);

  //  model.boneTransform(transformations,"/Users/logpoint/Downloads/ogldev-source/Content/boblampclean.md5mesh");
    
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
         vector<glm::mat4> transformations;
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
  
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        sp.use();
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)SCR_WIDTH /(float)SCR_HEIGHT, 0.1f, 100.0f);
        
        glm::mat4 view = camera.GetViewMatrix();
        sp.setMat4("projection", projection);
        sp.setMat4("view", view);

        // render the loaded model
     //   anim.loadAnimationTransform((float)glfwGetTime(),transformations);

        glm::mat4 modelM = glm::mat4(1.0f);
       modelM = glm::translate(modelM, glm::vec3(0.0f, 0.0f, -50.0f)); // translate it down so it's at the center of the scene
     //   modelM = glm::rotate(modelM,glm::radians(-90.0f), glm::vec3(1.0f,0.0f,0.0f));
     //   modelM = glm::scale(modelM, glm::vec3(0.05f, 0.05f, 0.05f));
      // modelM = glm::rotate(modelM, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp[2]=modelM;
        sp.setMat4("model", modelM);
        for(int i=0; i<3; i++){
            sp.setMat4("mvp["+to_string(i)+"]", mvp[i]);
            
        }
        
        
   //     sp.setMat4("nodeTransform",anim.nodeTransformationsMap["Cube"] );
        model.animate((float)glfwGetTime(), transformations);
        for(int i=0; i<transformations.size(); i++){
            cout << "gBones["+to_string(i)+"]";
            cout << glm::to_string(transformations[i]);
            sp.setMat4("gBones["+to_string(i)+"]", transformations[i]);
            
        }
        model.Draw(sp);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
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
    camera.ProcessMouseScroll(yoffset);
}
