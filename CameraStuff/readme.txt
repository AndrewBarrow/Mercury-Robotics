plays overwatch video locally well but have not managed to stream to other computer
cvlc -v v4l2:///dev/video0:chroma="H264":width=1920:height=1080:fps=15 \ --sout="#rtp{sdp=rtsp://:8554/live}" --rtsp-timeout=-1

using on pi
 raspivid -t 999999 -h 720 -w 1080 -fps 25 -hf -b 2000000 -o - | gst-launch-1.0 -v fdsrc ! h264parse !  rtph264pay config-interval=1 pt=96 ! gdppay ! tcpserversink host=YOUR-PI-IP-ADDRESS port=5000 
and in windows command or mac terminal
 gst-launch-1.0 -v tcpclientsrc host=YOUR-PI-IP-ADDRESS port=5000  ! gdpdepay !  rtph264depay ! avdec_h264 ! videoconvert ! autovideosink sync=false
 works very well locally but has some problems over internet
 trying to switch to udp
 also can drop frame rate. will have to determine smallest resolution needed for claw cam.
 
 http://pimylifeup.com/raspberry-pi-webcam-server/
works but webcam_localhost is now stream_localhost and webcam_maxrate is now stream_maxrate
also press ctrl-w to search in nano SUPPER USEFUL
unfortunately motion seems very slow and laggy
 
 http://wiki.oz9aec.net/index.php/Raspberry_Pi_Camera
 
 some important notes, have been doing gstreamer on the assumption that the camera is h.264 encoded, but using
 v4l2-ctl --list-formats
 shows its not
 but... opencv complained about opengl not being availible so i ran
 sudo apt-get install libgl1-mesa-dri
 and after reboot there were three listed camera devices
 v4l2-ctl --list-formats
 shows that the usb cam is video0 and video1 and
  v4l2-ctl --list-formats -d /dev/video1
  shows that that is how you access the h.264 encoded camera
  after this change the cvlc function is supper slow and opencv still has capture problems.
  need to refind the gstreamer pipeline for sending 
