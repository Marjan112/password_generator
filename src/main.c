#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    int password_length;
    char c;
    do {
        printf("Enter password length: ");
        if(scanf("%d", &password_length) != 1) {
            while((c = getchar()) != '\n' && c != EOF);
            continue;
        }
    } while(password_length < 4 || password_length > 255);

    srand(time(NULL));
    char password[password_length + 1];
    memset(password, 0, password_length + 1);
    for(int i = 0; i < password_length; ++i) {
        password[i] = (rand() % (122 - 33 + 1)) + 33;
    }

    printf("Your password is: %s\n", password);
    return 0;
}