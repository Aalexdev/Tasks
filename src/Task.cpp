#include "Tasks/Task.hpp"
#include "Tasks/Context.hpp"
#include <iostream>

namespace Tasks{
	Task::Task(Context& context) : _id{INVALID_TASK_ID}, _context{&context}{}
	Task::Task(const TaskID& id, Context& context) : _id{id}, _context{&context}{}
	Task::Task(const Task& other) : _id{other._id}, _context{other._context}{}
	Task::~Task(){}

	const TaskData& Task::getData() const{
		return _context->registry.data(_id);
	}

	TaskData& Task::getData(){
		return _context->registry.data(_id);
	}

	const TaskID& Task::id() const noexcept{
		return _id;
	}

	const Priority& Task::priority() const noexcept{
		auto lock = _context->syncManager.registryRead();
		return getData().basePriority;
	}

	void Task::setCycle(const TaskCycle& cycle){
		auto lock = _context->syncManager.registryWrite();

		auto& data = getData();
		data.cycle = cycle;

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

	const Operation& Task::operation() const noexcept{
		auto lock = _context->syncManager.registryRead();
		return getData().operation;
	}

	const Importance& Task::importance() const noexcept{
		auto lock = _context->syncManager.registryRead();
		return getData().importance;
	}

	const TimeConstraint& Task::timeConstraint() const noexcept{
		auto lock = _context->syncManager.registryRead();
		return getData().timeConstraint;
	}
	
	const TaskCycle& Task::cycle() const noexcept{
		auto lock = _context->syncManager.registryRead();
		return getData().cycle;
	}

	bool Task::isCycle() const noexcept{
		return cycle().isCyclic();	
	}

	void Task::setOperation(const Operation& operation) noexcept{
		auto lock = _context->syncManager.registryWrite();
		getData().operation = operation;
	}

	void Task::setOperation(const Operation::FunctionPointer& fnc) noexcept{
		setOperation(Operation(fnc));
	}

	void Task::setPriority(const Priority& priority) noexcept{
		auto lock = _context->syncManager.registryWrite();
		getData().basePriority = priority;
	}

	void Task::setPriority(const float& priority) noexcept{
		setPriority(Priority(priority));
	}
	
	void Task::setImportance(const Importance& importance) noexcept{
		auto lock = _context->syncManager.registryWrite();
		getData().importance = importance;
	}

	void Task::setImportance(const float& importance) noexcept{
		setImportance(Importance(importance));
	}

	void Task::setTimeConstraint(const TimeConstraint& constraint) noexcept{
		auto lock = _context->syncManager.registryWrite();
		getData().timeConstraint = constraint;
	}

	void Task::setTimeConstraint(const TimeConstraint::Duration& duration) noexcept{
		setTimeConstraint(TimeConstraint(duration));
	}

	const std::list<Concurrency> Task::concurencies() const noexcept{
		getData().concurrencies;
	}
}