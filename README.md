<h1 align="center"> <img alt="QUIZO" title="QUIZO" src="https://github.com/user-attachments/assets/fdc6ec64-1d98-450f-b6eb-1f1b06fa5346" width="450"> </h1> <br>

<p align="center">
  Una aplicación innovadora para estudiantes que utiliza IA para evaluar su desempeño con precisión y seguridad, garantizando un entorno protegido y privado.
  
</p>
<h1 align="center"><img alt="QUIZO" title="QUIZO" src="https://github.com/user-attachments/assets/79297f50-3118-4778-a586-785f6945be1d" width="50"></h1>

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
## Tabla de Contenidos

- [Introducción](#introducción)
- [Características](#características)
- [Descripción de la Aplicación](#descripción-de-la-aplicación)
- [Funcionamiento](#funcionamiento)
- [Proceso de Compilación](#proceso-de-compilación)
- [Retroalimentación](#retroalimentación)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Introducción

ByteStorm se embarca en una nueva era de innovación tecnológica. Desde su fundación en 2024, ByteStorm ha avanzado en la creación de soluciones prácticas y eficientes. Nos enorgullece presentar nuestra nueva aplicación de evaluación digital, diseñada para estudiantes y enfocada en una evaluación justa y precisa mediante inteligencia artificial. Esta plataforma garantiza la seguridad de los datos y la privacidad del usuario, ayudando a los estudiantes a alcanzar su máximo potencial de aprendizaje.

## Características

* Evaluación del desempeño estudiantil mediante IA
* Entorno seguro para todas las evaluaciones
* Protección de datos y privacidad de los usuarios
* Análisis en tiempo real sobre el progreso del estudiante
* Acceso a materiales interactivos y ejercicios de estudio

## Descripción de la Aplicación

La aplicación de ByteStorm facilita el acceso a herramientas de aprendizaje avanzadas para estudiantes. Ofrece:

- **Ventana a Pantalla Completa**: Una interfaz sin distracciones con el texto "Funciona" en una fuente moderna, centrado en la pantalla.
- **Bloqueo de Teclas**: Restringe el uso de teclas como `Alt+Tab`, `Ctrl+Esc` y la tecla de Windows para garantizar un enfoque ininterrumpido.
- **Cierre con la tecla Q**: La única forma de cerrar la ventana es presionando la tecla `Q`.
- **Gestión de Explorer.exe**: Cierra y reinicia `explorer.exe` para evitar interrupciones mientras se utiliza la aplicación.

## Funcionamiento

1. **Inicialización**: La aplicación inicializa GDI+ para el renderizado gráfico.
2. **Creación de la Ventana**: Se crea una ventana a pantalla completa sin bordes.
3. **Hook de Teclado**: Intercepta y bloquea combinaciones de teclas específicas.
4. **Renderizado de Texto**: Muestra el texto "Funciona" en pantalla.
5. **Gestión de Explorer**: Ejecuta comandos del sistema para cerrar y reiniciar `explorer.exe`.
6. **Bucle de Mensajes**: Mantiene el estado de la ventana y la entrada del usuario.

## Proceso de Compilación

1. **Compilar**: Utiliza un compilador C++ compatible con la API de Windows y GDI+.
2. **Ejecutar**: Ejecuta el binario compilado. La aplicación tomará control de la pantalla hasta que se presione `Q`.

## Retroalimentación

Si tienes comentarios, sugerencias o encuentras algún problema, siéntete libre de contactarnos a través de [github issue](https://github.com/Soy-Katsito/QUIZO/issues/new). ¡Las solicitudes de características siempre son bienvenidas!
