#!/usr/bin/expect


set timeout 10

spawn adb shell

# login
expect "login:"
send "root\r"

# Password
expect "Password:"
send "Password\r"

expect ":"

send "cd logs\r"

send "netstat > netstat_output.txt\r"
send "ifconfig > ifconfig_output.txt\r"

send "exit\r"


expect "$"

#./Get.sh

#adb pull /home/root/logs .




