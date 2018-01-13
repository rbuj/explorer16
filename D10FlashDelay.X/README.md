# D10FlashDelay
## Description
Flash LED D10 using __delay_ms(d) macro.

## Usage
- Set up the Developmnent Board:
    - Unplug the 9V power supply and the programmer from the development board.
    - Plug PIM to the development board.
    - Set switch S2 to PIM position.
    - Install the jumper JP2 to enable the LEDs.
    - Plug the 9V power supply and the programmer to the development board.
- Set up the project:
    - Open MPLAB X IDE.
    - Select "File -> Open Project..." from the MPLAB X IDE menu.
    - Select the project and click on "Open Project"
    - Right click on project name, select "Set configuration" and select the installed PIM.
- Run the project:
    - Right click on project name, select "Run"

## Pinout
###### Indicator LEDs
| LED | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with | U   | I   |
| --- | :----------------: | :-------------: | :-----------: | :-: | :-: |
| D3  | RA0                | RA0             |               |     | x   |
| D4  | RA1                | RA1             |               |     | x   |
| D5  | RA2                | RA2             |               |     | x   |
| D6  | RA3                | RA3             |               |     | x   |
| D7  | RA4                | RA4             |               |     | x   |
| D8  | RA5                | RA5             |               |     | x   |
| D9  | RA6                | RA6             |               |     | x   |
| D10 | RA7                | RA7             | S5            | x   | x   |

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
