#ifndef __TASKS_TASK_REGISTRY_HPP__
#define __TASKS_TASK_REGISTRY_HPP__

#include "common.hpp"
#include "TaskData.hpp"
#include <cstring>

namespace Tasks{
	class TaskRegistry{
		public:
			TaskRegistry(Context& context);
			~TaskRegistry();

			TaskID createTask();
			void destroyTask(const TaskID& id);

			template<typename T, typename Member>
			inline T read(const TaskID& id, Member member) const{
				T temp;
				{
					std::shared_lock lock(_mutex);
					read(id, &temp, offsetof(TaksID, member), sizeof(T));
				}
				return temp;
			}

			template<typename T, typename Member>
			inline void write(const TaskID& id, Member member, const T& data){
				std::unique_lock lock(_mutex);
				write(id, &data, offsetof(TaskID, member), sizeof(T));
			}

			TaskData read(const TaskID& id) const;
			void write(const TaskID& id, const TaskData& data);

			const std::shared_mutex& mutex() const;
			std::shared_mutex& mutex();

		private:
			Context& _context;
			std::queue<TaskID> _ids;
			std::vector<TaskData> _data;
			std::shared_mutex _mutex;
			
			// @note: not thread safe
			void read(const TaskID& id, void* dst, const std::size_t& memberOffset = 0, const std::size_t& memberSize = sizeof(TaskData)) const;
			void write(const TaskID& id, const void* src, const std::size_t& memberOffset = 0, const std::size_t& memberSize = sizeof(TaskData));

			// @note: not thread safe
			const void* cget(const TaskID& id, const std::size_t& offset = 0) const;
			void* get(const TaskID& id, const std::size_t& offset = 0);
	};
}


#endif