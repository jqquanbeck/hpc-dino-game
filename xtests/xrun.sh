#!/bin/bash

# number of instances
N=$((5))
rootDisplay=$DISPLAY

echo "Launched from display "$rootDisplay

echo "Killing all Xnest instances"
killall Xnest -s SIGKILL

echo "Removing temporary files"
rm -rf /tmp/dino/*

# determine highest X display number in use
highestX=$(ls /tmp/.X11-unix | tail -1 | cut -c2-)
firstX=$(($highestX + 1));

echo "Starting with Xnest :"$firstX

echo "Starting Xnest and google chrome"

echo "starting at "$firstX
echo "ending at "$(($firstX + $N))
read -p "Press enter to continue"

for (( i=$firstX; i<$(($firstX + $N)); i++))
do
    export DISPLAY=$rootDisplay
    echo "Launching window "$i
    Xnest :$i -geometry 600x150+0+$((180 * ($i - $firstX))) -bw 0 &
    google-chrome-stable --display=:$i --incognito --user-data-dir=/tmp/dino/$i --no-first-run &
done

sleep 5
./xrun.out $N $firstX