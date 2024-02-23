#include "Tasks/TaskRegistry.hpp"

#include <cassert>
#include <stdexcept>
#include <algorithm>

// #define assertTaskID(id) assert(_ids.size() > id); 
#define assertTaskID(id) if(!(_data.size() > id)) throw std::runtime_error("assertion failed");

namespace Tasks{
	TaskRegistry::TaskRegistry(Context& context) : _context{context}{}
	TaskRegistry::~TaskRegistry(){}

	TaskID TaskRegistry::createTask(TaskName name){
		static constexpr std::size_t TASK_COUNT = 50;

		if (_ids.empty()){
			std::size_t baseId = _data.size();
			_data.resize(_data.size() + TASK_COUNT);
			
			for (std::size_t i=0; i<TASK_COUNT; i++){
				_ids.push(baseId + i);
			}
		}

		TaskID id = _ids.front();
		_ids.pop();

		if (name.empty()){
			name = "Task " + std::to_string(id);
		}

		_nameToID[name] = id;
		return id;
	}

	void TaskRegistry::destroyTask(const TaskID& id){
		assertTaskID(id);

		auto it = std::find_if(
			_nameToID.begin(),
			_nameToID.end(),
			[&id](const std::unordered_map<TaskName, TaskID>::value_type &it){
				return it.second == id;
			}
		);

		if (it == _nameToID.end()){
			// TODO: change to custom exception
			throw std::runtime_error("Failed to find task");
		}

		destroyTask(it);
	}

	void TaskRegistry::destroyTask(const TaskName& name){
		return destroyTask(_nameToID.find(name));
	}

	void TaskRegistry::destroyTask(const std::unordered_map<TaskName, TaskID>::iterator& it){
		std::size_t id = it->second;

		_nameToID.erase(it);
		_ids.push(id);
		// _data[id].reset()

		_nameToID.erase(it);
	}

	TaskData& TaskRegistry::data(const TaskID& id){
		assertTaskID(id);
		return _data[id];
	}

	const TaskData& TaskRegistry::data(const TaskID& id) const{
		assertTaskID(id);
		return _data[id];
	}

	TaskData& TaskRegistry::data(const TaskName& name){
		return data(get(name));
	}

	const TaskData& TaskRegistry::data(const TaskName& name) const{
		return data(get(name));
	}
	
	TaskID& TaskRegistry::get(const TaskName& name){
		auto it = _nameToID.find(name);

		if (it == _nameToID.end()){
			// TODO: change to custom exception
			throw std::runtime_error("Failed to find task");
		}

		return it->second;
	}

	const TaskID& TaskRegistry::get(const TaskName& name) const{
		auto it = _nameToID.find(name);

		if (it == _nameToID.end()){
			// TODO: change to custom exception
			throw std::runtime_error("Failed to find task");
		}

		return it->second;
	}
}