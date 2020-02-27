#!/bin/sh
PACKAGE=$1
echo "monkey..."
/home/user/Android/Sdk/platform-tools/adb -d shell monkey -p $1 1
APPPID=`/home/user/Android/Sdk/platform-tools/adb -d shell ps | grep "${PACKAGE}" | awk '{print $2}'`
echo "Application PID : $APPPID"
/home/user/Android/Sdk/platform-tools/adb -d logcat -v long | grep -1 " ${APPPID}:"
