/*
** EPITECH PROJECT, 2024
** functions_hunter
** File description:
** H files for functions of my_top
*/

#include "./include/my.h"

#ifndef FUNCTIONS_SUDO_H_
    #define FUNCTIONS_SUDO_H_
int parse_options(int argc, char **argv, int *env);
void hide_input_mode(void);
void restore_input_mode(void);
int display_flag_h(void);
int handle_flag_u(char *user);
int handle_flag_g(const char *group_name);
int handle_flag_s(void);
void displaying(int i);
int check_password(const char *password_hash);
char *find_hash(void);
char *get_username(char *uid, char *pathfile);
int in_sudoers(char *username);
int my_len_int(int num);
char *int_to_str(int uid);
#endif
