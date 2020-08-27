#include "Renderer.h"

void GLClearError(){
    while(glGetError());
}

bool GLLogCall(void){

    unsigned int errr;
    bool didGoInside = false;

    while((errr = glGetError()) != GL_NO_ERROR){
        std::cout << "Error has occured: "<<errr << std::endl;
        didGoInside = true;
    }

    return !didGoInside;

}