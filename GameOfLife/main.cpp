#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <sstream>
#include "GameOfLife.h"


static void showPopulationCount(bool* p_open,int *pop);

static void showLifeCycleCount(bool *p_open,long *cycle);
static void showPopulationGraph(bool *p_open,RingBuffer *rb,float *scaleMax);

static void ShowTool(bool* p_open,bool* keyPressed,
        bool*showPop,int *pop,bool*showCycle,
        long *cycle, long long int *lifeCycleTime,
        sf::RenderWindow *window,bool *showPopGraph,RingBuffer *rb,float *scaleMax);

int main() {

    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Test",sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(0,0));
    ImGui::SFML::Init(window);
    GameOfLife GOL(window);
    GOL.fillCellMap(1);
    sf::VertexArray lastState;
    window.setKeyRepeatEnabled(true);
    bool keyPressed=false;
    bool devMenuToggled = false;
    RingBuffer ringBuffer(10);
    Cell** cellptr;
    Cell* it;
    GOL.genPop();
    sf::Clock deltaClock;
    long long int LifeCycleExecTime = 0;
    float scaleMax = 10000.f;
    bool showPopGraph = false;
    bool showCycle = true;
    bool showPop = true ;
    bool openPopCount = true;
    bool open = true;

    //*toolActive = false;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            ImGui::SFML::ProcessEvent(event);
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();

            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                //std::cout << GOL.returnCellIndex()  << std::endl;


            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LShift)
            {

                devMenuToggled = true;


            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl){
                if (!keyPressed){
                    keyPressed = true;

                }




            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl){
                if (keyPressed){
                    keyPressed = false;

                }

            }

        }
        ImGui::SFML::Update(window,deltaClock.restart());
        ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_FirstUseEver);
        if (devMenuToggled)
        {
            open = true;
            devMenuToggled = false;
        }
        ShowTool(&open,&keyPressed,&showPop,&GOL._population,&showCycle,&GOL._cycleCount,&LifeCycleExecTime,&window,&showPopGraph,&ringBuffer,&scaleMax);


        window.clear();
        if(keyPressed){
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            GOL.LifeCycle();
            std::chrono::steady_clock::time_point end   = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            //printf("Time = %lld ms\n", static_cast<long long int>(elapsed.count()));
            LifeCycleExecTime = static_cast<long long int>(elapsed.count());

            sf::VertexArray drawArray= GOL.drawCell();
            lastState = drawArray;

            window.draw(drawArray);




            ImGui::SFML::Render(window);
            window.display();


        } else{

            window.draw(GOL.drawAliveCells());
            //window.draw(image);
            ImGui::SFML::Render(window);

            window.display();
        }




    }
    ImGui::SFML::Shutdown();
    return 0;
}

static void showPopulationCount(bool* p_open,int *pop)
{
    if (!*p_open)
        return;
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(135, 70), ImGuiCond_Always);


    ImGui::Begin("Population",p_open);
    ImGui::Text("Population %d", *pop);
    ImGui::End();
}
static void showLifeCycleCount(bool *p_open,long *cycle)
{
    if (!*p_open)
        return;
    ImGui::SetNextWindowPos(ImVec2(880, 10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(135, 70), ImGuiCond_Always);


    ImGui::Begin("Generation",p_open);
    ImGui::Text("Generation %ld", *cycle);
    ImGui::End();
}

static void ShowTool(bool* p_open,bool* keyPressed,bool*showPop,int *pop,bool*showCycle,long *cycle,long long int *timeFloat,sf::RenderWindow *window,bool *showPopGraph,RingBuffer *rb,float *scaleMax)
{
    if (!*p_open)
        return;
    ImGui::Begin("Tool",p_open,ImGuiWindowFlags_MenuBar);


    rb->add((float)*pop);
    if(ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("Settings"))
        {
            if(ImGui::MenuItem("Load..","Ctrl+L")){}
            if(ImGui::MenuItem("Save..","Ctrl+S")) {}
            if(ImGui::MenuItem("Close","Ctrl+W")) {*p_open = false;}

            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
    ImGui::Text("Single Cycle Execution Time: %lld ms",*timeFloat);
    ImGui::Checkbox("Show Population",showPop);
    if (*showPop)
    {
        showPopulationCount(showPop,pop);
    }
    ImGui::Checkbox("Show Generation",showCycle);
    if(*showCycle)
    {
        showLifeCycleCount(showCycle,cycle);
    }
    ImGui::Checkbox("Show Population Graph",showPopGraph);
    if(*showPopGraph)
    {
        showPopulationGraph(showPopGraph,rb,scaleMax);
    }

    if ( ImGui::Button("Resize to 512x512(Unstable!!)"))
    {
        window->setSize(sf::Vector2u(512,512));
    }
    if (ImGui::Button("Start Sim"))
    {
        *keyPressed = true;
    }
    if (ImGui::Button("Stop Sim"))
    {
        *keyPressed = false;

    }
    ImGui::End();
}
static void showPopulationGraph(bool* p_open,RingBuffer *rb,float *scaleMax)
{
    if (!*p_open)
        return;


    ImGui::Begin("Population Graph",p_open);
    ImGui::SliderFloat("Set Maximum",scaleMax, 0.0f, 10000.0f, "Maximum Value");

    ImGui::PlotLines("PopulationGraph", rb->getBufferArray(), 10, 0, NULL, 0.0f, *scaleMax, ImVec2(500,100));
    ImGui::End();
}
