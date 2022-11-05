# Embedded device utilities in C
Utility libraries for embedded devices written in C. Easily portable to any device.

## Concept
Each utility (buttons, lcd, ...) is split on two parts: implementation part (portable logic) and user part (MCU or user specific handlers). For example (buttons):
* _buttons.h, buttons.c_: logic that determines if button events should be generated (call user callbacks). User does not need to modify these files as there is no MCU-specific code (as long as library behaviour must not be changed).  
* _buttons_user.h, buttons_user.c_: user implementation of low level GPIO read (MCU specific) and button events callback functions.  

# Buttons  
_buttons.h, buttons.c, buttons_user.h, buttons_user.c_  
This is a generic button handling library that supports:
* debouncing and event generation
* select key press mode: single press, repetitive presses, single/long press
* callback functions based on button event&mode
* generic code, that is easily portable on any device
* simple API that does not require interrupts or special timers (rely on systick/generic millisecond timer):
    * user need to add only low layer function call to get GPIO state
    * register new button with `btn_register()`
    * handle buttons with `btn_handle()`
    * handle events in functions: `btn_on_press()` and `btn_on_longpress()` in user-specific files

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

# LCD
_lcd.h, lcd.c, lcd\_user.h, lcd\_user.c_  
This is a generic LCD HD44780-based library that supports:
* printing strings
* printing numbers (integers, floats)
* printing strings in a specific window (optional scrolling)
* creating and printing custom characters
* controlling of LCD settings like: display on/off, cursor blinking on/off, scrolling, clearing

# Rotary encoder
_rot\_enc.h, rot\_enc.c, rot\_enc\_user.h, rot\_enc\_user.c_  
This is a generic, single-interrupt based library to handle basic three-pin (2 GPIO + common pin) rotary encoder.
Library supports: 
* reading difference from the last read (last `get` function call)
* reading absolute value from the last `reset` action
* setting count direction
* reset count value
NOTE: User must manually implement interrupt routine (and set irq priority) on rising & falling edge on one rotary encoder pin, and call `rot_enc_update()` function. 
This ensure library to register all rotary encoder interactions, and properly debounce any glitches so that the count is a valid number.

## Examples (STM32)
See examples in [SunAlarm](https://github.com/damogranlabs/SunAlarm) and [STM32 USB Shortcutter (programable keys) project](https://github.com/damogranlabs/USB-Shortcutter-based-on-STM32-and-AHK-script). 
