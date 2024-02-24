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
			Priority priority() const noexcept;
			Operation operation() const noexcept;
			Importance importance() const noexcept;
			TimeConstraint timeConstraint() const noexcept;
			TaskCycle cycle() const noexcept;

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

			std::list<Concurrency> concurrencies() const;
			void pushConcurrency(const Concurrency& concurrent);
			void popConccurency(const Concurrency& concurrent);

		private:
			Context* _context;
			TaskID _id;
	};
}

#endif