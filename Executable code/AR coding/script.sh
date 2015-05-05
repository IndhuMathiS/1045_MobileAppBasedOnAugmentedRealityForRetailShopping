    #!/bin/bash

    host=localhost
    port=8190
    file=/home/stack/rtsp/rtspmod2/pc/test/code/mjpg/out.jpg

    bitrate=1024

# option --fake-fps will not work with value less than 4

    cvlc -vv  --sout "#transcode{vcodec=h264,vb=$bitrate}:standard{access=http,mux=ts,dst=$host:$port}"  
#fake
