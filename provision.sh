#!/bin/bash
# this shell is run as root so there is no need for sudo

# update pacman and system
pacman -Sqyu --noconfirm

# install opencv
pacman -Sq   --noconfirm opencv

# install blender
pacman -Sq   --noconfirm blender

# disable 1394 driver
ln /dev/null /dev/raw1394