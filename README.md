# Embedded device utilities in C
Utility libraries for embedded devices written in C. Easily portable to any device.

# Buttons  
_buttons.h, buttons.c, buttons_user.h, buttons_user.c_  
This is a generic button handling library that supports:
* debouncing and event generation
* select key press mode: single press, repetitive presses, single/long press
* callback functions based on button event&mode
* generic code, that is easily portable on any device
* simple API that does not require interrupts or special timers (rely on systick/generic millisecond timer):
    * user need to add only low layer function call to get GPIO state
    * register new button with `register_button()`
    * handle buttons with `handle_buttons()`
    * handle events in functions: `on_button_press()` and `on_button_longpress()` in user-specific files

# Ring buffer  
_ring_buffer.h, ring_buffer.c_  
This is a FIFO (ring) buffer to store data, with simple API that allow user to:
* put number of bytes into the buffer
* get number of bytes from the buffer
* check buffer size, state and free space
* handle error checking by returning status

# UART print
_uart_print.h, uart_print.c, uart_print_user.h, uart_print_user.c_  
This is an Arduino-inspired library for embedded devices, that allows user to send printable data over UART with simple API.
* numbers (signed/unsigned integers, floats) with selective base (DEC, BIN, HEX, OCT)
* strings
* new-line characters
* User only need to implement UART 'send byte(s)' low layer call, while formatting is done by this library.

## Examples (STM32)
See examples in [STM32 USB Shortcutter project](https://github.com/damogranlabs/USB-Shortcutter-based-on-STM32-and-AHK-script). 
