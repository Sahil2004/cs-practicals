#!/bin/bash

echo "Welcome to the program!"

write sahil << End_Of_Message
Hello Sahil! We ran the OSCodeEditor!!!
End_Of_Message

echo "Message is sent to the user."

exiting=false

until [ $exiting = true ]
do
    read -p "Enter the name of the file to create: " filename
    touch "$filename by script.txt"
    echo "File created successfully!"
    wannaWrite=true
    until [ $wannaWrite = false ]
    do
        read -p "Enter the text to write in the file: " text
        echo $text >> "$filename by script.txt"
        read -p "Do you want to write more text in the file? (y/n): " choice
        if [ $choice = "n" ]
        then
            wannaWrite=false
        fi
    done
    echo "Here is the content of the file:"
    cat "$filename by script.txt"
    read -p "Do you want to create more files? (y/n): " choice
    if [ $choice = "n" ]
    then
        exiting=true
    fi
done