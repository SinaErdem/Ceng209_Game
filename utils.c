#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()
#include "utils.h"

void clear_screen() {
#ifdef _WIN32
    system("cls"); // Windows için ekran temizleme
#else
    system("clear"); // Linux/Mac için ekran temizleme
#endif
}

void print_delayed(const char *message) {
    while (*message) {
        printf("%c", *message++);
        fflush(stdout); // Anında ekrana yazdır
        usleep(50000);  // 50 ms gecikme
    }
    printf("\n");
}
