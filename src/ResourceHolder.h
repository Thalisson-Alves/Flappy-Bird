#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <map>
#include <string>
#include <stdexcept>

template<typename Identifier, typename Resource>
class ResourceHolder
{
public:
    void load(Identifier, const std::string&);
    template<typename Param>
    void load(Identifier, const std::string&, Param);

    Resource& get(Identifier);
    const Resource& get(Identifier) const;

private:
    void insertResource(Identifier, std::unique_ptr<Resource>);

    std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;
};

#include "ResourceHolder.inl"
#endif