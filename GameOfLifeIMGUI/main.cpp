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

static void ShowTool(bool* p_open,bool* keyPressed,bool*showPop,int *pop,bool*showCycle,long *cycle, long long int *lifeCycleTime);

int main() {

    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Test",sf::Style::None);
    window.setPosition(sf::Vector2i(0,0));
    ImGui::SFML::Init(window);
    GameOfLife GOL(window);
    GOL.fillCellMap(1);
    sf::VertexArray lastState;
    window.setKeyRepeatEnabled(true);
    bool keyPressed=false;
    bool devMenuToggled = false;

    Cell** cellptr;
    Cell* it;
    GOL.genPop();
    sf::Clock deltaClock;
    long long int LifeCycleExecTime = 0;
    bool *showCycle;
    bool d = true;
    showCycle = &d;
    bool *showPop;
    bool c = true;
    showPop = &c;
    bool *openPopCount;
    bool b = true;
    openPopCount = &b;
    bool *open;
    bool a = true;
    open = &a;
    //*toolActive = false;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            ImGui::SFML::ProcessEvent(event);
            if(event.type==sf::Event::Closed)
            {
                window.close();
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
            *open = true;
            devMenuToggled = false;
        }
        ShowTool(open,&keyPressed,showPop,&GOL._population,showCycle,&GOL._cycleCount,&LifeCycleExecTime);


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

static void ShowTool(bool* p_open,bool* keyPressed,bool*showPop,int *pop,bool*showCycle,long *cycle,long long int *timeFloat)
{
    if (!*p_open)
        return;
    ImGui::Begin("Tool",p_open,ImGuiWindowFlags_MenuBar);



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
    //const float my_values[] = { 4000.2f, 20000.1f, 1000, 1500.1f, 10000.f, 2000.2f };
    //ImGui::PlotLines("PopulationGraph", my_values, IM_ARRAYSIZE(my_values), 0, NULL, 0.0f, 100000.0f, ImVec2(0,80));

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
