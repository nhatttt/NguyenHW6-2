/*
for homework 6-2, this program has been extended to accept two new command line arguments "blink" and an
integer n that sets how many times to turn the LED on and off with a 1 sec
interval in between.
*/
#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

#define LED3_PATH "/sys/class/leds/beaglebone:green:usr3"

void writeLED(string filename, string value){
   fstream fs;
   string path(LED3_PATH);
   fs.open((path + filename).c_str(), fstream::out);	//c_str() is used to convert to a usable c++ string
   fs << value;
   fs.close();
}

void removeTrigger(){
  writeLED("/trigger", "none");
}

int main(int argc, char* argv[]){
   if(argc<2){
	cout << "Usage is makeLED and one of: " << endl;
        cout << "   on, off, flash or status" << endl;
	cout << " e.g. makeLED flash" << endl;
        return 2;
   }
   string cmd(argv[1]);
   int blinkNum = atoi(argv[2]);
   cout << "Starting the makeLED program" << endl;
   cout << "The current LED Path is: " << LED3_PATH << endl;

   // select whether command is on, off, flash or status
   if(cmd=="on"){
        cout << "Turning the LED on" << endl;
	removeTrigger();
        writeLED("/brightness", "1");
   }
   else if (cmd=="off"){
        cout << "Turning the LED off" << endl;
	removeTrigger();
        writeLED("/brightness", "0");
   }
   else if (cmd=="flash"){
        cout << "Flashing the LED" << endl;
        writeLED("/trigger", "timer");
        writeLED("/delay_on", "50");
        writeLED("/delay_off", "50");
   }
   else if (cmd=="status"){
	// display the current trigger details
        std::fstream fs;
	fs.open( LED3_PATH "/trigger", std::fstream::in);
	string line;
	while(getline(fs,line)) cout << line << endl;
	fs.close();
   }
   else if (cmd=="blink"){
	removeTrigger();
	for(int i=0; i<blinkNum; i++){
		writeLED("/brightness", "1");
		sleep(1);
		writeLED("/brightness", "0");
		sleep(1);
	}
	
   }
   else{
	cout << "Invalid command!" << endl;
   }
   cout << "Finished the makeLED Program" << endl;
   return 0;
}
 
