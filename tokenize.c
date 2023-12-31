#include "samples/prototypes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// What cases does this test? Trace the code and find out!
static int fixed_test(void) {
    const char *input = "hip-po-pot-a-mus gir-affe e-le-phant kang-a-roo rhi-no-ce-ros";
    char word[100], sub[10];

    while (scan_token(&input, " ", word, sizeof(word))) {
        int nsyll = 0;
        const char *next = word;
        while (scan_token(&next, "-", sub, sizeof(sub))) {
            printf("%s", sub);
            nsyll++;
        }
        int nlett = 0;
        next = word;
        while (scan_token(&next, "-", sub, 2)) {
            nlett++;
        }
        printf(" (%d syllables, %d letters)\n", nsyll, nlett);
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc < 3) {
        return fixed_test();
    }

    const char *delim = argv[1];
    const char *input = argv[2];

    int bufsize = argc == 4 ? atoi(argv[3]) : strlen(input) + 1;
    char buf[bufsize];
    const char *remaining = input;
    printf("Tokenized: { ");
    while (scan_token(&remaining, delim, buf, sizeof(buf))) {
        printf("\"%s\" ", buf);
    }
    printf("}\n");

    return 0;
}
