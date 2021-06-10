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
    
    Camera();

    Camera(glm::vec3 loc, CameraDirection dir);

    void set_ratio(float ratio);

    void move_location(glm::vec3 delta);
    void horizontal_rotate(float alpha);
    void vertical_rotate(float alpha);
    void zoom(float alpha);

    float near();
    float far();

    void change_view(glm::vec4& vector);
    void set_perspective(glm::vec4& vector);
    void set_to_screen(glm::vec4& vector);

//private:

    glm::vec3 location;
    glm::mat4 camera_view_matrix;
    glm::mat4 perspective_matrix;
    glm::mat4 set_to_screen_matrix;
    CameraDirection direction;
    struct ScreenRate screen;

    void calculate_view_matrix();
    void calculate_perspective_matrix();
    void calculate_set_to_screen_matrix();
    void normalize_vertical_angle();
    void normalize_horizontal_angle();
    void normalize_view_angle();
    void check_depth();
};

}//namespace Sanches_project