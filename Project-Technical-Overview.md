# Project Technical Overview

---

This file has as goal to fully explain the project in details. This is useful to easily keep track of the project progress and to help potential contributors to know what they are doing.

## Objectives

The main objective of this task manager is to handle complex task hierarchy in multi-threading while still being very fast.
It’s goal is to be fast, versatile, easy to use, safe.

## Hierarchy

```mermaid
flowchart TD
	user(User)
	api(Task manager)
    schedule(Task scheduler)

	subgraph Memory
		registry(Task registry)
		queue(Task queue)
		refs(Task refs)
		priority(Priority updater)
	end

	subgraph Sync
        pool(Thread pool)
        sync(Syncronization handler)
	end

	user --> api

	api --> registry
	api --> queue
	api --> schedule
	api --> priority
	api --> pool
	api --> sync

	queue --> refs


```

Here is the main hierarchy of the project. This tells the ownership of each if the components.
Note that this is only a graph and does not shows the links between every modules nor the modules contents.

## Components

### Task Manager

So, the role of the task manager is to create a link between the user and the actual task manager. It is not a critical part but act more like a bridge. It is supposed to be easily understood, and easy to work with. This part HAS to be documented.

In more details, the task managers owns a `Context` member, this is the structure that owns every sub modules. The task manager act as a bridge between the context’s submodules and the user.

```mermaid
flowchart LR
	user(User)
	task(Task manager)
	context(Context)
	submodule(Submodule)

	user -->|request| task
	task --> context --> submodule
	submodule --> |response| user
```

And so, thanks to this bridge, this code :

```cpp
TaskContext.submodule.tasks.get(ID);
```

becomes this :

```cpp
manager.getTask(ID);
```

### Task Registry

The task registry is used to store task data and link them to a unique ID. One of it’s goal is to efficiently handle memory usage.

The registry stores tasks data in an array, using this, all the tasks can be accessed efficiently with a O(1) complexity. To keep track of the unused IDs, theses are stored in a queue. When creating a new task, the first element of the queue is popped and used as the new ID. If there is no free ids in the queue, there could be two cases : easer the registry reallocate the task data array, or it simply throws an exception.

This way of handling IDs have multiple benefits such as it’s fast yet simple implementation, it’s versatility and robustness. It is maybe not the best way of handling, but it is efficient enough for this scenario and would not cause issues with the api global speed.

```mermaid
---
title: Task creation
---
stateDiagram-v2
	IsEmpty: Is the queue empty
    [*] --> IsEmpty
  
	state if_state <<choice>>
    IsEmpty --> if_state
  
    NotEmpty: Returns the next ID
    if_state --> NotEmpty: False
    NotEmpty --> [*]
  
    Empty: Is this critical
    if_state --> Empty: True
  
    state is_critical <<choice>>
    Empty --> is_critical
  
    note right of is_critical
    	Note that this step
    	is defined a compulation
    end note
  
    Allocate: Allocates more IDs
    is_critical --> Allocate: False
  
    Exception: Throws an exception
    is_critical --> Exception: True
    Exception --> [*]
  
  
    Allocate --> NotEmpty
  
  

```

### Task Queue

The task queue goal is to handle the currently requested task, it has to respect the task priorities while still being easily updated. Note that the task queue does not have a copy of each tasks in the registry, it otherwise uses Task Refs, classes that link to the base task while maintaining runtime changing variables such as the priority.

Whats make the task queue a bit more complex that a simple priority queue is it’s dynamic aspect. The requested tasks priority is supposedly increasing over time. For example, of Task A and Task B with both a priority of 1, knowing that A has be request before B, it should be executed before and therefor have a larger priority. This dynamic priority update is what makes the queue more complex to handle.

The most naive way to handle that is to fully sort each time we increase a priority. But this can cause major performance downfall, even if this depends of requested task count and update rate, we can still find a better solution.

