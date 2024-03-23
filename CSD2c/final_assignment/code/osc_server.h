/**********************************************************************
 *          Copyright (c) 2013, Hogeschool voor de Kunsten Utrecht
 *                      Hilversum, the Netherlands
 *                          All rights reserved
 ***********************************************************************
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.
 *  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 *
 *  File name     : osc_server.cpp
 *  System name   : osc++ : Open Sound Control
 *
 *  Description   : Demo program using C++ wrapper for liblo
 *
 *
 *  Author        : Marc_G
 *  E-mail        : marcg@dinkum.nl
 *
 **********************************************************************/

#include "osc.h"

#include <atomic>

// subclass OSC into a local class so we can provide our own callback
class localOSC : public OSC {
public:
  int realcallback(const char *path, const char *types, lo_arg **argv,
                   int argc) {
    string msgpath = path;

    cout << "path: " << msgpath << endl;
    if (!msgpath.compare("/sound")) {
      string paramname = (char *)argv[0];
      int int1 = argv[1]->i;
      int int2 = argv[2]->i;

      // assign incoming value to OSC field
      oscValue = int1;

      /* cout << "Message: " << paramname << " " << int1 << " " << int2 << " "
           << endl; */
    } // if

    return 0;
  } // realcallback()

  void runServer() {
    int done = 0;
    localOSC osc;
    string serverport = "7777";

    osc.init(serverport);

    osc.set_callback("/sound", "siii");

    osc.start();
    cout << "Listening on port " << serverport << endl;

    while (!done) {
      usleep(1000);
    }
  }

  int getOscValue() { return oscValue.load(); }

  std::atomic<int> oscValue = 0;
};
