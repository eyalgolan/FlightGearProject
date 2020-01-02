#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"

#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv) {
  char *input_file = argv[1];
  char *argv0 = argv[0];
  Lexer l(input_file);
  //openDataServer,5400,connectControlClient,"127.0.0.1,5402",varwarp->sim,"/sim/time/warp",varmagnetos->sim,"/controls/switches/magnetos",varthrottle->sim,"/controls/engines/current-engine/throttle",varmixture->sim,"/controls/engines/current-engine/mixture",varmasterbat->sim,"/controls/switches/master-bat",varmasterlat->sim,"/controls/switches/master-alt",varmasteravionics->sim,"/controls/switches/master-avionics",varbrakeparking->sim,"/sim/model/c172p/brake-parking",varprimer->sim,"/controls/engines/engine/primer",varstarter->sim,"/controls/switches/starter",varautostart->sim,"/engines/active-engine/auto-start",varbreaks->sim,"/controls/flight/speedbrake",varheading<-sim,"/instrumentation/heading-indicator/offset-deg",varairspeed<-sim,"/instrumentation/airspeed-indicator/indicated-speed-kt",varroll<-sim,"/instrumentation/attitude-indicator/indicated-roll-deg",varpitch<-sim,"/instrumentation/attitude-indicator/internal-pitch-deg",varrudder->sim,"/controls/flight/rudder",varaileron->sim,"/controls/flight/aileron",varelevator->sim,"/controls/flight/elevator",varalt<-sim,"/instrumentation/altimeter/indicated-altitude-ft",varrpm<-sim,"/engines/engine/rpm",Print,"waiting2minutesforgui",Sleep,120000,Print,"let'sstart",warp=32000,Sleep,1000,magnetos=3,throttle=0.2,mixture=0.949,masterbat=1,masterlat=1,masteravionics=1,brakeparking=0,primer=3,starter=1,autostart=1,Print,"engineiswarming...",Print,rpm,whilerpm<=750{,	Print,rpm,},Sleep,5000,Print,"let'sfly",varh0=heading,breaks=0,throttle=1,whilealt<1000{,	rudder=,h0-heading/80,	aileron=-roll/70,	elevator=pitch/50,	Sleep,250,},Print,"done", = heading,breaks = 0,throttle = 1,while alt < 1000 {,	rudder = ,h0 - heading /80,	aileron = -roll / 70,	elevator = pitch / 50,	Sleep,250 ,},Print,"done" ,
  //vector<string> emulateLexerResult = {"openDataServer","5400",
  //                                     "connectControlClient", "\"127.0.0.1,5402\"",
  //                                     "varwarp->sim", "\"/sim/time/warp\""};
  vector<string> emulateLexerResulttest=l.getvecor();
  vector<string> notspace;
  int i =0;
  SymbolTable &symblTbl = SymbolTable::getInstance();

  while ( i < emulateLexerResulttest.size()){

      string dammy=emulateLexerResulttest[i];
      if (dammy.compare("Print")==0){
          notspace.push_back(emulateLexerResulttest[i]);
          i++;
          notspace.push_back(emulateLexerResulttest[i]);
          i++;
      }
      else if (emulateLexerResulttest[i].compare("print")!=0){
          int start_pos = 0;
          while ((start_pos = emulateLexerResulttest[i].find(" ", start_pos)) != string::npos)
          {
              emulateLexerResulttest[i].replace(start_pos, 1, "");
              start_pos += 0; // Handles case where 'to' is a substring of 'from'
          }
          notspace.push_back(emulateLexerResulttest[i]);
          i++;
      }

  }
  Parser p(notspace);
  p.runCommands();

  return 0;

}