#!/bin/sh

echo "This script will set up SFML on your system."
echo "Which distribution are you running?"
echo "  [0] Fedora (or CentOS, RedHat, etc.)"
echo "  [1] Debian (or Ubuntu, Mint, etc.)"

read -p "Choice [0,1]: " distro
case $distro in
    0) yum install -y wget cmake mesa-libGL-devel libXrandr-devel freetype-devel glew-devel libjpeg-devel openal-soft-devel libsndfile-devel fontconfig-devel gcc-c++
        ;;
    1) apt-get install -y cmake libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev
        ;;
    *) echo Invalid Input;
        exit 1
        ;;
esac

wget https://github.com/LaurentGomila/SFML/tarball/master -O sfml.tgz
tar -xvzf sfml.tgz
rm -f sfml.tgz
cd LaurentGomila-SFML-*
cmake .
make install -j 4
cd ../
mv LaurentGomila-SFML-* sfml

echo "Installation Complete!"

