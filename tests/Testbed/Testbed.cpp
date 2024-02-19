#include <Tasks/Manager.hpp>
#include <iostream>

using namespace std::chrono_literals;

int main(int argc, char** argv){
	Tasks::Manager manager;
	
	std::cout << "Crating a task ..." << std::endl;
	Tasks::Task task = manager.create("MyTask");
	task.cyclic(Tasks::TaskCycle(1.f));
	task.setOperation(
		[&](void) -> void {
			std::cout << "aaa" << std::endl;
		}
	);

	manager.start();

	std::this_thread::sleep_for(3s);

	manager.stop();

	return 0;
}