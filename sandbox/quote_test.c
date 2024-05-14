#include <stdio.h>
#include <string.h>

/*void removeQuotes(char *str) {
    char *src = str;
    char *dst = str;
    int inQuotes = 0;

    // Count the number of single and double quotes
    int singleQuotes = 0;
    int doubleQuotes = 0;

    while (*src) {
        if (*src == '\'') {
            singleQuotes++;
        } else if (*src == '"') {
            doubleQuotes++;
        }
        src++;
    }

    // If both single and double quotes are even, remove them
    if (singleQuotes % 2 == 0 && doubleQuotes % 2 == 0) {
        src = str; // Reset source pointer

        while (*src) {
            if (*src == '\'' || *src == '"') {
                // Toggle inQuotes when encountering a quote
                inQuotes = !inQuotes;
                src++;
                continue;
            }
            
            // Copy characters from src to dst
            *dst = *src;
            dst++;
            src++;
        }

        // Null-terminate the modified string
        *dst = '\0';
    }
}*/



int main() {
    char str[] = "hello""world";
    
    printf("Before: %s\n", str);
    
    check_in_cmd_array_for_quotes(str);
    
    printf("After: %s\n", str);
    
    return 0;
}