To solve this issue we can tackle this part by part. First of all, let’s just not sort the whole queue but only the updated tasks. Lucky for us, the sorted characteristic of the queue can help us, we can, instead of a linear search, we can use a binary search for the best position. To make the position updating easier, we can use a list to store the data and note having to move a whole bunch of the queue array, but this will completely break the binary search system. This is why we can use a cleverly designed array to store a  binary tree while not having to swap much data.

In this data layout, the task with the highest priority will be placed at the begin of the array.

Here is a simple priority array, note that here it’s just an array of integers.

| 8 | 5 | 5 | 4 | 2 | 1 |
| :-: | :-: | :-: | :-: | :-: | :-: |

So, as wanted, the first element of the array is the highest. Now, what happens if we update the last element priority to 7 ?

First of all, nothing much except the change in the value.

| 8 | 5 | 5 | 4 | 2 | 7 |
| :-: | :-: | :-: | :-: | :-: | :-: |

since it’s index is 5, it will check check the $\frac {id - 1} 2$ index, in this case this gives $\frac {5 - 1} 2$ which gives index 2. And the it compares the attributes values, here it gives $7 > 5$ and thus, it swaps them.

Note that we use $\frac {id-1} 2$ instead of simply $\frac {id} 2$ because it is a zero starting array, and the $-1$ compensate this.

| 8 | 5 | 7 | 4 | 2 | 5 |
| :-: | :-: | :-: | :-: | :-: | :-: |

 it will do it again, in this case compare itself with the index 1, and again $7>5$. Which gives us another swap.

| 8 | 7 | 5 | 4 | 2 | 5 |
| :-: | :-: | :-: | :-: | :-: | :-: |

This works great and it is also what is done when when pushing a value, it is pushed at the end of the queue.
But as you can see, there is a little issue, the queue is not completely sorted, the 5 that we swapped at the beginning is now at the back of the queue even tho it is not the smallest element. What the queue ensure us, is that the first element will always be the largest of the queue and not that it is entirely sorted. Even tho this look like an issue right now. When popping the first element, what’s behind get sorted. Here is how it is done :

When popping the first element, it moves the last element value to the first place, which gives us :

| 5 | 7 | 5 | 4 | 2 |
| :-: | :-: | :-: | :-: | :-: |

it will then check the value of it’s left and right child, respectively $2*id+1$ and $2*id+2$. Here element $1$ and $2$. Once it has found it’s child, it will swap itself with the largest. Here it is $7$, the first child’s value.

| 7 | 5 | 5 | 4 | 2 |
| :-: | :-: | :-: | :-: | :-: |

It checks again, but in this case, it’s first child’s value is $4$ and second one is $2$. None if them is greater, it will stop here.

This gives us here a sorted queue, but as seen before, it is not said that the queue will be fully sorted every time, but what’s count is that the firsts elements are the greatest.

### Priority updater

As seen in the task queue explanation. The task priority grows over time to unsure that tasks are executed in the least amount of time after their execution request. It is the job of the priority updater. The update rate of tasks can be a difficult part of this project. Here are potential non concurrent possibilities :

- Importance and criticality
  Tasks that are flagged as important and or critical should be increased more often to ensure that they are executed at time.
- Dependency
  Tasks whose dependencies has been triggered should increase their priority to avoid delay between both tasks.
  This is the same with concurrent tasks.
- Threshold
  Tasks that have not been updated in a long time (relative to the program execution) should have their priority increased.
- Success / failure reward
  Tasks that constantly success and end on time should see their priority increase and tasks that do not respect their time limit and or fails should see their priority decreased to avoid bottleneck.

These are potential systems, of course, the user should be able to set which tasks are viable for each of these system. But this do not really tells us when to update their priority, as seen before, updating a priority is not that expensive as itself, but done multiple time, it can get more and more expensive. This is why i thought of updating their priority every time a new task get requested. This way, if nothing is requested anymore, it will just finish the existing tasks and be done.

Here is a simple example implementing some of theses parameters

