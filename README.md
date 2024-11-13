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
- [Contribuidores](#contribuidores)
- [Patrocinadores](#patrocinadores-)
- [Agradecimientos](#agradecimientos)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Introducción

[![Estado de Construcción](https://img.shields.io/travis/byte-storm/byte-storm-app.svg?style=flat-square)](https://travis-ci.org/byte-storm/byte-storm-app)
[![Cobertura](https://img.shields.io/coveralls/github/byte-storm/byte-storm-app.svg?style=flat-square)](https://coveralls.io/github/byte-storm/byte-storm-app)
[![Todos los Contribuidores](https://img.shields.io/badge/all_contributors-73-orange.svg?style=flat-square)](./CONTRIBUTORS.md)
[![PRs Bienvenidos](https://img.shields.io/badge/PRs-bienvenidos-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)
[![Compatible con Commitizen](https://img.shields.io/badge/commitizen-compatible-brightgreen.svg?style=flat-square)](http://commitizen.github.io/cz-cli/)
[![Chat en Gitter](https://img.shields.io/badge/chat-en_gitter-008080.svg?style=flat-square)](https://gitter.im/byte-storm)

ByteStorm se embarca en una nueva era de innovación tecnológica. Desde su fundación en 2024, ByteStorm ha avanzado en la creación de soluciones prácticas y eficientes. Nos enorgullece presentar nuestra nueva aplicación de evaluación digital, diseñada para estudiantes y enfocada en una evaluación justa y precisa mediante inteligencia artificial. Esta plataforma garantiza la seguridad de los datos y la privacidad del usuario, ayudando a los estudiantes a alcanzar su máximo potencial de aprendizaje.

<p align="center">
  <img src="http://i.imgur.com/HowF6aM.png" width=350>
</p>

## Características

* Evaluación del desempeño estudiantil mediante IA
* Entorno seguro para todas las evaluaciones
* Protección de datos y privacidad de los usuarios
* Análisis en tiempo real sobre el progreso del estudiante
* Acceso a materiales interactivos y ejercicios de estudio

<p align="center">
  <img src="http://i.imgur.com/IkSnFRL.png" width=700>
</p>

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

Si tienes comentarios, sugerencias o encuentras algún problema, siéntete libre de contactarnos a través de [Twitter](https://twitter.com/byte-storm) o [abrir un issue](https://github.com/byte-storm/byte-storm-app/issues/new). ¡Las solicitudes de características siempre son bienvenidas! Si deseas contribuir, por favor revisa nuestras [guías de contribución](./CONTRIBUTING.md).

Si deseas discutir algo, únete a nuestro [chat en Gitter](https://gitter.im/byte-storm).

## Contribuidores

Este proyecto sigue la especificación de [all-contributors](https://github.com/kentcdodds/all-contributors) y es posible gracias a estos [increíbles contribuidores](./CONTRIBUTORS.md).

## Patrocinadores [![Patrocinadores en Open Collective](https://opencollective.com/byte-storm/sponsors/badge.svg)](#patrocinadores)

Apoya este proyecto convirtiéndote en patrocinador. Tu logo aparecerá aquí con un enlace a tu sitio web. [[Convertirse en patrocinador](https://opencollective.com/byte-storm#sponsor)]

<a href="https://opencollective.com/byte-storm/sponsor/0/website" target="_blank"><img src="https://opencollective.com/byte-storm/sponsor/0/avatar.svg"></a>
<a href="https://opencollective.com/byte-storm/sponsor/1/website" target="_blank"><img src="https://opencollective.com/byte-storm/sponsor/1/avatar.svg"></a>
<a href="https://opencollective.com/byte-storm/sponsor/2/website" target="_blank"><img src="https://opencollective.com/byte-storm/sponsor/2/avatar.svg"></a>

## Agradecimientos

Gracias a [JetBrains](https://www.jetbrains.com) por apoyarnos con una [licencia de código abierto gratuita](https://www.jetbrains.com/buy/opensource).
