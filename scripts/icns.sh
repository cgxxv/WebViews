#!/bin/bash

ICONS="ChatGPTs.iconset"

rm -rf $ICONS
mkdir $ICONS

magick assets/ChatGPTs.png -resize 16x16 $ICONS/icon_16x16.png
magick assets/ChatGPTs.png -resize 32x32 $ICONS/icon_16x16@2x.png
magick assets/ChatGPTs.png -resize 32x32 $ICONS/icon_32x32.png
magick assets/ChatGPTs.png -resize 64x64 $ICONS/icon_32x32@2x.png
magick assets/ChatGPTs.png -resize 128x128 $ICONS/icon_128x128.png
magick assets/ChatGPTs.png -resize 256x256 $ICONS/icon_128x128@2x.png
magick assets/ChatGPTs.png -resize 256x256 $ICONS/icon_256x256.png
magick assets/ChatGPTs.png -resize 512x512 $ICONS/icon_256x256@2x.png
magick assets/ChatGPTs.png -resize 512x512 $ICONS/icon_512x512.png
magick assets/ChatGPTs.png -resize 1024x1024 $ICONS/icon_512x512@2x.png

iconutil -c icns $ICONS

rm -rf $ICONS
