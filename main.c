#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear system("clear||@cls");
#define COMMAND_LEN 256
#define boolean char

typedef struct fac_struct {
    char* name;
    struct fac_struct* next;
    struct fac_struct* prev;
} f_node;
typedef struct fac_head {
    struct fac_struct* first;
    struct fac_struct* last;
    int cnt;
} f_head;
typedef struct student_struct {
    char* name;
    f_node* faculty;
    int no;
    int age;
    int id;
    float avg_score;
    float completion_rate;
    int gia_results[3];
    struct student_struct *next;
    struct student_struct *prev;
} node;
typedef struct student_head {
    struct student_struct* first;
    struct student_struct* last;
    int cnt;
} head;


/** Called by User **/
void enter(head * hd, f_head * f_hd, char* cmd);
void import(head * hd, f_head * f_hd, char * cmd);
void export(head * hd, char * cmd);
void show(head * hd, char * cmd);
void change(head * hd, f_head * f_hd, char * cmd);
void swap(head * hd, char * cmd);
void sort(head * hd, char * cmd);
void filter(head* hd, char * cmd);
void delete_all(head * hd, f_head * f_hd);
void delete(head * hd, char * cmd);
void delete_by(head * hd, char * cmd);
void quick_look(head * hd);
void help(char * cmd);

/** Internal Functions **/
void csv_line_parser_(head *hd, f_head* f_hd, char* line);
f_node * foreign_key_(f_head *f_hd, char* fac_name);
void make_new_f_(f_head * f_hd, char * node_name);
void create_(head * hd, f_head * f_hd);
void UI_(head * hd, f_head * f_hd);
boolean cmd_check_(char * cmd, head * hd, f_head * f_hd);
boolean func_cmp_(char * cmd, char * compare);
char* just_copy_(const char* st);
void new_no_(head * hd);
void delete_node_(head * hd, node * student);
void delete_str_(head * hd, char* (*field)(node*), char how, char * value);
void delete_int_(head * hd, char column, char how, int value);
void delete_float_(head * hd, char column, char how, float value);
void filter_int_(head * hd, char column, char how, int value);
void filter_float_(head * hd, char column, char how, float value);
void filter_str_(head * hd, char* (*field)(node*), char how, char * value);
void swap_(node * temp0, node * temp1);
void swap_cpy_(node * buff, node * temp1);
void q_sort_(node * left, node * right, char mode, char ad);
void str_q_sort_(node * left, node * right, char* (*field)(node*), char ad);
char* get_name_(node * student);
char* get_fac_name_(node * student);
void output_(node * student);

/** BFuncs **/
char* bgets(char *st, int len, FILE *fp);
int ibgets(FILE *fp);
float fbgets(FILE *fp);
char** split(char *line, char sep);
int strcount(char* in, char* substring);


int main() {
    f_head * f_hd;
    head * hd;
    printf("Welcome to Kartoteka v1.0\n"
           " ___   ___   ________   ______   _________  ______   _________  ______   ___   ___   ________      \n"
           "/___/\\/__/\\ /_______/\\ /_____/\\ /________/\\/_____/\\ /________/\\/_____/\\ /___/\\/__/\\ /_______/\\     \n"
           "\\::.\\ \\\\ \\ \\\\::: _  \\ \\\\:::_ \\ \\\\__.::.__\\/\\:::_ \\ \\\\__.::.__\\/\\::::_\\/_\\::.\\ \\\\ \\ \\\\::: _  \\ \\    \n"
           " \\:: \\/_) \\ \\\\::(_)  \\ \\\\:(_) ) )_ \\::\\ \\   \\:\\ \\ \\ \\  \\::\\ \\   \\:\\/___/\\\\:: \\/_) \\ \\\\::(_)  \\ \\   \n"
           "  \\:. __  ( ( \\:: __  \\ \\\\: __ `\\ \\ \\::\\ \\   \\:\\ \\ \\ \\  \\::\\ \\   \\::___\\/_\\:. __  ( ( \\:: __  \\ \\  \n"
           "   \\: \\ )  \\ \\ \\:.\\ \\  \\ \\\\ \\ `\\ \\ \\ \\::\\ \\   \\:\\_\\ \\ \\  \\::\\ \\   \\:\\____/\\\\: \\ )  \\ \\ \\:.\\ \\  \\ \\ \n"
           "    \\__\\/\\__\\/  \\__\\/\\__\\/ \\_\\/ \\_\\/  \\__\\/    \\_____\\/   \\__\\/    \\_____\\/ \\__\\/\\__\\/  \\__\\/\\__\\/ "
           "\nPlease, resize your window so that Kartoteka logo is readable and press Enter\n");
    getchar();
    clear

    /* Allocating Memory */
    f_hd = (f_head*)malloc(sizeof(f_head));
    hd = (head*)malloc(sizeof(head));
    create_(hd, f_hd);
    /* Launching User Interface */
    UI_(hd, f_hd);
    return 0;
}

void UI_(head * hd, f_head * f_hd) {
    char * cmd;
    boolean quit;
    quit = 0;
    cmd = malloc(COMMAND_LEN);
    quick_look(hd);
    while (!quit) {
        printf("\nType Help to see what Kartoteka can do\n"
               "Type Quit to quit\n\n");
        printf(">>> ");
        bgets(cmd, COMMAND_LEN - 1, stdin);
        if (strcount(cmd, "&") == 0)
            quit = cmd_check_(cmd, hd, f_hd);

    }
}

