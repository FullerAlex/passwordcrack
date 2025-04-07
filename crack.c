#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    // Hash the plaintext
    char *hash = md5(plaintext, strlen(plaintext));
    // Open the hash file
    FILE *fileHash = fopen(hashFilename, "r");
    //current has being tested
    char pickHash[33];

    // Loop through the hash file, one line at a time.
    while((fgets(pickHash, 33, fileHash)))
    {

        // Attempt to match the hash from the file to the
        // hash of the plaintext.
        if(strcmp(pickHash, hash) == 0)
        {
            fclose(fileHash);
            return hash;
        }
    }
    // If there is a match, you'll return the hash.
    // If not, return NULL.
    fclose(fileHash);
    free(hash);
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Open the dictionary file for reading.
    char *dictionary = argv[2];
    char *hashes = argv[1];
    FILE *dictFile = fopen(dictionary, "r"); 
    char line[PASS_LEN];
    //tracks number of found words
    int wordCount = 0;

    // For each dictionary word, pass it to tryWord, which
    // will attempt to match it against the hashes in the hash_file.
    while((fgets(line, sizeof(line), dictFile)))
    {

        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == '\n')
            {
                line[i] = '\0';
                break;
            }
        } 

        // If we got a match, display the hash and the word.
        char *found = tryWord(line, hashes);
        if (found != NULL)
        {
            printf("%s %s\n", found, line);
            wordCount++;
            free(found);
        }
    }
    fclose(dictFile);
    // Display the number of hashes that were cracked.
    printf("%d hashes cracked!\n", wordCount);
}




//clang crack.c md5.c -l crypto