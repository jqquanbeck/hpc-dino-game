#!/bin/bash

killall Xnest
echo "Starting Xnest"
Xnest :2 -geometry 600x150+0+0 &
export DISPLAY=:2
google-chrome-stable &
sleep 5
./key.out