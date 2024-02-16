#include <Tasks/TaskRegistry.hpp>

int main(int argc, char** argv){
	Tasks::TaskRegistry registry;

	Tasks::TaskID taskID = registry.createTask("MyTask");
}