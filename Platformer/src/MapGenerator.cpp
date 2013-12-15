#include "MapGenerator.h"

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <assert.h>


MapGenerator::Component::Component(void) : id(NULL), componentMap(std::vector<std::vector<int16_t> >(0, std::vector<int16_t>(0))) {}

MapGenerator::Component::Component(std::string filename) {
    std::ifstream fin(filename);
    fin >> this->id;
    uint32_t width, height;
    fin >> width >> height;
    for(int i = 0; i < width; i++) {
        this->componentMap.push_back(std::vector<int16_t>(height));
        for(int j = 0; j < height; j++)
            fin >> this->componentMap[i][j];
    }
}

MapGenerator::Component::Component(std::string id, std::vector<std::vector<int16_t> > componentMap) {
    this->id = id;
    this->componentMap = componentMap;
}

MapGenerator::Component::Component(const MapGenerator::Component &other) {
    this->id = other.id;
    this->componentMap = other.componentMap;
}

MapGenerator::Component::~Component(void) {

}

sf::Vector2i MapGenerator::Component::get_size(void) {
    return sf::Vector2i(this->componentMap.size(), this->componentMap[0].size());
}

std::string MapGenerator::Component::get_id(void) {
    return this->id;
}

std::vector<std::vector<int16_t> > MapGenerator::Component::get_component_map(void) {
    return this->componentMap;
}

void MapGenerator::Component::set_id(std::string id) {
    this->id = id;
}

void MapGenerator::Component::set_component_map(std::vector<std::vector<int16_t> > componentMap) {
    this->componentMap = componentMap;
}

void MapGenerator::Component::populate(std::string filename) {
    std::ifstream fin(filename);
    fin >> this->id;
    uint32_t width, height;
    fin >> width >> height;
    for(int i = 0; i < width; i++) {
        this->componentMap.push_back(std::vector<int16_t>(height));
        for(int j = 0; j < height; j++)
            fin >> this->componentMap[i][j];
    }
}

void MapGenerator::Component::populate(std::string id, std::vector<std::vector<int16_t> > componentMap) {
    this->id = id;
    this->componentMap = componentMap;
}

void MapGenerator::Component::populate(const MapGenerator::Component other) {
    this->id = other.id;
    this->componentMap = other.componentMap;
}

MapGenerator::Component& MapGenerator::Component::operator=(const MapGenerator::Component other) {
    this->id = other.id;
    this->componentMap = other.componentMap;
    return *this;
}

void MapGenerator::Component::paint_to(std::vector<std::vector<int16_t> > &generation, bool walls) {
    uint32_t xpos = std::rand() % generation.size();
    xpos = xpos == 0 ? walls : xpos;
    uint32_t ypos = std::rand() % generation[0].size();
    ypos = ypos == 0 ? walls : ypos;
    for(uint32_t x = xpos; x < xpos + this->componentMap.size(); x++) {
        if(x >= generation.size() - walls)
            break;
        for(uint32_t y = ypos; y < ypos + this->componentMap[0].size(); y++) {
            if(y >= generation[0].size() - walls)
                break;
            if(this->componentMap[x - xpos][y - ypos] != -1)
                generation[x][y] = this->componentMap[x - xpos][y - ypos];
        }
    }
}

void MapGenerator::Component::paint_to(uint32_t xpos, uint32_t ypos, std::vector<std::vector<int16_t> > &generation) {
    for(uint32_t x = xpos; x < xpos + this->componentMap.size(); x++) {
        for(uint32_t y = ypos; y < ypos + this->componentMap[0].size(); y++) {
            if(this->componentMap[x - xpos][y - ypos] != -1)
                generation[x][y] = this->componentMap[x - xpos][y - ypos];
        }
    }
}

void MapGenerator::Component::paint_to_fit(std::vector<std::vector<int16_t> > &generation, bool walls) {
    uint32_t xpos = std::rand() % (generation.size() - this->componentMap.size());
    xpos = xpos == 0 ? walls : xpos;
    uint32_t ypos = std::rand() % (generation[0].size() - this->componentMap[0].size());
    ypos = ypos == 0 ? walls : ypos;
    this->paint_to(xpos, ypos, generation);

}

MapGenerator::MapGenerator(void) : walls(true), resources(std::vector<MapGenerator::Component>(0)), generation(std::vector<std::vector<int16_t> >(0, std::vector<int16_t>(0))) {}

