/*
  This file is part of the DSP-Crowd project
  https://www.dsp-crowd.com

  Author(s):
      - Johannes Natter, office@dsp-crowd.com

  File created on 02.06.2017

  Copyright (C) 2017 Authors and www.dsp-crowd.com

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <string>
#include <iostream>
#include <algorithm>
#include <tclap/CmdLine.h>
#include "DspcHello.h"
#include "config.h"
#include "hal.h"

using namespace std;

// http://tclap.sourceforge.net/

DspcHello::DspcHello() {

}

DspcHello::~DspcHello() {

}

int DspcHello::exec(int argc, char *argv[]) {

	cout << "Hello World!" << endl;
	cout << "This is " << PACKAGE_STRING << endl;

	try {
		TCLAP::CmdLine cmd("Command description message", ' ', VERSION);

		TCLAP::ValueArg<string> nameArg("n","name","Name to print",true,"homer","string");
		cmd.add( nameArg );

		TCLAP::SwitchArg reverseSwitch("r","reverse","Print name backwards", cmd, false);

		cmd.parse( argc, argv );

		string name = nameArg.getValue();
		bool reverseName = reverseSwitch.getValue();

		// Do what you intend
		if ( reverseName )
		{
			reverse(name.begin(),name.end());
			cout << "My name (spelled backwards) is: " << name << endl;
		}
		else
			cout << "My name is: " << name << endl;

	} catch (TCLAP::ArgException &tclapE) {
		cerr << "error: " << tclapE.error() << " for arg " << tclapE.argId() << endl;
	}

	return 0;
}

