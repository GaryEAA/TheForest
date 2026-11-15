#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "src/Shader.h"
#include "src/Motor_Cadenas.h"
#include "src/Motor_Reglas.h"
#include "src/Geometria_Tortuga.h"
#include "src/Follaje.h"
#include "src/Escena_Fondo.h"
#include "src/Escena_Bosque.h"

float posX = 0.0f;
float posY = 0.0f;
float zoom = 1.0f;
float aspecto = 1.5f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool teclaRSuelta = true;
unsigned semillaBosque = 1;

unsigned int VBO, VAO;
int totalVertices = 0;

void responsive(GLFWwindow* window, int width, int height);
void userInput(GLFWwindow* window);
void cargarBosque();

inline float calcularViento(float tiempo)
{
    float brisaBase = std::sin(tiempo * 2.2f) * 0.025f;
    float rafaga = std::sin(tiempo * 5.1f + 1.3f) * 0.008f;
    return brisaBase + rafaga;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1200, 800, "TheForest", NULL, NULL);
    if (!window) { std::cout << "Error en la ventana\n"; glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, responsive);
    if (glewInit() != GLEW_OK) { std::cout << "Error Glew\n"; glfwTerminate(); return -1; }

    Shader myShader("res/Shader/vertexShader.glsl", "res/Shader/fragmentShader.glsl");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    cargarBosque();

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        userInput(window);

        myShader.use();
        myShader.setFloat("xOffset", posX);
        myShader.setFloat("yOffset", posY);
        myShader.setFloat("escala", zoom);
        myShader.setFloat("viento", calcularViento(currentFrame));
        myShader.setFloat("aspecto", aspecto);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, totalVertices);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void cargarBosque()
{
    Malla bosque = construirBosque(semillaBosque);
    totalVertices = bosque.vertices();
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, bosque.datos.size() * sizeof(float), bosque.datos.data(), GL_STATIC_DRAW);
}

void responsive(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    if (height > 0) aspecto = (float)width / (float)height;
}

void userInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    float velocidad = 1.2f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        posX += velocidad;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        posX -= velocidad;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        posY -= velocidad;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        posY += velocidad;

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        zoom = limitar(zoom + 1.0f * deltaTime, 0.5f, 3.0f);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        zoom = limitar(zoom - 1.0f * deltaTime, 0.5f, 3.0f);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (teclaRSuelta)
        {
            semillaBosque++;
            cargarBosque();
            teclaRSuelta = false;
        }
    }
    else
    {
        teclaRSuelta = true;
    }
}
