#include "Tasks/Task.hpp"
#include "Tasks/TaskData.hpp"
#include "Tasks/Context.hpp"
#include <iostream>

namespace Tasks{
	Task::Task(Context& context) : _id{INVALID_TASK_ID}, _context{&context}{}
	Task::Task(const TaskID& id, Context& context) : _id{id}, _context{&context}{}
	Task::Task(const Task& other) : _id{other._id}, _context{other._context}{}
	Task::~Task(){}

	const TaskID& Task::id() const noexcept{
		return _id;
	}

	Priority Task::priority() const noexcept{
		return _context->registry.read<Priority>(_id, offsetof(TaskData, basePriority));
	}

	Operation Task::operation() const noexcept{
		return _context->registry.read<Operation>(_id, offsetof(TaskData, operation));
	}

	Importance Task::importance() const noexcept{
		return _context->registry.read<Importance>(_id, offsetof(TaskData, importance));
	}

	TimeConstraint Task::timeConstraint() const noexcept{
		return _context->registry.read<TimeConstraint>(_id, offsetof(TaskData, timeConstraint));
	}
	
	TaskCycle Task::cycle() const noexcept{
		return _context->registry.read<TaskCycle>(_id, offsetof(TaskData, cycle));
	}

	void Task::setCycle(const TaskCycle& cycle){
		_context->registry.write<TaskCycle>(_id, offsetof(TaskData, cycle), cycle);

		if (cycle.isCyclic()){
			_context->scheduler.push(_id);
		} else {
			_context->scheduler.pop(_id);
		}
	}

	void Task::setCycle(const TaskCycle::Period& period){
		setCycle(TaskCycle(period));
	}

	void Task::setCycle(const TaskCycle::Frequency& frequency){
		setCycle(TaskCycle(frequency));
	}

	bool Task::isCycle() const noexcept{
		return cycle().isCyclic();	
	}

	void Task::setOperation(const Operation& operation) noexcept{
		_context->registry.write<Operation>(_id, offsetof(TaskData, operation), operation);
	}

	void Task::setOperation(const Operation::FunctionPointer& fnc) noexcept{
		setOperation(Operation(fnc));
	}

	void Task::setPriority(const Priority& priority) noexcept{
		_context->registry.write<Priority>(_id, offsetof(TaskData, basePriority), priority);
	}

	void Task::setPriority(const float& priority) noexcept{
		setPriority(Priority(priority));
	}
	
	void Task::setImportance(const Importance& importance) noexcept{
		_context->registry.write<Importance>(_id, offsetof(TaskData, importance), importance);
	}

	void Task::setImportance(const float& importance) noexcept{
		setImportance(Importance(importance));
	}

	void Task::setTimeConstraint(const TimeConstraint& constraint) noexcept{
		_context->registry.write<TimeConstraint>(_id, offsetof(TaskData, timeConstraint), constraint);
	}

	void Task::setTimeConstraint(const TimeConstraint::Duration& duration) noexcept{
		setTimeConstraint(TimeConstraint(duration));
	}
}