#ifndef __TASKS_TASK_HPP__
#define __TASKS_TASK_HPP__

#include "common.hpp"
#include "TaskID.hpp"
#include "Priority.hpp"
#include "TimeConstraint.hpp"
#include "Operation.hpp"
#include "Importance.hpp"
#include "TaskCycle.hpp"
#include "Concurrency.hpp"

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
			const Importance& importance() const noexcept;
			const TimeConstraint& timeConstraint() const noexcept;
			const TaskCycle& cycle() const noexcept;

			void setOperation(const Operation& operation) noexcept;
			void setOperation(const Operation::FunctionPointer& fnc) noexcept;

			void setPriority(const Priority& priority) noexcept;
			void setPriority(const float& priority = Priority::MEDIUM) noexcept;

			void setImportance(const Importance& importance) noexcept;
			void setImportance(const float& importance = Importance::MODERATE) noexcept;

			void setTimeConstraint(const TimeConstraint& constraint) noexcept;
			void setTimeConstraint(const TimeConstraint::Duration& duration = TimeConstraint::NONE) noexcept;

			void setCycle(const TaskCycle& cycle);
			void setCycle(const TaskCycle::Period& period);
			void setCycle(const TaskCycle::Frequency& frequency);

			bool isCycle() const noexcept;

			const std::list<Concurrency>& concurencies() const noexcept;

		private:
			Context* _context;
			TaskID _id;

			const TaskData& getData() const;
			TaskData& getData();
	};
}

#endif