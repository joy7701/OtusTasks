#!/bin/bash

#deb package information
mkdir -p helloworld_0.0.$TRAVIS_BUILD_NUMBER/DEBIAN/
{
  echo 'Package: helloworld'
  echo 'Version: 0.0.'$TRAVIS_BUILD_NUMBER
  echo 'Section: Base'
  echo 'Priority: optional'
  echo 'Architecture: '$TRAVIS_CPU_ARCH
  echo 'Depends:'
  echo 'Maintainer: Philipp Yaroslavtsev phyaroslavtsev@gmail.com'
  echo 'Description: Hello World'
} > helloworld_0.0.$TRAVIS_BUILD_NUMBER/DEBIAN/control

#set up binary files
mkdir -p helloworld_0.0.$TRAVIS_BUILD_NUMBER/usr/local/bin
cp helloworld helloworld_0.0.$TRAVIS_BUILD_NUMBER/usr/local/bin

#make package
dpkg-deb --build helloworld_0.0.$TRAVIS_BUILD_NUMBER
#clear useless data
rm -rf helloworld_0.0.$TRAVIS_BUILD_NUMBER
