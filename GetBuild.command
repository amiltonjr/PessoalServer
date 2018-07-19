#! /bin/bash
current_path="$(dirname "$BASH_SOURCE")"
cd $current_path
cp -R ./build-server-Desktop_Qt_5_7_1_clang_64bit-Debug/server.app/Contents/MacOS/server ./1.0.0/server
cp -R ./server/etc/Server.ini ./1.0.0/Server.ini
