#include "stdafx.h"
#include "Framework.h"
#include "SpriteGo.h"

void Framework::Init(int width, int height, const std::string& name)
{
    FONT_MGR.Load("fonts/DS-DIGI.ttf");

    sf::ContextSettings setting;
    setting.antialiasingLevel = 8;
	window.create(sf::VideoMode(width, height), name, sf::Style::Default, setting);
    Utils::Init();
    SCENE_MGR.Init();
    InputMgr::Init();

    // Ŀ�� ����
    sf::Image cursorImage;
    cursorImage.loadFromFile("Graphics/crosshair.png");
    cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), { 0, 0 });
    window.setMouseCursor(cursor);
}

void Framework::Do()
{
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        realDeltaTime = deltaTime = dt.asSeconds();
        deltaTime *= timeScale;
        realTime += realDeltaTime;
        time += deltaTime;

        InputMgr::Clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::GainedFocus)
            {
                window.setMouseCursor(cursor);
            }
            InputMgr::UpdateEvent(event);
        }
        InputMgr::Update(deltaTime);
        
        SCENE_MGR.Update(deltaTime);
        if (SCENE_MGR.isExitGame)
            break;

        SCENE_MGR.LateUpdate(deltaTime);

        window.clear();
        SCENE_MGR.Draw(window);
        window.display();
    }
}

void Framework::Release()
{
    SCENE_MGR.Release();
    TEXTURE_MGR.Unload("Graphics/crosshair.png");
    FONT_MGR.Unload("fonts/DS-DIGI.ttf");
}
