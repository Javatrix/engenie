<p align="center">
<img src="https://i.imgur.com/SgaLRWZ.png" width="50%" alt="tsuki-chan"/>
</p>

<h1 align="center">WORK IN PROGRESS</h1>

## You say what you want. He does it.
Engenie is designed to be an easy to grasp, bloat-free game engine using C++ following a pure-code approach. That said, there will hopefully appear some sort level editor one day.

# Licensing
This project is published under the [GNU General Public License](https://github.com/Javatrix/engenie/blob/main/LICENSE).
You can use code from this project as long as you disclose the source of your work. For more details, view LICENSE.

# Features
There is pretty much none for now, but the engine is under steady development, so stay tuned for updates!

# Building
### For now, automatic building only supports Linux. You can still however build  the project manually.

The repository is split into two parts:
 - [Engenie Core](https://github.com/Javatrix/engenie/tree/main/Engenie-Core) containing the actual engine
 - [Engenie App](https://github.com/Javatrix/engenie/tree/main/Engenie-App) configured as an example application

## The core
To build the core, just run the [build script](https://github.com/Javatrix/engenie/blob/main/Engenie-Core/build.sh) for Linux, or, if you are on another OS, you can execute these operations manually:

1. Create a directory inside the Engenie-Core called build
2. Open terminal there and run:
	```shell
	cmake ..
	make
	```

The library file will be generated inside the build/libs directory. However, since the core is a sub-directory of the application, it will be built automatically with it, so there is no reason to build it independently, unless you want to use the static library somewhere else.

## The application
Again, if on Linux, just run the [build script.](https://github.com/Javatrix/engenie/blob/main/Engenie-App/build.sh) Otherwise, here are the steps to manually build the executable:

1. Create a build directory inside Engenie-App
2. Run 
	```shell
	cmake ..
	make
	```

The executable will be created in the same directory the commands were ran.

# Documentation
The project is in very early stage, so the documentation is... well, non existent.
Along with the codebase, the documentation will slowly appear. Perhaps on the first official release.