MapGenerator::MapGenerator(std::string file) : walls(true), generation(std::vector<std::vector<int16_t> >(0, std::vector<int16_t>(0))) {
    this->resources.push_back(MapGenerator::Component(file));
}

MapGenerator::MapGenerator(std::vector<std::string> files) : walls(true), generation(std::vector<std::vector<int16_t> >(0, std::vector<int16_t>(0))){
    for(int i = 0; i < files.size(); i++)
        this->resources.push_back(MapGenerator::Component(files[i]));
}

MapGenerator::MapGenerator(const MapGenerator &other) : walls(other.walls), resources(other.resources), generation(std::vector<std::vector<int16_t> >(0, std::vector<int16_t>(0))) {}

MapGenerator::~MapGenerator(void) {

}

void MapGenerator::fetch_resources(std::string file) {
    this->resources.clear();
    this->resources.push_back(MapGenerator::Component(file));
}

void MapGenerator::fetch_resources(std::vector<std::string> files) {
    this->resources.clear();
    for(int i = 0; i < files.size(); i++)
        this->resources.push_back(MapGenerator::Component(files[i]));
}

void MapGenerator::append_resources(std::string file) {
    this->resources.push_back(MapGenerator::Component(file));
}

void MapGenerator::append_resources(std::vector<std::string> files) {
    for(int i = 0; i < files.size(); i++)
        this->resources.push_back(MapGenerator::Component(files[i]));
}

void MapGenerator::remove_resources(uint32_t index) {
    this->resources.erase(this->resources.begin() + index);
}

void MapGenerator::remove_resources(std::string id) {
    for(int i = 0; i < this->resources.size(); i++)
        if(this->resources[i].get_id() == id)
            this->resources.erase(this->resources.begin() + i);
}

void MapGenerator::clear_resources(void) {
    this->resources.clear();
}

uint32_t MapGenerator::get_solids(void) {
    uint32_t count = 0;
    for(uint32_t i = 0 + this->walls; i < this->generation.size() - this->walls; i++)
        for(uint32_t j = 0 + this->walls; j < this->generation[0].size() - this->walls; j++)
            count += generation[i][j] == 1 ? 1 : 0;
    return count;
}

void MapGenerator::connect_nodes(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    int8_t dx = x2 > x1 ? 1 : -1;
    int8_t dy = y2 > y1 ? 1 : -1;
    while(x1 != x2 || y1 != y2) {
        if(x1 != x2 && y1 != y2) {
            uint8_t order = std::rand() % 2;
            if(order == 0) {
                this->generation[x1+dx][y1] = 2;
                this->generation[x1+dx][y1+dy] = 2;
            }else {
                this->generation[x1][y1+dy] = 2;
                this->generation[x1+dx][y1+dx] = 2;
            }
            x1 += dx;
            y1 += dy;
        }else if(x1 != x2) {
            this->generation[x1+dx][y1] = 2;
            x1 += dx;
        }else if(y1 != y2) {
            this->generation[x1][y1+dy] = 2;
            y1 += dy;
        }
    }
}

void MapGenerator::check_node(uint32_t x, uint32_t y, bool silent) {
    if(this->generation[x][y] != 1) {
        for(int i = 0; i < this->blacklist.size(); i++)
            if(x == this->blacklist[i].first && y == this->blacklist[i].second)
                return;
        this->blacklist.push_back(std::pair<uint32_t,uint32_t>(x,y));
        if(!silent)
            this->subsets.push_back(std::vector<coordinate_t>(0));
        this->subsets[this->subsets.size() - 1].push_back(std::pair<uint32_t,uint32_t>(x,y));
        if(x != 0)
            this->check_node(x - 1, y, true);
        if(y != 0)
            this->check_node(x, y - 1, true);
        if(x != this->generation.size() - 1)
            this->check_node(x + 1, y, true);
        if(y != this->generation[0].size() - 1)
            this->check_node(x, y + 1, true);
    }
}

void MapGenerator::fix_generation(void) {
    for(int x = 0; x < this->generation.size(); x++)
        for(int y = 0; y < this->generation[0].size(); y++)
            this->check_node(x, y, false);
    for(int i = 0; i < this->subsets.size() - 1; i++) {
        uint32_t pos1 = std::rand() % this->subsets[i].size();
        uint32_t pos2 = std::rand() % this->subsets[i+1].size();
        this->connect_nodes(this->subsets[i][pos1].first, this->subsets[i][pos1].second, this->subsets[i+1][pos2].first, this->subsets[i+1][pos2].second);
    }
}

