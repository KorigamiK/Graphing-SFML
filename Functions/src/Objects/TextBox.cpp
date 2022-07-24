#include "Objects/TextBox.hpp"
#include "app.hpp"

TextBox::TextBox(int size, sf::Color color, bool selected, sf::Vector2f position) : window(Application::get().window)
{
    setFont(Application::get().textFont);
    setPosition(position);

    textbox.setCharacterSize(size);

    textbox.setFillColor(color);
    textbox.setOutlineColor(color);
    isSelected = selected;

    // Check if the textbox is selected upon creation and display it accordingly:
    if (isSelected)
        textbox.setString("_");
    else
        textbox.setString("");
}

void TextBox::setFont(sf::Font &fonts)
{
    textbox.setFont(fonts);
}

void TextBox::setPosition(sf::Vector2f point)
{
    textbox.setPosition(point);
}

// Set char limits:
void TextBox::setLimit(bool ToF)
{
    hasLimit = ToF;
}

void TextBox::setLimit(bool ToF, int lim)
{
    hasLimit = ToF;
    limit = lim - 1;
}

// Change selected state:
void TextBox::setSelected(bool sel)
{
    isSelected = sel;

    // If not selected, remove the '_' at the end:
    if (!sel)
    {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length(); i++)
        {
            newT += t[i];
        }
        textbox.setString(newT);
    }
}

std::string TextBox::getText()
{
    return text.str();
}

void TextBox::draw()
{
    window.draw(textbox);
}

// Function for event loop:
void TextBox::typedOn(sf::Event &input)
{
    std::cout << getText() << std::endl;

    if (!isSelected)
        return;

    int charTyped = input.text.unicode;

    // Only allow normal inputs:
    if (charTyped > 127)
        return;

    // If no limit exists, just run the function:
    if (!hasLimit)
        return inputLogic(charTyped);

    // There's a limit, don't go over it:
    if (text.str().length() <= limit)
        inputLogic(charTyped);
    // But allow for char deletions:
    else if (text.str().length() > limit && charTyped == DELETE_KEY)
        deleteLastChar();
}
