
#include "Engine.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL.h"
#include "Text.h"
#include <fstream>
#include "Image.h"
#include <sstream>
#include <time.h>
#include <math.h>
#include <windows.h>
//#include "SDL_image.h";

double deg2rad(int nr)
{
    float pi = 3.141592;
    return (double)nr * pi / 180;
}

typedef unsigned char byte;
typedef struct rgb
{
    byte red = 0, green = 0, blue = 0;
}
RGB_t;


bool write_truecolor_tga(const std::string& filename, RGB_t* data, unsigned width, unsigned height)
{
    std::ofstream tgafile(filename.c_str(), std::ios::binary);
    if (!tgafile) return false;

    // The image header
    byte header[18] = { 0 };

    header[2] = 2;
    header[12] = width & 0xFF;
    header[13] = (width >> 8) & 0xFF;
    header[14] = height & 0xFF;
    header[15] = (height >> 8) & 0xFF;
    header[16] = 24;  // bits per pixel

    tgafile.write((const char*)header, 18);

    // The image data is stored bottom-to-top, left-to-right
    for (int y = height - 1; y >= 0; y--)
        for (int x = 0; x < width; x++)
        {
            tgafile.put((char)data[(x * height) + y].blue);
            tgafile.put((char)data[(x * height) + y].green);
            tgafile.put((char)data[(x * height) + y].red);
        }

    tgafile.close();
    return true;
}



//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
TTF_Font* font;

bool Engine::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL


    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("Abstract Image generator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    if (TTF_Init() < 0)
    {
        std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
        success = false;
    }

    font = TTF_OpenFont("OpenSans-Bold.ttf", 72);
    if (!font)
    {
        std::cout << "Error loading font: " << TTF_GetError() << std::endl;
        return false;
    }

    return success;
}




void  Engine::closeWindow(SDL_Window* window)
{

    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL subsystems
    //SDL_Quit();
}


void Engine::loadButtons()
{

    //main menu
    Button* bgMenu1 = new Button(0, 0, 1080, 920);
    bgMenu1->setPath("background.bmp");
    buttonsMenu[0] = bgMenu1;
    buttonsImageViewer[0] = bgMenu1;
    buttonsImageGenerator[0] = bgMenu1;

    Button* viewImage = new Button(380, 390, 260, 60);
    viewImage->setPath("Image_Viewer.bmp");
    buttonsMenu[1] = viewImage;

    Button* generateImage = new Button(380, 570, 260, 60);
    generateImage->setPath("Generare_Imagine.bmp");
    buttonsMenu[2] = generateImage;

    Button* exit = new Button(380, 750, 260, 60);
    exit->setPath("Exit.bmp");
    buttonsMenu[3] = exit;

    //second menu
    Button* visualize = new Button(380, 570, 260, 60);
    visualize->setPath("View_Image.bmp");
    buttonsImageViewer[1] = visualize;

    Button* backViewer = new Button(380, 750, 260, 60);
    backViewer->setPath("Back.bmp");
    buttonsImageViewer[2] = backViewer;

    Button* textBox = new Button(100, 382, 950, 60);
    textBox->setPath("text_box.bmp");
    buttonsImageViewer[3] = textBox;


    Button* generateImageMenu = new Button(380, 570, 260, 60);
    generateImageMenu->setPath("Generate_Image.bmp");
    buttonsImageGenerator[1] = generateImageMenu;

    Button* backImageGenerator = new Button(380, 750, 260, 60);
    backImageGenerator->setPath("Back.bmp");
    buttonsImageGenerator[2] = backImageGenerator;

    Button* textBoxNamePicture = new Button(100, 152, 950, 60);
    textBoxNamePicture->setPath("text_box.bmp");
    buttonsImageGenerator[3] = textBoxNamePicture;

    Button* textBoxWidth = new Button(100, buttonsImageGenerator[3]->getY()+130, 950, 60);
    textBoxWidth->setPath("lil_text_box.bmp");
    buttonsImageGenerator[4] = textBoxWidth;


    Button* textBoxHeight = new Button(100, buttonsImageGenerator[4]->getY()+130, 950, 60);
    textBoxHeight->setPath("lil_text_box.bmp");
    buttonsImageGenerator[5] = textBoxHeight;


    Button* mainButton = new Button(700, 414, 260, 60);
    mainButton->setPath("dropdown1.bmp");
    dropdownButtons[1] = mainButton;

    Button* formula1 = new Button(dropdownButtons[1]->getX(), dropdownButtons[1]->getY()+60, 260, 60);
    formula1->setPath("dropdown2.bmp");
    dropdownButtons[2] = formula1;

    Button* formula2 = new Button(dropdownButtons[1]->getX(), dropdownButtons[2]->getY() + 60, 260, 60);
    formula2->setPath("dropdown3.bmp");
    dropdownButtons[3] = formula2;

    Button* formula3 = new Button(dropdownButtons[1]->getX(), dropdownButtons[3]->getY() + 60, 260, 60);
    formula3->setPath("dropdown4.bmp");
    dropdownButtons[4] = formula3;

    Button* formula4 = new Button(dropdownButtons[1]->getX(), dropdownButtons[4]->getY() + 60, 260, 60);
    formula4->setPath("dropdown5.bmp");
    dropdownButtons[5] = formula4;

    Button* formula5 = new Button(dropdownButtons[1]->getX(), dropdownButtons[5]->getY() + 60, 260, 60);
    formula5->setPath("dropdown6.bmp");
    dropdownButtons[6] = formula5;

}