boolean cmd_check_(char * cmd, head * hd, f_head * f_hd) {
    boolean q;
    q = 0;
    if(func_cmp_(cmd, "Quit")) {
        printf("Thank You for using Kartoteka\n");
        q = 1;
    }
    else if(func_cmp_(cmd, "Enter")) {
        clear
        enter(hd, f_hd, cmd);
        printf("Done.\n");
        clear
    }
    else if(func_cmp_(cmd, "Import")) {
        import(hd, f_hd, cmd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Export")) {
        export(hd, cmd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Delete All")) {
        delete_all(hd, f_hd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Delete By")) {
        delete_by(hd, cmd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Delete")) {
        delete(hd, cmd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Show")) {
        show(hd, cmd);
    }
    else if(func_cmp_(cmd, "Sort")) {
        sort(hd, cmd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Change")) {
        change(hd, f_hd, cmd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Swap")) {
        swap(hd, cmd);
        printf("Done.\n");
    }
    else if(func_cmp_(cmd, "Filter")) {
        filter(hd, cmd);
    }
    else if(func_cmp_(cmd, "Quick")) {
        quick_look(hd);
    }
    else if(func_cmp_(cmd, "Help")) {
        help(cmd);
    }
    else if(func_cmp_(cmd, "Clear")) clear
    else {
        printf("typo error: Command not found: %s\n", cmd);
        if(cmd[0] > 'Z' || cmd[0] < 'A') printf("Note that all commands start with capital letter\n");
        else printf("Type 'Help' to see commands available\n\n");
    }
    return q;
}

void enter(head * hd, f_head * f_hd, char * cmd) {
    char * mode, * temp, * yn;
    node * student;
    int i;
    mode = malloc(3);
    if (*(cmd+5) != '\0') {
        cmd += 5;
        for(;*cmd == ' '; cmd++);
        if(!strcmp(cmd, "csv")) *mode = 'c';
        else if(!strcmp(cmd, "lbl")) *mode = 'l';
        else { printf("typo error: Mode %s not found\n", cmd); *mode = 0; }
        *(mode+1) = 0;
    }
    while (*mode == 0) {
        printf("How would you like to print data?\n1 - Line by line\n2 - CSV Format\n0 - Cancel\n\n");
        bgets(mode, 2, stdin);
        if (*mode == '1') *mode = 'l';
        else if (*mode == '2') *mode = 'c';
        else if (*mode == '0') *mode = 'a';
        else *mode = 0;
        if (*mode == 0) printf("typo error: Unexpected input. Write only '1', '2' or '0'.\n");
        fflush(stdin);
    }

    yn = malloc(3); *yn = 'Y'; *(yn+1) = 0;
    if (*mode == 'l') {
        while(*yn == 'Y' || *yn == 'y') {
            temp = malloc(41);
            student = (node*)malloc(sizeof(node));
            if(student == NULL) {printf("fatal error: Unknown Memory Error while allocating memory in Enter. (student)\n"); exit(1);}
            printf("Enter the name: ");
            bgets(temp, 32 - 1, stdin);
            student->name = just_copy_(temp);
            printf("Enter the faculty: ");
            bgets(temp, 32 - 1, stdin);
            student->faculty = foreign_key_(f_hd, temp);
            printf("Enter the Age: ");
            student->age = ibgets(stdin);
            printf("Enter the ID: ");
            student->id = ibgets(stdin);
            printf("Enter the Average Score: ");
            student->avg_score = fbgets(stdin);
            printf("Enter the Completion Rate: ");
            student->completion_rate = fbgets(stdin);
            for (i = 0; i < 3; i++) {
                printf("Enter the GIA Result #%d: ", i + 1);
                student->gia_results[i] = ibgets(stdin);
            }
            student->no = ++hd->cnt;
            student->next = NULL;
            if (hd->cnt < 1) {
                printf("fatal error: Unknown Error Negatives in counter (Enter: hd->cnt < 0)");
                exit(1);
            }
            if (hd->cnt == 1) {
                hd->first = student;
                hd->last = student;
                student->prev = NULL;
            } else {
                student->prev = hd->last;
                hd->last->next = student;
                hd->last = student;
            }
            free(temp);
            printf("Would you like to Enter Line by line once more? (Y/N): ");
            bgets(yn, 3, stdin);
        }

    }
    else if (*mode == 'c') {
        temp = malloc(128);
        printf("Enter CSV Kartoteka line. Type Stop when finished:\n");
        bgets(temp, 127, stdin);
        while(strcmp(temp, "Stop") != 0) {
            if(strcount(temp, ";") != 8) {
                printf("typo error: Wrong Amount of Members in CSV\n"
                       "Input Should something like 'one;two;3;4;5;6;7;8;9'\n"
                       "Type Stop to finish\n");
            } else csv_line_parser_(hd, f_hd, temp);

            bgets(temp, 127, stdin);
        }
    }
}

void import(head * hd, f_head * f_hd, char * cmd) {
    FILE * fp = NULL;
    char * file_name, * line;
    boolean cancel;
    file_name = malloc(32);

    if(*(cmd+6) != '\0') {
        cmd += 7;
        file_name = just_copy_(cmd);
    } else {
        printf("Type File Name to import from (Just hit Enter to cancel): ");
        bgets(file_name, 31, stdin);
    }

    cancel = 0;
    if(*file_name != '\0') fp = fopen(file_name, "r");
    else cancel = 1;

    while(fp == NULL && cancel == 0) {
        printf("typo error: Can not open file '%s'. Maybe that file does not exist?\n"
               "Type file name once again (Just hit Enter to cancel): ", file_name);
        bgets(file_name, 31, stdin);
        if(*file_name != '\0') fp = fopen(file_name, "r");
        else cancel = 1;
    }

    if(!cancel) {
        line = malloc(128);
        while (bgets(line, 128, fp) != NULL) {
            csv_line_parser_(hd, f_hd, line);
        }
    }

    fclose(fp);
}

void export(head * hd, char * cmd) {
    FILE * fp = NULL;
    char * file_name, * yn;
    node * temp;
    unsigned long i;
    boolean cancel;
    cancel = 0;
    if(hd->cnt == 0) {
        printf("warning: Kartoteka is empty.\n"
               "Are you sure you want to continue? (Y/N): ");
        yn = malloc(3);
        bgets(yn, 11, stdin);
        cancel = 1;
        if((*yn == 'Y' || *yn == 'y') && *(yn+1) == '\0') cancel = 0;
    }
    if(!cancel) {
        file_name = malloc(32);

        if (*(cmd + 6) != '\0') {
            cmd += 7;
            file_name = just_copy_(cmd);
        } else {
            printf("Type File Name to export to (Just hit Enter to cancel): ");
            bgets(file_name, 31, stdin);
        }

        cancel = 0;
        if (*file_name != '\0') fp = fopen(file_name, "r");
        else cancel = 1;
        if (fp != NULL) {
            yn = malloc(3);
            cancel = 1;
            printf("warning: File '%s' already exists.\n"
                   "This will overwrite file\n"
                   "Are you sure you want to continue? (Y/N): ", file_name);
            bgets(yn, 11, stdin);
            if ((*yn == 'Y' || *yn == 'y') && *(yn + 1) == '\0') cancel = 0;
        }
        fclose(fp);

        if (!cancel) {
            fp = fopen(file_name, "w");
            for (temp = hd->first, i = 0; temp != NULL; temp = temp->next, i++) {
                fprintf(fp, "%s;%s;%d;%d;%.3f;%.2f;%d;%d;%d",
                        temp->name,
                        temp->faculty->name, temp->age, temp->id,
                        temp->avg_score, temp->completion_rate,
                        temp->gia_results[0], temp->gia_results[1], temp->gia_results[2]);
                if (temp->next != NULL) fprintf(fp, "\n");
            }
        }
    }
    fclose(fp);
}

void quick_look(head * hd) {
    unsigned long count;
    int i;
    node * temp;
    count = 0;
    if (!hd->cnt) printf("Kartoteka is empty for now.\n"
                         "Use Enter or Import to fill it.\n");
    else {
        printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
        for (temp = hd->first; temp != NULL && count < 5; temp = temp->next, count++) {
            printf("| %-2d | %-2d | %-23s | %-7s | %-3d | %.3f | %.2f | %-3d | %-3d | %-3d |\n",
                   temp->no, temp->id, temp->name,
                   temp->faculty->name, temp->age,
                   temp->avg_score, temp->completion_rate,
                   temp->gia_results[0], temp->gia_results[1], temp->gia_results[2]);
        }
        if(hd->cnt - 5 > 0) { for(i = 0; i <= 85; i++) printf("-"); printf("\n| Hidden : %-5d %68s|\n", hd->cnt - 5, " "); }
    }

}

void show(head * hd, char * cmd) {
    int maks;
    unsigned int i;
    char * st = NULL;
    node * temp;
    maks = 0;
    if(*(cmd+4) != '\0') {
        st = cmd + 5;
        if(*st > '9' || *st < '0')
            while (maks == 0) {
                printf("typo error: Argument of Show function should be a number.\n"
                       "Print number of max lines (0 if no bounds, -1 to cancel): ");
                maks = ibgets(stdin);
            }
        else maks = (int)strtol(st, NULL, 10);
    }
    if (maks != -1) {
        if (!hd->cnt)
            printf("Kartoteka is empty for now.\n"
                   "Use Enter or Import to fill it.\n");
        else {
            printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age",
                   "Score", "C.R.", "GIA Results");
            for (temp = hd->first, i = 0; temp != NULL && (i < maks || maks == 0); temp = temp->next, i++) {
                printf("| %-2d | %-2d | %-23s | %-7s | %-3d | %.3f | %.2f | %-3d | %-3d | %-3d |\n",
                       temp->no, temp->id, temp->name,
                       temp->faculty->name, temp->age,
                       temp->avg_score, temp->completion_rate,
                       temp->gia_results[0], temp->gia_results[1], temp->gia_results[2]);
            }
            if (hd->cnt - maks > 0 && maks > 0) {
                for (i = 0; i <= 85; i++) printf("-");
                printf("\n| Hidden : %-5d %68s|\n", hd->cnt - maks, " ");
            }
        }
    }
}

void change(head * hd, f_head * f_hd, char * cmd) {
    int no, num_len, i, line;
    char * mode, * temp, ** splitLine;
    node * student;

    mode = malloc(3);
    if(mode == NULL) {
        printf("fatal error: Unknown Memory Error while allocating memory in Change. (mode)\n");
        exit(1);
    }
    *mode = 0;
    if(*(cmd + 6) != '\0') {
        cmd += 6;
        for(;*cmd == ' '; cmd++);
        if(*cmd < '9' && *cmd > '0') {
            no = (int)strtol(cmd, NULL, 10);
            if(no > 0) {
                num_len = 0;
                for (i = no; i; i /= 10, num_len++);
                cmd += num_len;
                if(*cmd != '\0') {
                    for (; *cmd == ' '; cmd++);
                    if (!strcmp(cmd, "csv")) *mode = 'c';
                    else if (!strcmp(cmd, "lbl")) *mode = 'l';
                    else printf("typo error: Mode %s not found\n", cmd);
                }
            }
        }
        else {
            printf("typo error: First argument of Change function should be a number.\n"
                   "Print number of a line to change (0 to cancel): ");
            no = ibgets(stdin);
        }
    } else {
        printf("Print No of element to change (0 to cancel): ");
        no = ibgets(stdin);
    }
    if(no > 0 && no <= hd->cnt) {
        while(*mode == 0) {
            printf("How would you like to print data?\n1 - Line by line\n2 - CSV Format\n0 - Cancel\n");
            line = ibgets( stdin);
            if(line == 1) *mode = 'l';
            else if(line == 2) *mode = 'c';
            else if(line == 0) *mode = 'q';
            else printf("typo error: Unexpected input. Write only '1', '2' or '0'.\n");
        }
         if(*mode != 'q') {
            for (student = hd->first; student != NULL && student->no != no; student = student->next);
            if (student == NULL) printf("error: Element with No %d not found\n", no);
            else {
                if (*mode == 'l') {
                    temp = malloc(41);
                    if(temp == NULL) {
                        printf("fatal error: Unknown Memory Error while allocating memory in Change. (temp)\n");
                        exit(1);
                    }
                    printf("Enter the name: ");
                    bgets(temp, 32 - 1, stdin);
                    student->name = just_copy_(temp);
                    printf("Enter the faculty: ");
                    bgets(temp, 32 - 1, stdin);
                    student->faculty = foreign_key_(f_hd, temp);
                    printf("Enter the Age: ");
                    student->age = ibgets(stdin);
                    printf("Enter the ID: ");
                    student->id = ibgets(stdin);
                    printf("Enter the Average Score: ");
                    student->avg_score = fbgets(stdin);
                    printf("Enter the Completion Rate: ");
                    student->completion_rate = fbgets(stdin);
                    for (i = 0; i < 3; i++) {
                        printf("Enter the GIA Result #%d: ", i + 1);
                        student->gia_results[i] = ibgets(stdin);
                    }
                    free(temp);
                } else if (*mode == 'c') {
                    temp = malloc(128);
                    bgets(temp, 127, stdin);
                    if(strcount(temp, ";") != 8) {
                        printf("typo error: Wrong Amount of Members in CSV\n"
                               "Input Should be something like 'one;two;3;4;5;6;7;8;9'\n"
                               "Type Stop to finish\n");
                    } else {
                        splitLine = split(temp, ';');
                        if (splitLine == NULL) {
                            printf("fatal error: Unknown Memory Error while parsing CSV line. (Change: splitLine)\n");
                            exit(1);
                        }
                        student->name = splitLine[0];
                        student->faculty = foreign_key_(f_hd, splitLine[1]);
                        student->age = (int) strtol(splitLine[2], NULL, 10);
                        student->id = (int) strtol(splitLine[3], NULL, 10);
                        student->avg_score = (float)atof(splitLine[4]);
                        student->completion_rate = (float)atof(splitLine[5]);
                        for (i = 0; i < 3; i++) student->gia_results[i] = (int) strtol(splitLine[6 + i], NULL, 10);
                        free(splitLine);
                    }
                }
            }
        }
    } else if (no > hd->cnt) printf("error: This No is out of bounds\n");
}

void csv_line_parser_(head *hd, f_head* f_hd, char* line) {
    int j;
    node *db, *temp;
    char **splitLine;
    db = (node*)malloc(sizeof(node));
    if(db == NULL) {
        printf("fatal error: Unknown Memory Error while parsing CSV line. (db)\n");
        exit(1);
    }
    splitLine = split(line, ';');
    if(splitLine == NULL) {
        printf("fatal error: Unknown Memory Error while parsing CSV line. (splitLine)\n");
        exit(1);
    }

    db->name = splitLine[0];
    db->faculty = foreign_key_(f_hd, splitLine[1]);
    db->age = (int)strtol(splitLine[2], NULL, 10);
    db->id = (int)strtol(splitLine[3], NULL, 10);
    db->avg_score = (float)atof(splitLine[4]);
    db->completion_rate = (float)atof(splitLine[5]);
    for(j = 0; j < 3; j++) db->gia_results[j] = (int)strtol(splitLine[6+j], NULL, 10);
    db->next = NULL;
    db->no = ++hd->cnt;
    if (hd->cnt < 1) {printf("fatal error: Unknown Error Negatives in counter (Parser: hd->cnt < 0)"); exit(1);}
    if(hd->cnt == 1) {
        hd->first = db;
        db->prev = NULL;
    } else {
        temp = hd->last;
        temp->next = db;
        db->prev = temp;
    }
    hd->last = db;
    free(splitLine);
}

void delete_all(head * hd, f_head * f_hd) {
    node * temp;
    f_node * f_temp;
    if (hd->cnt > 0) {
        temp = hd->first;
        hd->first = NULL;
        hd->last = NULL;
        hd->cnt = 0;
        if(temp->next != NULL) {
            for (temp = temp->next; temp->next != NULL; free(temp->prev), temp = temp->next);
            free(temp);
        } else {
            free(temp);
        }
    }
    if(f_hd->cnt > 0)
    {
        f_temp = f_hd->first;
        f_hd->first = NULL;
        f_hd->last = NULL;
        f_hd->cnt = 0;
        if(f_temp->next != NULL) {
            for (f_temp = f_temp->next; f_temp->next != NULL; free(f_temp->prev), f_temp = f_temp->next);
            free(f_temp->prev);
            free(f_temp);
        } else {
            free(f_temp);
        }
    }
}

void delete(head * hd, char * cmd) {
    int no;
    node * student;
    if(*(cmd + 6) != '\0') {
        cmd += 6;
        for(;*cmd == ' '; cmd++);
        if(*cmd < '9' && *cmd > '0') no = (int)strtol(cmd, NULL, 10);
        else {
            printf("Argument of Delete function should be a number.\n"
                   "Print number of a line to delete (0 to cancel): ");
            no = ibgets(stdin);
        }
    } else {
        printf("Print No of element to delete (0 to cancel): ");
        no = ibgets(stdin);
    }
    if(no > 0 && no <= hd->cnt) {
        for(student = hd->first; student != NULL && student->no != no; student = student->next);
        if (student == NULL) printf("error: Element with No %d not found\n", no);
        else {
            if(no == 1) {
                hd->first = student->next;
                hd->first->prev = NULL;
                free(student);
            }
            else if (no == hd->cnt) {
                hd->last = student->prev;
                hd->last->next = NULL;
                free(student);
            }
            else {
                student->prev->next = student->next;
                student->next->prev = student->prev;
                free(student);
            }
            hd->cnt--;
            new_no_(hd);
        }
    }
    else if (no > hd->cnt) printf("error: This No is out of bounds\n");
}

void delete_by(head* hd, char * cmd) {
    char column, how;
    char * line_value;
    int int_value;
    float float_value;
    boolean done;
    done = 0;
    column = -3;
    if(*(cmd+9) != '\0') {
        for(cmd+=9; *cmd == ' '; cmd++);
        if(func_cmp_(cmd, "Name")) { column = -2; cmd += 4;}
        else if(func_cmp_(cmd, "Faculty")) { column = -1; cmd += 7;}
        else if(func_cmp_(cmd, "No")) { column = 0; cmd += 2;}
        else if(func_cmp_(cmd, "Age")) { column = 1; cmd += 3;}
        else if(func_cmp_(cmd, "ID")) { column = 2; cmd += 2;}
        else if(func_cmp_(cmd, "Score")) { column = 3; cmd += 5;}
        else if(func_cmp_(cmd, "CR")) { column = 4; cmd += 2;}
        else if(func_cmp_(cmd, "GIA 1")) { column = 5; cmd += 5;}
        else if(func_cmp_(cmd, "GIA 2")) { column = 6; cmd += 5;}
        else if(func_cmp_(cmd, "GIA 3")) { column = 7; cmd += 5;}
        else printf("typo error: Column not found.\n");
        if(*cmd != '\0' && column != -3) {
            for(;*cmd == ' '; cmd++);
            if(func_cmp_(cmd, "==")) { how = 4; cmd+=2;}
            else if(func_cmp_(cmd, "=")) { how = 1; cmd++;}
            else if(func_cmp_(cmd, ">=")) { how = 3; cmd+=2;}
            else if(func_cmp_(cmd, ">")) { how = 2; cmd++;}
            else if(func_cmp_(cmd, "<=")) { how = -2 ; cmd+=2;}
            else if(func_cmp_(cmd, "<")) { how = -1; cmd++;}
            if(*cmd != '\0' && how != 0) {
                for(;*cmd == ' '; cmd++);
                if(column < 0) {
                    line_value = malloc(32);
                    line_value = cmd;
                    if(how == 1 || how == 4)
                    {
                        if(column == -1)
                            delete_str_(hd, get_fac_name_, how, line_value);
                        if(column == -2)
                            delete_str_(hd, get_name_, how, line_value);
                        done = 1;
                    }
                } else if (column == 3 || column == 4) {
                    if(how == 4) how = 1;
                    float_value = (float)atof(cmd);
                    delete_float_(hd, column, how, float_value);
                    done = 1;
                } else {
                    if(how == 4) how = 1;
                    int_value = (int)strtol(cmd, NULL, 10);
                    delete_int_(hd, column, how, int_value);
                    done = 1;
                }
            }
        }
    }
    if(!done) {
        while (column == -3) {
            printf("Choose Column to delete by\n"
                   "0 - Cancel\n"
                   "1 - Name\n"
                   "2 - Faculty\n"
                   "3 - No\n"
                   "4 - Age\n"
                   "5 - ID\n"
                   "6 - Score\n"
                   "7 - CR\n"
                   "8 - GIA 1\n"
                   "9 - GIA 2\n"
                   "10 - GIA 3\n\nColumn: ");
            column = ibgets(stdin);
            if (column == 0) column = -4;
            else if (column >= 1 && column <= 10) column -= 3;
            else {
                printf("typo error: Column not found.\n");
                column = -3;
            }
        }
        while (how == 0 && column != -4) {
            printf("Choose relation\n"
                   "0 - Cancel\n"
                   "1 - <=\n"
                   "2 - <\n"
                   "3 - =\n"
                   "4 - >\n"
                   "5 - >=\n"
                   "6 - ==\n\nRelation: ");
            how = ibgets(stdin);
            if (how == 0) column = -4;
            else if (how >= 1 && how <= 2) how -= 3;
            else if (how >= 3 && how <= 6) how -= 2;
            else {
                printf("typo error: Mode not found.\n");
                how = 0;
            }
        }
        if (column < 0 && column != -4) {
            line_value = malloc(32);
            if (how != 1 && how != 4) printf("typo error: Can only check equality of strings (=/==)\n");
            else {
                printf("Enter the Value: ");
                bgets(line_value, 31, stdin);
                if (column == -1)
                    delete_str_(hd, get_fac_name_, how, line_value);
                if (column == -2)
                    delete_str_(hd, get_name_, how, line_value);
            }
        } else if (column == 3 || column == 4) {
            printf("Enter the Value: ");
            if (how == 4) how = 1;
            float_value = fbgets(stdin);
            delete_float_(hd, column, how, float_value);
        } else if (column != -4) {
            printf("Enter the Value: ");
            if (how == 4) how = 1;
            int_value = ibgets(stdin);
            delete_int_(hd, column, how, int_value);
        }
    }
}

void delete_node_(head * hd, node * student) {
    if(hd->first == student) {
        hd->first = student->next;
        hd->first->prev = NULL;
        free(student);
    }
    else if(hd->last == student) {
        hd->last = student->prev;
        hd->last->next = NULL;
        free(student);
    }
    else {
        student->prev->next = student->next;
        student->next->prev = student->prev;
        free(student);
    }
    hd->cnt--;
}

void delete_str_(head * hd, char* (*field)(node*), char how, char * value) {
    node * student;
    boolean printed;
    printed = 0;
    if(how == 4) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (!strcmp(field(student), value)) {
                delete_node_(hd, student);
            }
        }
    }
    else if(how == 1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (func_cmp_(field(student), value)) {
                delete_node_(hd, student);
            }
        }
    }
}

void delete_int_(head * hd, char column, char how, int value) {
    node * student;
    if (how == 1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) == value) {
                delete_node_(hd, student);
            }
        }
    }
    else if (how == 2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) > value) {
                delete_node_(hd, student);
            }
        }
    }
    else if (how == 3) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) >= value) {
                delete_node_(hd, student);
            }
        }
    } else if (how == -2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) <= value) {
                delete_node_(hd, student);
            }
        }
    } else if (how == -1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) < value) {
                delete_node_(hd, student);
            }
        }
    }
}

