#! /bin/bash

make

echo ''

echo 'Copying libPwn.so to /usr/lib, need permission...'

sudo cp ./libPwn.so /usr/lib

exit 0