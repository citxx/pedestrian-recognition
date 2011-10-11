#include <fstream>

#include "PatchPositions.hpp"

PatchPositions::PatchPositions() {
}

PatchPositions::PatchPositions(std::string fileName) {
    std::ifstream file(fileName.c_str());

    std::string name;
    int left, right, top, bottom;
    while (file >> name >> top >> left >> bottom >> right) {
        this->position.insert(
            pair <std::string, Rectangle>(name, Rectangle(left, top, right - left, bottom - top))
        );
    }
}


void PatchPositions::addPosition(std::string name, Rectangle rect) {
    this->position.insert(pair <std::string, Rectangle>(name, rect));
}

void PatchPositions::save(std::string fileName) const {
    ofstream file(fileName.c_str());
    for (std::multimap::iterator it = this->position.begin(); it != this->position.end(); ++it) {
        ofstream << it->first << ' ' <<
                    it->second.top << ' ' <<
                    it->second.left << ' ' <<
                    it->second.bottom << ' ' <<
                    it->second.right << std::endl;
    }
}

std::vector <Rectangle> PatchPositions::getPositions(std::string name) const {
    std::vector <Rectangle> answer;
    std::multimap::iterator it = this->position.find(name);
    if (it != this->position.end()) {
        while (it != this->position.end() && it->first == name) {
            answer.push_back(it->second);
            ++it;
        }
    }
    return answer;
}

