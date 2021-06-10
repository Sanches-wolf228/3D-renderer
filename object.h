#pragma once

#include <vector>
#include "figures.h"

namespace Sanches_project {

class Object {
public:

    std::vector<Triangle> data;

    void move(glm::vec3 delta);

    void homotetia(glm::vec3 base, float koef);
};


}//namespace Sanches_project