#include "Tasks/TaskRegistry.hpp"

#include <cassert>
#include <stdexcept>
#include <algorithm>

#define assertTaskID(id) assert(_data.size() > id);

namespace Tasks{
	TaskRegistry::TaskRegistry(Context& context) : _context{context}{}
	TaskRegistry::~TaskRegistry(){}

	void* TaskRegistry::get(const TaskID& id, const std::size_t& offset){
		assertTaskID(id);
		return reinterpret_cast<uint8_t*>(_data.data()) + (id * sizeof(TaskData)) + offset;
	}
	
	const void* TaskRegistry::cget(const TaskID& id, const std::size_t& offset) const{
		assertTaskID(id);
		return reinterpret_cast<const uint8_t*>(_data.data()) + (id * sizeof(TaskData)) + offset;
	}

	void TaskRegistry::write(const TaskID& id, const void* src, const std::size_t& memberOffset , const std::size_t& memberSize){
		assertTaskID(id);
		void* dst = get(id, memberOffset);
		std::memcpy(dst, src, memberSize);
	}

	void TaskRegistry::read(const TaskID& id, void* dst, const std::size_t& memberOffset, const std::size_t& memberSize) const{
		assertTaskID(id);
		const void* src = cget(id, memberOffset);
		std::memcpy(dst, src, memberSize);
	}

	TaskData TaskRegistry::read(const TaskID& id) const{
		assertTaskID(id);
		TaskData temp;
		{
			std::shared_lock lock(_mutex);
			read(id, &temp);
		}
		return temp;
	}

	void TaskRegistry::write(const TaskID& id, const TaskData& data){
		assertTaskID(id);
		std::unique_lock lock(_mutex);
		write(id, data);
	}
	
	const std::shared_mutex& TaskRegistry::mutex() const{
		return _mutex;
	}

	std::shared_mutex& TaskRegistry::mutex(){
		return _mutex;
	}
	
	TaskID TaskRegistry::createTask(){
		std::unique_lock lock(_mutex);
		static constexpr std::size_t IDS_INCREASE = 15;

		if (_ids.empty()){
			const std::size_t base = _data.size();
			for (std::size_t i=0; i<IDS_INCREASE; i++){
				_ids.push(i + base);
			}

			_data.resize(base + IDS_INCREASE);
		}

		TaskID id = _ids.front();
		_ids.pop();

		return id;
	}

	void TaskRegistry::destroyTask(const TaskID& id){
		assertTaskID(id);
		std::unique_lock lock(_mutex);
		_ids.push(id);
		_data[id] = TaskData();
	}
}