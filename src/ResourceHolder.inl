template<typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    
    insertResource(id, std::move(resource));
}

template<typename Identifier, typename Resource>
template<typename Param>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& filename, Param secondParam)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    
    insertResource(id, std::move(resource));
}

template<typename Identifier, typename Resource>
Resource& ResourceHolder<Identifier, Resource>::get(Identifier id)
{
    auto found = m_resourceMap.find(id);
    if (found == m_resourceMap.end())
        throw std::logic_error("ResourceHolder::get - Resource not loaded");
    
    return *found->second;
}

template<typename Identifier, typename Resource>
const Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) const
{
    auto found = m_resourceMap.find(id);
    if (found == m_resourceMap.end())
        throw std::logic_error("ResourceHolder::get - Resource not loaded");
    
    return *found->second;
}

template<typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    if (!m_resourceMap.insert(std::make_pair(id, std::move(resource))).second)
        throw std::logic_error("ResourceHolder::insertResource - Changing an existing id value ");
}