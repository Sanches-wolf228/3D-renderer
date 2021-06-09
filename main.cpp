#pragma once

#include "application.h"
#include "test1.h"

namespace pj = Sanches_project;

int main()
{
		//pj::Test1::test_4();
		pj::Camera camera;
		camera.direction.horisontal_angle = 3.14;
		camera.direction.vertical_angle = 0.7853;
		camera.direction.near = 3;
		camera.direction.far = 10;
		camera.location = { 1, 2, 3 };
		camera.calculate_view_matrix();
		camera.calculate_perspective_matrix();
	//pj::Test1::run_tests();
	return 0;
}