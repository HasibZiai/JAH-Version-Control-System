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

First the user specifies the source folder and the path of the repo that they would like to copy.
Then 3 vectors are created to sort the follow parameters: paths, filenames, and the artifact path.
After a root folder is specified, the various folder and subfolder paths are stored in their
respective vectors. Inside the artifact folders, the checksum algorithm is ran in order to
rename the files inside the artifact folders. After the checksum value is created, the path,
filename and checksum is stored inside the artifact vector. The process repeats until all the 
folders/subfolders have been visited. Finally, another loop is initialized to cleanup the
original, unnamed files (the original checksum files).


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
The source path entered was: mypt2
The target path entered was: mypt2_repo2



Size of the file is: 5
Final string is: 4206-L5
The relative path is: mypt2_repo2\hx.txt


Size of the file is: 134
Final string is: 83430-L134
The relative path is: mypt2_repo2\manifest.txt


Size of the file is: 8
Final string is: 3993-L8
The relative path is: mypt2_repo2\Stuff\goodbye.txt


Size of the file is: 12
Final string is: 8700-L12
The relative path is: mypt2_repo2\Stuff\hello.txt


There are 4 files in the repository (including the manifest.txt file).


Features
--------
Checksum algorithm that takes in the file's contents and size and renames it based on the algorithm
parameters.

Additional folders will be made according to the name of the files.

Bugs
----
The ostream creates a manifest.txt but it is empty during the first iteration. 
The first entry of the manifest will be for manifest.txt, but it has no size or checksum.
