#ifndef __TASKS_TASK_REGISTRY_HPP__
#define __TASKS_TASK_REGISTRY_HPP__

#include "common.hpp"
#include "TaskData.hpp"

namespace Tasks{
	class TaskRegistry{
		public:
			TaskRegistry(Context& context);
			~TaskRegistry();

			TaskID createTask();
			void destroyTask(const TaskID& id);

			template<typename T>
			inline T read(const TaskID& id, const std::size_t& offset) const{
				T temp;
				{
					std::shared_lock lock(_mutex);
					read(id, &temp, offset, sizeof(T));
				}
				return temp;
			}

			template<typename T>
			inline void write(const TaskID& id, const std::size_t& offset, const T& data){
				std::unique_lock lock(_mutex);
				write(id, &data, offset, sizeof(T));
			}

			TaskData read(const TaskID& id) const;
			void write(const TaskID& id, const TaskData& data);

			const std::shared_mutex& mutex() const;
			std::shared_mutex& mutex();

			const TaskData& cdata(const TaskID& id) const;
			TaskData& data(const TaskID& id);

		private:
			Context& _context;
			std::queue<TaskID> _ids;
			std::vector<TaskData> _data;
			mutable std::shared_mutex _mutex;
			
			// @note: not thread safe
			void read(const TaskID& id, void* dst, const std::size_t& memberOffset = 0, const std::size_t& memberSize = sizeof(TaskData)) const;
			void write(const TaskID& id, const void* src, const std::size_t& memberOffset = 0, const std::size_t& memberSize = sizeof(TaskData));

			// @note: not thread safe
			const void* cget(const TaskID& id, const std::size_t& offset = 0) const;
			void* get(const TaskID& id, const std::size_t& offset = 0);
	};
}


#endif