void delete_float_(head * hd, char column, char how, float value) {
    node * student;
    boolean printed;
    printed = 0;
    if (how == 1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) == value) {
                delete_node_(hd, student);
            }
        }
    }
    else if (how == 2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) > value) {
                delete_node_(hd, student);
            }
        }
    }
    else if (how == 3) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) >= value) {
                delete_node_(hd, student);
            }
        }
    } else if (how == -2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) <= value) {
                delete_node_(hd, student);
            }
        }
    } else if (how == -1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) < value) {
                delete_node_(hd, student);
            }
        }
    }
}

void filter(head* hd, char * cmd) {
    char column, how;
    char * line_value;
    int int_value;
    float float_value;
    boolean done;
    done = 0;
    column = -3;
    if(*(cmd+6) != '\0') {
        for(cmd+=6; *cmd == ' '; cmd++);
        if(func_cmp_(cmd, "Name")) { column = -2; cmd += 4;}
        else if(func_cmp_(cmd, "Faculty")) { column = -1; cmd += 7;}
        else if(func_cmp_(cmd, "No")) { column = 0; cmd += 2;}
        else if(func_cmp_(cmd, "Age")) { column = 1; cmd += 3;}
        else if(func_cmp_(cmd, "ID")) { column = 2; cmd += 2;}
        else if(func_cmp_(cmd, "Score")) { column = 3; cmd += 5;}
        else if(func_cmp_(cmd, "CR")) { column = 4; cmd += 2;}
        else if(func_cmp_(cmd, "GIA 1")) { column = 5; cmd += 5;}
        else if(func_cmp_(cmd, "GIA 2")) { column = 6; cmd += 5;}
        else if(func_cmp_(cmd, "GIA 3")) { column = 7; cmd += 5;}
        else printf("typo error: Column not found.\n");
        if(*cmd != '\0' && column != -3) {
            for(;*cmd == ' '; cmd++);
            if(func_cmp_(cmd, "==")) { how = 4; cmd+=2;}
            else if(func_cmp_(cmd, "=")) { how = 1; cmd++;}
            else if(func_cmp_(cmd, ">=")) { how = 3; cmd+=2;}
            else if(func_cmp_(cmd, ">")) { how = 2; cmd++;}
            else if(func_cmp_(cmd, "<=")) { how = -2 ; cmd+=2;}
            else if(func_cmp_(cmd, "<")) { how = -1; cmd++;}
            if(*cmd != '\0' && how != 0) {
                for(;*cmd == ' '; cmd++);
                if(column < 0) {
                    line_value = malloc(32);
                    line_value = cmd;
                    if(how == 1 || how == 4) {
                        if(column == -1)
                            filter_str_(hd, get_fac_name_, how, line_value);
                        if(column == -2)
                            filter_str_(hd, get_name_, how, line_value);
                        done = 1;
                    }
                } else if (column == 3 || column == 4) {
                    if(how == 4) how = 1;
                    float_value = (float)atof(cmd);
                    filter_float_(hd, column, how, float_value);
                    done = 1;
                } else {
                    if(how == 4) how = 1;
                    int_value = (int)strtol(cmd, NULL, 10);
                    filter_int_(hd, column, how, int_value);
                    done = 1;
                }
            }
        }
    }
    if(!done){
        while (column == -3) {
            printf("Choose Column to filter\n"
                   "0 - Cancel\n"
                   "1 - Name\n"
                   "2 - Faculty\n"
                   "3 - No\n"
                   "4 - Age\n"
                   "5 - ID\n"
                   "6 - Score\n"
                   "7 - CR\n"
                   "8 - GIA 1\n"
                   "9 - GIA 2\n"
                   "10 - GIA 3\n\nColumn: ");
            column = ibgets(stdin);
            if (column == 0) column = -4;
            else if (column >= 1 && column <= 10) column -= 3;
            else {
                printf("typo error: Column not found.\n");
                column = -3;
            }
        }
        while (how == 0 && column != -4) {
            printf("Choose relation to a value\n"
                   "0 - Cancel\n"
                   "1 - <=\n"
                   "2 - <\n"
                   "3 - =\n"
                   "4 - >\n"
                   "5 - >=\n"
                   "6 - ==\n\nRelation: ");
            how = ibgets(stdin);
            if (how == 0) column = -4;
            else if (how >= 1 && how <= 2) how -= 3;
            else if (how >= 3 && how <= 6) how -= 2;
            else {
                printf("typo error: Mode not found.\n");
                how = 0;
            }
        }
        if (column < 0 && column != -4) {
            line_value = malloc(32);
            if (how != 1 && how != 4) printf("typo error: Can only check equality of strings (=/==)\n");
            else {
                printf("Enter the Value: ");
                bgets(line_value, 31, stdin);
                if (column == -1)
                    filter_str_(hd, get_fac_name_, how, line_value);
                if (column == -2)
                    filter_str_(hd, get_name_, how, line_value);
            }
        } else if (column == 3 || column == 4) {
            printf("Enter the Value: ");
            if (how == 4) how = 1;
            float_value = fbgets(stdin);
            filter_float_(hd, column, how, float_value);
        } else if (column != -4) {
            printf("Enter the Value: ");
            if (how == 4) how = 1;
            int_value = ibgets(stdin);
            filter_int_(hd, column, how, int_value);
        }
    }
}
void filter_str_(head * hd, char* (*field)(node*), char how, char * value) {
    node * student;
    boolean printed;
    printed = 0;
    if(how == 4) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (!strcmp(field(student), value)) {
                if (!printed)
                    printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty",
                           "Age", "Score", "C.R.", "GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    else if(how == 1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (func_cmp_(field(student), value)) {
                if (!printed)
                    printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty",
                           "Age", "Score", "C.R.", "GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    if(!printed) printf("Nothing Found.\n");
}

void filter_int_(head * hd, char column, char how, int value) {
    node * student;
    boolean printed;
    printed = 0;
    if (how == 1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) == value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    else if (how == 2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) > value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    else if (how == 3) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) >= value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    } else if (how == -2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) <= value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    } else if (how == -1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->no + column) < value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    if(!printed) printf("Nothing Found.\n");
}

