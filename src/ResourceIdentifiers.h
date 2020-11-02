#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

enum class TexturesId
{
    Bird,
    Pipe,
    Background,
    Base,
    PlayButton,
    ButtonNormal,
    ButtonPressed,
    ButtonSelected
};

enum class FontsId
{
    Main
};

namespace sf
{
    class Texture;
    class Font;
}

template<typename Identifier, typename Resource>
class ResourceHolder;

typedef ResourceHolder<TexturesId, sf::Texture> TextureHolder;
typedef ResourceHolder<FontsId, sf::Font> FontHolder;

#endif