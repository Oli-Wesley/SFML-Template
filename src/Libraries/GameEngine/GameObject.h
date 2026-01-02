#pragma once
#include <vector>
#include <string>
#include <memory>       // Required for std::unique_ptr, std::make_unique
#include <stdexcept>    // Required for std::runtime_error
#include <algorithm>    // Required for std::remove_if
#include "ComponentInterfaces.h"
#include "Components/Transform.h"
#include "Tools/Helpers.h"

class GameObject {
public:
    explicit GameObject(const std::string &_name);
    ~GameObject();
    // lifecycle events
    void fixedUpdate(float timestep);
    void physicsUpdate(float timestep);
    void update(float dt) const;
    void lateUpdate(float dt) const;
    std::vector<IRenderable*> render();
    void destroy();


    // Template functions for all template function definitions

    // usage: addComponent<ComponentType>(args)  CONSTRUCTOR OF THE COMPONENT MUST HAVE CORRESPONDING ARGUMENTS.
    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of_v<IComponent, T>, "T must derive from Component");

        // Check if component already exists
        for (const auto& comp : components) {
            if (dynamic_cast<T*>(comp.get())) {
                throw std::runtime_error("Cannot Have 2 components of same type on the same game object");
            }
        }

        // Create and add new component using make_unique
        std::unique_ptr<T> new_component = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawPtr = new_component.get(); // Get raw pointer to return before moving ownership

        rawPtr->setGameObject(this);
        rawPtr->start();

        components.push_back(std::move(new_component)); // Move ownership to the vector

        return rawPtr;
    }

    // returns the component on this gameObject with type.
    template<typename T>
    T* getComponent() {
        if constexpr (std::is_base_of_v<IComponent, T>) {
            for (const auto& comp : components) {
                if (auto casted = dynamic_cast<T*>(comp.get()))
                    return casted;
            }

            // special case for transform as it isn't in the components list (best to use getTransform)
            if constexpr (std::is_same_v<T, Transform>)
                return getTransform();
        }
        // case to get scripts from the scriptable behaviour. 
        else
        {
            if (auto* iscript = getComponent<IScriptableBehaviour>()) {
                return iscript->getScript<T>();
            }
        }
        return nullptr;
    }

    template<typename T>
    std::vector<GameObject*> getAllChildrenWithComponent() {
        // Get all children as raw pointers
        std::vector<GameObject*> all_children = getAllChildren();

        // remove elements from the list that do not have the asked for component.
        all_children.erase(
            std::remove_if(all_children.begin(), all_children.end(),
                [](const GameObject* child) {
                    return !child->hasComponent<T>();
                }),
            all_children.end()
        );

        return all_children;
    }

    // returns the component on this gameObject with type.
    template<typename T>
    bool hasComponent() const {
        for (const auto& comp : components) {
            if (dynamic_cast<T*>(comp.get()))
                return true;
        }
        return false;
    }

    // attach a script to the gameObject
    template<typename T, typename... Args>
    T* addScript(Args&&... args) {
        static_assert(std::is_base_of_v<ScriptableBehaviour, T>,
            "T must derive from ScriptableBehaviour");

        // Check if the GameObject already has a Scriptable interface
        auto* script_interface = getComponent<IScriptableBehaviour>();
        
        // If not found, add one
        if (!script_interface) {
            script_interface = addComponent<IScriptableBehaviour>();
        }

        // Create the new script. 
        std::unique_ptr<T> new_script = std::make_unique<T>(std::forward<Args>(args)...);

        T* ptr = new_script.get();
        // Add it to the script interface
        script_interface->addScript(std::move(new_script)); // move script to scriptable interface. 

        // return script to be used elsewhere.
        return ptr;
    }

    // Takes ownership of the child
    GameObject* addChild(std::unique_ptr<GameObject> _game_obj);
    std::unique_ptr<GameObject> releaseChild(const GameObject* child_to_release);

    bool isActive() const;
    void setActive(bool);

    bool isDrawn() const;
    void setDrawn(bool);

    // Returns raw pointers for observation
    std::vector<IComponent*> getAllComponents() const;

    // get all children (including children of children)
    std::vector<GameObject*> getAllChildren() const;

    Transform* getTransform() const;

    // gets the Local bounds of all renderable objects on the gameObject
    sf::FloatRect getLocalBounds();
    // gets the Global bounds of all renderable objects on the gameObject
    sf::FloatRect getGlobalBounds();

    // gets the Local bounds of all renderable objects on the gameObject and its children
    // sf::FloatRect getLocalBoundsWithChildren();
    // gets the Global bounds of all renderable objects on the gameObject and its children
    sf::FloatRect getGlobalBoundsWithChildren();

    // checks if any of the renderable objects on this object was rendered last frame
    bool wasRenderedLastFrame();
    // checks if any of the renderable objects on this object or children were rendered last frame
    bool wasRenderedLastFrameWithChildren();

    std::vector<GameObject*> getChildren() const;

    GameObject* getChildByName(const std::string &child_name) const;

    GameObject* getParent() const;
    void setParent(GameObject*);

    std::string getName();
    void setName(const std::string &_name);

    bool isPendingDestroy() const { return pending_destroy; };

    void outputChildrenTree();

    void setLayer(const std::string &layer_name);
    void setLayer(const std::string &layer_name, bool include_children);
    void setLayer(int layer_id);
    void setLayer(int layer_id, bool include_children);
    int getLayer() const;
    std::string getLayerId() const;

protected:
    void outputChildrenTree(const std::string &prefix);
    std::string name;
    std::vector<std::unique_ptr<IComponent>> components;
    bool is_active = true;
    bool is_drawn = true;
    bool pending_destroy = false;
    int layer = 0;
    std::vector<std::unique_ptr<GameObject>> children;
    std::unique_ptr<Transform> transform;

    // CHANGED: Must be a raw pointer (weak reference) to avoid circular ownership memory leaks.
    GameObject* parent = nullptr;
};