void filter_float_(head * hd, char column, char how, float value) {
    node * student;
    boolean printed;
    printed = 0;
    if (how == 1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) == value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    else if (how == 2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) > value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    else if (how == 3) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) >= value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    } else if (how == -2) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) <= value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    } else if (how == -1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (*(&student->avg_score + column - 3) < value) {
                if(!printed) printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
                output_(student);
                printed = 1;
            }
        }
    }
    if(!printed) printf("Nothing Found.\n");
}

void output_(node * student) {
    printf("| %-2d | %-2d | %-23s | %-7s | %-3d | %.3f | %.2f | %-3d | %-3d | %-3d |\n",
           student->no, student->id, student->name,
           student->faculty->name, student->age,
           student->avg_score, student->completion_rate,
           student->gia_results[0], student->gia_results[1], student->gia_results[2]);
}




void sort(head * hd, char * cmd) {
    char mode, ad;
    mode = 0; ad = 0;
    if(*(cmd+4) != '\0') {
        cmd += 4;
        while(*cmd == ' ') cmd++;
        if(func_cmp_(cmd, "Name")) { mode = -2; cmd += 4;}
        else if(func_cmp_(cmd, "Faculty")) { mode = -1; cmd += 7;}
        else if(func_cmp_(cmd, "Age")) { mode = 1; cmd += 3;}
        else if(func_cmp_(cmd, "ID")) { mode = 2; cmd += 2;}
        else if(func_cmp_(cmd, "Score")) { mode = 3; cmd += 5;}
        else if(func_cmp_(cmd, "CR")) { mode = 4; cmd += 2;}
        else if(func_cmp_(cmd, "GIA 1")) { mode = 5; cmd += 5;}
        else if(func_cmp_(cmd, "GIA 2")) { mode = 6; cmd += 5;}
        else if(func_cmp_(cmd, "GIA 3")) { mode = 7; cmd += 5;}
        else printf("typo error: Column not found.\n");
        if (*cmd != '\0' && mode != 0) {
            while (*cmd == ' ') cmd++;
            if(*cmd == 'a') ad = 1;
            else if(*cmd == 'd') ad = -1;
        }
    }
    while(mode == 0) {
        printf("Choose Column to sort\n"
               "0 - Cancel\n"
               "1 - Name\n"
               "2 - Faculty\n"
               "3 - Age\n"
               "4 - ID\n"
               "5 - Score\n"
               "6 - CR\n"
               "7 - GIA 1\n"
               "8 - GIA 2\n"
               "9 - GIA 3\n\nColumn: ");
        mode = ibgets(stdin)-2;
        if (mode <= 0) mode -= 1;
        if(mode < -3 || mode > 7) { mode = 0; printf("typo error: column not found.\n"); }
    }
    while(ad == 0 && mode != -3) {
        printf("How to sort?\n0 - Cancel\n1 - Ascending\n2 - Descending\n\nMode: ");
        ad = (char)ibgets(stdin);
        if(ad > 2 || ad < 1) {printf("error: sort mode not found\n"); ad = 0;}
        if(ad == 2) ad = -1;
        if(ad == 0) ad = -3;
    }
    if(ad != -3 && mode != -3) {
        if (mode > 0 && mode <= 7)
            q_sort_(hd->first, hd->last, mode, ad);
        else if (mode == -1)
            str_q_sort_(hd->first, hd->last, get_fac_name_, ad);
        else if (mode == -2)
            str_q_sort_(hd->first, hd->last, get_name_, ad);
        else
            printf("unknown error: Unknown operation mode of Sort (mode > 7 or mode < -3)\n");
    }
}

