# QLogueLibrarian

**Author:** David Emmanuel Lopez

A minimal cross-platform GUI wrapper for KORG logue-sdk/logue-cli tools, built with **Qt6** and **CMake**. It wraps the official [`logue-cli`](https://github.com/korginc/logue-sdk/tree/main/tools/logue-cli) command-line tool to provide a graphical interface for probing MIDI ports and uploading custom oscillator/effect units to your device.

---

## Motivation

- **No Linux GUI exists.** Korg Sound Librarian is a Windows-only application. There is no official (or unofficial) equivalent for Linux users.
- **MIDI just works on Linux.** Korg's USB-MIDI drivers are notoriously problematic on Windows (driver conflicts, unsigned driver warnings, etc.). On Linux, logue-series devices are recognized out-of-the-box as standard ALSA MIDI devices — no driver installation required.

## Current Features

| Feature | Description |
|---|---|
| **Probe MIDI ports** | Runs `logue-cli probe -l`, parses the output and populates In/Out port selectors. Ports containing `SOUND` are auto-selected (these are the correct SysEx ports for prologue / minilogue xd). |
| **Upload unit files** | Lets you browse for a `.prlgunit`, `.mnlgxdunit`, `.ntkdigunit` (or other logue unit format), then runs `logue-cli load -u <file> -i <in> -o <out>`. Parses the output to determine success (platform, module, CRC32). |
| **Persistent settings** | The path to the `logue-cli` executable is saved via `QSettings` and restored on next launch. |
| **Live log** | All `logue-cli` stdout/stderr output is shown in a log panel inside the application. |

## Project Structure

```
src/
├── main.cpp                         # Application entry point
├── model/
│   └── KorgEnums.h                  # Unit file extension filters
├── controller/
│   └── LogueCLIWrapper.h/.cpp       # QProcess wrapper for logue-cli
└── view/
    └── MainWindow.h/.cpp            # Qt GUI (probe + load)
```

## Prerequisites

### Build Dependencies

| Package | Minimum Version |
|---|---|
| CMake | 3.20 |
| GCC (or Clang) | GCC 9+ / Clang 10+ (C++17) |
| Qt6 (Core, Widgets) | 6.2 |

**Debian / Ubuntu:**

```bash
sudo apt install build-essential cmake qt6-base-dev
```

**Fedora:**

```bash
sudo dnf install gcc-c++ cmake qt6-qtbase-devel
```

**Arch Linux:**

```bash
sudo pacman -S base-devel cmake qt6-base
```

### Installing logue-cli

`logue-cli` is the official Korg command-line utility for communicating with logue-series devices. It is **not** included in this repository — you need to download it separately.

**Linux (automatic):**

```bash
git clone https://github.com/korginc/logue-sdk.git
cd logue-sdk/tools/logue-cli
./get_logue_cli_linux.sh
```

This downloads and unpacks `logue-cli` into `logue-sdk/tools/logue-cli/logue-cli-linux64-0.07-2b/`.

**macOS:**

```bash
cd logue-sdk/tools/logue-cli
./get_logue_cli_osx.sh
```

**Windows (MSYS2):**

```bash
cd logue-sdk/tools/logue-cli
./get_logue_cli_msys.sh
```

For manual Windows downloads, see the [official logue-cli README](https://github.com/korginc/logue-sdk/blob/main/tools/logue-cli/README.md).

Once installed, point the application to the `logue-cli` executable using the path field at the top of the window. The path is remembered between sessions.

## Building & Running

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/QLogueLibrarian
```

## Disclaimer

**This project is not affiliated with, endorsed by, or related to KORG Inc. in any way.** It is an independent, open-source GUI that acts as a wrapper around the officially published `logue-cli` tool.

> ⚠️ **Important licensing note:** `logue-cli` is a **proprietary binary** distributed by KORG under its own End User License Agreement (EULA). It is **not** open-source and is **not** covered by the BSD 3-Clause license of the [logue-sdk](https://github.com/korginc/logue-sdk) source code. This project does not bundle, redistribute, or modify `logue-cli` in any way — it only invokes it as an external process. You must obtain `logue-cli` directly from KORG and comply with their EULA when using it.

All product names and trademarks mentioned are the property of their respective owners.

## License

This project is licensed under the **GNU General Public License v3.0**. See [LICENSE](LICENSE) for details.

---
---

# QLogueLibrarian (Español)

**Autor:** David Emmanuel Lopez

Interfaz gráfica minimalista y multiplataforma que actúa como wrapper de las herramientas KORG logue-sdk/logue-cli, construida con **Qt6** y **CMake**. Funciona como wrapper de la herramienta oficial [`logue-cli`](https://github.com/korginc/logue-sdk/tree/main/tools/logue-cli).

---

## Motivación

- **No existe una GUI similar a Korg Sound Librarian para Linux.** La aplicación oficial de Korg es exclusiva de Windows. No hay alternativa gráfica oficial ni de terceros para usuarios de Linux.
- **Los drivers MIDI de Korg son conflictivos en Windows.** En Linux, los dispositivos de la serie logue son reconocidos automáticamente como dispositivos ALSA MIDI estándar, sin necesidad de instalar drivers.

## Funcionalidad Actual

| Función | Descripción |
|---|---|
| **Detección de puertos MIDI** | Ejecuta `logue-cli probe -l`, parsea la salida y llena los selectores de puertos In/Out. Los puertos que contienen `SOUND` se seleccionan automáticamente (son los puertos SysEx correctos para prologue / minilogue xd). |
| **Subida de archivos unit** | Permite seleccionar un archivo `.prlgunit`, `.mnlgxdunit`, `.ntkdigunit` (u otro formato logue), luego ejecuta `logue-cli load -u <archivo> -i <in> -o <out>`. Parsea la salida para determinar éxito (plataforma, módulo, CRC32). |
| **Configuración persistente** | La ruta al ejecutable `logue-cli` se guarda con `QSettings` y se restaura al reiniciar la aplicación. |
| **Log en vivo** | Toda la salida stdout/stderr de `logue-cli` se muestra en un panel de log dentro de la aplicación. |

## Estructura del Proyecto

```
src/
├── main.cpp                         # Punto de entrada
├── model/
│   └── KorgEnums.h                  # Filtros de extensiones de archivos unit
├── controller/
│   └── LogueCLIWrapper.h/.cpp       # Wrapper de QProcess para logue-cli
└── view/
    └── MainWindow.h/.cpp            # GUI Qt (probe + load)
```

## Requisitos

### Dependencias de Compilación

| Paquete | Versión Mínima |
|---|---|
| CMake | 3.20 |
| GCC (o Clang) | GCC 9+ / Clang 10+ (C++17) |
| Qt6 (Core, Widgets) | 6.2 |

**Debian / Ubuntu:**

```bash
sudo apt install build-essential cmake qt6-base-dev
```

**Fedora:**

```bash
sudo dnf install gcc-c++ cmake qt6-qtbase-devel
```

**Arch Linux:**

```bash
sudo pacman -S base-devel cmake qt6-base
```

### Instalación de logue-cli

`logue-cli` es la utilidad oficial de línea de comandos de Korg para comunicarse con dispositivos de la serie logue. **No está incluida** en este repositorio — hay que descargarla por separado.

**Linux (automático):**

```bash
git clone https://github.com/korginc/logue-sdk.git
cd logue-sdk/tools/logue-cli
./get_logue_cli_linux.sh
```

Esto descarga y descomprime `logue-cli` en `logue-sdk/tools/logue-cli/logue-cli-linux64-0.07-2b/`.

**macOS:**

```bash
cd logue-sdk/tools/logue-cli
./get_logue_cli_osx.sh
```

**Windows (MSYS2):**

```bash
cd logue-sdk/tools/logue-cli
./get_logue_cli_msys.sh
```

Para descargas manuales en Windows, ver el [README oficial de logue-cli](https://github.com/korginc/logue-sdk/blob/main/tools/logue-cli/README.md).

Una vez instalado, configurá la ruta al ejecutable `logue-cli` en el campo de la parte superior de la ventana. La ruta se recuerda entre sesiones.

## Compilación y Ejecución

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/QLogueLibrarian
```

## Aviso Legal (Disclaimer)

**Este proyecto no está afiliado, respaldado ni relacionado con KORG Inc. de ninguna manera.** Es una GUI independiente y de código abierto que funciona como wrapper de la herramienta `logue-cli` publicada oficialmente por KORG.

> ⚠️ **Nota importante sobre licencias:** `logue-cli` es un **binario propietario** distribuido por KORG bajo su propio Acuerdo de Licencia de Usuario Final (EULA). **No es** software de código abierto y **no está** cubierto por la licencia BSD 3-Clause del código fuente del [logue-sdk](https://github.com/korginc/logue-sdk). Este proyecto no incluye, redistribuye ni modifica `logue-cli` de ninguna manera — únicamente lo invoca como proceso externo. Debés obtener `logue-cli` directamente de KORG y cumplir con su EULA al utilizarlo.

Todos los nombres de productos y marcas registradas mencionados son propiedad de sus respectivos dueños.

## Licencia

Este proyecto está licenciado bajo la **GNU General Public License v3.0**. Ver [LICENSE](LICENSE) para más detalles.
