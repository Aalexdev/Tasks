#include <Tasks/Manager.hpp>
#include <iostream>
#include <random>

using namespace std::chrono_literals;

void testbed(){
	Tasks::Manager manager;
	
	std::cout << "Crating a task ..." << std::endl;
	
	Tasks::Task taskA = manager.create();
	taskA.setOperation(
		[](void) -> void {
			std::cout << "A" << std::endl;
			std::this_thread::sleep_for(0.5s);
		}
	);
	taskA.setCycle(5);

	Tasks::Task taskB = manager.create();
	taskB.setOperation(
		[](void) -> void {
			std::cout << "B" << std::endl;
		}
	);
	taskB.setCycle(10);

	taskB.pushConcurrency(Tasks::Concurrency(taskA.id()));
	taskA.pushConcurrency(Tasks::Concurrency(taskB.id()));

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