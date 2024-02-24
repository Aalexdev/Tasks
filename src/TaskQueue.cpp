#include "Tasks/TaskQueue.hpp"
#include "Tasks/Context.hpp"

#include <stdexcept>

namespace Tasks{
	TaskQueue::TaskQueue(Context& context) : _context{context}{}
	TaskQueue::~TaskQueue(){}

	void TaskQueue::push(const Task& task){
		std::unique_lock lock(_mutex);

		_tasks.emplace_back(task);
		std::size_t index = _tasks.size() - 1;
		_taskIDToIndex[task.id()] = index;
		percolateUp(index);
	}

	void TaskQueue::pop(std::size_t id){
		if (empty()) return;

		std::unique_lock lock(_mutex);
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
		std::shared_lock lock(_mutex);
		return Task(_tasks[id].id(), _context);
	}

	const TaskRef& TaskQueue::cdata(const std::size_t& id) const{
		return _tasks[id];
	}

	TaskRef& TaskQueue::data(const std::size_t& id){
		return _tasks[id];
	}
	
	void TaskQueue::percolateDown(std::size_t id){
		std::size_t smallest = id;
		std::size_t left = leftChild(id);
		std::size_t right = rightChild(id);

		if (left < _tasks.size() && _tasks[left].priority() < _tasks[smallest].priority()){
			smallest = left;
		} if (right < _tasks.size() && _tasks[right].priority() < _tasks[smallest].priority()){
			smallest = right;
		}

		if (smallest == id) return;

		swapNodes(id, smallest);
		percolateDown(smallest);
	}

	void TaskQueue::percolateUp(std::size_t id){
		while (id > 0 && _tasks[parent(id)].priority() > _tasks[id].priority()){
			swapNodes(id, parent(id));
			id = parent(id);
		}
	}

	void TaskQueue::swapNodes(std::size_t id1, std::size_t id2){
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
		std::shared_lock lock(_mutex);
		return _tasks.empty();
	}

	void TaskQueue::update(const Task& task, const Priority& priority){
		size_t id = find(task.id());
		updateID(id, priority);
	}

	void TaskQueue::updateID(const std::size_t& id, const Priority& priority){
		std::unique_lock lock(_mutex);

		_tasks[id].priority() = priority;
		percolateUp(id);
		percolateDown(id);
	}

	const std::shared_mutex& TaskQueue::mutex() const noexcept{
		return _mutex;
	}
	
	std::shared_mutex& TaskQueue::mutex() noexcept{
		return _mutex;
	}

	std::size_t TaskQueue::find(const TaskID& id) const{
		std::shared_lock lock(_mutex);

		auto it = _taskIDToIndex.find(id);
		if (it == _taskIDToIndex.end()) throw std::runtime_error("Cannot find ID");

		return it->second;
	}
}