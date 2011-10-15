#ifndef PATCH_POSITIONS_HPP
#define PATCH_POSITIONS_HPP

#include <string>
#include <map>
#include <set>
#include <vector>

#include "Rectangle.hpp"

class PatchPositions {
    std::set <std::string> names;
    std::multimap <std::string, Rectangle> position;

  public:
    PatchPositions();
    PatchPositions(std::string fileName);

    void addPosition(std::string name, Rectangle rect);
    void save(std::string fileName) const;
    std::vector <Rectangle> getPositions(std::string name) const;
    std::vector <std::string> getNames() const;
};

#endif  // PATCH_POSITIONS_HPP
