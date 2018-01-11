# explorer16
Samples for Explorer 16 Development Board of Microchip

| Project Name     | Short description | [1] | [2] |
| ---------------- | ----------------- | :-: | :-: |
| [D10OnOffS3](D10OnOffS3.X/) | Switch on D10 LED by pressing and holding S3 switch button, LED is switched off when it's not pressed. | x | x |
| [D10ToggleTimer1](D10ToggleTimer1.X/) | Toggle switch on/off the D10 LED using Timer1 Interrupt at 1Hz. | x | x |
| [LEDsOnOffS3](LEDsOnOffS3.X/)| Switch on D3:D10 LEDs by pressing and holding S3 switch button, LED is switched off when it's not pressed. | x | x |
| [LEDsToggleTimer1](LEDsToggleTimer1.X/) | Toggle switch on/off the D3:D10 LEDs using Timer1 Interrupt at 1Hz. | x | x |

[1] PIC24FJ128GA010,[2] dsPIC33FJ256GP710A

## Requirements

###### Software
- [MPLAB X IDE](http://www.microchip.com/mplab/mplab-x-ide) is a software program that runs on a PC (Windows®, Mac OS®, Linux®), supports project management, code editing, debugging and programming of Microchip microcontrollers.
- [MPLAB XC16](http://www.microchip.com/mplab/compilers) is a C compiler for 16-bit PIC devices.

###### Hardware
- Explorer 16 Development Board with ICD3 Bundle, [Part Number: DV164037](http://www.microchip.com/developmenttools/ProductDetails.aspx?PartNO=DV164037)

<img src="http://www.microchip.com/_ImagedCopy/DV164037.jpg" width="640">

or

- Development Board:
    - Explorer 16 Development Board with 100-pin PIM, Part Number: [DM240001](http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM240001) or
    - Explorer 16/32 Development Board, Part Number: [DM240001-2](http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=DM240001-2)
- Supported Processor Plug-In Modules (PIMs):
    - dsPIC33FJ256GP710A Plug-In-Module [Part Number: MA330011](http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=MA330011)
    - PIC24FJ128GA010 Plug-In-Module [Part Number: MA240011](http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=MA240011)
- 9V power supply, Part Number: AC162039, AC002014
- Hardware debugger/programmer: MPLAB REAL ICE, MPLAB ICD or PICkit
