#include "tools/Screen_SPI/screen.h"

Screen::Screen(std::string name, int16_t width, int16_t height)
    : name(name), width(width), height(height), currentSelected(0) {};

void Screen::draw(lv_obj_t* obj)
{
    if (currentSelected < 0 || currentSelected > selectables.size() - 1)
    {
        Serial.println("WARNING: Tried to select a non existant selectable");
    }
    else
    {
        if (selectables.size() > 0)
        {
            selectables[currentSelected]->active = true;
        }
    }

    for (Component *comp : components)
    {
        comp->draw(obj);
    }

    for (Selectable *sel : selectables)
    {
        sel->draw(obj);
    }
};

void Screen::addComponent(Component *comp)
{
    components.push_back(comp);
}

void Screen::addSelectable(Selectable *sel)
{
    selectables.push_back(sel);
}

void Screen::activeSelected()
{
    if (currentSelected < 0 || currentSelected > selectables.size() - 1)
    {
        Serial.println("WARNING: Tried to select a non existant selectable");
        return;
    }
    selectables[currentSelected]->activate();
}

void Screen::nextSelected()
{
    if (selectables.size() == 0)
    {
        return;
    };

    selectables[currentSelected]->active = false;
    currentSelected++;
    currentSelected %= selectables.size();
}

void Screen::previousSelected()
{
    if (selectables.size() == 0)
    {
        return;
    };

    selectables[currentSelected]->active = false;
    currentSelected--;
    currentSelected %= selectables.size();
}