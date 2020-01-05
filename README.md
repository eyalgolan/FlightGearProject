# FlightGearProject

## Preview
An interpreter that runs an autopilot for the **FlightGear** simulator
 (You can learn more about FlightGear [here](https://www.flightgear.org/ "FlightGear Homepage")).

The program gets a script as an argument which contains different commands and
interprets the commands. First, the program lexes the input file, then it parses 
it and finally it executes the commands.

This project includes the following elements:
* Design Patters
* Client-Server architecture
* Usage of data structures
* Working with files
* Working with threads

## Setup
First, in order to set the FlightGear simulator to connect to our server and 
accept a connection from our client, go to `Settings` -> `Additional Settings` 
and add:
```
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
‪--telnet=socket,in,10,127.0.0.1,5402,tcp‬
```
Note that:
 
 * `--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small` means that
 the simulator will try to send flight input to IP `127.0.0.1` in port `5400`, 
 by the format of `generic_small.xml`.
 * `‪--telnet=socket,in,10,127.0.0.1,5402,tcp‬` means that the simulator will try
 to receive flight instructions in IP `127.0.0.1` and port `5402`.
 
Then, in order to compile our program, `cd` to the folder to which you downloaded
 the project. Run:
```
g++ -std=c++11 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```
Then, run the program with the script of commands: (for example, if the script
 name is `fly.txt`)
```
./a.out fly.txt
```
**Note** that the script file needs to reside in the **SAME FOLDER** in which you 
compiled the project.

## Program explanation:
### Commands

1. **openDataServer**: Receives a port number and opens a server in another thread,
 which listens in that port. The simulator connects to the server and sends it
  flight data. 
  
  	For example:
  	```
  	openDataServer(5400)
  	```
  	Will open a server thread that will listen for information from the 
  	simulator in port `5400`.
2. **connectControlClient**: Receives the simulator's port number and an IP address, 
and opens a thread that connects to it. The thread gets flight instructions from
 the program and sends them to the simulator.
 	
 	For example:
 	```
 	connectControlClient("127.0.0.1",5402)
 	```
 	Will open a client thread that will try to connect to the simulator in IP
 	 `127.0.0.1` and port `5402`.
3. **Sleep**: Receives a numeric value and pauses the execution of new commands
 from the script for the time received.
 	
 	For example:
 	```
 	Sleep(5000)
 	```
 	Will Pause the program from executing new commands from the script, for 
 	`5000` milliseconds (5 seconds).
4. **Print**: Receives a numeric, string or var (more about variables in the 
*"Working with variables"* section) input and prints it to the 
console.

	For example:
	```
	Print(5000)
	```
	Will print `5000` to the console.

### Working with variables
We work with variables in the following ways:
1. Defining a new variable: A new var can be set with:
	* A value, for example:
		```
		var rudder = 0
		```
	* A simulator path with a side indicator:
		```
		var heading <- sim("/instrumentation/heading-indicator/offset-deg")
		```
	* Another existing variable:
		```
		var h0 = heading
		```
2. Setting an existing variable with a value, by value or by variable:
	```
	magnetos = 3
	```
	Or:
	```
	magnetos = rudder
	```
### Conditions and Loops
The script we interpret can contain `if` condition and `while` loops:
* In the case of an `if` condition, the program will execute the commands in the
 `if`'s scope, if it's condition is met.
* In the case of a `while` loop, the program will loop over the commands in the
 `while`'s scope, while it's condition is met.

### Program architecture
The program contains the following classes:
1. Lexer: The lexer gets a filename. The script in the file is written in a new 
          programing language that we need to interpret.
          The role of the lexer is to seperate the code by commas and build then into a
          vector.
2. Parser: Runs each command in the input vector and executes it.
5. SymbolTable: A singelton class. The symbol table maintains the current state 
of the plane, the current values of all the variables defined in the program, 
and a mutex used for controlling the threads access to the symbol table.
3. Command: A parent class, containing a virtual `exec` function. 

	Each of the following inheriting classes implement their own version of the
	 `exec` function:
	* OpenServerCommand
	* ConnectCommand
	* DefineVarCommand
	* setVarCommand
	* AssignVarCommand
	* IfCommand
	* LoopCommand
	* SleepCommand
	* PrintCommand
4. ConditionParser: Used by the `IfCommand` and `LoopCommand` to checks if a 
	provided condition is satisfied and updates accordingly.
5. ExpressionHandler: Interprets nested mathematical expressions that include 
	variables and evaluate them.

