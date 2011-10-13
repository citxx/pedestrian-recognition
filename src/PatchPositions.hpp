#ifndef PATCH_POSITIONS_HPP
#define PATCH_POSITIONS_HPP

#include <string>
#include <map>
#include <vector>

#include "Rectangle.hpp"

class PatchPositions {
    std::multimap <std::string, Rectangle> position;

  public:
    PatchPositions();
    PatchPositions(std::string fileName);

    void addPosition(std::string name, Rectangle rect);
    void save(std::string fileName) const;
    std::vector <Rectangle> getPositions(std::string name) const;
};

#endif  // PATCH_POSITIONS_HPP
