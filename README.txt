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

The check-out function takes in 3 arguments: the source path, a folder path to copy to, and a label
name. Check-out will iterate through all the files, folders, and subfolders and will check for a
"manifest.txt". If it finds a manifest.txt then it will search the text file for the label. It will
then check the label against the argument that is provided in the original function. If the two
labels are the same then it will copy all the files in the parent path of the iterator into the new
folder provided in the arguments. 


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

