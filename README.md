<p>
  <img src="img/icono.png" align="right"  width="60" height="60" />
</p>


# MarioCraft
#### Autores:
- Jorge Cárdenas Cárdenas
- Ricardo Antonio Hernández Torres
- Samuel Arturo Garrido Sánchez


### Ejecutable

Dentro del archivo `Ejecutable.zip`, existe el archivo MarioCraft.exe que se puede ejecutar simplemente con doble click.

+ Tiene un ícono de honguito.


![](img/ImagenPrincipal.png)

### INSTRUCCIONES PARA COMPILAR:

**PASO 1:**

Abrir el proyecto de Visual Studio (MarioCraft.vcxproj)

**PASO 2:**

**SELECCIONAR ARQUITECTURA x86**, si se elige x64 habrá un error inicial.

**PASO 3:**

Abrir las propiedades del proyecto:

-  En **DEPURACIÓN** hacer click en **ENTORNO**
   - Hacer click en editar y agregar la siguiente entrada:
   
   `PATH=$(ProjectDir)dll`

![](img/Imagen1.png)

### En caso de existir un error al compilar, asegurarse que se encuentren las siguientes configuraciones. 

Ir a Propiedades de Configuración del Proyecto y colocar las siguientes configuraciones:

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


### Estructura general del proyecto
El proyecto fue generado utilizando el paradigma Orientado a Objetos de tal manera que cada elemento colocado en pantalla es una clase y algunos heredan atributos y métodos para que el proyecto sea más escalable y mejor estructurado.

- **dll:** Bibliotecas de Enlaces Dinámicos
- **include:** Bibliotecas generales del proyecto (headers)
- **lib:** Bibliotecas de Enlaces Estáticos
- **resources:** Modelos, imágenes y sonidos.
- **shaders:** Scripts del GPU
- **src:** Archivos fuente
  - **headers:** Definición de las clases del proyecto.
    - Model3D.h  (Clase general de todos los modelos, mejora las transformaciones, hereda de Model.h)
    - StaticModel.h (Clase para objetos estáticos, heredada de Model3D)
    - DynamicModel.h (Clase para objetos dinámicos, heredada de Model3D)
    - sound.h (Clase para el audio)
    - MarioCraft.h (Encabezado general del objeto del plano)
    - ModelManager. (Controlador de los modelos, para mandarlos al shader)
    - Lightning.h (Clase de la luz diurna)
    - Camera.h (Clase de la cámara)
    - Golem.h
    - Dragon.h
    - Kart.h
    - Peach.h
    - JumpAnimation.h (Clase para saltos generales)
    - MobMinecraft (Clase general de mobs de minecraft, para caminar solamente)
    - Vaca.h
    - Creeper.h
    - Moneda.h
  - **sources:** Contenido de las clases del proyecto.
  - **main.cpp:** Archivo principal, instancia las clases que conforman el proyecto. 
- **MarioCraft.sln:** Archivo de solución
- **MarioCraft.vcxproj:** Archivo del proyecto.

### Interacciones con el ambiente

- 1: Cámara
  - Para moverse por el escenario, se cuenta con una cámara que se puede mover usando la siguiente configuración de teclas y mouse.
    - W : Arriba
    - S : Abajo
    - D : Derecha
    - A : Izquierda
    - Scroll mouse: Acerca y Aleja
    - Puntero mouse: Ángulo de la cámara
  
- 2: Carrera de autos
   -  Para realizar la animación de carrera de autos:
      -  Barra espaciadora: Iniciar animación (se reproduce sonido).

### Animaciones implementadas

- 1: **Dragón volando y lanzando bolas de fuego**

![](img/Imagen2.png)

- 2: **Peach perseguida por Creeper**

![](img/Imagen3.png)

- 3: **Carrera de autos**
  
![](img/Imagen6.png)
- 4: **Toad saltando**

![](img/Imagen4.png)
- 5: **Golem vigilando**

![](img/Imagen5.png)

- 6: **Ciclo diurno (Sol y Luna)**

![](img/Imagen8.png)

