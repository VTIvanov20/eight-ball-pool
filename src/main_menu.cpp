#include "main_menu.hpp"

void MainMenu::Create()
{
    const char* texts[] = { "PLAY GAME", "SETTINGS", "QUIT" };

    for (int i = 0; i < 3; i++)
        buttons.push_back(new Button(texts[i], { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + (i - 1) * 75.0f, 200, 50 }, 0.f));
}

void MainMenu::Update()
{
    int idx = 0;
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        if ((*it)->IsClicked())
        {
            switch(idx)
            {
            case 0:
                GameManager::ChangeScene(GameManager::Scene::IN_GAME);
                break;
            case 1:
                GameManager::ChangeScene(GameManager::Scene::SETTINGS_MENU);
                break;
            case 2:
                GameManager::Quit();
                break;
            default:
                break;
            }
        }

        idx++;
    }
}