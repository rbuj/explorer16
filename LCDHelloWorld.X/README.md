# D10OnOffS3
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
| LCD | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --- | :----------------: | :-------------: | :-----------: |
| E   | RD4                | PMWR            |               |
| R/W | RD5                | PMRD            |               |
| RS  | RB15               | PMAO            |               |
| DB0 | RE0                | PMD0            |               |
| DB1 | RE1                | PMD1            |               |
| DB2 | RE2                | PMD2            |               |
| DB3 | RE3                | PMD3            |               |
| DB4 | RE4                | PMD4            |               |
| DB5 | RE5                | PMD5            |               |
| DB6 | RE6                | PMD6            |               |
| DB7 | RE7                | PMD7            |               |

###### ADC
| Analog Input       | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| ------------------ | :----------------: | :-------------: | :-----------: |
| Potentiometer      | AN5/RB5            | AN5/RB5         |               |
| Temperature sensor | AN4/RB4            | AN4/RB4         |               |

###### Oscillators
| Oscillator                  | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --------------------------- | :----------------: | :-------------: | :-----------: |
| Primary: 8 MHz crystal (Y3) | OSC1/RC12          | OSC1/RC12       |               |
| Primary: 8 MHz crystal (Y3) | OSC2/RC15          | OSC2/RC15       |               |

###### MPLAB ICD programmer/debugger module
| ICD Pin   | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --------- | :----------------: | :-------------: | :-----------: |
| Vpp/!MCLR | !MCLR              | !MCLR           |               |
| PGD       | PGED1/RB7          | PGED1/RB7       |               |
| PGC       | PGEC1/RB6          | PGEC1/RB6       |               |
