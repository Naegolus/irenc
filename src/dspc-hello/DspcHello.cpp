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
using namespace TCLAP;

// http://tclap.sourceforge.net/
class MyOutput : public StdOutput
{
public:
	virtual void usage(CmdLineInterface& c)
	{
		list<Arg*> argList = c.getArgList();
		string message = c.getMessage();
		XorHandler xorHandler = c.getXorHandler();
		vector< vector<Arg*> > xorList = xorHandler.getXorList();

		cout << PACKAGE << " " << VERSION << endl << endl;

		cout << "Send arbitrary data bytes via infrared on the Raspberry Pi" << endl << endl;

		cout  << "usage:";
		_shortUsage(c, cout);
		cout << endl << endl << "Options: " << endl << endl;

		// first the xor
		for(int i = 0; static_cast<unsigned int>(i) < xorList.size(); i++)
		{
			for(ArgVectorIterator it = xorList[i].begin(); it != xorList[i].end(); it++)
			{
				spacePrint(cout, (*it)->longID(), 75, 3, 3);
				spacePrint(cout, (*it)->getDescription(), 75, 5, 0);

				if(it + 1 != xorList[i].end())
					spacePrint(cout, "-- OR --", 75, 9, 0);
			}
			cout << endl << endl;
		}

		// then the rest
		for(ArgListIterator it = argList.begin(); it != argList.end(); it++)
		{
			if(!xorHandler.contains(*it))
			{
				spacePrint(cout, (*it)->longID(), 75, 3, 3);
				spacePrint(cout, (*it)->getDescription(), 75, 5, 0);
				cout << endl;
			}
		}

		cout << endl << "Home page:\t\t" << PACKAGE_URL << endl;
		cout << "Send bug reports to:\t" << PACKAGE_BUGREPORT << endl << endl;
	}
};

DspcHello::DspcHello() {

}

DspcHello::~DspcHello() {

}

int DspcHello::exec(int argc, char *argv[]) {

	try {
		TCLAP::CmdLine cmd("x", ' ', VERSION);

		MyOutput my;
		cmd.setOutput(&my);

		TCLAP::ValueArg<string> nameArg("n", "name", "Name to print", true, "homer", "string");
		cmd.add(nameArg);

		TCLAP::ValueArg<int> nameArg2("i", "namei", "Name to print", false, 3, "int");
		cmd.add(nameArg2);

		TCLAP::SwitchArg reverseSwitch("r", "reverse", "Print name backwards", cmd, false);

		cmd.parse(argc, argv);

		name = nameArg.getValue();
		reverseName = reverseSwitch.getValue();

	} catch (TCLAP::ArgException &tclapE) {
		cerr << "error: " << tclapE.error() << " for arg " << tclapE.argId() << endl;
		return 1;
	}

	return init();
}

int DspcHello::init() {

	cout << "Hello World!" << endl;
	cout << "This is " << PACKAGE_STRING << endl;

	if (reverseName)
	{
		reverse(name.begin(),name.end());
		cout << "My name (spelled backwards) is: " << name << endl;
	}
	else
		cout << "My name is: " << name << endl;

	return 0;

}

