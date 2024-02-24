#include <Tasks/Manager.hpp>
#include <iostream>
#include <random>

using namespace std::chrono_literals;

void testbed(){
	Tasks::Manager manager;
	
	std::cout << "Crating a task ..." << std::endl;
	
	Tasks::Task task = manager.create();
	task.setOperation(
		[](void) -> void {
			std::cout << "hello" << std::endl;
		}
	);
	task.setCycle(5);

	manager.start();
	std::this_thread::sleep_for(3s);
	manager.stop();
}

int main(int argc, char** argv){

	std::cout << "Running Testbed ..." << std::endl;
	testbed();
	std::cout << "Testbed finished." << std::endl;

	return 0;
}