```cpp
TaskRef& reference = reference();

float factor = 0.f;

factor += reference.importancy();
factor += reference.criticality();
factor *= reference.successRate();

reference.updatePriority(reference.priority() * factor);
```

This example illustrate simply the point being made.

### Task scheduler

This part can also be quite hard to think of. There can be one system that can do the trick. A simple description of this will be, a system that will just sleep until the next task scheduled execution, once it is done, it will query the next task to execute, look at the time until this and just sleep until this moment. This would require a whole thread just for itself, but i will however minimize CPU usage since it would only sleep most of it time.

This class should store a list of all cyclically scheduled tasks, there time between each trigger and the time since the last execution. This system will iterate though all of them, performing simple subtractions and know what is the next task to trigger. Thanks to that, is knows when to trigger it next time and will just sleep until this time. Once it has finished sleeping, it will trigger it and repeat the whole process. If there is not a single task to wait for, it will just either wait for one task to be scheduled or the system to be killed.

### Thread pool

The thread pool is, as it’s name suggest a list of threads. It’s goal is to handle the thread in use count. it will tests multiple thread combination to know which one is the most effective. The user should be able to set, the minimal and the maximal amount of thread to have. Each threads run a function that will try to execute the task with the highest priority. But before running the task, it will check things such as the concurrencies / dependencies. If everything is correct, it will run it and store the time of this execution. This time since last execution value is used by dependency to see how many time passed by and to check if the dependency is still valid. Once the execution is done, it will store in another registry the time of execution and if the task got successfully executed. As seen before, these values are useful to perform efficiency tests.
But, if the dependencies are not met during the check, it will try to run the next task in the queue. Even tho it is not promised that it is the task with the second greatest priority, it is still one of the largest and has still to be done. And again, if the checks still fails, it will try the 3rd one, etc…

For the exclusivity system to work, when a thread start executing a task, the task’s id is stored. When testing an exclusive task, it will firstly check if any of the currently executing tasks are in conflict with it. Since there can only be a limited amount of threads, the exclusivity testing is quite a light command to do.

### Synchronization handler

