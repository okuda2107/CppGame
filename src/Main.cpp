#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class LogManager
{
public:
    LogManager(){};
    //Info out
    void LOGI(std::string msg)
    {
        std::cout << msg << std::endl;
        
    }

    //Error out
    void LOGE(std::string msg)
    {
        std::cerr << msg << std::endl;
    }
};

class App
{
public:
    App(LogManager *log) : m_log(log) {};
    bool run()
    {
        if(!init())
            return false;

        while(glfwWindowShouldClose(m_win) == GL_FALSE)
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glfwSwapBuffers(m_win);
            glfwWaitEvents();
        }

        terminate();

        return true;
    }; 

private:
    LogManager *m_log;
    GLFWwindow *m_win;

    bool init()
    { 
        if(!init_glfw())
        {
            m_log->LOGE("Failed to initialize GLFW.");
            terminate();
            return false;
        }
        m_log->LOGI("GLFW Initialized.");

        if(!init_window(640, 480, "SAMPLE"))
        {
            m_log->LOGE("Failed to initialize window.");
            terminate();
            return false;
        }
        m_log->LOGI("Window Initialized.");

        //必ずGLEW初期化より前
        glfwMakeContextCurrent(m_win);
        
        if(!init_glew())
        {
            m_log->LOGE("Failed to initialize GLEW.");
            terminate();
            return false;
        }
        m_log->LOGI("GLEW Initialized.");


        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

        return true;
    }
    
    void terminate()
    {
        glfwTerminate();
    }

    bool init_glfw(void)
    {
        if(glfwInit() == GL_FALSE)
            return false;

        return true;
    }

    bool init_window(int width, int height, std::string title)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        
        if(m_win == nullptr)
            return false;

        return true;
    }

    bool init_glew(void)
    {
        GLenum err;
        err = glewInit();
        if(err != GLEW_OK)
        {
            m_log->LOGE(
                    "GLEW Error :"
                    + std::string((char*)glewGetErrorString(err))
            );
            return false;
        }

        return true;
    }
};

static LogManager s_logman;

int main(void)
{
    App app(&s_logman);
    
    return app.run() ? 0 : -1;
}
