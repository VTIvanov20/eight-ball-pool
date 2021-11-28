#include "main_menu.hpp"

void Button::Draw()
{
    is_clicked = GuiButton(bounds, text);
}

bool Button::IsClicked()
{
    if (is_clicked)
    {
        is_clicked = false;
        return true;
    } else return false;
}

void MainMenu::Create()
{
    const char* texts[] = { "PLAY GAME", "SETTINGS", "QUIT" };
    for (int i = 0; i < 3; i++)
        buttons.push_back(new Button(texts[i], { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + (i - 1) * 75, 200, 50 }));
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
                GameManager::ChangeScene(GameManager::GameScene::IN_GAME);
                break;
            case 1:
                GameManager::ChangeScene(GameManager::GameScene::SETTINGS_MENU);
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