void q_sort_(node * left, node * right, char mode, char ad) {
    node * last, * current;
    if (left != right) {
        if (left->next == right) {
            if ((*(&left->no + mode))*ad > (*(&right->no + mode))*ad)
                swap_(left, right);
        } else {
            last = left;
            current = left;
            do {
                current = current->next;
                if ((*(&current->no + mode))*ad < (*(&left->no + mode))*ad) {
                    last = last->next;
                    swap_(last, current);
                }
            } while (current != right);
            swap_(left, last);
            q_sort_(left, last, mode, ad);
            if (last != right)
                q_sort_(last->next, right, mode, ad);
        }
    }
}

char* get_name_(node * student) { return student->name; }
char* get_fac_name_(node * student) { return student->faculty->name; }

void str_q_sort_(node * left, node * right, char* (*field)(node*), char ad) {
    node * last, * current;
    if (left != right) {
        if (left->next == right) {
            if((strcmp(field(left), field(right)) > 0 && ad == 1) || (strcmp(field(left), field(right)) < 0 && ad == -1))
                swap_(left, right);
        } else {
            last = left;
            current = left;
            do {
                current = current->next;
                if((strcmp(field(current), field(left)) < 0 && ad == 1) || (strcmp(field(current), field(left)) > 0 && ad == -1)) {
                    last = last->next;
                    swap_(last, current);
                }
            } while (current != right);
            swap_(left, last);
            str_q_sort_(left, last, field, ad);
            if (last != right)
                str_q_sort_(last->next, right, field, ad);
        }
    }
}

