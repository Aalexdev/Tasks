#ifndef __TASKS_TASK_HPP__
#define __TASKS_TASK_HPP__

#include "common.hpp"
#include "TaskID.hpp"
#include "Priority.hpp"
#include "TimeConstraint.hpp"
#include "Operation.hpp"

namespace Tasks{
	class Task{
		friend class TaskRef;
		public:
			Task(Context& context);
			Task(const TaskID& id, Context& context);
			Task(const Task& other);
			~Task();
			
			const TaskID& id() const noexcept;
			const Priority& priority() const noexcept;
			const Operation& operation() const noexcept;

			void setOperation(const Operation& operation) noexcept;
			void setOperation(const Operation::FunctionPointer& fnc) noexcept;

			void cyclic(const TaskCycle& cycle);

		private:
			Context* _context;
			TaskID _id;

			const TaskData& getData() const;
			TaskData& getData();
	};
}

#endif