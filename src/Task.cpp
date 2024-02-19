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

	void Task::cyclic(const TaskCycle& cycle){
		auto lock = _context->syncManager.registryWrite();

		auto& data = getData();
		data.cycle = cycle;

		if (cycle.isCyclic()){
			_context->scheduler.push(_id);
		} else {
			_context->scheduler.pop(_id);
		}
	}

	const Operation& Task::operation() const noexcept{
		auto lock = _context->syncManager.registryRead();
		return getData().operation;
	}

	void Task::setOperation(const Operation& operation) noexcept{
		auto lock = _context->syncManager.registryWrite();
		getData().operation = operation;
	}

	void Task::setOperation(const Operation::FunctionPointer& fnc) noexcept{
		setOperation(Operation(fnc));
	}
}