- 7: **Monedas girando**

![](img/Imagen7.png)


### Modelos implementados (con link)

- Escenario - [Link](https://skfb.ly/6VFZK)
- Casa Toad  - [Link](https://3dwarehouse.sketchup.com/model/5909ca01-6452-4743-a96a-2da59de4d93f/Mario-Toad-House)
- Castillo  - [Link](https://skfb.ly/BKKG)
- Kart  - [Link](https://skfb.ly/6Rn7G)
- Toad - [Link](https://www.models-resource.com/3ds/supermario3dland/model/12811/)
- Carretera  - [Link](https://www.models-resource.com/wii/mariokartwii/model/32084/)
- Creeper  - [Link](https://skfb.ly/6RnEO)
- Peach  - [Link](https://skfb.ly/o6DrV)
- Golem  - [Link](https://skfb.ly/6RCVI)
- Dragon  - [Link](https://skfb.ly/6Roty)
- Sol  - [Link](https://free3d.com/es/modelo-3d/sun-v2--446713.html)
- Luna  - [Link](https://free3d.com/es/modelo-3d/moon-photorealistic-2k-853071.html)
- Monedas  - [Link](https://skfb.ly/6YUOC)
- Mobs de Minecraft en General  - [Link](https://sketchfab.com/vinceyanez)
- Árbol  - [Link](https://free3d.com/es/modelo-3d/minecraft-simple-tree-4959.html)
- CasaMinecraft1  - [Link](https://3dwarehouse.sketchup.com/model/4f179c1a5075703749568b6dc5d39ae5/Minecraft-Village-House?hl=en)
- CasaMinecraft2  - [Link](https://3dwarehouse.sketchup.com/model/4f179c1a5075703749568b6dc5d39ae5/Minecraft-Village-House?hl=en)
- CasaMinecraft3  - [Link](https://skfb.ly/6vpUF)
- CasaMinecraft4  - [Link](https://sketchfab.com/3d-models/minecraft-simple-house-0ae7f28a376d4758abf9f9de30b989c1)

### Música de fondo

[LINK PARA ARCHIVO](https://vgmsite.com/soundtracks/super-smash-bros.-ultimate-vol.-37-minecraft/aeblqycxwm/01.%20Halland%20~%20Dalarna%20%28Minecraft%20Dungeons%29.mp3)

**TÍTULO:**  Halland / Dalarna
**COMPOSITOR:** Mojang AB
**ARREGLO:** SEKAI WALKER
Producers LLC.

Composition Copyright Mojang AB

Arrangement Copyright Nintendo


<audio src="https://vgmsite.com/soundtracks/super-smash-bros.-ultimate-vol.-37-minecraft/aeblqycxwm/01.%20Halland%20~%20Dalarna%20%28Minecraft%20Dungeons%29.mp3">
  Your browser does not support the <code>audio</code> element.
</audio>

### Herramientas de desarrollo

#### Jira

Se implementó Jira utilizando un enfoque de metodologías ágiles para realizar el proyecto

![](img/scr2.png)

CRONOGRAMA: [LINK DE DRIVE](https://drive.google.com/file/d/12qRsRaWpavHYcGm8vWarMVYnLSACj_VJ/view?usp=sharing)


### Costos del proyecto 

- Estimación de costo por modelo: $30 usd x 20 = $ 600 usd
- Salario de modelador: $1500 usd x 1 = $1500 usd 
- Salario de desarrollador: $1200 usd x 2 = $2400 usd
- Licencia de 3DSMax:$1700 usd x 3 año = $ 5100 usd
- Licencia de Visual Studio: $100 x 3 usd = $300 usd
- Luz eléctrica promedio: $50 x3 usd = $150 usd
- Gasto de equipo de cómputo: $1500 usd x computadora (3) = $4500 usd
- Internet: $30 x 3 = $90 usd
- GitHub Pro: $5 x 3 = $15 usd
- Jira Software: $100

### Total
**$14755 x 1.3 de ganancia  = $19181.5 usd**

### $380,931.19 MXN



