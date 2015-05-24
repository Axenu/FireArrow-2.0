#include <iostream>
#include "FANode.h"
#include "FARenderPass.h"

GLFWwindow* window;

void setupWindow() {
	if (!glfwInit())
    	exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    FARenderPass *pass = new FARenderPass();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
    	pass->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

int main()
{
	setupWindow();
    std::cout << "Hello World!" << std::endl << "Makefile working with modifications";
    FANode *n = new FANode();
    n->setPosition(2,2,2);
    glm::vec3 v = glm::vec3(3,4,5);
    std::cout << v.x << std::endl;
    delete n;
    // std::cin.ignore();
    // int i = 0;
    // std::cin >> i;
    return 0;
}
