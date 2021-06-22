#include <iostream>
#include "../headers/rCube.hpp"
#include "../headers/solver.hpp"
#include <sys/resource.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


void fixRam();
void startUp();
void renderCube(rCube &cube);

int main() {

    //Call start up function
    startUp();

    //Create image processor
    //imageProcessor processor = imageProcessor();
    //Init the processing of images
    //processor.init();

    //Create solver and cube objects
    rCube rcube1 = rCube();
    solver solver1 = solver();

    rcube1.printCube();

    //Apply random solver to the cube
    solver1.randomSolver(rcube1);

    renderCube(rcube1);

    return 0;
}


/*
 * Small function to start up required functionality such as
 * init of the random seed for later use, and to allocate more ram to the stack
 */
void startUp(){

    std::srand((unsigned int) std::time(NULL));
    fixRam();


}

void fixRam(){

    //Cast to u_long to fix compiler error
    const rlim_t kStackSize = (u_long) 5000 * 1024 * 1024;   // min stack size = 500 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }
}

void updateFaces(sf::RectangleShape faces[6][9], rCube &cube){

    //set each face to have the same size and give them a location to be drawn
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 9; j++){
            faces[i][j].setSize(sf::Vector2f(40,40));
            faces[i][j].setPosition(sf::Vector2f(40 + (i*150) + ((j+1)%3 *40),((j/3)+1)*40));
            faces[i][j].setOutlineThickness(1);
            faces[i][j].setOutlineColor(sf::Color::Black);

            //May as well set the color while we are here
            sf::Color bColor;

            switch (cube.cube[i][(j+1)%3][(j/3)]){
                case white:
                    bColor = sf::Color::White;
                    break;
                case red:
                    bColor = sf::Color::Red;
                    break;
                case green:
                    bColor = sf::Color::Green;
                    break;
                case blue:
                    bColor = sf::Color::Blue;
                    break;
                case yellow:
                    bColor = sf::Color::Yellow;
                    break;
                case orange:
                    bColor = sf::Color(255, 156,0);
                    break;
                default:
                    bColor = sf::Color::Black;
            }
            faces[i][j].setFillColor(bColor);
        }
    }

}

void renderCube(rCube &cube){


    sf::RectangleShape faces[6][9];

    //set each face to have the same size and give them a location to be drawn
    updateFaces(faces, cube);
    // create the window
    sf::RenderWindow window(sf::VideoMode(950, 200), "Cube");

    window.setFramerateLimit(20);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();


            /*
             * Handle all of the key input
             */
            if(event.type == sf::Event::KeyPressed){

                switch (event.key.code){

                    case sf::Keyboard::Num1 :
                        cube.makeMove((moves)0);
                        break;

                    case sf::Keyboard::Num2 :
                        cube.makeMove((moves)1);
                        break;

                    case sf::Keyboard::Num3 :
                        cube.makeMove((moves)2);
                        break;

                    case sf::Keyboard::Num4 :
                        cube.makeMove((moves)3);
                        break;

                    case sf::Keyboard::Num5 :
                        cube.makeMove((moves)4);
                        break;

                    case sf::Keyboard::Num6 :
                        cube.makeMove((moves)5);
                        break;

                    case sf::Keyboard::Num7 :
                        cube.makeMove((moves)6);
                        break;

                    case sf::Keyboard::Num8 :
                        cube.makeMove((moves)7);
                        break;

                    case sf::Keyboard::Num9 :
                        cube.makeMove((moves)8);
                        break;


                    case sf::Keyboard::Num0 :
                        cube.makeMove((moves)9);
                        break;

                    case sf::Keyboard::Dash :
                        cube.makeMove((moves)10);
                        break;
                    case sf::Keyboard::Equal :
                        cube.makeMove((moves)11);
                        break;
                    default:
                        break;
                }


            }



        }

        // clear the window with black color
        window.clear(sf::Color(220,220,220));
        updateFaces(faces, cube);
        // draw everything here...
        // window.draw(...);

        for(int i = 0; i < 6; i++){

            for(int j = 0; j < 9; j++){

                window.draw(faces[i][j]);

            }

        }

        // end the current frame
        window.display();
    }

}