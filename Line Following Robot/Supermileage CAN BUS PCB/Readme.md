## This is a Folder for the Description of my Can Bus PCB
In the 2018/2019 winter session, I have had the priveledge of working in UBC's Supermileage team to design a multipurpose PCB to
communicate over the CAN BUS communiaction protocol.\
The purpose of this project was to the wiring complexity on their Urban vehicle and reduce the overall vehicle weight.\
The PCB was designed using the Altium software suite.\
The PCB consists of a MCP2515 CAN controller and CAN tranceiver connected to a Texas Instruments MSP 430 G2553 microcontroller.\
The microcontroller communicates with the CAN controller via SPI communications, and the CAN controller with the tranceiver via UART.\
The primary immediate purpose of this PCB is to interperet CAN BUS signals from the steering wheel to control headlights.
The microcontroller has a total of four GPIO pins attached to opto-isolators and MOSFETs. 
These opto-isolators can then be connected to the headlight circuitry to supply and remove power.\
