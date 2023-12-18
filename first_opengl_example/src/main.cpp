#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void OnFramebufferSizeChange(GLFWwindow* window, const int width, const int height);
void OnKeyEvent(GLFWwindow* window, const int key, const int scancode, const int action, const int mods);
void Render();

int main(int argc, const char** argv)
{
    // 시작을 알리는 로그
    SPDLOG_INFO("Start Program!");

    // glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize GLFW");
    if (!glfwInit()) 
    {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
    }

    // ... glfwInit() 호출 후

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ... glfwCreateWindow() 호출 전

    // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    auto glVersion = (const char*)glGetString(GL_VERSION);
    SPDLOG_INFO("OpenGL context version: {}", glVersion);

    // ... context 지정 부분

    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);

    // ... loop 시작 부분

    // glfw 루프 실행, 윈도우 close 버튼을 누르면 정상 종료
    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) 
    {
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void OnFramebufferSizeChange(GLFWwindow *window, const int width, const int height)
{
    SPDLOG_INFO("framebuffer size changed : ({} x {})", width, height);
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow *window, const int key, const int scancode, const int action, const int mods)
{
    SPDLOG_INFO("key : {}, scancode : {}, action : {}, mods : {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" : 
        action == GLFW_RELEASE ? "Released" : 
        action == GLFW_REPEAT ? "Repeat" : "Unknown", 
        mods & GLFW_MOD_CONTROL ? "C" : "_",
        mods & GLFW_MOD_SHIFT ? "S" : "_", 
        mods & GLFW_MOD_ALT ? "A" : "_" );
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Render()
{
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
