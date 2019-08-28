#!/bin/sh

echo "create release folder ..."
rm -R arco1500-release
mkdir arco1500-release

echo "copying arduino ide ..."
cp -R arduino arco1500-release/arduino
rm -R arco1500-release/arduino/portable/staging
rm -R arco1500-release/arduino/portable/*json*
rm -R arco1500-release/arduino/portable/preferences.txt

echo "copying game uploader exe ..."
cp game_uploader/bin/Release/ARCO1500_Uploader.exe arco1500-release/ARCO1500_Uploader.exe

echo "copying not_emulator ..."
cp -R not_emulator arco1500-release/not_emulator

echo "copying games ..."
cp -R games arco1500-release/games

echo "copying url shortcut ..."
cp www.arco1500.com.url arco1500-release/www.arco1500.com.url

echo "zipping ..."
7z a -tzip arco1500.zip arco1500-release
rm -R arco1500-release