void swap_(node * temp0, node * temp1) {
    node * buff;

    buff = (node*)malloc(sizeof(node));

    swap_cpy_(buff, temp1);
    swap_cpy_(temp1, temp0);
    swap_cpy_(temp0, buff);

    free(buff);
}

void swap_cpy_(node * buff, node * temp1) {
    buff->name = just_copy_(temp1->name);
    buff->faculty = temp1->faculty;
    buff->age = temp1->age;
    buff->id = temp1->id;
    buff->avg_score = temp1->avg_score;
    buff->completion_rate = temp1->completion_rate;
    buff->gia_results[0] = temp1->gia_results[0];
    buff->gia_results[1] = temp1->gia_results[1];
    buff->gia_results[2] = temp1->gia_results[2];
}


void swap(head * hd, char * cmd) {
    int no1, no2;
    node * student1, * student2;
    boolean err;
    no1 = no2 = 0;
    err = 0;
    if(*(cmd + 4) != '\0') {
        for(cmd+=4; *cmd == ' '; cmd++);
        for(; err == 0 && *cmd != ' ' && *cmd != '\0'; cmd++) {
            if(*cmd >= '0' && *cmd <= '9') no1 = no1*10 + (int)(*cmd - '0');
            else {
                printf("typo error: Swap First Argument should be a number");
                no1 = 0;
                err = 1;
            }
        }
        if(!err && *cmd != '\0') {
            for (; *cmd == ' '; cmd++);
            for(; err == 0 && *cmd != ' ' && *cmd != '\0'; cmd++) {
                if(*cmd >= '0' && *cmd <= '9') no2 = no2*10 + (int)(*cmd - '0');
                else {
                    printf("typo error: Swap Second Argument should be a number");
                    no2 = 0;
                    err = 1;
                }
            }
        }
    }
    if(err == 1 || no1 == 0 || no2== 0) {
        while (no1 == 0) {
            printf("Type no of first string to swap: ");
            no1 = ibgets(stdin);
            if(no1 <= 0) printf("typo error: No should be a positive number\n");
        }
        while (no2 == 0) {
            printf("Type no of second string to swap: ");
            no2 = ibgets(stdin);
            if(no2 <= 0) printf("typo error: No should be a positive number\n");
        }
    }
    for(student1 = hd->first; student1 != NULL && student1->no != no1; student1 = student1->next);
    if (student1 == NULL) {
        printf("error: Element with No %d not found\n", no1);
    } else {
        for(student2 = hd->first; student2 != NULL && student2->no != no2; student2 = student2->next);
        if (student2 == NULL) printf("error: Element with No %d not found\n", no2);
        else swap_(student1, student2);
    }
}

