#include "viewer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include "mesh.h"

using std::string;
using std::vector;

void meshFromHeightmap(const vector< unsigned char >& heightmap, Mesh& mesh,
                       unsigned int size)
{
    mesh.clear();
    GLfloat inc = 2.0f / (size - 1);
    GLfloat position[4], color[4];
    position[3] = 1.0f;
    color[3] = 1.0f;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            GLfloat z = heightmap[j + i * size] / 255.0f;
            position[0] = j * inc - 1.0f;
            position[1] = i * inc - 1.0f;
            position[2] = z;
            color[0] = color[1] = color[2] = z;
            mesh.insertVertex(position, color);
        }
    }
    unsigned int indices[3];
    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - 1; j++) {
            indices[0] = j + i * size;
            indices[1] = (j + 1) + i * size;
            indices[2] = j + (i + 1) * size;
            mesh.makeFace(indices);
            indices[0] = indices[1];
            indices[1] = (j + 1) + (i + 1) * size;
            mesh.makeFace(indices);
        }
    }
} // meshFromHeightmap()

string loadFile(const char* filename)
{
    std::ifstream ifs(filename);
    string content((std::istreambuf_iterator< char >(ifs)),
                        (std::istreambuf_iterator< char >()));
    return content;
} // loadFile()

GLuint compileShader(GLenum shaderType, const char *shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    
    // Check for error during compilation
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    // If not successful
    if(status == GL_FALSE) {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cout << buffer << std::endl;
    }
    return shader;
} // compileShader()

void Viewer::run()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Windowed
    GLFWwindow* window = glfwCreateWindow(800, 600, "Viewer", 
            nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    // Transform heightmap data into mesh data
    Mesh mesh;
    meshFromHeightmap(heightmap, mesh, size);

    // Create Vertex Array Object to hold attribute layout data
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create Vertex Buffer Object to hold vertex data
    GLuint vbo;
    glGenBuffers(1, &vbo); 

    // Make VBO active array buffer and pass it vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 
    glBufferData(GL_ARRAY_BUFFER, mesh.vertexCount() * Mesh::vertexSize(),
            mesh.getVertexData(), GL_STATIC_DRAW);

    // Create Element Buffer for vertex order
    GLuint ebo;
    glGenBuffers(1, &ebo); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            mesh.faceCount() * 3 * sizeof(unsigned int),
            mesh.getIndexData(), GL_STATIC_DRAW);

    // Load and compile shaders
    string vertexSource = loadFile("src/shaders/shader.vert").c_str();
    string fragmentSource = loadFile("src/shaders/shader.frag").c_str();
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, 
            vertexSource.c_str());
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, 
            fragmentSource.c_str());
    
    // Create shader program and link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram); 

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    // Specify how data is retrieved from vertex buffer
    glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, 
            Mesh::vertexSize(), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE,
            Mesh::vertexSize(), (void*)(4 * sizeof(float)));

    glm::mat4 model;
    model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));

    glm::mat4 view = glm::lookAt(
            glm::vec3(1.2f, 1.2f, 2.4f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 
            800.0f / 600.0f, 1.0f, 10.0f);

    GLint uniMvp = glGetUniformLocation(shaderProgram, "mvpTransform");
    glm::mat4 mvp = proj * view * model;
    glUniformMatrix4fv(uniMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    while(!glfwWindowShouldClose(window)) {

        float rotateDeg = 0.0f;
        float scale = 1.0f;

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GL_TRUE);
        } else if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            rotateDeg = -1.0f;
        } else if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            rotateDeg =  1.0f;
        } else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            scale = 1.02f;
        } else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            scale = 0.98f;
        }

        if(rotateDeg != 0.0f || scale != 1.0f) {
            view = glm::rotate(view, glm::radians(rotateDeg), 
                    glm::vec3(0.0f, 0.0f, 1.0f));
            view = glm::scale(view, glm::vec3(scale, scale, scale));

            mvp = proj * view * model;
            glUniformMatrix4fv(uniMvp, 1, GL_FALSE, glm::value_ptr(mvp));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, mesh.faceCount() * 3, 
                GL_UNSIGNED_INT, 0);
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    glDeleteVertexArrays(1, &vao);

    glfwTerminate();

} // run()


void Viewer::setHeightmap(const std::vector< unsigned char >& heightmap,
                          unsigned int size)
{
    this->heightmap = heightmap;
    this->size = size;
} // loadHeightmap()
