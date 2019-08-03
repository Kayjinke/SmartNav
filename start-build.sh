#! /bin/bash

_fullname=`pwd`
_dirname=`dirname $_fullname`
_basename=`basename $_fullname`

#echo "Fullname is $_fullname"
#echo "Dirname is $_dirname"
#echo "Basename is $_basename"


#echo "_buildout_fullname is $_buildout_fullname"

arch=x86_64
cleanflag=0

for arg in $*
do
    echo "arg $arg"
    if [ "$arg"x = "-c"x ]
       then
           cleanflag=1
    fi
    if [ "$arg"x = "-arm"x ]
       then
           arch=arm
    fi
done

#echo "arch is " $arch


_buildout_basename=$_basename-$arch-build
_buildout_fullname=$_dirname/$_buildout_basename

if [ "$cleanflag"x = "1"x ]
    then
        rm -rf $_buildout_fullname
        exit 0
fi     


cd ..
if [ ! -d $_buildout_fullname ]
   then
      mkdir $_buildout_fullname
fi

cd $_buildout_fullname
cmake $_fullname -DARCH=$arch -DCMAKE_INSTALL_PREFIX=$_buildout_fullname/install
make
make install
