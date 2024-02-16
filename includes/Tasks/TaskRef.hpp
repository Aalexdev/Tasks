#ifndef __TASKS_TASK_REF_HPP__
#define __TASKS_TASK_REF_HPP__

#include "common.hpp"
#include "TaskID.hpp"
#include "Priority.hpp"

namespace Tasks{
	class TaskRef{
		public:
			TaskRef(const TaskID& id, TaskRegistry& registry);
			~TaskRef() noexcept;

			const Priority& priority() const noexcept;
			void updatePriority();
			
			bool operator>(const TaskRef& other) const noexcept;
			bool operator<(const TaskRef& other) const noexcept;
			bool operator>=(const TaskRef& other) const noexcept;
			bool operator<=(const TaskRef& other) const noexcept;

			bool operator>(const Priority& priority) const noexcept;
			bool operator<(const Priority& priority) const noexcept;
			bool operator>=(const Priority& priority) const noexcept;
			bool operator<=(const Priority& priority) const noexcept;

		private:
			TaskRegistry& _registry;
			TaskID _id;
			Priority _priority;
	};
}

#endif