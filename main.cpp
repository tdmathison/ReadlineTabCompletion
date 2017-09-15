// ReadlineTabCompletion
//
// This is a small example to demo the tab completion and history feature of
// the readline C library.  The tab completion works at two levels so if you
// have tab completed one command you can further tab complete a sub-command
// as well.
//
// Author: Travis Mathison

#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <algorithm>
#include <iomanip>

// Core commands
constexpr char *g_core_commands[4] = {
    const_cast<char *>("exit"),
    const_cast<char *>("show"),
    const_cast<char *>("help"),
    nullptr
};

// Tab complete commands for the "show" command
constexpr char *g_show_commands[3] = {
    const_cast<char *>("options"),
    const_cast<char *>("info"),
    nullptr
};

// Called when the "show" command is executed
void exec_show() {
    std::cout << "usage: show options" << std::endl;
    std::cout << "       show info" << std::endl << std::endl;
}

// Called when the "show options" command is executed
void exec_show_options() {
    std::cout << "OPTION 1: X" << std::endl;
    std::cout << "OPTION 2: Y" << std::endl << std::endl;
}

// Called when the "show info" command is executed
void exec_show_info() {
    std::cout << "This is just an example command where you can tab" << std::endl
              << "complete after tab completing an initial command" << std::endl << std::endl;
}

// Called when the "help" command is executed
void exec_help() {
    std::cout << "Simple shell using readline with multiple levels of tab completion" << std::endl << std::endl;
    std::cout << "Core Commands" << std::endl;
    std::cout << "=============" << std::endl << std::endl;
    std::cout << std::setw(4) << "" << std::left <<std::setw(11) << "Command"
              << std::setw(25) << "Description" << std::endl;
    std::cout << std::setw(4) << "" << std::left << std::setw(11) << "-------"
              << std::setw(25) << "-----------" << std::endl;
    std::cout << std::setw(4) << "" << std::setw(7) << "help" << std::setw(4) << ""
              << std::left << std::setw(25) << "Shows this menu" << std::endl;
    std::cout << std::setw(4) << "" << std::setw(7) << "show" << std::setw(4) << ""
              << std::left << std::setw(25) << "Shows options and information" << std::endl;
    std::cout << std::setw(4) << "" << std::setw(7) << "exit" << std::setw(4) << ""
              << std::left << std::setw(25) << "Exits this shell" << std::endl << std::endl;
}

// Generator function that returns each matching command that the text is a substring of
char* command_name_generator(const char *text, int state) {
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = static_cast<int>(strlen(text));
    }

    std::string buffer(rl_line_buffer);

    // Tab completing sub-commands specific to the "show" command
    if (buffer.length() >= 4 && buffer.substr(0, 4) == "show") {
        while ((name = g_show_commands[list_index++])) {
            if (strncmp(name, text, static_cast<size_t>(len)) == 0) {
                return strdup(name);
            }
        }
    } else {
        // Level 1 core commands
        while ((name = g_core_commands[list_index++])) {
            if (strncmp(name, text, static_cast<size_t>(len)) == 0) {
                return strdup(name);
            }
        }
    }

    return nullptr;
}

// Called when you hit tab
char** command_name_completion(const char *text, int start, int end) {
    return rl_completion_matches(text, command_name_generator);
}

int main() {
    rl_attempted_completion_function = command_name_completion;

    bool exit = false;

    while (!exit) {
        // Display shell and receive line input from the user
        char *buffer = readline("shell > ");
        std::string command(buffer);

        // Trim whitespace from end
        size_t last = command.find_last_not_of(' ');
        command = command.substr(0, (last+1));

        // Check to see what command was entered
        if (buffer) {
            add_history(buffer);

            if (command == "exit") {
                exit = true;
            } else if (command == "help") {
                exec_help();
            } else if (command == "show") {
                exec_show();
            } else if (command == "show options") {
                exec_show_options();
            } else if (command == "show info") {
                exec_show_info();
            } else if (!command.empty()){
                std::cout << "Unknown command." << std::endl << std::endl;
            }

            free(buffer);
        }
    }

    return 0;
}
