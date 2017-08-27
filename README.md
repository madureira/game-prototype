# game-prototype
A simple 2D top-down game framework, built on top of SDL2 and modern C++11.

Using this structure, you are able to build simple [2D top-down games](https://en.wikipedia.org/wiki/Video_game_graphics#Top-down_perspective), like some titles listed **[here](https://en.wikipedia.org/wiki/Category:Top-down_video_games)**.

To facilitate game development, the framework integrates with some useful tools:
* [Tiled Map Editor](http://www.mapeditor.org/) (Used to build maps based on tiles)
* [Aseprite](https://www.aseprite.org/) (Used to generates sprites and animations)

![example](https://raw.githubusercontent.com/madureira/game-prototype/master/game-prototype/assets/game-prototype.gif)

## Dependencies
This structure is built using the following libraries:
* [SDL2](https://www.libsdl.org/)
* [SDL_image 2.0](https://www.libsdl.org/projects/SDL_image/)
* [SDL_mixer 2.0](https://www.libsdl.org/projects/SDL_mixer/)
* [SDL_ttf 2.0](https://www.libsdl.org/projects/SDL_ttf/)
* [TinyXML-2](https://github.com/leethomason/tinyxml2)
* [nlohmann/json](https://github.com/nlohmann/json)

## Importing the project
If you use [Microsoft Visual Studio Community 2017](https://www.visualstudio.com) to develop, follow the steps below.

1. Open Visual Studio IDE
1. On menu bar, select: **File > New > Project...**
1. On left-side, select **Templates** and **Visual C++**
1. On right-side, select: **Empty Project**
1. On the field **Name:** write: `game-prototype`
1. On the field **Location:** write the path where your project folder is. In this example: `C:\Users\your-user\projects\workspace`
1. On field **Solution name:** write: `game-prototype`
1. Check the box: **Create directory for solution**
1. Hit **OK**

If all went well, you will see your project in the column: **Solution Explorer**

Now to be easier to understand the project structure, change the view mode:
1. On **Solution Explorer** click on **Show All Files** icon.
1. Now, expands some folders inside *assets* and *src*, to see some files...
1. Observes if the files has a red icon, indicating that it is not included on the project. If it is, right-click on the file and click **Include In Project**. Try to include the whole folder to add all files to the project (sometimes this does not works).

Done, the project was imported and the source files were included, now we need to configure it.

## Configuring
To be able to build and run our project, we need to configure it. So, let's start!

### *Configuring the output folder*
1. Right click on **game-prototype** in **Solution Explorer**
1. Properties
1. You gonna see on the top of the window, the selector: **Configuration**, so, choose the option: `All Configurations`
1. On selector **Plataform**, choose the option `Win32`
1. On left-side of the window, click on **General**
1. Now, in right-side, edit the field **Output Directory**. Change the default value to: `$(SolutionDir)bin\$(Configuration)\`
1. In **Intermediate Directory** put the value: `$(SolutionDir)bin\$(Configuration)\intermediates\`
1. Hit the button **Apply**

### *Configuring the include paths*
1. On left-side, select **VC++ Directories**
1. Now, in right-side, edit the field **Include Directories**. A modal is gonna open. Now add this folders, each on a different line:
  ```
  $(SolutionDir)dependencies\SDL2-2.0.5\include
  $(SolutionDir)dependencies\SDL2_image-2.0.1\include
  $(Solutiondir)dependencies\SDL2_mixer-2.0.1\include
  $(SolutionDir)dependencies\SDL2_ttf-2.0.14\include
  $(SolutionDir)dependencies\glm
  ```
1. Hit the button **OK** to close modal and hit the button **Apply**


### *Configuring Linker*
1. On left-side, expand **Linker** and select **General**
1. Edit the field: **Additional Library Directories**. A modal is gonna open, so, include the follow paths, each on a different line:
  ```
  $(SolutionDir)dependencies\SDL2-2.0.5\lib\x86
  $(SolutionDir)dependencies\SDL2_image-2.0.1\lib\x86
  $(SolutionDir)dependencies\SDL2_mixer-2.0.1\lib\x86
  $(SolutionDir)dependencies\SDL2_ttf-2.0.14\lib\x86
  ```
1. Hit the button **OK** to close modal and hit the button **Apply**
1. On left-side, expand **Linker** and now select **Input**
1. Edit the field: **Additional Dependencies**. A modal is gonna open, so, include the follow libraries:
  ```
  SDL2.lib
  SDL2main.lib
  SDL2_image.lib
  SDL2_mixer.lib
  SDL2_ttf.lib
  ```
1. Hit the button **OK** to close modal and hit the button **Apply**
1. On left-side, expand **Linker** and now select **System**
1. Edit the field: **SubSystem** and choose the option: `Console (/SUBSYSTEM:CONSOLE)`
1. Hit the button **Apply**
1. Now you can hit **OK** to close the configuration properties window.

## Adding DLL's
Now, we need to add the project's DLL's before build.

You can find all needed DLL's inside the path: `game-prototype/dependencies/DLLs/`.

Copy everything and paste inside of: `game-prototype/bin/Debug/` and `game-prototype/bin/Release/`

## Building
After all this boring configuration, we able to finally build and run the project.

1. On the top of Visual Studio, you can see a selector where you have the options: `Debug`, `Release` and `Configuration Manager...`. Choose the option `Debug`.
1. Now, choose `x86` on the next selector.
1. Click on play button `Local Windows Debugger` to run the application in Debug mode.
