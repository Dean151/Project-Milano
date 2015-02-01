#!/bin/bash
# this shell is run as root so there is no need for sudo

# update pacman and system
pacman -Sqyu --noconfirm

# install opencv
pacman -Sq   --noconfirm opencv

# install numpy python2 aka opencv binder
pacman -Sq   --noconfirm python2-numpy

# disable 1394 driver
ln /dev/null /dev/raw1394

# remove symlink to python3
rm /usr/bin/python

# and replace it with symlink to python2
ln -s /usr/bin/python2 /usr/bin/python