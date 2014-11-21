#!/bin/sh

i=1

start=1
end=10
while [ $i -lt 120 ];
do
    parted /dev/sdc <<EOF
    mkpart
    sdc${i}
    ext4
    ${start}M
    ${end}M
EOF
    start=$end
    end=$(($end+10))
    i=$(($i+1))
done
exit 0
