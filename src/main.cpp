#include "main.hpp"

float SCREEN_WIDTH_FACTOR = 1.0;
float SCREEN_HEIGHT_FACTOR = 1.0;
bool isProportional = false;
string self_ip = "127.0.0.1";
string self_pubport = "5556";

/**
 * @brief The main entry point for the program.
 *
 * This function initializes SDL, loads the game entities, and then enters a
 * loop where it processes input, modifies the game world, and presents the
 * resulting scene. The loop continues indefinitely until the user closes the
 * window.
 *
 * @param argc The number of command line arguments passed to the program.
 * @param argv An array of strings containing the command line arguments.
 * @return 0 if the program exits successfully, non-zero otherwise.
 */
int main(int argc, char* argv[])
{
    //Call the initialization functions
    if(argc > 1)
    {
        if(std::string(argv[1]) == "server")
        {
            server_loop();
        }
        else if(std::string(argv[1]) == "client")
        {
            if(argc > 3)
            {
                string server_ip = argv[2];
                self_ip = argv[3];
                self_pubport = argv[4];
                // self_ip = getHostIP();
                client_loop(server_ip, self_ip, self_pubport);
            }
            else
            {
                std::cerr<<"Please provide the client ID"<<std::endl;
            }
        }
    }
    else
    {
        std::cerr<<"Please provide the mode of operation"<<std::endl;
    }
    return 0;
    // initSDL();
    // running=1;
    // l_s=r_s=0;
    // static int lastTime=0;
    // l_paddle.x=32; l_paddle.h=SCREEN_HEIGHT/4; l_paddle.y=(SCREEN_HEIGHT/2)-(l_paddle.h/2); l_paddle.w=12;
    // r_paddle=l_paddle; r_paddle.x=SCREEN_WIDTH-r_paddle.w-32;
    // ball.w=ball.h=SIZE;

    // serve();

    // while(running) {
    //     prepareScene();
    //     lastFrame=SDL_GetTicks();
    //     if(lastFrame>=(lastTime+1000)) {
    //         lastTime=lastFrame;
    //         fps=frameCount;
    //         frameCount=0;
    //     }

    //     update();
    //     input();
    //     render();
    // }
    // SDL_DestroyRenderer(app->renderer);
    // SDL_DestroyWindow(app->window);
    // SDL_Quit();
}