# cpsc585

## Downloading a playable build
1. Go to the Releases on the Github page to download the .zip
1. Unzip and launch 'libengine.exe'

## Controls
AD : steer
W : Forward
S : Backwards/brake
Space : Jump
R: Reset race
F1 : Pause
P : Toggle debug panel (useful if you need to see framerate)

## Setting up the coding enviroment (windows)
---
### Using Visual Studio (tested with VS2022)
1. Click 'Open a local folder'
1. Select/open CPSC-585
1. If VS prompts about CMake Integration then enable it and set the source directory to be CPSC-585/src/engine/CMakeLists.txt (this is the top level CMake file)
1. In the top bar of VS there should now be options to build "Windows x64 Debug" and "Windows x64 Release" and the executable will be named "libengine.exe"
1. The project can now be built, run and installed

### Using CMake without an IDE
1. install "Desktop Development with C++" in the visual studio installer (it provides `cmake`)
1. open powershell and cd to the root directory of the project
1. run the command `Set-ExecutionPolicy -ExecutionPolicy Bypass -Scope Process` (still in powershell in the root dir)
1. run the command `.\init.ps1` in powershell (still in powershell in the root dir)
1. setup your IDE to run with the project. (if not using IDE, I'd recommend just using the commands from the `init` scripts manually)
- Install "Desktop Development with C++" in the visual studio installer (for cmake) if you haven't already
- It will ask which cmake thing to use, use <project_root>/code/CMakeLists.txt
- Everything should build for you wooooo lmk if there's an issue
1. To run, use the green button dropdown to find `cpsc585-client.exe` or someth it'll work I think

- see the IDE integration section here:
  - https://vcpkg.io/en/docs/users/buildsystems/cmake-integration.html
  
## project organization

- the project consists of an 'include' folder that contains headers for functions accessable from outside the engine, any engine only headers should be put in the appropiate system folder.
- each system folder contains the files for performing a defined system in the engine as well as a CMakeLists file to describe what is needed to compile that system.
- Builds and installs are located in the 'out' folder which is generated with the first build performed
- Client contains the vast majority of game specific logic and assets

