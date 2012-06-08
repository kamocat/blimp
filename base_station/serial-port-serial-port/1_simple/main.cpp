
#include <iostream>
#include "SimpleSerial.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
	int a = 52;
	int b = 57;
	int c =	75;
	int n;
	char buffer_data[3];
	int count = 0;

	while (count < 15){
		n=sprintf (buffer_data, "%c%c%c\n",a,b,c);


		try{
			SimpleSerial serial("/dev/ttyUSB0",9600);
			serial.writeString(buffer_data);
			cout<<"Received : "<<serial.readLine()<<" : end"<<endl;
		}
		catch(boost::system::system_error& e){
			cout<<"Error: "<<e.what()<<endl;
		}
		count++;
	}	
	return 1;
}

