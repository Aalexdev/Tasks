# Project Technical Overview

---

This file has as goal to fully explain the project in details. This is useful to easily keep track of the project progress and to help potential contributors to know what they are doing.

## Objectives

The main objective of this task manager is to handle complex task hierarchy in multi-threading while still being very fast.



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
	
	schedule --> Sync
	
	queue --> refs
	queue --> priority
	queue --> schedule
	
	
	pool --> sync
	registry --> refs
	priority --> refs
	
	
	
```

