core:
	Contains base level files with no dependencies to other systems in the engine. This includes critical things
	like ecs and serialization.
other:
	Other files are systems that can rely on core (but idealy not on other non-core systems). Each folder contains
	the system code and code for components that the system cna act on. the include folder contains header
	files that can be used in the client to access the system and components