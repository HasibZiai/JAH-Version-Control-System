CPSC 362 
Project #2: Check-out & and Check-In

Team Name: JAH

Aaron Gumabong
Joe Vanacore
Hasib Ziai 

Intro
-----
The goal of the project was to implement 3 different functions: label, check-out, and check-in.
Project #2 builds on the functionality of the first project, VCS Create Repo, but adds the three
aforementioned functions. 

The label function takes in two arguments: the file path to the manifest and the a specified label
name. It will then ask the user if the manifest has been changed. If the user selects 'y', then the 
user will be prompted to enter the name of the manifest they wish to change. Afterwards, it will 
confirm if the user would like to change the manifest name. If the user selects 'n' then the name
of the label will be printed inside the manifest. 

The checkout function takes in two arguments: the file path to the folder being copied and the 
file path to a folder the user would like to copy the folder to. Once the function is called, it
asks the user if it would like to use the name of a label. If the user selects "N" or "n" it will
use "manifest.txt" as the default name of the manifest. After that the function will copy the 
contents of the first file path specified and will put an exact copy in the specified location.
Afterwards it will rename the manifest if a label was given and will write the time and date at
which the copy was created. 


Contents
--------
The file included in the .zip submission will be the source file (source.cpp) and the header file 
for the checksum(checksum.h). 


External Requirements
---------------------
A compiler with access to the <experimental/filesystem> library.
C++17 with the latest version.


Setup and Installation
----------------------
A source folder needs to be already made in the target destination. 


Sample
------

Features
--------
Functionality of the three functions are described in the intro.


Bugs
----

