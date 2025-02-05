/*
** EPITECH PROJECT, 2025
** output_functions
** File description:
** functions for output handle
*/

#include <termios.h>
#include <unistd.h>
#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions_sudo.h"

void hide_input_mode(void)
{
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void restore_input_mode(void)
{
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
