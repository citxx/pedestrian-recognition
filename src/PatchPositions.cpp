#include <fstream>
#include <utility>

#include "PatchPositions.hpp"

PatchPositions::PatchPositions() {
}

PatchPositions::PatchPositions(std::string fileName) {
    std::fstream file(fileName.c_str(), std::ios_base::in);

    std::string name;
    int left, right, top, bottom;
    while (file >> name >> top >> left >> bottom >> right) {
        this->position.insert(
            std::pair <std::string, Rectangle>(name, Rectangle(left, top, right - left, bottom - top))
        );
    }
}


void PatchPositions::addPosition(std::string name, Rectangle rect) {
    this->position.insert(std::pair <std::string, Rectangle>(name, rect));
}

void PatchPositions::save(std::string fileName) const {
    std::fstream file(fileName.c_str(), std::ios_base::out|std::ios_base::trunc);
    for (std::multimap <std::string, Rectangle>::const_iterator it = this->position.begin();
         it != this->position.end();
         ++it) {
        file << it->first << ' ' <<
                it->second.top() << ' ' <<
                it->second.left() << ' ' <<
                it->second.bottom() << ' ' <<
                it->second.right() << std::endl;
    }
}

std::vector <Rectangle> PatchPositions::getPositions(std::string name) const {
    std::vector <Rectangle> answer;
    std::multimap <std::string, Rectangle>::const_iterator it = this->position.find(name);
    if (it != this->position.end()) {
        while (it != this->position.end() && it->first == name) {
            answer.push_back(it->second);
            ++it;
        }
    }
    return answer;
}

