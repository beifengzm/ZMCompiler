#include <stdio.h>
#include <stdlib.h>

#include "SyntaxTree.h"

const char* filename = "../source/main.zm";

int main(int argc, char** argv)
{
    scanFile(filename);
    parsingSyntaxTree();
    printSyntaxTree();
    freeTokenList();

    return 0;
}