std::vector<std::vector<int16_t> > MapGenerator::generate(uint32_t width, uint32_t height, float weight) {
    assert(weight < 1 && weight >= 0);
    for(int i = 0; i < height; i++)
        this->generation.push_back(std::vector<int16_t>(width, 1));
    while((float) this->get_solids() / (width * height) > weight) {
        uint32_t index = std::rand() % resources.size();
        this->resources[index].paint_to(this->generation, this->walls);
    }
    this->fix_generation();
    return this->generation;
}

std::vector<std::vector<int16_t> > MapGenerator::generate(uint32_t width, uint32_t height, std::vector<float> weights) {
    for(int i = 0; i < height; i++)
        this->generation.push_back(std::vector<int16_t>(width, 1));
}

std::vector<std::vector<int16_t> > MapGenerator::generate_orderly(uint32_t rooms, uint32_t lining, int16_t solid_fill, int16_t nonsolid_fill) {
    std::vector<std::vector<std::vector<int16_t> > > components;
    std::vector<std::vector<int16_t> > temp;
    uint32_t index;
    int8_t dir;
    for(int i = 0; i < rooms; i++) {
        index = std::rand() % resources.size();
        for(int i = 0; i < this->resources[index].get_size().y + 2 * lining; i++)
            temp.push_back(std::vector<int16_t>(this->resources[index].get_size().x + 2 * lining, -7));
        std::cout << temp.size() << " " << temp[0].size() << std::endl;
        this->resources[index].paint_to_fit(temp, true);
        components.push_back(temp);
        temp.clear();
    }
    std::cout << components[0].size() << " " << components[0][0].size() << std::endl;
    this->generation = components[0];
    if(rooms == 1)
        goto RETURN;
    int max_w, max_h;
    for(int i = 1; i < components.size(); i++) {
        max_w = std::max(this->generation.size(), components[i].size());
        max_h = std::max(this->generation[0].size(), components[i][0].size());
        while(this->generation.size() != max_w || components[i].size() != max_w || this->generation[0].size() != max_h || components[i][0].size() != max_h) {
            if(this->generation.size() != max_w)
                this->generation.push_back(std::vector<int16_t>(this->generation[0].size(), -7));
            if(this->generation[0].size() != max_h)
                for(int j = 0; j < this->generation.size(); j++)
                    this->generation[j].push_back(-7);
            if(components[i].size() != max_w)
                components[i].push_back(std::vector<int16_t>(components[i][0].size(), -7));
            if(components[i][0].size() != max_h)
                for(int j = 0; j < components[i].size(); j++)
                    components[i][j].push_back(-7);
        }
        dir = std::rand() % 2;
        if(dir == 1) {
            for(int j = 0; j < components[i].size(); j++)
                this->generation.push_back(components[i][j]);
        }else {
            for(int j = 0; j < components[i].size(); j++)
                for(int k = 0; k < components[i][0].size(); k++)
                    this->generation[j].push_back(components[i][j][k]);
        }
    }
    RETURN:
    components.clear();
    std::vector<coordinate_t> doors;
    std::vector<std::vector<Node> > toggle;
    for(uint32_t x = 0; x < this->generation.size(); x++)
        for(uint32_t y = 0; y < this->generation[0].size(); y++)
            if(this->generation[x][y] == 3) {
                doors.push_back(std::pair<uint32_t,uint32_t>(x,y));
                std::cout << x << " " << y << std::endl;
            }
    PathFinder router;
    //for(int i = 0; i < 1; i++) {
    //    toggle.push_back(router.pathfind(doors[i].second, doors[i].first, doors[i+1].second, doors[i+1].first, this->generation, -7));
    //}
    for(int i = 0; i < toggle.size(); i++)
        for(int j = 0; j < toggle[i].size(); j++)
            this->generation[toggle[i][j].x][toggle[i][j].y] = nonsolid_fill;
    for(int i = 0; i < this->generation.size(); i++)
        for(int j = 0; j < this->generation[0].size(); j++)
            this->generation[i][j] = this->generation[i][j] == -7  ? solid_fill : this->generation[i][j];
    return this->generation;
}