To unsure that everything works well, the synchronization handler is critical, it is simply said just a collection of [mutexes](https://en.cppreference.com/w/cpp/thread/mutex) and barriers, but despite this simple task, it is very important and nice to have in a well organized class.

## Synchronization

In a multi-threaded system like this, one big challenge is synchronization. By itself it is not that hard but can get tricky when wanting to make it efficient and lowering wait time.
As said before, the synchronization structures are all stored in the Synchronization handler, this does not specifically make things faster, but helps with maintainability and makes things a bit more structured.

To make the system the most efficient possible, it is a good practice to batch operations. Instead of locking a [mutex](https://en.cppreference.com/w/cpp/thread/mutex), writing data, unlocking, and then re-locking it again. We can just lock it once, write/read everything we need, and then unlock it. Even tho it can sound a bit silly to say, modeling the system this way can speed it up quite a bit, but requires a more tedious observation and planning.

Before performing any tests and reflexions about how to optimize and synchronize everything. Let’s think, what do we even need to synchronize and with what ?

### Task threads

First of all, and one of the most obvious one, the task threads. Once they finished their current task, they need to access the task queue, and, probably removing it’s first element. So we need a task queue [mutex](https://en.cppreference.com/w/cpp/thread/mutex).
But what happens if the queue is empty ? It just cannot test if the queue is not empty anymore, it would cause too much overhead and a useless use of processing power.

Well, to solve this issue, we can also add a [condition variable](https://en.cppreference.com/w/cpp/thread/condition_variable). It will check if the queue is empty, if it is, it will wait a signal letting it know when the queue gets an element added. If the queue is not empty, it will simply continue.

```mermaid
---
title: Task queue check
---
stateDiagram-v2
	IsEmpty: Is the task queue empty

	[*] --> IsEmpty
	state is_empty <<choice>>
	IsEmpty --> is_empty

	NotEmpty: The task queue has elements
	is_empty --> NotEmpty: False

	Query: Get the first task
	NotEmpty --> Query

	Test: Test the task requirements
	Query --> Test

	state requirements_met <<choice>>
	Test --> requirements_met

	Met: Requirements met
	requirements_met --> Met: True

	Exec: Execute the task
	Met --> Exec

	Exec --> [*]

	NotMet: Requirements not met
	requirements_met --> NotMet: False

	SecondChance: Get the next task
	NotMet --> SecondChance
	SecondChance --> Test

	Empty: The task queue is empty
	is_empty --> Empty: True

	Signal: Wait for the update singnal
	Empty --> Signal
	Signal --> IsEmpty

```

To avoid wasted time, if the first task’s requirements (dependencies, exclusivities) are not met, it will try the second task in the queue.
The task will be executed by another thread once it’s requirements will be met.

Another point to consider is when exiting the system, we want the program to quit a soon as possible. To avoid working, we can firstly clear the task queue. And so, can be two possibilities:

- A waiting thread
  As seen in the diagram, a waiting thread would just wait for the queue to get updated. And if we update is, it will just do the next task and not exiting the program.
- A working thread
  A working thread would have to finish it’s current task, and then wait for the queue to be updated.

As we can see, all threads would eventually end up as a waiting thread.
This is why we can add a condition at our [condition variable](https://en.cppreference.com/w/cpp/thread/condition_variable), we can now test if either the queue has elements, or if the system is terminating. If either of them is true, then it will pass the [condition variable](https://en.cppreference.com/w/cpp/thread/condition_variable) and test which one of them is true.

```mermaid
---
title: Task condition test
---
stateDiagram-v2
	Wait: Wait for the signal
	[*] --> Wait

	state conditions_met <<choice>>
	Wait --> conditions_met

	Met: Conditions met
	conditions_met --> Met: True

	IsEmpty: Is the queue empty
	Met --> IsEmpty

	state is_empty <<choice>>
	IsEmpty --> is_empty

	Empty: The queue is empty
	is_empty --> Empty: True

	Quit: Exiting
	Empty --> Quit

	Quit --> [*]

	NotEmpty: The queue has elements
	is_empty --> NotEmpty: False

	TestAndExec: Test and execute
	NotEmpty --> TestAndExec
	TestAndExec --> [*]

	NotMet: Conditions not met
	conditions_met --> NotMet: False
	NotMet --> Wait
```

### Registry

The registry is also a very sensitive part. This has to be accessed continuously from different threads for both writing and and reading. Synchronization structures can add a lot of overhead and useless waits is not used correctly.

- Task threads
  Operation (read)
  Exclusivities (read)
  Execution speed (write)
- Task scheduler
  Cycle (read)
  Request time point (write)
- User
  virtually anything (read/write)

From all of this, we can understand what is required to make this system safe.
One very simple and yet efficient way to solve this is to use a [shared mutex](https://en.cppreference.com/w/cpp/thread/shared_mutex). But, if you really want to push this system far, it is possible to divide the registry into multiple sections, and then define a [mutex](https://en.cppreference.com/w/cpp/thread/mutex) to use per fractions.

### Task queue

The task queue can get a bit tricky to get right. As before let’s breakdown the different dependencies.

- Task threads
  Query (read)
  Pop (write)
- Task scheduler
  push (write)
- User
  push (write)
- Manager
  clear (write)

Here, since a lot of writing appends, using a [shared mutex](https://en.cppreference.com/w/cpp/thread/shared_mutex) would just be a waste, we will just use a simple [mutex](https://en.cppreference.com/w/cpp/thread/mutex). If the performances become a real issue. It will be nice to improve the task queuing system.

### Thread pool

> [!NOTE]
>
> we will leave for now. The major goal of the thread pool is to manage the count of task threads and dynamically change it. It could be useful to scale the required prepossessing power (ex, a low / hight tier computer with different compute power).
