 #!/usr/bin/env bash

 # Execute this file to install the points cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Points-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Points-Qt.app/Contents/MacOS/pointsd /usr/local/bin/pointsd
 sudo ln -s ${LOCATION}/Points-Qt.app/Contents/MacOS/points-cli /usr/local/bin/points-cli
