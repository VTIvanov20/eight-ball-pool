#include "main_menu.hpp"

void MainMenu::Create()
{
    // Text that is written on buttons
    const char* texts[] = { "PLAY GAME", "SETTINGS", "QUIT" };

    // Displays the texts on the buttons
    for (int i = 0; i < 3; i++)
        buttons.push_back(new Button(texts[i], { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + (i - 1) * 75.0f, 200, 50 }, 0.f));
}

void MainMenu::Update()
{
    int idx = 0;

    // Checks whether or not a button has been pressed
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