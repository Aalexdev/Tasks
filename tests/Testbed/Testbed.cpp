#include <Tasks/TaskRegistry.hpp>
#include <iostream>

int main(int argc, char** argv){
	Tasks::TaskRegistry registry;
	
	std::cout << "Crating a task ..." << std::endl;
	Tasks::TaskID taskID = registry.createTask("MyTask");

	return 0;
}