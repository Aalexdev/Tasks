#include <Tasks/Manager.hpp>
#include <iostream>
#include <random>

using namespace std::chrono_literals;

void testbed(){
	Tasks::Manager manager;
	
	std::cout << "Crating a task ..." << std::endl;

	static std::size_t taskA_counter = 0;
	static std::size_t taskB_counter = 0;
	
	Tasks::Task taskA = manager.create();
	taskA.setOperation(
		[](void) -> void {
			taskA_counter++;
			std::cout << "A" << std::endl;
			std::this_thread::sleep_for(2ms);
		}
	);
	taskA.setCycle(5);

	Tasks::Task taskB = manager.create();
	taskB.setOperation(
		[](void) -> void {
			taskB_counter++;
			std::cout << "B" << std::endl;
			std::this_thread::sleep_for(5ms);
		}
	);
	taskB.setCycle(60);

	taskB.pushConcurrency(taskA);
	taskA.pushConcurrency(taskB);

	Tasks::Task singleTask = manager.create();
	singleTask.setOperation(
		[](void) -> void {
			std::this_thread::sleep_for(1s);
			std::cout << "single task" << std::endl;
		}
	);

	singleTask.addCallback(
		[&manager, &singleTask](void) -> void {
			manager.destroy(singleTask);
		}
	);

	manager.start();

	manager.trigger(singleTask);

	std::this_thread::sleep_for(3s);
	manager.stop();
	
	std::cout << "Report :: " << std::endl;
	std::cout << "taskA : " << taskA_counter / 3 << "fps" << std::endl;
	std::cout << "taskB : " << taskB_counter / 3 << "fps" << std::endl;
}

int main(int argc, char** argv){

	std::cout << "Running Testbed ..." << std::endl;
	testbed();
	std::cout << "Testbed finished." << std::endl;

	return 0;
}