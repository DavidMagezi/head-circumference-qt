#/!/bin/bash
echo "Installing tools necessary for head-circumference-qt"
needed_packages=qt5-base
pacman -Q $needed_packages || sudo pacman -S --needed $needed_packages
