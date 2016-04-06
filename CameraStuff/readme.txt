plays overwatch video locally well but have not managed to stream to other computer
cvlc -v v4l2:///dev/video0:chroma="H264":width=1024:height=570:fps=30 \ --sout="#rtp{sdp=rtsp://:8554/live}" --rtsp-timeout=-1

using on pi
 raspivid -t 999999 -h 720 -w 1080 -fps 25 -hf -b 2000000 -o - | gst-launch-1.0 -v fdsrc ! h264parse !  rtph264pay config-interval=1 pt=96 ! gdppay ! tcpserversink host=YOUR-PI-IP-ADDRESS port=5000 
and in windows command or mac terminal
 gst-launch-1.0 -v tcpclientsrc host=YOUR-PI-IP-ADDRESS port=5000  ! gdpdepay !  rtph264depay ! avdec_h264 ! videoconvert ! autovideosink sync=false
 works very well locally but has some problems over internet
 trying to switch to udp
 also can drop frame rate. will have to determine smallest resolution needed for claw cam.
 
 
