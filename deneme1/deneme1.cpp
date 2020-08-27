#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

using namespace std;


struct ShaderProgramSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath){
    
    std::ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){

            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        
        }
        else{
            ss[(int)type] << line << "\n";
            
        }
    }

    return {ss[0].str(), ss[1].str()};

}



namespace {
   void errorCallback(int error, const char* description) {
      fprintf(stderr, "GLFW error %d: %s\n", error, description);
   }

   GLFWwindow* initialize() {
      int glfwInitRes = glfwInit();
      if (!glfwInitRes) {
         fprintf(stderr, "Unable to initialize GLFW\n");
         return nullptr;
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
      if (!window) {
         fprintf(stderr, "Unable to create GLFW window\n");
         glfwTerminate();
         return nullptr;
      }

      glfwMakeContextCurrent(window);

      int gladInitRes = gladLoadGL();
      if (!gladInitRes) {
         fprintf(stderr, "Unable to initialize glad\n");
         glfwDestroyWindow(window);
         glfwTerminate();
         return nullptr;
      }

      return window;
   }
}

static int CompileShader(unsigned int type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char * src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        std::cout << "error" << std::endl;

        char * logMessage = new char[length];
        glGetShaderInfoLog(id, length, &length, logMessage);



        std::cout << "Failed to compile the"<<
                 (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" <<  std::endl;
        std::cout << logMessage << std::endl;
        delete logMessage;

        glDeleteShader(id);
        return 0;
    }


    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){

    unsigned int program = glCreateProgram();

    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(int argc, char* argv[]) {
    glfwSetErrorCallback(errorCallback);

    GLFWwindow* window = initialize();
    if (!window) {
        return 0;
    }

    float positions[12] ={
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.4f, -0.1f,
        0.7, 0.1f,
        0.5f, -0.8f        
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };


    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;

    layout.Push<float>(2);

    va.Bind();
    va.AddBuffer(vb, layout);


    IndexBuffer ib(indices, 6);


    
    ShaderProgramSource shaderSources = ParseShader("./resources/shaders.shader");

    unsigned int shader = CreateShader(shaderSources.VertexSource, shaderSources.FragmentSource);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    assert(location != -1);

    glUniform4f(location, 0.3f, 0.1f, 0.f, 1.0f);    


    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
    

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}