f_node * foreign_key_(f_head *f_hd, char* fac_name) {
    f_node * node, * res;
    boolean found;
    found = 0;
    for(node = f_hd->first; node != NULL && found == 0; node = node->next) {
        if(!strcmp(fac_name, node->name)) {
            found = 1;
            res = node;
        }
    }
    if(!found) {
        make_new_f_(f_hd, fac_name);
        res = f_hd->last;
    }
    return res;
}

void make_new_f_(f_head * f_hd, char * node_name) {
    f_node * node;
    node = (f_node*)malloc(sizeof(f_node));
    node->name = just_copy_(node_name);
    node->next = NULL;
    if(!f_hd->cnt) {
        node->prev = NULL;
        f_hd->first = node;
        f_hd->last = node;
    } else {
        node->prev = f_hd->last;
        node->prev->next = node;
        f_hd->last = node;
    }
    f_hd->cnt++;
}

char** split(char *line, const char sep) {
    int separators_in_line, i, k, m;
    char** result_array = NULL;

    for (i = 0, separators_in_line = 0; i < strlen(line); i++)
        if(line[i] == sep) separators_in_line++;

    result_array = (char**)malloc((separators_in_line + 1) * sizeof (char*));

    for(i = 0; i < separators_in_line + 1; i++) {
        if(result_array != NULL) {
            result_array[i] = (char*)malloc(strlen(line) * sizeof(char));
            if (result_array[i] == NULL) result_array = NULL;
        } else i = separators_in_line + 1;
    }

    if (result_array != NULL) {
        k = m = 0;
        for (i = 0; i < strlen(line); i++) {
            if (line[i] != sep) result_array[m][i - k] = line[i];
            else {
                result_array[m][i - k] = '\0';
                k = i + 1;
                m++;
            }
        }
    }

    return result_array;
}

char* bgets(char *st, int const len, FILE *fp) {
    unsigned long str_len;
    char* err;
    err = fgets(st, len, fp);
    str_len = strlen(st);
    if (st[str_len - 1] == '\n') {
        if (st[str_len - 2] == '\r')
            st[str_len - 2] = '\0';
        else
            st[str_len - 1] = '\0';
    }
    return err;
}

int ibgets(FILE *fp) {
    char * st;
    st = malloc(11);
    return (int)strtol(bgets(st, 11, fp), NULL, 10);
}

float fbgets(FILE *fp) {
    char* st;
    st = malloc(31);
    return (float)atof(bgets(st, 31, fp));
}

boolean func_cmp_(char * cmd, char * compare) {
    char * temp1, * temp2;
    boolean res;
    res = 1;
    for(temp1 = cmd, temp2 = compare; *temp1 != '\0' && *temp2 != '\0' && res == 1; temp1++, temp2++) {
        if (*temp1 != *temp2) res = 0;
    }
    return res;
}

int strcount(char* in, char* substring) {
    int count;
    unsigned long substring_len;
    char* st0;
    count = 0;
    substring_len = strlen(substring);
    st0 = strstr(in, substring);
    while(st0 != NULL) {
        count++;
        st0 += substring_len;
        st0 = strstr(st0, substring);
    }
    return count;
}

void create_(head * hd, f_head * f_hd) {
    hd->cnt = 0;
    hd->first = NULL;
    hd->last = NULL;
    f_hd->cnt = 0;
    f_hd->first = NULL;
    f_hd->last = NULL;
}

