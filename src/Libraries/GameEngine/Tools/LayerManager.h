#pragma once
#include <string>
#include <unordered_map>

class LayerManager {
public:
    static LayerManager* get();
    LayerManager(LayerManager const&) = delete;
    void operator=(LayerManager const&) = delete;

    static int addLayer(const std::string &layer);

    static int getLayerIndex(const std::string &layer);

    static std::string getLayerName(int index);
    void debugLayers() const;
private:
    static LayerManager* instance;
    LayerManager() = default;

    static std::string toLower(std::string str);

    std::unordered_map<std::string, int> layer_map;
    int next_layer_index = 0;
};

