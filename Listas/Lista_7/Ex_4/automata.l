%option noyywrap 

%{
    int total_lines = 1;
    int blank_lines = 0;
    int lines_with_comment = 0;
    int not_blank_no_comment = 0;
    int semi_colons = 0;
    int preprocessor_directives = 0;
%}
%x IN_COMMENT

%%

<INITIAL>{
"/*" { BEGIN(IN_COMMENT); }
";" { semi_colons++; }
"#include" { preprocessor_directives++; }
"#define" { preprocessor_directives++; }
"//" { lines_with_comment++; }
^[ ]*[\n] { blank_lines++; total_lines++; }
[\n] { total_lines++; }
. 
}

<IN_COMMENT>{
"*/"    { lines_with_comment++; BEGIN(INITIAL); }
[^*\n]+ 
"*"
[\n] { lines_with_comment++; total_lines++; }
}

%%

void format_number_with_spaces(int value, int plus){

    int spaces = 0;

    if(value < 10) {
        spaces = 5;
    } else if (value < 100) {
        spaces = 4;
    } else if (value < 1000) {
        spaces = 3;
    } else if (value < 10000) {
        spaces = 2;
    } else if (value < 100000) {
        spaces = 1;
    }

    spaces += plus;

    for(int i = 0; i < spaces; i++) {
        printf(" ");
    }

    printf("%d ", value);
}

int main (int argc, char *argv[]) {

    if(argc < 2) {
        return 0;
    }

    printf(" total    blank lines w/   nb, nc    semi- preproc. file\n");
	printf(" lines    lines comments    lines   colons  direct.\n");
	printf("------+--------+--------+--------+--------+--------+----\n");

    int final_total, final_blank, final_comment, final_not_blank, final_semi_colons, final_preprocessor_directives;

    final_total = 0;
    final_blank = 0;
    final_comment = 0;
    final_not_blank = 0;
    final_semi_colons = 0;
    final_preprocessor_directives = 0;

    for(int i = 1; i < argc; i++) {

        FILE *file = fopen(argv[i], "r");
        if(!file) {
            perror(argv[i]);
            return 1;
        }

        total_lines = 1;
        blank_lines = 0;
        lines_with_comment = 0;
        not_blank_no_comment = 0;
        semi_colons = 0;
        preprocessor_directives = 0;

        yyrestart(file);
        yylex();

        final_total += total_lines;
        final_blank += blank_lines;
        final_comment += lines_with_comment;
        final_not_blank += (total_lines - blank_lines - lines_with_comment);
        final_semi_colons += semi_colons;
        final_preprocessor_directives += preprocessor_directives;
        not_blank_no_comment = total_lines - blank_lines - lines_with_comment;

        fclose(file);
        
        format_number_with_spaces(total_lines, 0);
        format_number_with_spaces(blank_lines, 2);
        format_number_with_spaces(lines_with_comment, 2);
        format_number_with_spaces(not_blank_no_comment, 2);
        format_number_with_spaces(semi_colons, 2);
        format_number_with_spaces(preprocessor_directives, 2);
        printf("%s\n", argv[i]);
    }

    format_number_with_spaces(final_total, 0);
    format_number_with_spaces(final_blank, 2);
    format_number_with_spaces(final_comment, 2);
    format_number_with_spaces(final_not_blank, 2);
    format_number_with_spaces(final_semi_colons, 2);
    format_number_with_spaces(final_preprocessor_directives, 2);
    printf("total (all files)\n");

    printf("------+--------+--------+--------+--------+--------+----\n");

}