char* just_copy_(const char* st) {
    char * res;
    unsigned long len, i;
    len = strlen(st);
    res = malloc(len);
    for(i = 0; i < len; *(res + i) = *(st + i), i++);
    *(res + i) = '\0';
    return res;
}

void new_no_(head * hd) {
    node * student;
    int i;
    for(i = 0, student = hd->first; student != NULL; student->no = ++i, student = student->next);
}

void help(char * cmd) {
    if (!strcmp(cmd, "Help"))
        printf("Available Commands:\n"
               "Quit                             - to quit\n"
               "Enter <csv/lbl>                  - to fill Kartoteka from keyboard\n"
               "Import <file name>               - to fill Kartoteka from file\n"
               "Export <file name>               - to make file from Kartoteka data\n"
               "Show <max amount>                - to show up to positive max amount of lines\n"
               "Change <No>                      - to change line #N\n"
               "Swap <No1> <No2>                 - to swap lines with no N1 and N2\n"
               "Sort <Column> <a/d>              - to sort column ascending/descending\n"
               "Filter <Column> <(how)value>     - to show all lines with necessary value\n"
               "Delete All                       - to delete all Kartoteka database\n"
               "Delete <No>                      - to delete line #N\n"
               "Delete By <Column> <(how)value>  - to delete lines with necessary value\n"
               "Quick                            - to quick look data in Kartoteka\n"
               "Clear                            - to clear the screen\n"
               "Help <Command>                   - for documentation\n\n"
               "Use Help <Command> for specific Function documentation\n\n");
    else {
        cmd += 4;
        for(; *cmd == ' '; cmd++);
        if (!strcmp(cmd, "Quit"))
            printf("Quit function is used to terminate Kartoteka\n"
                   "Just type 'Quit' if you had enough.\n\n");
        else if (func_cmp_(cmd, "Enter"))
            printf("Enter function is used to fill Kartoteka database from keyboard.\n"
                   "You can fill with 'Line by Line' mode or 'CSV' mode\n"
                   "Command 'Enter' will lead to menu where you can choose between them\n"
                   "However, you can type 'Enter csv' or 'Enter lbl' to get right into necessary mode.\n"
                   "\n"
                   "Usage Example:\n"
                   "Enter csv\none;two;3;4;5;6;7;8;9\n\n");
        else if(func_cmp_(cmd, "Show"))
            printf("Show function is used to print all the data from Kartoteka\n"
                   "By Default prints all the lines\n"
                   "You can also give an argument of max amount of lines to print.\n"
                   "\n"
                   "Usage Example:\n"
                   "Show 5\n\n");
        else if(func_cmp_(cmd, "Import"))
            printf("Import function is used to get Kartoteka lines from csv line\n"
                   "You can type Import and then choose a file\n"
                   "Or just type Import <name of file>\n"
                   "\n"
                   "Usage Example:\n"
                   "Import example.txt\n\n");
        else if(func_cmp_(cmd, "Export"))
            printf("Export function is used to write Kartoteka lines in CSV format into a file.\n"
                   "This file can be later imported in Kartoteka\n"
                   "You can type Export and then choose a file\n"
                   "Or just type Export <name of file>\n\n"
                   "Note: If file with a given name does not exist,\n"
                   "it will be automatically created in Kartoteka folder.\n"
                   "\n"
                   "Usage Example:\n"
                   "Export example.txt\n\n");
        else if(func_cmp_(cmd, "Change"))
            printf("Change function is used to change line with a specific No from keyboard\n"
                   "You can type a new line in CSV format or in Line by Line mode.\n"
                   "You can type Change and then pick all the parameters\n"
                   "Or just type Change <No> <csv/lbl>\n"
                   "\n"
                   "Usage Example:\n"
                   "Change 1 csv\n\n");
        else if(func_cmp_(cmd, "Delete All"))
            printf("Delete All function is used to delete all Kartoteka database\n"
                   "All the lines and faculties will be deleted.\n\n");
        else if(func_cmp_(cmd, "Delete By"))
            printf("Delete By function is used to delete all the lines that meet the requirements\n"
                   "You can type Delete By and choose Column and Requirements\n"
                   "Or Just type Delete By <Column> <Requirements>\n"
                   "\n"
                   "Note: In strings: '==' finds exact match.\n"
                   "                  '=' finds if it is first substring.\n"
                   "      In numeric '=' and '==' are the same.\n"
                   "\n"
                   "Usage Example:\n"
                   "Delete By Age < 18\n\n");
        else if(func_cmp_(cmd, "Delete"))
            printf("Delete function is used to delete line with a specific No\n"
                   "You can type Delete and the pick a No\n"
                   "Or just type Delete <No>\n"
                   "\n"
                   "Usage Example:\n"
                   "Delete 2\n\n");
        else if(func_cmp_(cmd, "Quick"))
            printf("Quick function is used to quickly Show 5.\n"
                   "Use it if you need to check if the Kartoteka has changed\n\n");
        else if(func_cmp_(cmd, "Swap"))
            printf("Swap function is used to swap to lines in Kartoteka database\n"
                   "You can type Swap and pick No's\n"
                   "Or just type Swap <No1> <No2>\n"
                   "\n"
                   "Usage Example:\n"
                   "Swap 1 2\n\n");
        else if(func_cmp_(cmd, "Sort"))
            printf("Sort function is used to sort Kartoteka database by any column\n"
                   "You can type Sort and pick a column and mode (ascending/descending)\n"
                   "Or just type Sort <Column> <a/d>\n"
                   "\n"
                   "Usage Example:\n"
                   "Sort ID a\n\n");
        else if(func_cmp_(cmd, "Filter"))
            printf("Filter function is used to show lines that meet the requirements\n"
                   "It doesn't change database\n"
                   "You can type Filter and choose column and requirements\n"
                   "Or just type Filter <Column> <Requirements>\n"
                   "\n"
                   "Note: In strings: '==' finds exact match.\n"
                   "                  '=' finds if it is first substring.\n"
                   "      In numeric '=' and '==' are the same.\n"
                   "\n"
                   "Usage Example:\n"
                   "Filter ID >= 5\n\n");
        else if(func_cmp_(cmd, "Clear"))
            printf("Clear function is used to clear your terminal.\n\n");
        else if(func_cmp_(cmd, "Help"))
            printf("Help function is used to keep documentation\n"
                   "And access it from the program\n"
                   "With no arguments shows all the available Kartoteka commands\n"
                   "Can also show documentation of the specific function\n"
                   "\n"
                   "Usage Example:\n"
                   "Help Enter\n\n");

    }
}