#include "settings_menu.hpp"

void SettingsMenu::Create()
{
    elements.push_back(new Button("BACK", { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + (1) * 75.0f, 200, 50 }, 0.f));
    elements.push_back(new CheckBox("FULL SCREEN", { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + (0) * 75.0f, 50, 50 }, 0.f, IsWindowFullscreen()));
    elements.push_back(new CheckBox("SOUND", { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + (-1) * 75.0f, 50, 50 }, 0.f, GameManager::IsAudioOn()));
}

void SettingsMenu::Update()
{
    int idx = 0;
    for (auto& element : elements)
    {
        switch(idx)
        {
        case 0:
            if (static_cast<Button*>(element)->IsClicked())
                GameManager::ChangeScene(GameManager::GameScene::MAIN_MENU);
            break;
        case 1:
            if (static_cast<CheckBox*>(element)->IsChecked() && !IsWindowFullscreen())
                ToggleFullscreen();
            else if (!static_cast<CheckBox*>(element)->IsChecked() && IsWindowFullscreen())
                ToggleFullscreen();
            break;
        case 2:
            if (static_cast<CheckBox*>(element)->IsChecked() && !GameManager::IsAudioOn())
                GameManager::ToggleAudio();
            else if (!static_cast<CheckBox*>(element)->IsChecked() && GameManager::IsAudioOn())
                GameManager::ToggleAudio();
            break;
        }
        idx++;
    }
}