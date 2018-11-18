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

The check-in function takes in 2 arguments: The source path of the repo the user wants to check in,
and the target path of the repo the user wants to check-in into. Check-in will create two iterators,
one to go through the files in Source Repo, and another to go through the files in Target Repo. 
If the parent folder of the two files are the same, this means that they are different versions of
the same file. If the names of two files are the same, this means that the file is unchanged in the
Source Repo, and will not be copied over to the Target Repo. Regular file count will be incremented.
Otherwise, if the filenames are different, this signifies a change has occurred, and the selected file
will be copied over from the selected directory, from Source Repo to Target Repo. The file will also be
assigned a new checksum and filename, so that it is easy to keep track of changes made. These commands
will be written into the manifest.txt inside the Target Repo, as well as the date and time of commands.

Contents
--------
The file included in the .zip submission will be the source file (source.cpp) and the header file(Repo.h) 


External Requirements
---------------------
A compiler with access to the <experimental/filesystem> library.
C++17 with the latest version.


Setup and Installation
----------------------
A source folder needs to be already made in the target destination. 


Sample
------

Create Repo
Sat Nov 17 22:24:14 2018

The source path entered was: C:\sandbox\test1
The target path entered was: C:\sandbox\test2



Size of the file is: 63 bytes.
Final string is: 39675-L63
The relative path is: sandbox\test2\subfolder1\subfolder 3\subfolder 4\test doc 6.txt


Size of the file is: 7 bytes.
Final string is: 4361-L7
The relative path is: sandbox\test2\subfolder1\subfolder 3\testdoc3.txt


Size of the file is: 8 bytes.
Final string is: 5932-L8
The relative path is: sandbox\test2\subfolder1\subfolder 3\testdoc4.txt


Size of the file is: 10 bytes.
Final string is: 7962-L10
The relative path is: sandbox\test2\subfolder1\testdoc2.txt


Size of the file is: 25 bytes.
Final string is: 15792-L25
The relative path is: sandbox\test2\subfolder1\testdoc5.txt


Size of the file is: 13 bytes.
Final string is: 8694-L13
The relative path is: sandbox\test2\testdoc.txt


There are 7 files in the repository (including the manifest file).
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Label: TestLabel

Check In
Sat Nov 17 22:27:37 2018

The source path entered was: C:\sandbox\test3
The target path entered was: C:\sandbox\test2



There are 8 files in the repository (including the manifest file).
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


Features
--------
The user can Create Repo, add a Label, Check Out a repo, and Check In files to a repo.
Descriptions and functionality for each feature is described above.


Bugs
----
Check-In does not currently work. While it is able to detect when files are the same and increments
the file count, it does not detect when the filenames are different, and as a result, cannot copy the new file into 
the Target Repo. 
