# SWROTS-MUD-RESTORED-2019

Hello, 

My Name is Randal. Found this old game laying around the 
internet full of bugs and decided to bring it back to life.

Now lets begin.

Ignore all other README files within this build. 
Ill bring parts of it here. (MAYBE)

----------------------------------------------------------------------------------
## Step 1. Compile

Navigate to SRC folder with terminal ( Ubuntu 16+ Ubuntu 18+ )

type: make all

if crashes. Read error and submit to GIT and download later version.

----------------------------------------------------------------------------------
## Step 2. Configure

Port is important :)  

Currently set at 1111

You can change this by navigating to startup file within the SRC folder. 
Edit using your favorite text editor.

----------------------------------------------------------------------------------
## Step 3. Run Server

If you're using ubuntu 18+ you will need to install CSH "sudo apt-get install csh"

then navigate to SRC dir and Type: ./startup

----------------------------------------------------------------------------------
## Step for Developers

To erase all .o files if you decide to recompile SRC here is a short script to do so.

Type: find . -type f -name '*.o' -delete

Please note you must execute command above within SRC dir.

## Thanks to these guys for helping me sort out a bug in 1 of the files.

https://stackoverflow.com/questions/54794046/solved-error-lvalue-required-as-left-operand-of-assignment-swrots