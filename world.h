#pragma once

#include <vector>
#include "object.h"

namespace Sanches_project {

class World {

public:
    std::vector<Object> data;
    void add(const Object& obj);
};

}//namespace Sanches_project

