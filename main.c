#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
	const char *keywords[32];
	keywords[0] = "auto";
	keywords[1] = "double";
	keywords[2] = "int";
	keywords[3] = "struct";
	keywords[4] = "const";
	keywords[5] = "float";
	keywords[6] = "short";
	keywords[7] = "unsigned";
	keywords[8] = "break";
	keywords[9] = "else";
	keywords[10] = "long";
	keywords[11] = "switch";
	keywords[12] = "continue";
	keywords[13] = "for";
	keywords[14] = "signed";
	keywords[15] = "void";
	keywords[16] = "case";
	keywords[17] = "enum";
	keywords[18] = "register";
	keywords[19] = "typedef";
	keywords[20] = "default";
	keywords[21] = "goto";
	keywords[22] = "sizeof";
	keywords[23] = "volatile";
	keywords[24] = "char";
	keywords[25] = "extern";
	keywords[26] = "return";
	keywords[27] = "union";
	keywords[28] = "do";
	keywords[29] = "if";
	keywords[30] = "static";
	keywords[31] = "while";

	FILE *fid = fopen("input", "r");
	if (fid == NULL) {
		exit(EXIT_FAILURE);
	}
	int c;
	int preprocessorDirective = 0;
	int characterConstant = 0;
	int identifier = 0;
	char buffer[100] = { 0 };
	int bufferIndex = 0;
	int i;
	while ((c = fgetc(fid)) != EOF) {
		if (characterConstant && !((c == '\"') || (c == '\''))) {
			buffer[bufferIndex++] = c;
		} else if (c == '#'){
			preprocessorDirective = 1;
			printf("Preprocessor Directive:\n");
			printf("%c", c);
		} else if (preprocessorDirective) {
			if (c == '\n') {
				preprocessorDirective = 0;
			}
			printf("%c", c);
			//preprocessor directives !identifier && ((c == '_') || ( !!isalnum() ))
		} else if (!characterConstant && !identifier && ((c == '_') || (isalpha(c)) )) {
			identifier = 1;
			bufferIndex = 0;
			buffer[bufferIndex++] = c;
			//printf("\nsomething else:\n");
		} else if (!characterConstant && identifier && ((c == '_') || (isalnum(c)) )) {
			//printf("identifier continuing");
			buffer[bufferIndex++] = c;
		} else {
			if ( (c == '\"') || (c == '\'') ) {
				buffer[bufferIndex++] = c;
				if (characterConstant) {
					characterConstant = 0;
					buffer[bufferIndex] = '\0';
					bufferIndex = 0;
					printf("Constant: %s\n", buffer);
				} else {
					characterConstant = 1;
				}

			} else if (bufferIndex) {
				buffer[bufferIndex] = '\0';
				bufferIndex = 0;
				identifier = 0;
				for (i = 0; i < 32; i++) {
					if (strcmp(keywords[i], buffer) == 0) {
						printf("Keyword: %s\n", buffer);
						break;
					}
				}
				if (i == 32) {
					printf("Identifier: %s\n", buffer);
				}
				if (ispunct(c)) {
					printf("Operators and Punctuations: %c\n", c);
				}
			} else if (ispunct(c)) {
				printf("Operators and Punctuations: %c\n", c);
			}
		}
	}
	return EXIT_SUCCESS;
}