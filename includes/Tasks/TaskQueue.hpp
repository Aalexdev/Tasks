#ifndef __TASKS_TASK_QUEUE_HPP__
#define __TASKS_TASK_QUEUE_HPP__

#include "common.hpp"
#include "TaskRef.hpp"
#include "Task.hpp"

namespace Tasks{
	class TaskQueue{
		public:
			TaskQueue(TaskRegistry& registry);
			~TaskQueue();

			void push(const Task& task);
			void pop(std::size_t id = 0);

			bool empty() const noexcept;

			Task top() const;
			Task get(std::size_t id) const;

		private:
			TaskRegistry& _registry;
			std::unordered_map<TaskID, std::size_t> _taskIDToIndex;
			std::vector<TaskRef> _tasks;

			void percolateDown(std::size_t id);
			void percolateUp(std::size_t id);

			void swapNodes(size_t idx1, size_t idx2);

			static std::size_t parent(std::size_t id) noexcept;
			static std::size_t leftChild(std::size_t id) noexcept;
			static std::size_t rightChild(std::size_t id) noexcept;
	};
}

#endif