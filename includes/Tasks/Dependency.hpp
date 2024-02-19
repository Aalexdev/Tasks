#ifndef __TASKS_DEPENDENCY_HPP__
#define __TASKS_DEPENDENCY_HPP__

#include "common.hpp"
#include "TaskID.hpp"

namespace Tasks{
	class Dependency{
		public:
			Dependency(const TaskID& id = INVALID_TASK_ID) noexcept;
			Dependency(const Dependency& other) noexcept;
			~Dependency() noexcept;

			Dependency& operator=(const Dependency& other) noexcept;
			Dependency& operator=(const TaskID& id) noexcept;

			const TaskID& id() const noexcept;
			TaskID& id() noexcept;

		private:
			TaskID _id;
	};
}

#endif