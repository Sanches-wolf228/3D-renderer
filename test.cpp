#include "test.h"
#include "application.h"
#include "iostream"

namespace Sanches_project {

namespace Test {

void test_1() {
		std::cout << "Run test\n";

		Camera camera({0, 0, 0}, { 3, 100, 0, 0 });

		Point t1, t2, t3, t4;

		t1.coordinates = { 8, 6, 0, 1 };
		t2.coordinates = { 10, -6, -3, 1 };
		t3.coordinates = { 9, 0, 4, 1 };
		t4.coordinates = { 4, 1, 0, 1 };

		Triangle a1{ {t1, t2, t3}, {255, 0, 0} };
		Triangle a2{ {t2, t3, t4}, {0, 255, 0} };
		Triangle a3{ {t1, t3, t4}, {0, 0, 255} };
		Triangle a4{ {t1, t2, t4}, {0, 0, 0} };

		Object obj1{ {a1, a2, a3, a4} };
		Object obj2 = obj1;
		Object obj3 = obj1;
		Object obj4 = obj1;
		Object obj5 = obj1;

		obj2.homotetia({ 2, 0, 0 }, 2);
		obj3.homotetia({ 0, 0, 0 }, -4);
		obj4.homotetia({ 10, 8, 6 }, 0.5);
		obj5.move({ 4, -6, 10 });

		Application app1(200, 200, camera, "Programme test");
		app1.add_object(obj1);
		app1.add_object(obj2);
		app1.add_object(obj3);
		app1.add_object(obj4);
		app1.add_object(obj5);
		app1.exec();

		std::cout << "Test finished\n";
}

void run_tests() {
		test_1();
}

}//namespace Test2

}//namespace Sanches_project