# FlightGearProject

An interpreter that allows autopilot FlightGear simulator. the program gets a script as an argument which contains different commands.

The program first lexes the script, then parses it and execute each command.
The first command open a server in another thread. The simulator connects to the
server and sends it flight data.
The second command opens a client which connects to the simulator and sends it
flight commands.
With the script, the programs sends commands to the simulator and autopilot and airplane