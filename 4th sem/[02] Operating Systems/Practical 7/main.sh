#!/bin/bash

function add {
    echo "$(($a + $b))"
}

function subtract {
    echo "$(($a - $b))"
}

function multiply {
    echo "$(($a * $b))"
}

function divide {
    if [ $b -eq 0 ]; then
        echo "Can not divide by 0"
    else
        echo "$(($a / $b))"
    fi
}

function modulus {
    echo "$(($a % $b))"
}

function menu {
    echo "Select an operation to perform:"
    echo "1. Add"
    echo "2. Subtract"
    echo "3. Multiply"
    echo "4. Divide"
    echo "5. Modulus"
    echo "6. Exit"
    read -p "Enter your choice: " choice
    read -p "Enter number 1: " a
    read -p "Enter number 2: " b
    case $choice in
        1) add $a $b;;
        2) subtract $a $b;;
        3) multiply $a $b;;
        4) divide $a $b;;
        5) modulus $a $ba;;
        6) exit;;
    esac
}

exiting=false

until [ "$exiting" = true ]
do
    menu
    read -p "Do you want to continue? (1 -> continue; 0 -> exit) " choice 
    if [ $choice -eq 0 ]; then
        exiting=true
    fi
done