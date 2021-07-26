# MarioCraft

## Configuraciones de Visual Studio

Ir a Propiedades de Configuración del Proyecto y colocar las siguientes configuraciones:

-  En Depuracion, Entorno hacer click en editar y agregar la siguiente entrada:
   - `PATH=$(ProjectDir)dll`

-  En C/C++ >> General, en la opción Dirección de inclusión adicicionales hacer click en editar y agregar en el mismo orden las siguientes entradas:
   - `$(SolutionDir)src\headers`
   - `$(SolutionDir)include`
   - `$(SolutionDir)include\SFML`
   - `$(SolutionDir)include\ASSIMP`
   - `$(SolutionDir)include\GLAD`
   - `$(SolutionDir)include\GLFW`
   - `$(SolutionDir)include\GLM`
   - `$(SolutionDir)include\KHR`
   - `$(SolutionDir)include\SDL`

-  En Vinculador >> General, en la opción Dirección de bibliotecas adicicionales hacer click en editar y agregar las siguientes entradas:
   - `$(SolutionDir)lib\SFML`
   - `$(SolutionDir)lib\SDL2`
   - `$(SolutionDir)lib\GLFW3`
   - `$(SolutionDir)lib\ASSIMP`

-  En Vinculador >> Entrada, en la opción Dependencias adicicionales hacer click en editar y agregar las siguientes entradas:
   - `opengl32.lib`
   - `glfw3.lib`
   - `assimp-vc141-mtd.lib`
   - `SDL2.lib`
   - `SDL2main.lib`
   - `sfml-main-d.lib`
   - `sfml-graphics-d.lib`
   - `sfml-system-d.lib`
   - `sfml-window-d.lib`
   - `sfml-audio-d.lib`