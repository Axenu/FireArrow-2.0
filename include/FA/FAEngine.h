#ifndef __First__FAEngine__
#define __First__FAEngine__

#include <stdio.h>
#include <string>
#include <IL/il.h>
#include "FAScene.h"

class FAEngine {
    
private:
    
//    static FAEngine instance;
    
    FAScene* activeScene;
    GLFWwindow* window;
    
    
    float lastBufferedTime;
    
    void initLibraries();
    float tpf();
    void setupWindow();
    
public:
    FAEngine();
    
    void update();
    void render();
    
    void setWindowsSize(int width, int height);
    void setWindowTitle(std::string title);
    void setSamples(int sample);
    void setWindowColor(glm::vec3 color);
    void setDecorated(bool decoration);
    void setScene(FAScene* scene);
    void setCursorState(int state);
    void setPosition(float x, float y);
    
    int getCursorState();
    
    void initEngine();
    
    void swapScene(FAScene* scene);
    
    static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
    void forwardKeyInput(int key, int action);
    static void mouse_key_callback(GLFWwindow* win, int button, int action, int mods);
    void forwardMouseKeyInput(int button, int action);
    static void cursorPosition_callback(GLFWwindow* win, double x, double y);
    void forwardcursorPosition(double x, double y);
    
    bool shouldTerminate();
    
    virtual void setWindowAttributes(){}
    
    virtual ~FAEngine();
    
protected:
    
    int windowWidth;
    int windowHeigth;
    int samples;
    std::string windowTitle;
    glm::vec3 windowColor;
    bool isDecorated;
    int cursorState;
    glm::vec2 position;
    
    virtual FAScene* setInitialScene();
    virtual void init(){}
};

#endif /* defined(__FireArrow__FAEngine__) */
