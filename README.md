# Képfeldolgozás (OpenCV):

   **Extract OpenCV in C:\opencv**

   ### Setting up OpenCV in Windows:
    
       1. Open Environmental Variables
    
       2. Under "User Variables":
        Path -> Edit -> C:\opencv (directory of OpenCV)

       3. Under "System Variables":
        Path -> Edit -> C:\opencv\build\x64\vc15\bin


   ### Setting up OpenCV in Visual Studio: 

    1. Project -> <Project name> properties
       Configuration: All Configuration
       Platform: x64

    2. C/C++ - General - Additional Include Directories:
       <OpenCV_dir>\build\include

    3. Linker - General - Additional Library Directories:
       <OpenCV_dir>\build\x64\vc15\lib

    4. Linker Configuration - Release:
       Linker - Input:
       Additional Dependencies: opencv_world460.lib

    5. Linker Configuration - Debug:
       Linker - Input:
       Additional Dependencies: opencv_world460d.lib
