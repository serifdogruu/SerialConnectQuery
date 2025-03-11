Sh files working for get netstat, ifconfig and last log reports. 
C file getting information UART via ttyUSB3 

before launch sh file use ; 
  $ sed -i -e 's/\r$//' <sh_filename>.sh 
  in your terminal.

C file launc as known ;
  $ gcc -o SerialConList SerialConList.c 
  $ sudo ./SerialConList
