#include <stdio.h>
#include <stdlib.h>

char *readline(FILE*);

int main(void)
{
        FILE *fs = fopen("foo.txt", "r");

        char *line;

        while((line = readline(fs)) != NULL){
                printf("%s\n", line);
                free(line);
        }

        fclose(fs);
}

char *readline(FILE *fs)
{
        int offset = 0;
        int bufsize = 4;
        char *buf;
        int c;

        if((buf = malloc(bufsize)) == NULL){
                return NULL;
        }

        while(c = fgetc(fs), c != '\n' && c != EOF){ /* Fill the buffer with the current line */

                if(offset == bufsize - 1){
                        bufsize *= 2;

                        char *new_buf;

                        if((new_buf = realloc(buf, bufsize)) == NULL){
                                free(buf);
                                return NULL;
                        }

                        buf = new_buf;
                }

                buf[offset++] = c;
        }

        if(c == EOF && offset == 0){ /* No data was read (EOF)*/
                free(buf);
                return NULL;
        }

        if(offset < bufsize - 1){ /* If buffer is too big (Accounting for null terminator) */
                char *new_buf;
                if((new_buf = realloc(buf, offset + 1)) == NULL){
                        free(buf);
                        return NULL;
                }

                buf = new_buf;
        }

        buf[offset] = '\0';

        return buf;

}