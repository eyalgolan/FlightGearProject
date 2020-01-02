cmake_minimum_required(VERSION 3.12)
project(FlightGearProject)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 11)

add_executable(FlightGearProject main.cpp main.h Lexer.cpp Lexer.h Parser.cpp Parser.h Command.cpp Command.h OpenServerCommand.cpp OpenServerCommand.h ConnectCommand.cpp ConnectCommand.h DefineVarCommand.cpp DefineVarCommand.h ConditionParser.cpp ConditionParser.h IfCommand.cpp IfCommand.h LoopCommand.cpp LoopCommand.h SymbolTable.cpp SymbolTable.h SetVarCommand.cpp SetVarCommand.h AssignVarCommand.cpp AssignVarCommand.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h LoopCommand.h ExpressionHandler.cpp ExpressionHandler.h Expression.h ExpressionHandler.cpp ExpressionHandler.h)