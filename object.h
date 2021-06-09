#pragma once

#include <vector>
#include "figures.h"
#include "camera.h"

namespace Sanches_project {

class Object {
    std::vector<Triangle> data;

    //void transform(const Camera &cam);

    void move(glm::vec3 delta);
};


}//namespace Sanches_project