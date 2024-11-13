# -->> BYTESTORM TM <<--

### English

#### Application Overview

This application creates a fullscreen window with a modern, elegant font displaying the text "Funciona". The window remains on top of all other windows and prevents switching between windows. The application also blocks certain key combinations to ensure that the window remains the primary focus.

#### Key Features

- **Fullscreen Window**: The application opens a window that occupies the entire screen.
- **Text Display**: Shows the text "Funciona" in a modern font, centered on the screen.
- **Key Blocking**: Blocks the Windows key, `Alt+Tab`, and `Ctrl+Esc` to prevent window switching.
- **Close with Q**: The only way to close the window is by pressing the `Q` key.
- **Explorer.exe Management**: Closes `explorer.exe` when the application starts and restarts it when the application closes.

#### How It Works

1. **Initialization**: The application initializes GDI+ for graphics rendering.
2. **Window Creation**: A fullscreen window is created with the `WS_POPUP` style to avoid borders.
3. **Keyboard Hook**: Sets a global keyboard hook to intercept and block specific key combinations.
4. **Text Rendering**: Uses GDI+ to draw the text "Funciona" on the window.
5. **Explorer Management**: Executes system commands to close and restart `explorer.exe`.
6. **Message Loop**: Runs a message loop to handle user input and maintain the window state.

##### Compilation and Execution

1. **Compile**: Use a C++ compiler that supports Windows API and GDI+.
2. **Run**: Execute the compiled binary. The application will take control of the screen until `Q` is pressed.

---

### Español

#### Descripción de la Aplicación

Esta aplicación crea una ventana a pantalla completa con una fuente moderna y elegante que muestra el texto "Funciona". La ventana permanece encima de todas las demás ventanas y evita el cambio entre ventanas. La aplicación también bloquea ciertas combinaciones de teclas para asegurar que la ventana siga siendo la principal.

#### Características Principales

- **Ventana a Pantalla Completa**: La aplicación abre una ventana que ocupa toda la pantalla.
- **Visualización de Texto**: Muestra el texto "Funciona" en una fuente moderna, centrada en la pantalla.
- **Bloqueo de Teclas**: Bloquea la tecla de Windows, `Alt+Tab` y `Ctrl+Esc` para evitar el cambio de ventanas.
- **Cerrar con Q**: La única forma de cerrar la ventana es presionando la tecla `Q`.
- **Gestión de Explorer.exe**: Cierra `explorer.exe` al iniciar la aplicación y lo reinicia cuando se cierra la aplicación.

#### Funcionamiento

1. **Inicialización**: La aplicación inicializa GDI+ para el renderizado gráfico.
2. **Creación de la Ventana**: Se crea una ventana a pantalla completa con el estilo `WS_POPUP` para evitar bordes.
3. **Hook de Teclado**: Establece un hook global de teclado para interceptar y bloquear combinaciones de teclas específicas.
4. **Renderizado de Texto**: Utiliza GDI+ para dibujar el texto "Funciona" en la ventana.
5. **Gestión de Explorer**: Ejecuta comandos del sistema para cerrar y reiniciar `explorer.exe`.
6. **Bucle de Mensajes**: Ejecuta un bucle de mensajes para manejar la entrada del usuario y mantener el estado de la ventana.

#### Compilación y Ejecución

1. **Compilar**: Utiliza un compilador C++ que soporte la API de Windows y GDI+.
2. **Ejecutar**: Ejecuta el binario compilado. La aplicación tomará control de la pantalla hasta que se presione `Q`.
