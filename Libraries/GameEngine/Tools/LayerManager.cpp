#include "LayerManager.h"

#include <algorithm>
#include <iostream>

LayerManager* LayerManager::instance = nullptr;

std::string LayerManager::toLower(std::string str) {
    std::string lower_string = str;
    lower_string.reserve(str.length());
    std::ranges::transform(str, lower_string.begin(), ::tolower);
    return lower_string;
}

LayerManager * LayerManager::get() {
    if (instance == nullptr) {
        instance = new LayerManager();
        instance->addLayer("Default"); // some default useful layers.
        instance->addLayer("Player");
        instance->addLayer("UI");
    }
    return instance;
}

int LayerManager::addLayer(const std::string &layer) {
    std::string key = toLower(layer);
    LayerManager* lm = get();
    if (!lm->layer_map.contains(key) && lm->next_layer_index < 32)
    {
        lm->layer_map.insert({key, lm->next_layer_index});
        lm->next_layer_index++;
    }
    return lm->layer_map[key];
}

int LayerManager::getLayerIndex(const std::string &layer) {
    const LayerManager* lm = get();
    if (const std::string key = toLower(layer); lm->layer_map.contains(key))
        return lm->layer_map.find(key)->second;
    return -1;
}

std::string LayerManager::getLayerName(const int index) {
    const LayerManager* lm = get();
    for (const auto& it : lm->layer_map) {
        if (it.second == index) {
            return it.first;
        }
    }
    return "";
}

void LayerManager::debugLayers() const {
    std::cout << "LAYERS:  " << std::endl;
    for (auto & it : layer_map) {
        std::cout  << "- (" << it.first << ": " << it.second <<") \n";
    }
}


