CPSC 362 
Project #1: VCS Create Repo

Team Name: JAH

Aaron Gumabong
Joe Vanacore
Hasib Ziai 

Intro
-----
The goal of the project was to create a working repository system for our first version of the VCS.
In concept, the first folder is used as the root folder whose purpose is to hold all subsequent 
sub-folders and files. After the user specifies the root folder, a folder will be made for each 
file in the root folder. These folders will be named after the name of the file. Inside those 
folders will be the original version of the file as well as a folder to hold changes to the file.
The folder that holds changes to the file will be named using a checksum algorithm. This algorithm
takes the name and size of the file and renames the folder accordingly. Inside the renamed folder
there will be the changed file with the same name as the folder. This process will repeat as long
as changes are made to the file, regardless if it is an edited version or the original.

First 3 vectors are created to sort the follow parameters: paths, filenames, and the artifact path.
After a root folder is specified, the various folder and subfolder paths are stored in their
respective vectors. Inside the artifact folders, the checksum algorithm is ran in order to
rename the files inside the artifact folders. After the checksum value is created, the path,
filename and checksum is stored inside the artifact vector. The process repeats until all the 
folders/subfolders have been visited. 


Contents
--------
The file included in the .zip submission will be the source file (source.cpp) and the header file 
for the checksum(checksum.h).


External Requirements
---------------------
A compiler with access to the <experimental/filesystem> library. 


Setup and Installation
----------------------
None.


Sample
------
TBD


Features
--------
Checksum algorithm that takes in the file's contents and size and renames it based on the algorithm
parameters.
