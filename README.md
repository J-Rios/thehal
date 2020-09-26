
# TheHAL

Universal Hardware Abstraction Layer to unify embedded development through an unique API for different kind of devices (AVR, PIC, SAM, STM, etc.) and frameworks (Arduino, Mbed, ASF, ESP-IDF, etc.).

## Characteristics

- **Structured:** The project must keep a clean and simple structure to avoid innecesary complexity that could affect the maintenanance.

- **Modular:** The project must keep a modular structure to isolate each supported functionality using different *components* that allows implements new characteristics

- **Normalized:** To keep the code readable and easy to maintain across multiple developers, it must share the same code style and structure between files.

- **Simplicity:** Code must be written simple and easy to understand, avoid long functions and keep hardware access just at the lowest functions of each component.

- **Maintenable:** Be compliant with all previous characteristics should make the project to be simple, easy to understand, modify, add new functionalities and be maintainable.

## Code Style

- **End of lines:** LF

- **Identation:** 4 spaces

- **Maximum number of characters per line:** 79

- **Maximum number of lines in each function:** 50
