#include "Tasks/TaskQueue.hpp"
#include "Tasks/TaskRegistry.hpp"

namespace Tasks{
	TaskQueue::TaskQueue(TaskRegistry& registry) : _registry{registry}{}
	TaskQueue::~TaskQueue(){}

	void TaskQueue::push(const Task& task){
		_tasks.emplace_back(task);
		std::size_t index = _tasks.size() - 1;
		_taskIDToIndex[task.id()] = index;
		percolateUp(index);
	}

	void TaskQueue::pop(std::size_t id){
		if (empty()) return;

		_taskIDToIndex.erase(_tasks[id].id());
		_tasks[id] = _tasks.back();
		_taskIDToIndex[_tasks[id].id()] = id;
		_tasks.pop_back();
		percolateDown(id);
	}

	Task TaskQueue::top() const{
		return get(0);
	}

	Task TaskQueue::get(std::size_t id) const{
		return Task(_tasks[id].id(), _registry);
	}
	
	void TaskQueue::percolateDown(std::size_t id){
		std::size_t smallest = id;
		std::size_t left = leftChild(id);
		std::size_t right = rightChild(id);

		if (left < _tasks.size() && _tasks[left].priority() < _tasks[smallest].priority())
			smallest = left;
		if (right < _tasks.size() && _tasks[right].priority() < _tasks[smallest].priority())
			smallest = right;

		if (smallest != id) {
			swapNodes(id, smallest);
			percolateDown(smallest);
		}
	}

	void TaskQueue::percolateUp(std::size_t id){
		while (id > 0 && _tasks[parent(id)].priority() > _tasks[id].priority()) {
			swapNodes(id, parent(id));
			id = parent(id);
		}
	}

	void TaskQueue::swapNodes(std::size_t id1, std::size_t id2) {
		std::swap(_tasks[id1], _tasks[id2]);
		_taskIDToIndex[_tasks[id1].id()] = id1;
		_taskIDToIndex[_tasks[id2].id()] = id2;
	}

	std::size_t TaskQueue::parent(std::size_t id) noexcept{
		return (id - 1) / 2;
	}

	std::size_t TaskQueue::leftChild(std::size_t id) noexcept{
		return 2 * id + 1;
	}

	std::size_t TaskQueue::rightChild(std::size_t id) noexcept{
		return 2 * id + 2;
	}

	bool TaskQueue::empty() const noexcept{
		return _tasks.empty();
	}
}