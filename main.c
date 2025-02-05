#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <limits.h>


#define MAX_PATH 50
void authenticate();
void compute_sha256(const char *filename, char outputBuffer[SHA256_DIGEST_LENGTH * 2 + 1]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char buffer[1024];
    FILE *file = fopen(filename, "rb");

    if (!file) {
        perror("Error opening file");
        return;
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        SHA256_Update(&sha256, buffer, bytesRead);
    }

    fclose(file);
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[SHA256_DIGEST_LENGTH * 2] = '\0'; // Null-terminate the string
}
void secret_function()
{
    printf("You have found the secret function! 🎉\n");
    printf("You earned 40 points\n");
}
void authenticate(){
    unsigned int canary = 0xdeafbeef;
    char username[69]; //Dummy Size
    char STATIC_HASH[65] = "5d41402abc4b2a76b9719d911017c5925e3f8a7a4d9e7a3a3f2a1e9b5a1c5a2f";

    // read the username
    printf("Enter your username: ");
    scanf("%9s", username);

    // read and compute the hash for the password
    char resolved_path[MAX_PATH];
    if (!realpath("private_key", resolved_path)) {
        perror("Error resolving path");
        exit(EXIT_FAILURE);
    }
    char computed_hash[SHA256_DIGEST_LENGTH * 2 + 1];
    compute_sha256(resolved_path, computed_hash);


    // check for stack overflows
    // printf("%x\n", canary);
    if(canary != 0xdeafbeef){
        printf("Stack Smashing Detected! Exiting\n");
        
        exit(EXIT_FAILURE);
    }


    if (strncmp(computed_hash, STATIC_HASH, 64) == 0) {
        printf("Access Granted ✅\n");
        printf("You earned 30 points\n");
    } else {
        printf("Access Denied ❌\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {

    authenticate();

    printf("Exiting...\n");

    return EXIT_SUCCESS;
}
