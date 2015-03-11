# Project Milano

## Instructions

### Vagrant Virtual Machine configuration
* Install Vagrant from [vagrantup.com](https://www.vagrantup.com)
* Install VirtualBox from [virtualbox.org](https://www.virtualbox.org)
* Pull from Git
* In Terminal, use `vagrant up` command in your git folder (make sure you have a good connexion, this could be long)
* use `vagrant ssh` to connect to virtual machine (in windows call from git bash instead of cmd)

### Updates and Blender installation
* make sure your VM is up to date with `sudo pacman -Sqyu --noconfirm`
* now, install Blender : `sudo pacman -S blender` (confirm installation with Y)

> You are connected to the machine, your work directory inside the virtual machine is in `/vagrant` and is synced with your git folder.
OpenCV, C++ and Python are now available in the virtual machine.

## Input Data.
Because of the large size of videos, the data folder is ignored.
Moreover, the path of input videos are in param for functions.

But we choose those conventions for naming input data :
* data/
  * calibration/
    * cal_1.avi (0:16 - 65.9Mo)
    * cal_2.avi (0:17 - 69.8Mo)
    * cal_3.avi (0:36 - 142.6Mo)
  * maquette/
    * new.avi (0:44 - 166.3Mo)
  * stl/
    * CorsoComoAscii.stl (97.6Mo)
    * CorsoComoBinary.stl (18.1Mo)
    * GarRep.stl (9.3Mo)


## Calibration
> TODO

## Undistorted frames and video calculation
> TODO

## Solve Camera Pose calculation
> TODO

## Blender helped rendering with Python
> TODO
