#ifndef __TASKS_TASK_REF_HPP__
#define __TASKS_TASK_REF_HPP__

#include "common.hpp"
#include "TaskID.hpp"
#include "Priority.hpp"

namespace std{
	void swap(Tasks::TaskRef& first, Tasks::TaskRef& second);
}

namespace Tasks{
	class TaskRef{
		public:
			TaskRef(const TaskID& id, TaskRegistry& registry);
			TaskRef(const TaskRef& other);
			TaskRef(const Task& base);
			~TaskRef() noexcept;

			TaskRef& operator=(const TaskRef& other);

			const Priority& priority() const noexcept;
			const TaskID& id() const noexcept;
			
			bool operator>(const TaskRef& other) const noexcept;
			bool operator<(const TaskRef& other) const noexcept;
			bool operator>=(const TaskRef& other) const noexcept;
			bool operator<=(const TaskRef& other) const noexcept;

			bool operator>(const Priority& priority) const noexcept;
			bool operator<(const Priority& priority) const noexcept;
			bool operator>=(const Priority& priority) const noexcept;
			bool operator<=(const Priority& priority) const noexcept;

			friend void ::std::swap(Tasks::TaskRef& first, Tasks::TaskRef& second);

		private:
			TaskRegistry* _registry;
			TaskID _id;
			Priority _priority;
	};
}


#endif