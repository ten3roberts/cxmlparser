#include "xmlparser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char** argv)
{
	char filepath[2048];
	if (argc > 1)
		strcpy(filepath, argv[1]);
	else
	{
		scanf("%s", filepath);
	}

	XMLNode* root = xml_loadfile(filepath);
	xmlprint_tree(root);
}