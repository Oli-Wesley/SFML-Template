#pragma once
#include <vector>
#include <string>
#include <memory>       // Required for std::unique_ptr, std::make_unique
#include <typeindex>
#include <stdexcept>    // Required for std::runtime_error
#include <algorithm>    // Required for std::remove_if
#include "Components/IComponent.h"  
#include "Components/IRenderable.h"  
#include "Components/Transform.h"
#include "Components/IScriptableBehaviour.h"

class GameObject {
public:
    GameObject(std::string _name);
    ~GameObject();
    // lifecycle events
    void fixedUpdate(float timestep);
    void physicsUpdate(float timestep);
    void update(float dt);
    void lateUpdate(float dt);
    std::vector<IRenderable*> render();
    void destroy();


    // Template functions so have to go here bc I dont understand how to make them work elsewhere...

    // usage: addComponent<ComponentType>(args)  CONSTRUCTOR OF THE COMPONENT MUST HAVE CORRESPONDING ARGUMENTS. ;
    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of<IComponent, T>::value, "T must derive from Component");

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

            // special case for transform as it isnt in the components list (best to use getTransform)
            if constexpr (std::is_same_v<T, Transform>)
                return getTransform();
        }
        // case to get scripts from the scriptable behaviour. 
        else
        {
            IScriptableBehaviour* iscript = getComponent<IScriptableBehaviour>();
            if (iscript) {
                return iscript->getScript<T>();
            }
        }
        return nullptr;
    }

    template<typename T>
    std::vector<GameObject*> getAllChilderenWithComponent() {
        // Get all children as raw pointers
        std::vector<GameObject*> all_children = getAllChilderen();

        // remove elements from the list that do not have the asked for component.
        all_children.erase(
            std::remove_if(all_children.begin(), all_children.end(),
                [](GameObject* child) {
                    return !child->hasComponent<T>();
                }),
            all_children.end()
        );

        return all_children;
    }

    // returns the component on this gameObject with type.
    template<typename T>
    bool hasComponent() {
        for (const auto& comp : components) {
            if (dynamic_cast<T*>(comp.get()))
                return true;
        }
        return false;
    }

    // attatch a script to the gameObject
    template<typename T, typename... Args>
    T* addScript(Args&&... args) {
        static_assert(std::is_base_of<ScriptableBehaviour, T>::value,
            "T must derive from ScriptableBehaviour");

        // Check if the GameObject already has a Scriptable interface
        IScriptableBehaviour* script_interface = getComponent<IScriptableBehaviour>();
        
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
    std::unique_ptr<GameObject> releaseChild(GameObject* child_to_release);

    bool isActive();
    void setActive(bool);

    bool isDrawn();
    void setDrawn(bool);

    // Returns raw pointers for observation
    std::vector<IComponent*> getAllComponents();

    // get all children (including childeren of childeren)
    std::vector<GameObject*> getAllChilderen();

    Transform* getTransform();

    std::vector<GameObject*> getChilderen();

    GameObject* getChildByName(std::string name);

    GameObject* getParent();
    void setParent(GameObject*);

    std::string getName();
    void setName(std::string _name);

    bool isPendingDestroy() { return pending_destroy; };

    void outputChildrenTree();
protected:
    void outputChildrenTree(std::string prefix);
    std::string name;
    std::vector<std::unique_ptr<IComponent>> components;
    bool is_active = true;
    bool is_drawn = true;
    bool pending_destroy = false;
    std::vector<std::unique_ptr<GameObject>> childeren;
    std::unique_ptr<Transform> transform;

    // CHANGED: Must be a raw pointer (weak reference) to avoid circular ownership memory leaks.
    GameObject* parent = nullptr;
};