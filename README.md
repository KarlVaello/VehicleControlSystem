#Vehicle Control System

Electronic control units:

- CCU Central Control Unit
	- CCU Cluster Control Unit
	- CCU Central Control Unit

- ECU Engine Control Unit

![Alt text](VCS_WiringDiagram.png?raw=true "Wiring Diagram")



###SCREENSHOTS

![Alt text](/Screenshots/cluster.PNG?raw=true "Wiring Diagram")


##CCU - Central Control Unit

### TO DO (Software):

- [ ] CAN Bus 

- [ ] Warning and errors (UI whill show an icon when something fails and a message that explain de fail)
	Warning and error are separated classes, every new error or warning is a new object. They will be store and we will be able to access to warnings and errors independtly.

	Errors:
	- [ ] CAN Bus error, some devicer not respond or is missing, depends of the missing devices it will show error or warning icon.
	- [ ] P-Brake  error
	- [ ] Spoiler error


	Warnings:
	- [ ] Battery warning

### TO DO (Hardware):

- [ ] Planning


## ECU (Engine Control Unit)
It will control electric motor, speed. This ECU in conected via CAN Bus the other devices

- [ ]  Hardaware. 