void Engine::loadText()
{
    Text *nameText=new Text();
    nameText->createText(font, white, "Name:", 100, 80);
    nameText->setFont(57);
    textGenerator[0] = nameText;
    Text* heightText = new Text();
    heightText->createText(font, white, "Height:", 100, textGenerator[0]->getY()+210);
    heightText->setFont(57);
    textGenerator[1] = heightText;
    Text* widthText = new Text();
    widthText->createText(font, white, "Width:", 100, textGenerator[1]->getY()+340);
    widthText->setFont(57);
    textGenerator[2] = widthText;
}


/*
int getSizeOfArray(Button* buttons[]) {
	return sizeof(buttons) / sizeof(buttons[0]);

}
*/

void Engine::resetColor(int goodIndex){

    for (int indexButtons = 2; indexButtons < sizeof(dropdownButtons) / sizeof(dropdownButtons[0]); indexButtons++){
        if(indexButtons!=goodIndex){
            dropdownButtons[indexButtons]->changeColor(255,255,255);
        }
    }
}

void Engine::startProgram()
{

 ShowWindow(GetConsoleWindow(), SW_HIDE);

    loadButtons();

    bool quit = false;
    SDL_Event e;
    srand(time(NULL));
    //Start up SDL and create window
    if (!init())
    {
        return;
    }
    loadText();
    Uint32 mouse;
    int mouseX, mouseY;
    Image image;
    SDL_Window* window2= NULL;
    SDL_Rect dest;
    SDL_Color foreground = { 0, 0, 0 };
    std::string inputImageNameV;
    std::string inputHeight;
    std::string inputWidth;
    std::string inputImageNameG;
    Text nameImageG;
    Text nameImageV;
    Text heightG;
    Text widthG;
    Text nameImageText;
    Text nameImageTextV;
    int w=400, h=400;
    int previousMenu;
    int actualTextBox = 0;
    int marginOfError = 20;
    bool dropdownActivated = false;
    bool secondWindowExist = false;
    double formula;
    int formulaSelected=2;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            mouse = SDL_GetMouseState(&mouseX, &mouseY);

            if (e.type == SDL_QUIT)
            {
                quit = true;
            }



            //apasare tasta esc
            if (e.key.keysym.scancode == 41)
            {
                if (actualMenu > 0)
                {
                    inputImageNameV.clear();
                    actualMenu = 0;
                    actualTextBox = 0;

                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                previousMenu = actualMenu;
                SDL_PumpEvents();

                //era aici mouse

                std::cout << "Click " << mouseX << " " << mouseY << std::endl;
                if (actualMenu == 0)
                {
                    SDL_StopTextInput;
                    inputImageNameV.clear();
                    for (int indexButtons = 1; indexButtons < sizeof(buttonsMenu) / sizeof(buttonsImageGenerator[0]); indexButtons++)
                    {
                        if (buttonsMenu[indexButtons]->verifyCollisionWithMouse(mouseX, mouseY))
                        {

                            switch (indexButtons)
                            {
                            case 1:
                                actualMenu = 1;
                                break;
                            case 2:
                                actualMenu = 2;
                                break;
                            case 3:
                                closeWindow(gWindow);
                                break;
                            }
                        }
                    }
                }
                //SDL_RenderClear(renderer);

                if (actualMenu == 1)
                {


                    for (int indexButtons = 1; indexButtons < sizeof(buttonsImageGenerator) / sizeof(buttonsImageGenerator[0]); indexButtons++)
                    {
                        if (buttonsImageViewer[indexButtons]->verifyCollisionWithMouse(mouseX, mouseY))
                        {

                            if (indexButtons == 1 && secondWindowExist == false)
                            {
                                if (inputImageNameV.size() > 0)
                                {
                                    image.loadImage(inputImageNameV + ".tga");
                                    //asta e fereastra a 2-a de apare
                                    window2 = SDL_CreateWindow("Window 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, image.width, image.height, 0);
                                    SDL_Renderer* renderer1 = SDL_CreateRenderer(gWindow, -1, 0); //gwindow e fereastra parinte
                                    SDL_Renderer* renderer2 = SDL_CreateRenderer(window2, -1, 0);
                                    inputImageNameV = inputImageNameV + ".tga";  //input e numele pozei de il bagi in app
                                    SDL_Texture* texture1 = IMG_LoadTexture(renderer1, inputImageNameV.c_str());
                                    inputImageNameV.pop_back();
                                    inputImageNameV.pop_back();
                                    inputImageNameV.pop_back();
                                    inputImageNameV.pop_back();
                                    SDL_Texture* texture2 = SDL_CreateTexture(renderer2, SDL_GetWindowPixelFormat(gWindow), SDL_TEXTUREACCESS_STREAMING, 640, 480);
                                    SDL_Texture* target = SDL_CreateTexture(renderer1, SDL_GetWindowPixelFormat(gWindow), SDL_TEXTUREACCESS_TARGET, 640, 480);
                                    SDL_Surface* buffer = SDL_CreateRGBSurface(0, 640, 480, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
                                    SDL_RenderClear(renderer1);
                                    SDL_RenderClear(renderer2);
                                    SDL_SetRenderTarget(renderer1, target);
                                    SDL_RenderCopy(renderer1, texture1, NULL, NULL);
                                    SDL_RenderReadPixels(renderer1, NULL, SDL_GetWindowPixelFormat(gWindow), buffer->pixels, buffer->pitch);
                                    SDL_SetRenderTarget(renderer1, NULL);
                                    SDL_UpdateTexture(texture2, NULL, buffer->pixels, buffer->pitch);
                                    SDL_RenderCopy(renderer2, texture2, NULL, NULL);
                                    SDL_RenderPresent(renderer1);
                                    SDL_RenderPresent(renderer2);


                                    SDL_DestroyRenderer(renderer1);
                                    SDL_DestroyRenderer(renderer2);
                                    SDL_DestroyTexture(texture1);
                                    SDL_DestroyTexture(texture2);
                                    SDL_DestroyTexture(target);
                                    SDL_FreeSurface(buffer);
                                    secondWindowExist = true;
                                }
                            }
                            else if (indexButtons == 2)
                            {
                                inputImageNameV.clear();
                                actualMenu = 0;

                            }

                        }
                    }


                }

                if (actualMenu == 2 && previousMenu == actualMenu)
                {

                    if (dropdownButtons[1]->verifyCollisionWithMouse(mouseX, mouseY))
                    {

                        if (dropdownActivated)
                        {
                            dropdownActivated = false;
                        }
                        else dropdownActivated = true;
                    }


                    for (int indexButtons = 2; indexButtons < sizeof(dropdownButtons) / sizeof(dropdownButtons[0]); indexButtons++)
                    {
                        if (dropdownButtons[indexButtons]->verifyCollisionWithMouse(mouseX, mouseY)&&dropdownActivated==true)
                        {

                            dropdownButtons[indexButtons]->changeColor(0,200,0);
                            if(indexButtons==2)
                            {
                                formulaSelected=1;
                                resetColor(indexButtons);

                            }
                            if(indexButtons==3)
                            {
                                formulaSelected=2;
                                resetColor(indexButtons);

                            }
                            if(indexButtons==4)
                            {
                                formulaSelected=3;
                                resetColor(indexButtons);

                            }
                            if(indexButtons==5)
                            {
                                formulaSelected=4;
                                resetColor(indexButtons);

                            }
                            if(indexButtons==6)
                            {
                                formulaSelected=5;
                                resetColor(indexButtons);

                            }

                        }

                    }
                    for (int indexButtons = 1; indexButtons < sizeof(buttonsImageGenerator) / sizeof(buttonsImageGenerator[0]); indexButtons++)
                    {
                        if (buttonsImageGenerator[indexButtons]->verifyCollisionWithMouse(mouseX, mouseY))
                        {

                            if (indexButtons == 1)
                            {

                                if(inputWidth.size()>0 && inputHeight.size()>0)
                                {
                                w=stoi(inputWidth); h=stoi(inputHeight);
                                }


                            if(inputImageNameG.size()<=0){
                                    inputImageNameG="untitled";
                            }


                                float pi = 3.141592;
                                srand(time(NULL));
                                int nr = rand() % 6;
                                if (nr == 0)nr++;
                                if (nr == 1)nr++;

                                RGB_t red, blue, green, yellow, purple;
                                red.red = 255;
                                blue.blue = 255;
                                green.green = 255;
                                yellow.red = 255;
                                yellow.green = 255;
                                purple.blue = 130;
                                purple.red = 75;

                                int index[6];
                                for (int i = 0; i < 6; i++)
                                    index[i] = (i + nr) % 5;

                                RGB_t color_list[5];
                                color_list[0] = red;
                                color_list[1] = blue;
                                color_list[2] = purple;
                                color_list[3] = yellow;
                                color_list[4] = green;



                                //int aa, bb;
                                //	RGB_t *pixel[] = new RGB_t[w][h];
                                RGB_t pixel[w][h];
//								int* pixel = (RGB_t*)malloc(h * w * sizeof(RGB_t));

                                //							RGB_t** pixel = (RGB_t**)malloc(w * sizeof(RGB_t*));
                                //							for (int i = 0; i < w; i++)
                                //							pixel[i] = (RGB_t*)malloc(h * sizeof(RGB_t));




                                for(int i=0; i<h; i++)
                                {
                                    for(int j=0; j<w; j++)
                                    {
                                        double xt = deg2rad(i);
                                        double yt = deg2rad(j);

                                        if(formulaSelected==1)
                                        {
                                            formula=8*sin(xt) + 8*cos(yt);
                                        }
                                        if(formulaSelected==2)
                                        {
                                            formula=15*sin(xt + cos(yt));
                                        }
                                        if(formulaSelected==3)
                                        {
                                            formula=15*sin(cos(xt) + yt);
                                        }
                                        if(formulaSelected==4)
                                        {
                                            formula=8*cos(xt + tan(yt));
                                        }
                                        if(formulaSelected==5)
                                        {
                                            formula=8*tan(xt) + 8*tan(yt);
                                        }



                                        int c = static_cast<int>(formula) %nr;

                                        switch(c)
                                        {
                                        case 0:
                                            pixel[j][i] = color_list[index[0]];
                                            break;

                                        case 1:
                                            pixel[j][i] = color_list[index[1]];
                                            break;
                                        case -1:
                                            pixel[j][i] = color_list[index[1]];
                                            break;

                                        case 2:
                                            pixel[j][i] = color_list[index[2]];
                                            break;
                                        case -2:
                                            pixel[j][i] = color_list[index[2]];
                                            break;

                                        case 3:
                                            pixel[j][i] = color_list[index[3]];
                                            break;
                                        case -3:
                                            pixel[j][i] = color_list[index[3]];
                                            break;

                                        case 4:
                                            pixel[j][i] = color_list[index[4]];
                                            break;
                                        case -4:
                                            pixel[j][i] = color_list[index[4]];
                                            break;

                                        default:
                                            break;
                                        }
                                    }
                                }

                                write_truecolor_tga(inputImageNameG+".tga", *pixel, w, h);
                                actualTextBox = 0;


                                //}


                            }
                            if (indexButtons == 2)
                            {
                                inputImageNameV.clear();
                                actualMenu = 0;
                                actualTextBox = 0;

                                break;
                            }

                            if (indexButtons == 3)
                            {
                                actualTextBox = 1;
                            }
                            if (indexButtons == 4)
                            {
                                actualTextBox = 2;
                            }
                            if (indexButtons == 5)
                            {
                                actualTextBox = 3;
                            }

                        }
                    }

                }
            }

            if (actualMenu == 1)
            {

                SDL_StartTextInput();

                if (e.type == SDL_TEXTINPUT && inputImageNameV.size() < 22)
                {
                    inputImageNameV += e.text.text;
                    std::cout << inputImageNameV;
                }
                if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_BACKSPACE && inputImageNameV.size())
                    {
                        inputImageNameV.pop_back();
                    }
                }
            }
            else if (actualMenu == 2)
            {
                SDL_StartTextInput();

                if (actualTextBox == 1)
                {
                    if (e.type == SDL_TEXTINPUT && inputImageNameG.size() < 22)
                    {
                        inputImageNameG += e.text.text;
                        std::cout << inputImageNameG;
                    }
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_BACKSPACE && inputImageNameG.size())
                        {
                            inputImageNameG.pop_back();
                        }
                    }
                }

                if (actualTextBox == 2)
                {
                    if (e.type == SDL_TEXTINPUT && inputWidth.size() < 5)
                    {
                        std::cout << e.text.text << std::endl;

                        if (e.text.text[0] >= '0' && e.text.text[0] <= '9')
                        {
                            inputWidth += e.text.text;
                        }
                    }
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_BACKSPACE && inputWidth.size())
                        {
                            inputWidth.pop_back();
                        }
                    }
                }

                if (actualTextBox == 3)
                {
                    if (e.type == SDL_TEXTINPUT && inputHeight.size() < 5)
                    {

                        if (e.text.text[0] >= '0' && e.text.text[0] <= '9')
                        {
                            inputHeight += e.text.text;
                        }


                    }
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_BACKSPACE && inputHeight.size())
                        {
                            inputHeight.pop_back();
                        }
                    }
                }



            }
            if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
            {

                if (SDL_GetWindowID(gWindow) == e.window.windowID)
                {
                    closeWindow(gWindow);
                }
                if (SDL_GetWindowID(window2) == e.window.windowID)
                {
                    secondWindowExist = false;
                    closeWindow(window2);
                }
            }


        }
        if (actualTextBox == 0)
        {
            inputHeight.clear();
            inputWidth.clear();
            inputImageNameG.clear();
        }
        if (actualMenu == 0)
        {
            for (int indexButtons = 0; indexButtons < sizeof(buttonsMenu) / sizeof(buttonsMenu[0]); indexButtons++)
            {
                buttonsMenu[indexButtons]->draw(gScreenSurface);
            }
        }
        if (actualMenu == 1)
        {


            for (int indexButtons = 0; indexButtons < sizeof(buttonsImageViewer) / sizeof(buttonsImageViewer[0]); indexButtons++)
            {
                buttonsImageViewer[indexButtons]->draw(gScreenSurface);
            }

            nameImageTextV.createText(font, white, "Name:", 100, 300);
            nameImageTextV.setFont(57);
            nameImageTextV.draw(gScreenSurface);


        }
        if (actualMenu == 2)
        {
            for (int indexButtons = 0; indexButtons < sizeof(buttonsImageGenerator) / sizeof(buttonsImageGenerator[0]); indexButtons++)
            {
                buttonsImageGenerator[indexButtons]->draw(gScreenSurface);
            }
            for (int index = 0; index < sizeof(textGenerator) / sizeof(textGenerator[0]); index++)
            {
                textGenerator[index]->draw(gScreenSurface);
                textGenerator[index]->fixMemoryLeak();
            }

            dropdownButtons[1]->draw(gScreenSurface);
            if (dropdownActivated == true)
            {
                for (int indexButtons = 2; indexButtons < sizeof(dropdownButtons) / sizeof(buttonsMenu[0]); indexButtons++)
                {
                    dropdownButtons[indexButtons]->draw(gScreenSurface);




                }
            }

        }


        if (inputImageNameV.size())
        {

            nameImageV.createText(font, foreground, inputImageNameV, 100, 360);
            nameImageV.draw(gScreenSurface);
        }
        if (inputImageNameG.size())
        {

            nameImageG.createText(font, foreground, inputImageNameG, buttonsImageGenerator[3]->getX(), buttonsImageGenerator[3]->getY() - marginOfError);
            nameImageG.draw(gScreenSurface);

        }
        if (inputWidth.size())
        {

            nameImageG.createText(font, foreground, inputWidth, buttonsImageGenerator[4]->getX(), buttonsImageGenerator[4]->getY() - marginOfError);
            nameImageG.draw(gScreenSurface);

        }
        if (inputHeight.size())
        {
            nameImageG.createText(font, foreground, inputHeight, buttonsImageGenerator[5]->getX(), buttonsImageGenerator[5]->getY() - marginOfError);
            nameImageG.draw(gScreenSurface);
        }

        SDL_UpdateWindowSurface(gWindow);

    }
    //Free resources and close SDL
    SDL_Quit();
}
