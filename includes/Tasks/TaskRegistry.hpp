#ifndef __TASKS_TASK_REGISTRY_HPP__
#define __TASKS_TASK_REGISTRY_HPP__

#include "common.hpp"
#include "TaskData.hpp"

namespace Tasks{
	class TaskRegistry{
		public:
			TaskRegistry();
			~TaskRegistry();

			TaskID createTask(TaskName name = "");
			void destroyTask(const TaskID& id);
			void destroyTask(const TaskName& name);

			TaskData& data(const TaskID& id);
			const TaskData& data(const TaskID& id) const;
			TaskData& data(const TaskName& name);
			const TaskData& data(const TaskName& name) const;
			
			TaskID& get(const TaskName& name);
			const TaskID& get(const TaskName& name) const;

		private:
			std::queue<TaskID> _ids;
			std::vector<TaskData> _data;
			std::unordered_map<TaskName, TaskID> _nameToID;

			void destroyTask(const std::unordered_map<TaskName, TaskID>::iterator& it);
	};
}

#endif