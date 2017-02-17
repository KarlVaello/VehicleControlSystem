#Vehicle Electronic Control System

Electronic control units:

- CCU Cluster Control Unit
- ECU Engine Control Unit


##DRIVER DASH

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


##MAIN ECU
It will control electric motor, speed. This ECU in conected via CAN Bus the other devices

- [ ]  Hardaware. 
