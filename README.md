# Tasks

## How To Build

### CMake

Tasks uses [CMake](https://cmake.org/) to support cross-platform, efficient and easily customizable building. Please make sure that you have a recent enough version of [CMake](https://cmake.org/) installed on your device.

#### How to compile

Using the command line terminal, open the project directory.
Once in the project directory, create a build folder using the `mkdir` command.

```bash
mkdir build
	cd build/
```

Once in there, use the [CMake](https://cmake.org/) command

```bash
cmake ..
```

Note that you can customize the compilation settings such as the [generator](https://gitlab.kitware.com/cmake/community/-/wikis/doc/cmake/Generator-Specific-Information) or other settings. For better user experience, i recommend you to use the GUI version.

Once the [CMake](https://cmake.org/) compilation is done, run the project building using your generator command.
Note that this step usually take some time.

- On Windows, you might use "Visual Studio 12 2013" (VS 2013 32-bits), or "Visual Studio 14 2015 Win64" (VS 2015 64-bits).
- On OS X, you might use "[Xcode](https://developer.apple.com/xcode/)".
- On a UNIX-like system, omit the option (for a Makefile).

If everything runs smoothly, it should be done. You can now use the library, run the tests, and learn from the examples.

If your project cannot find the library, make sure you installed it properly and check the [CMake](https://cmake.org/) settings. If it still not work, you may seek help on the internet.

Note that to clean the building process, you just need to remove the `build` directory and create a new one.

## Features

- [ ] Operations

  - [X] Custom function set
  - [X] Function comparison
  - [ ] Profiling
  - [ ] Tests
  - [ ] Documentation
- [ ] Thread Pool

  - [ ] Dynamic pool count
  - [ ] Thread count benchmarking
  - [ ] Error handling / reporting
  - [ ] Profiling
  - [ ] Tests
  - [ ] Documentation
- [ ] Task Queue

  - [ ] Thread safety
  - [ ] Priority
  - [ ] Dynamic removing / adding
  - [ ] Error handling / reporting
  - [ ] Profiling
  - [ ] Tests
  - [ ] Documentation
- [ ] TaskRef

  - [ ] Runtime priority
  - [ ] Custom priority increase
  - [ ] Task exclusivity
- [ ] Task

  - [ ] Operation
  - [ ] Dependencies
  - [ ] Priority
  - [ ] Cyclic trigger
  - [ ] Event based trigger
  - [ ] Status tracking
  - [ ] Progress tracking
  - [ ] Error handling / reporting
  - [ ] Compute weight
  - [ ] ID referencing
  - [ ] Name referencing
  - [ ] Exclusivity
  - [ ] Recovery mechanism
  - [ ] Profiling
  - [ ] Tests
  - [ ] Documentation
- [ ] Task Manager

  - [ ] Task creation / removal
  - [ ] Task dependencies
  - [ ] Task execution
  - [ ] Task priority
  - [ ] Task Tracking
  - [ ] Thread pool management
  - [ ] Event handling
  - [ ] Error handling / reporting
  - [ ] Profiling
  - [ ] Tests
  - [ ] Documentation
