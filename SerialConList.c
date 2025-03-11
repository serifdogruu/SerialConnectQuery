#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define SERIAL_PORT "/dev/ttyUSB3" 
#define BAUDRATE B115200 

int defatturbutes(int fd){

    struct termios serial_options;
    tcgetattr(fd, &serial_options);

    cfsetispeed(&serial_options, BAUDRATE);
    cfsetospeed(&serial_options, BAUDRATE);


    serial_options.c_cflag &= ~PARENB;  // No parity
    serial_options.c_cflag &= ~CSTOPB;  // One stop bit
    serial_options.c_cflag &= ~CSIZE;
    serial_options.c_cflag |= CS8;  // 8 data bits
    serial_options.c_cflag |= (CLOCAL | CREAD);
    
    serial_options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw mode
    serial_options.c_iflag &= ~(IXON | IXOFF | IXANY);  // No flow control
    serial_options.c_oflag &= ~OPOST; // Raw output

    // Apply the settings
    tcsetattr(fd, TCSANOW, &serial_options);

    return 0 ; 
}

int send_command(int fd, char* command){

    int write_result = write(fd, command, strlen(command));

    char response[256];
    int bytes_read = read(fd, response, sizeof(response) - 1);
    if (bytes_read > 0) {
        response[bytes_read] = '\0'; // Null-terminate the string
        printf("Response: %s \n", response);
    } else {
        perror("Error reading response");
    }

    

}

char commands[15][15] = {"ATI", "AT+GMI", "AT+GMM", "AT&V", "AT+CIMI",
    "AT+CSQ", "AT+CPOL", "AT+COPN", "AT+CTZR", "AT+QSPN", "AT+CNUM",
    "AT+QSIMDET", "AT+QSIMSTAT","AT+QLTS","AT+QNWINFO"};

int main(){

    FILE *fptr = fopen("output.txt", "r"); 

    if (fptr == NULL){
        printf("File doesnt exist or couldnt openede properly");
    }

    int serial_fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY);
    defatturbutes(serial_fd);


    for(int i = 0 ; i < 15 ; i++){
        
        send_command(serial_fd, commands[i]);
        send_command(serial_fd, "\r");
        
        //printf("%s\n",commands[i]);
    }


    
/*
    char* mycommand = "AT+CNUM\r\n"; 
    send_command(serial_fd,mycommand);
*/

}












