#include "io/keyboard.h"
#include "io/terminal.h"
#include "defines.h"
#include "stdlib/stdlib.h"
#include "pseudo_terminal/commands.h"
#include "sysdata.h"
#include "kernel/kernel.h"
#include <stddef.h>
#include <stdbool.h>

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

char input[256];
int user_input_color = VGA_COLOR_LIGHT_GREEN;
int error_output_color = VGA_COLOR_RED;
int sys_output_color = VGA_COLOR_WHITE;

// Function to compare the first `HowMany` characters of two strings
bool compareSomeChars(const char *str1, const char *str2, int HowMany) {
    for (int i = 0; i < HowMany; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

char* get_command(char *str, char delimiter) {
    char *start = str;
    
    while (*str) {
        if (*str == delimiter) {
            *str = '\0';  // Replace delimiter with null terminator
            break;
        }
        str++;
    }
    return start;  // Return the first token
}

// Function to set text color
void setColor() {
    if (input[11] != '\n') {
        int color = Int(input[10]);
        if (color == 0) {
            user_input_color = VGA_COLOR_LIGHT_GREEN;
            terminal_setcolor(VGA_COLOR_LIGHT_GREEN);
        } else if (color == 1) {
            user_input_color = VGA_COLOR_GREEN;
            terminal_setcolor(VGA_COLOR_GREEN);
        }
    } else {
        printf("color not specified");
    }
}
// New syscall function, currently without action implementation
void syscall_command() {
    printf("syscall command called\n");
    // Additional handling for syscall arguments can be added here

}

// Function to check user commands
void check_command() {
    getInput(input);
    char *command = get_command(input, ' ');
    if (strcmp(input, "azbestfetch") == 0) {
        azbestFetch();
    } else if (strcmp(input, "help") == 0) {
        help();
    } else if (strcmp(input, "clear") == 0) {
        terminal_clear();
    } else if (strcmp(command, "setcolor")==0) {
        setColor();
    } else if (strcmp(command, "syscall") == 0) {
        syscall_command();  // Call syscall function
    }else if (strcmp(command, "test") == 0){
        
    } else {
        terminal_setcolor(error_output_color);
        terminal_writestring("no such command. enter help for more info\n");
        terminal_setcolor(user_input_color);
    }
}

// Function to display OS information
void azbestFetch() {
    printf("Azbest OS ");
    printf(OS_VERSION);
    printf("\n");
}

// Function to display available commands
void help() {
    printf("clear - clears the screen\n");
    printf("azbestfetch - prints data about OS. basically azbest os version of neofetch :).\n");
    printf("setColor - sets color of user input.\n light green = 0, green = 1\n");
    printf("syscall - base syscall command\n");
}
