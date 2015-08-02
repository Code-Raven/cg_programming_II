#include "Application.h"

GLFWwindow* window = NULL;

void setup::window_refresh_callback(GLFWwindow* window){
    glfwSwapBuffers(window);
}

int setup::InitWindowFailed(){
    if(glfwInit() == GLFW_FAIL){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return EXIT_WITH_ERROR;
    }
    
    glfwWindowHint(GLFW_SAMPLES, ANTIALIASING);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Gets working on mac...
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old open gl...
    
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_NAME, NULL, NULL);
    
    if(window == NULL){
        fprintf(stderr, "Failed to create/open GLFW window.\n");
        glfwTerminate();
        return EXIT_WITH_ERROR;
    }
    
    //Initialize GLEW.
    glfwMakeContextCurrent(window);
    
    //Ensure we can capture the escape key being pressed below.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    //glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
    
    return EXIT_WITH_SUCCESS;
}

GLuint setup::LoadShaders(const char *vertex_file_path, const char *fragment_file_path){
    
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    //Read in shader code here...
    string vertexShaderCode = "";
    ifstream vertexShaderStream(vertex_file_path, ios::in);
    if(vertexShaderStream.is_open()){
        string line = "";
        while(getline(vertexShaderStream, line)){
            vertexShaderCode += "\n" + line;
        }
        vertexShaderStream.close();
    }
    
    string fragmentShaderCode = "";
    ifstream fragmentShaderStream(fragment_file_path, ios::in);
    if(fragmentShaderStream.is_open()){
        string line = "";
        while(getline(fragmentShaderStream, line)){
            fragmentShaderCode += "\n" + line;
        }
        fragmentShaderStream.close();
    }
    
    GLint result = GL_FALSE;
    int infoLogLength = 0;
    
    //Compile shaders here...
    printf("Compiling vertex shader: %s", vertex_file_path);
    char const *vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);
    
    //Check Vertex Shader...
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    char* vertexShaderErrorMessage = new char[infoLogLength];
    glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &vertexShaderErrorMessage[0]);
    
    //Compile Fragment Shader...
    printf("Compiling fragment shader: %s\n", fragment_file_path);
    char const *fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);
    
    //Check Vertex Shader...
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    
    char* fragmentShaderErrorMessage = new char[infoLogLength];
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &fragmentShaderErrorMessage[0]);
    
    //Link Program...
    fprintf(stdout, "Linking program\n");
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    
    //Check the progam...
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    char *programErrorMessage = new char[glm::max(infoLogLength, int(1))];
    glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
    fprintf(stdout, "%s\n", &programErrorMessage[0]);
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    
    delete(programErrorMessage);
    programErrorMessage = NULL;
    
    delete(vertexShaderErrorMessage);
    vertexShaderErrorMessage = NULL;
    
    delete(fragmentShaderErrorMessage);
    fragmentShaderErrorMessage = NULL;
    
    return programID;
}

int setup::InitGlewFailed(){
    glewExperimental = true; //Has to do with core profile.
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "Failed to initialize GLEW\n");
        return EXIT_WITH_ERROR;
    }
    
    return EXIT_WITH_SUCCESS;
}

double setup::getDeltaTime(){
    static double lastTime = glfwGetTime();
    
    double now = glfwGetTime();
    double deltaTime = now - lastTime;
    
    lastTime = now;
    
    return deltaTime;
}

stdVecStr setup::ReadFiles(const char* fExt){
    
    stdVecStr files;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (RESOURCE_PATH)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            const char* fileName = ent->d_name;
            string str(fileName);
            size_t strPos = str.find(".");
            if(strPos != -1){
                const char* ext = fileName + strPos;
                if (strcmp(ext, fExt) == 0) {
                    files.push_back(RESOURCE_PATH + string(fileName));
                }
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("Cannot read file");
    }
    
    return files;
}

