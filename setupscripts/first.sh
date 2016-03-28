 
 sudo apt-get remove python-minecraftpi sonic-pi wolfram-engine bluej scratch greenfoot nodejs -y
 sudo apt-get update
 sudo apt-get upgrade -y
 wget https://node-arm.herokuapp.com/node_archive_armhf.deb
 sudo dpkg -i node_archive_armhf.deb
 sudo apt-get install rpi-update -y
 sudo rpi-update