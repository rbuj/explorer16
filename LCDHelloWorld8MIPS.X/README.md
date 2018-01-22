# LCDHelloWorld8MIPS
## Description
Print a message in the LCD Display

## Usage
- Set up the Developmnent Board:
    - Unplug the 9V power supply and the programmer from the development board.
    - Plug PIM to the development board.
    - Set switch S2 to PIM position.
    - Remove the jumper JP2 to disable the LEDs.
    - Plug the 9V power supply and the programmer to the development board.
- Set up the project:
    - Open MPLAB X IDE.
    - Select "File -> Open Project..." from the MPLAB X IDE menu.
    - Select the project and click on "Open Project"
    - Right click on project name, select "Set configuration" and select the installed PIM.
- Run the project:
    - Right click on project name, select "Run"

## Pinout
###### 16x2 LCD Display
| LCD | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with | U   | I   |
| --- | :----------------: | :-------------: | :-----------: | :-: | :-: |
| E   | RD4                | PMWR            |               | x   | x   |
| R/W | RD5                | PMRD            |               | x   | x   |
| RS  | RB15               | PMAO            |               | x   | x   |
| DB0 | RE0                | PMD0            |               | x   | x   |
| DB1 | RE1                | PMD1            |               | x   | x   |
| DB2 | RE2                | PMD2            |               | x   | x   |
| DB3 | RE3                | PMD3            |               | x   | x   |
| DB4 | RE4                | PMD4            |               | x   | x   |
| DB5 | RE5                | PMD5            |               | x   | x   |
| DB6 | RE6                | PMD6            |               | x   | x   |
| DB7 | RE7                | PMD7            |               | x   | x   |

*U: Used, I: Implemented*

###### ADC
| Analog Input       | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with | U   | I   |
| ------------------ | :----------------: | :-------------: | :-----------: | :-: | :-: |
| Potentiometer      | AN5/RB5            | AN5/RB5         |               |     |     |
| Temperature sensor | AN4/RB4            | AN4/RB4         |               |     |     |

*U: Used, I: Implemented*

###### Oscillators
| Oscillator                  | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with | U   | I   |
| --------------------------- | :----------------: | :-------------: | :-----------: | :-: | :-: |
| Primary: 8 MHz crystal (Y3) | OSC1/RC12          | OSC1/RC12       |               | x   | x   |
| Primary: 8 MHz crystal (Y3) | OSC2/RC15          | OSC2/RC15       |               | x   | x   |

*U: Used, I: Implemented*

###### MPLAB ICD programmer/debugger module
| ICD Pin   | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with | U   | I   |
| --------- | :----------------: | :-------------: | :-----------: | :-: | :-: |
| Vpp/!MCLR | !MCLR              | !MCLR           |               | x   | x   |
| PGD       | PGED1/RB7          | PGED1/RB7       |               | x   | x   |
| PGC       | PGEC1/RB6          | PGEC1/RB6       |               | x   | x   |

*U: Used, I: Implemented*
