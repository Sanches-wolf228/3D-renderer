#include "test1.h"
#include "application.h"
#include "iostream"

namespace Sanches_project {

namespace Test1 {

void test_1() {
	std::cout << "Run test 1\n";

	std::vector<Triangle> mas;
	Triangle a1{ {{40, 160, 10}, {100, 60, 10}, {160, 120, 10}}, {255, 0, 0} };
	Triangle a2{ {{20, 280, 10}, {80, 230, 10}, {180, 380, 10}}, {240, 240, 0} };
	Triangle a3{ {{280, 40, 10}, {360, 180, 10}, {380, 80, 10}}, {0, 255, 0} };
	Triangle a4{ {{250, 220, 10}, {300, 240, 10}, {360, 390, 10}}, {0, 180, 180} };
	Triangle a5{ {{440, 120, 10}, {540, 160, 10}, {580, 30, 10}}, {0, 0, 255} };
	Triangle a6{ {{430, 370, 10}, {460, 240, 10}, {540, 230, 10}}, {150, 0, 100} };

	Application app1(600, 400, "Configuration test");
	app1.add_triangle(a1);
	app1.add_triangle(a2);
	app1.add_triangle(a3);
	app1.add_triangle(a4);
	app1.add_triangle(a5);
	app1.add_triangle(a6);
	app1.exec();

	std::cout << "Test 1 finished\n";
}

void test_2() {
	std::cout << "Run test 2\n";

	std::vector<Triangle> mas;
	Triangle a1{ {{40, 160, 10}, {100, 60, -30}, {160, 120, 80}}, {255, 0, 0} };
	Triangle a2{ {{20, 280, 25}, {80, 230, 25}, {180, 380, -40}}, {240, 240, 0} };
	Triangle a3{ {{280, 40, -10}, {360, 180, -10}, {380, 80, 45}}, {0, 255, 0} };
	Triangle a4{ {{250, 220, -24}, {300, 240, 56}, {360, 390, 88}}, {0, 180, 180} };
	Triangle a5{ {{440, 120, 30}, {540, 160, 10}, {580, 30, 10}}, {0, 0, 255} };
	Triangle a6{ {{430, 370, -25}, {460, 240, -40}, {540, 230, -12}}, {150, 0, 100} };

	Application app1(600, 400, "Z-buffer test");
	app1.add_triangle(a1);
	app1.add_triangle(a2);
	app1.add_triangle(a3);
	app1.add_triangle(a4);
	app1.add_triangle(a5);
	app1.add_triangle(a6);
	app1.exec();

	std::cout << "Test 2 finished\n";
}

void test_3() {
	std::cout << "Run test 3\n";

	std::vector<Triangle> mas;
	Triangle a1{ {{40, 160, 10}, {40, 160, -30}, {160, 120, 80}}, {255, 0, 0} };
	// две точки с совпадающей проекцией
	// тест не проходит
	Triangle a2{ {{220, 30, 25}, {280, 80, 25}, {340, 130, 40}}, {255, 0, 0} };
	// точки на одной линии
	Triangle a3{ {{440, 120, 0}, {540, 160, 0}, {580, 30, -10}}, {255, 0, 0} };
	// только одно ребро касается экрана
	Triangle a4{ {{280, 40, -10}, {360, 180, -10}, {160, 240, 0}}, {0, 0, 255} };
	// только одна точка касается экрана
	Triangle a5{ {{250, 220, -30}, {250, 220, 36}, {250, 220, -24}}, {0, 0, 0} };
	// все точки имеют одинаковую проекцию
	// тест не проходит
	Triangle a6{ {{480, 220, 25}, {560, 290, 36}, {560, 290, 24}}, {255, 0, 0} };
	// две точки с совпадающей проекцией
	// тест не проходит


	Application app1(600, 400, "Critical cases");
	app1.add_triangle(a1);
	app1.add_triangle(a2);
	app1.add_triangle(a3);
	app1.add_triangle(a4);
	app1.add_triangle(a5);
	app1.add_triangle(a6);
	app1.exec();

	std::cout << "Test 3 finished\n";
}

void run_tests() {
	test_1();
	test_2();
	test_3();
}

}//namespace Test1

}//namespace Sanches_project