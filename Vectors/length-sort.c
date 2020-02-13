#include <stdio.h>
#include <string.h>

#include "svec.h"

void
sort(svec* xs)
{
    // TODO: --DONE-- sort input vector by string length
    // see "man 3 strlen"
    int pos = 0;
    while(pos < xs->size) {
	    if(pos == 0 || strlen(xs->data[pos]) >= strlen(xs->data[pos - 1])) { 
		    // if proper order by string size
		    pos = pos + 1; // we good, move on
	    }
	    else {
		    // if improper order by string size
		    svec_swap(xs, pos, pos - 1); // call the swap we already made
		    pos = pos - 1; // this length could be shorter than a few pervious
	    }
    }
}

void
chomp(char* text)
{
    // TODO: --DONE--  Modify input string to remove trailing newline ('\n')
    int len = strlen(text);
    if (text[len - 1] == '\n') {
	    text[len - 1] = '\0';
    }
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage:\n  %s input-file\n", argv[0]);
        return 1;
    }

    FILE* fh = fopen(argv[1], "r");
    if (!fh) {
        perror("open failed");
        return 1;
    }

    svec* xs = make_svec();
    char temp[128];

    while (1) {
        char* line = fgets(temp, 128, fh);
        if (!line) {
            break;
        }

        chomp(line);
        svec_push_back(xs, line);
    }

    fclose(fh);

    sort(xs);

    for (int ii = 0; ii < xs->size; ++ii) {
        char* line = svec_get(xs, ii);
        printf("%s\n", line);
    }

    free_svec(xs);
    return 0;
}
