
#!/bin/bash

N=$((1))

while getopts N: flag
do
    case "${flag}" in
        N) N=${OPTARG};;
    esac
done

# chick for dinolib.so
if [ ! -f "dinolib.so" ]; then
    echo "dinolib.so not found. Try runing make command"
    exit
fi

# number of instances
rootDisplay=$DISPLAY

echo "Launched from display "$rootDisplay

echo "Killing all Xnest instances"
killall Xnest -s SIGKILL

echo "Removing temporary files"
rm -rf /tmp/$USER/dino/*
rm -rf /tmp/.X11-unix/*
rm log.txt

# determine highest X display number in use
highestX=$(ls /tmp/.X11-unix | cut -c2- | sort -n | tail -1)
firstX=$(($highestX + 100));

echo "Starting with Xnest :"$firstX

echo "Starting Xnest and google chrome"

echo "starting at "$firstX
echo "ending at "$(($firstX + $N - 1))

#read -p "Press enter to continue"

for (( i=$firstX; i<$(($firstX + $N)); i++))
do
    export DISPLAY=$rootDisplay
    echo "Launching window "$i
    Xnest :$i -geometry 600x150+$((20 + 610 * (($i - $firstX) / 5)))+$((50 + 200 * (($i - $firstX) % 5))) -bw 0 &>> log.txt &
done

sleep 5

for (( i=$firstX; i<$(($firstX + $N)); i++))
do
    google-chrome-stable --display=:$i --incognito --user-data-dir=/tmp/$USER/dino/$i --no-first-run &>> log.txt &
done

sleep 5
read -p "Press enter to continue when all chrome windows are loaded."

python3 ./dinoai.py $N $firstX
