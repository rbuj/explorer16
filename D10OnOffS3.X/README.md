# D10OnOffS3
## Description
Switch on D10 LED by pressing and holding S3 switch button, LED is switched off when it's not pressed.

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
| LED | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --- | :----------------: | :-------------: | :-----------: |
| D3  | RA0                | RA0             |               |
| D4  | RA1                | RA1             |               |
| D5  | RA2                | RA2             |               |
| D6  | RA3                | RA3             |               |
| D7  | RA4                | RA4             |               |
| D8  | RA5                | RA5             |               |
| D9  | RA6                | RA6             |               |
| D10 | RA7                | RA7             | S5            |

###### Push button switches
| Push button switch    | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| --------------------- | :----------------: | :-------------: | :-----------: |
| S3: Active-low switch | RD6                | RD6             |               |
| S4: Active-low switch | RD13               | RD13            |               |
| S5: Active-low switch | RA7                | RA7             | D10           |
| S6: Active-low switch | RD7                | RD7             |               |

###### ADC
| Analog Input       | dsPIC33FJ256GP710A | PIC24FJ128GA010 | Overlaps with |
| ------------------ | :----------------: | :-------------: | :-----------: |
| Potentiometer      | RB5/AN5            | RB5/AN5         |               |
| Temperature sensor | RB4/AN4            | RB4/AN4         |               |
