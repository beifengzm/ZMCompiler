#include <stdio.h>
#include <stdlib.h>

#include "SyntaxTree.h"
#include "ThreeAdress.h"

const char* filename = "../source/main.zm";

int main(int argc, char** argv)
{
    scanFile(filename);
    parsingSyntaxTree();
    printSyntaxTree();
    generateIR("");
    freeTokenList();

    return 0;
}