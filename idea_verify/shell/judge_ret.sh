#!/bin/sh

ls /dev/sdc
if [ $? == 0 ];then
    echo "1"
else
    echo "2"
fi

