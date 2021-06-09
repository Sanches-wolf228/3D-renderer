#pragma once

#include <vector>
#include "object.h"

namespace Sanches_project {

class World {
    std::vector<Object> data;

    void add(const Object& obj);
};

}//namespace Sanches_project

