#include "object.h"

namespace Sanches_project {

void Object::move(glm::vec3 delta) {
    for (Triangle triangle : data) {
        for (Point point : triangle.vertices) {
            for (int i = 0; i != 3; ++i) {
                point.coordinates[i] += delta[i];
            }
        }
    }
}

void Object::homotetia(glm::vec3 base, float koef) {
    move(-base);
    for (Triangle triangle : data) {
        for (Point point : triangle.vertices) {
            point.coordinates *= koef;
        }
    }
    move(base);
}

}//namespace Sanches_project