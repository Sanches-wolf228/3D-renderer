#pragma once

#include <glm.hpp>

namespace Sanches_project {

constexpr glm::mat4 unit_matrix{
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
    };

constexpr float pi = (float)3.1415925;


struct CameraDirection {
    float near;
    float far;
    float horisontal_angle;
    float vertical_angle;
};

struct ScreenRate {
    float view_angle;
    float aspect_ratio;
};

class Camera {
public:
    
    glm::vec3 location;
    glm::mat4 camera_view_matrix;
    glm::mat4 perspective_matrix;
    glm::mat4 set_to_screen_matrix;
    CameraDirection direction;
    struct ScreenRate screen;

    void move_location(glm::vec3 delta);
    void horizontal_rotate(float alpha);
    void vertical_rotate(float alpha);

private:

    void calculate_view_matrix();
    void calculate_perspective_matrix();
    void calculate_set_to_screen_matrix();
    void normalize_vertical_angle();
    void normalize_horizontal_angle();
};

}//namespace Sanches_project