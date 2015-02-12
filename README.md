# Project Milano

## Instructions
* Install Vagrant from [vagrantup.com](https://www.vagrantup.com)
* Install VirtualBox from [virtualbox.org](https://www.virtualbox.org)
* Pull from Git
* In Terminal, use `vagrant up` command in your git folder (make sure you have a good connexion, this could be long)
* use `vagrant ssh` to connect to virtual machine

> You are connected to the machine, your work directory inside the virtual machine is in `/vagrant` and is synced with your git folder.
OpenCV, C++ and Python are now available in the virtual machine.

## Input Data.
Because of the large size of videos, the data folder is ignored.
Moreover, the input videos are adressed in param for functions.

But we came each other with those conventions for naming videos :
* data/
  * calibration/
    * cal_1.avi (0:16 - 65.9Mo)
    * cal_2.avi (0:17 - 69.8Mo)
    * cal_3.avi (0:36 - 142.6Mo)
  * maquette/
    * old.wmv (0:18 - 4.2Mo)
    * new.avi (0:44 - 166.3Mo)

## Calibration
> Brace yourselves, documentation is coming
