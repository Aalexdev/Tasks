#include <Tasks/Manager.hpp>
#include <iostream>
#include <random>

using namespace std::chrono_literals;

void testbed(){
	Tasks::Manager manager;
	
	std::cout << "Crating a task ..." << std::endl;
	
	Tasks::Task task = manager.create("MyTask");
	task.setOperation(
		[](void) -> void {
		}
	);
	task.setCycle(10);

	manager.start();
	std::this_thread::sleep_for(3s);
	manager.stop();
}

int main(int argc, char** argv){

	std::cout << "Running Testbed ..." << std::endl;
	testbed();
	std::cout << "Testbed terminated." << std::endl;

	return 0;
}