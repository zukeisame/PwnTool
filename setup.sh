#! /bin/bash

make

echo ''

echo 'Copying libPwn.so to /usr/lib, root permission is needed...'

sudo cp ./libPwn.so /usr/lib

exit 0