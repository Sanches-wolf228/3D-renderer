#include "camera.h"

namespace Sanches_project {

Camera::Camera() {
    screen.view_angle = pi / 4;
    screen.aspect_ratio = 1;
    direction = {5, 100, 0, 0};
    location = {0, 0, 0};
}

Camera::Camera(glm::vec3 loc, CameraDirection dir) : location(loc), direction(dir) {
    screen.view_angle = pi / 4;
    check_depth();
    normalize_horizontal_angle();
    normalize_vertical_angle();
    calculate_view_matrix();
    calculate_perspective_matrix();
    calculate_set_to_screen_matrix();
}

void Camera::set_ratio(float ratio) {
    screen.aspect_ratio = ratio;
    calculate_set_to_screen_matrix();
}

void Camera::move_location(glm::vec3 delta) {
    location += delta;
    calculate_view_matrix();
}

void Camera::horizontal_rotate(float alpha) {
    direction.horisontal_angle += alpha;
    normalize_horizontal_angle();
    calculate_view_matrix();
    calculate_perspective_matrix();
}

void Camera::vertical_rotate(float alpha) {
    direction.vertical_angle += alpha;
    normalize_vertical_angle();
    calculate_view_matrix();
    calculate_perspective_matrix();
}

void Camera::zoom(float alpha) {
    screen.view_angle += alpha;
    normalize_view_angle();
    calculate_set_to_screen_matrix();
}

float Camera::near() {
    return direction.near;
}

float Camera::far() {
    return direction.far;
}

void Camera::change_view(glm::vec4& vector) {
    vector = camera_view_matrix * vector;
}

void Camera::set_perspective(glm::vec4& vector) {
    vector = perspective_matrix * vector;
}

void Camera::set_to_screen(glm::vec4& vector) {
    vector = set_to_screen_matrix * vector;
}

void Camera::calculate_view_matrix() {
    glm::mat4 move, rotate1, rotate2;
    move = unit_matrix;
    for (int i = 0; i != 3; ++i) {
        move[3][i] = -location[i];
    }
    rotate1 = unit_matrix;
    rotate1[0][0] = cos(direction.horisontal_angle);
    rotate1[1][1] = cos(direction.horisontal_angle);
    rotate1[0][1] = -sin(direction.horisontal_angle);
    rotate1[1][0] = sin(direction.horisontal_angle);

    rotate2 = unit_matrix;
    rotate2[0][0] = sin(direction.vertical_angle);
    rotate2[2][2] = sin(direction.vertical_angle);
    rotate2[0][2] = cos(direction.vertical_angle);
    rotate2[2][0] = -cos(direction.vertical_angle);

    camera_view_matrix = rotate2 * rotate1 * move;
}

void Camera::calculate_perspective_matrix() {
    perspective_matrix = unit_matrix;
    perspective_matrix[0][0] = direction.near;
    perspective_matrix[1][1] = direction.near;
    perspective_matrix[2][2] = direction.near + direction.far;
    perspective_matrix[3][2] = -direction.near * direction.far;
    perspective_matrix[2][3] = 1;
    perspective_matrix[3][3] = 0;
}

void Camera::calculate_set_to_screen_matrix() {
    set_to_screen_matrix = unit_matrix;
    set_to_screen_matrix[3][0] = 0.5;
    set_to_screen_matrix[3][1] = 0.5;
    set_to_screen_matrix[3][2] = - direction.near;
    set_to_screen_matrix[0][0] = 1.f / direction.near / tan(screen.view_angle);
    set_to_screen_matrix[1][1] = set_to_screen_matrix[0][0] / screen.aspect_ratio;
}

void Camera::normalize_view_angle() {
    if (screen.view_angle > pi / 3) {
        screen.view_angle = pi / 3;
    }
    else if (screen.view_angle < pi / 24) {
        screen.view_angle = pi / 24;
    }
    return;
}

void Camera::normalize_horizontal_angle() {
    direction.vertical_angle -= trunc(direction.vertical_angle / pi / 2) * pi * 2;
    if (direction.vertical_angle < 0) {
        direction.vertical_angle += 2 * pi;
    }
}

void Camera::normalize_vertical_angle() {
    if (direction.vertical_angle > pi / 2) {
        direction.vertical_angle = pi / 2;
    }
    else if (direction.vertical_angle < -pi / 2) {
        direction.vertical_angle = -pi / 2;
    }
    return;
}

void Camera::check_depth() {
    if (direction.near < 1) {
        direction.near = 1;
    }
    if (direction.far < direction.near + 1) {
        direction.far = direction.near + 1;
    }
}

}//namespace Sanches_project