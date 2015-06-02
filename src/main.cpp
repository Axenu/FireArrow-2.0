#include <iostream>
#include "FANode.h"
#include "FARenderPass.h"
#include "FAModel.h"
#include "FAScene.h"
#include "Game.h"

// GLFWwindow* window;

// void setupWindow() {
// 	if (!glfwInit()) {
// 		std::cout << "GLFW init failed!" << std::endl;
//     	exit(EXIT_FAILURE);
// 	}
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//     window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//     if (!window)
//     {
//         glfwTerminate();
//         std::cout << "GLFW creation of window failed!" << std::endl;
//         exit(EXIT_FAILURE);
//     }
//     glfwMakeContextCurrent(window);
//     // FARenderPass *pass = new FARenderPass();
//     // FACamera *camera = new FACamera(40.0f, 640, 480, 0.1, 400);
//     // FAMesh *mesh = new FAMesh("/Users/Axenu/Developer/clang++/first/resources/models/barrel.fa");
//     // FAModel *m = new FAModel(*mesh);
//     FAScene *scene = new FAScene();
//     // std::cout << "GLFW completed" << std::endl;
//     /* Loop until the user closes the window */
//     // printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
//     while (!glfwWindowShouldClose(window))
//     {
//         /* Render here */
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     	// pass->render();
//         // camera->useView();
//         // m->render(camera);
//         scene->update(0.025);
//         scene->render();
// 		// std::cout << "Render" << std::endl;
//         /* Swap front and back buffers */
//         glfwSwapBuffers(window);

//         /* Poll for and process events */
//         glfwPollEvents();
//     }

//     glfwTerminate();
// }

int main()
{
	// std::cout << "Init window!" << std::endl;
	// setupWindow();
 //    // std::cout << "Hello World!" << std::endl << "Makefile working with modifications";
 //    FANode *n = new FANode();
 //    n->setPosition(2,2,2);
 //    glm::vec3 v = glm::vec3(3,4,5);
 //    std::cout << v.x << std::endl;
 //    delete n;

     Game *game = new Game();
    
    //    game->setWindowAttributes();
    
    while (game->shouldTerminate()) {
        game->update();
        game->render();
    }
    
    delete game;

    // std::cin.ignore();
    // int i = 0;
    // std::cin >> i;
    return 0;
}
