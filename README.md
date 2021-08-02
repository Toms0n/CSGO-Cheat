# CSGO-Cheat

## Performance TODOS:  
1. Make use of `std::shared_ptr` instead of `std::unique_ptr`. 
This prevents having many unique pointers to objects that need to be initialized once. 
E.g. in `MemoryManager` class, the `ProcessHandler` class is initialized with unique pointer but that is also done in `CsgoCheat` class.
But only ONE instance of `ProcessHandler` needs to be used. Thus use shared ptr to make many pointers have reference to only ONE instance of `ProcessHandler` class.