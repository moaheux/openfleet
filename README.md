To get the project 
$ git clone git@github.com:moaheux/openfleet.git

The aim of this software is to simulate a Distibution Machine.

Project made under LINUX

How to compile:
In root directory write:

$ make all

The binary file will be create in 
openfleet\build\apps

To launch the software type
$ cd build\apps

for the Distributech NA
$ ./program DNA US
or 
$ ./program DNA CAD

for the Distributech EU
$ ./program DEU EU

I decided to use a CLI as a user interface
The program will display the products available + the associated price
The program will ask for inputs:
    if you want to simulate a NFC tag, write:
        $NFC
    then it wil ask for the name of the employee, look at the Employees.txt in openfleet $ \build\apps\employee for the autorized name.
    if you need to go in technician mode write
        $ technician
    you will have a specific maintenance menu. (I didn't have the time to implement the change function because it need a full management of coin in the machine and it may take a bit longer of time)
    
    
The production description was written in xml files you can find in :
  $ openfleet\build\apps\productsFile