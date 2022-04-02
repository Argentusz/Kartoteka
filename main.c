#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear system("clear||@cls");
#define COMMAND_LEN 128
#define bool char

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

void csv_line_parser(head *hd, f_head* f_hd, char* line);
char** split(char *line, char sep);
char* bgets(char *st, int len, FILE *fp);
int ibgets(FILE *fp);
float fbgets(char *st, FILE *fp);
f_node * foreign_key(f_head *f_hd, char* fac_name);
void make_new_f(f_head * f_hd, char * node_name);
void create(head * hd, f_head * f_hd);
void UI(head * hd, f_head * f_hd);
void quick_look(head * hd);
bool cmd_check(char * cmd, head * hd, f_head * f_hd);
void enter(head * hd, f_head * f_hd, char* cmd);
void import(head * hd, f_head * f_hd, char * cmd);
void export(head * hd, char * cmd);
bool func_cmp(char * cmd, char * compare);
void help(char * cmd);
char* just_copy(const char* st);
void delete_all(head * hd, f_head * f_hd);
void delete(head * hd, char * cmd);
int strcount(char* in, char* substring);
void show(head * hd, char * cmd);
void new_no(head * hd);
void change(head * hd, f_head * f_hd, char * cmd);
void sort(head * hd, char * cmd);
void swap(node * temp0, node * temp1);
void swap_cpy_internal(node * buff, node * temp1);
void q_sort_internal(node * left, node * right);

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
    create(hd, f_hd);
    /* Launching User Interface */
    UI(hd, f_hd);
    return 0;
}

void UI(head * hd, f_head * f_hd) {
    char * cmd;
    bool quit;
    quit = 0;
    cmd = malloc(COMMAND_LEN);
    quick_look(hd);
    while (!quit) {
        printf(">>> ");
        bgets(cmd, COMMAND_LEN - 1, stdin);
        quit = cmd_check(cmd, hd, f_hd);
    }
}

bool cmd_check(char * cmd, head * hd, f_head * f_hd) {
    bool q;
    q = 0;
    if(func_cmp(cmd, "Quit")) {
        printf("Thank You for using Kartoteka\n");
        q = 1;
    }
    else if(func_cmp(cmd, "Enter")) {
        clear
        enter(hd, f_hd, cmd);
        clear
    }
    else if(func_cmp(cmd, "Import")) {
        import(hd, f_hd, cmd);
    }
    else if(func_cmp(cmd, "Export")) {
        export(hd, cmd);
    }
    else if(func_cmp(cmd, "Delete All")) {
        delete_all(hd, f_hd);
    }
    else if(func_cmp(cmd, "Delete By")) {
        //delete_by(hd, f_hd, cmd);
    }
    else if(func_cmp(cmd, "Delete")) {
        delete(hd, cmd);
    }
    else if(func_cmp(cmd, "Show")) {
        show(hd, cmd);
    }
    else if(func_cmp(cmd, "Sort")) {
        sort(hd, cmd);
    }
    else if(func_cmp(cmd, "Change")) {
        change(hd, f_hd, cmd);
    }
    else if(func_cmp(cmd, "Quick")) {
        quick_look(hd);
    }
    else if(func_cmp(cmd, "Help")) {
        help(cmd);
    }
    else if(func_cmp(cmd, "Clear")) clear
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
    mode = malloc(2);
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
            student->name = just_copy(temp);
            printf("Enter the faculty: ");
            bgets(temp, 32 - 1, stdin);
            student->faculty = foreign_key(f_hd, temp);
            printf("Enter the Age: ");
            student->age = ibgets(stdin);
            printf("Enter the ID: ");
            student->id = ibgets(stdin);
            printf("Enter the Average Score: ");
            student->avg_score = fbgets(temp, stdin);
            printf("Enter the Completion Rate: ");
            student->completion_rate = fbgets(temp, stdin);
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
            } else csv_line_parser(hd, f_hd, temp);

            bgets(temp, 127, stdin);
        }
    }
}

void import(head * hd, f_head * f_hd, char * cmd) {
    FILE * fp = NULL;
    char * file_name, * line;
    bool cancel;
    file_name = malloc(32);

    if(*(cmd+6) != '\0') {
        cmd += 7;
        file_name = just_copy(cmd);
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
            csv_line_parser(hd, f_hd, line);
        }
    }

    fclose(fp);
}

void export(head * hd, char * cmd) {
    FILE * fp = NULL;
    char * file_name, * yn;
    node * temp;
    unsigned long i;
    bool cancel;
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
            file_name = just_copy(cmd);
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
    printf("Type Help to see what Kartoteka can do\n"
           "Type Quit to quit\n\n");
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
            while ((*st > '9' || *st < '0') && *st != '-') {
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
                    student->name = just_copy(temp);
                    printf("Enter the faculty: ");
                    bgets(temp, 32 - 1, stdin);
                    student->faculty = foreign_key(f_hd, temp);
                    printf("Enter the Age: ");
                    student->age = ibgets(stdin);
                    printf("Enter the ID: ");
                    student->id = ibgets(stdin);
                    printf("Enter the Average Score: ");
                    student->avg_score = fbgets(temp, stdin);
                    printf("Enter the Completion Rate: ");
                    student->completion_rate = fbgets(temp, stdin);
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
                        student->faculty = foreign_key(f_hd, splitLine[1]);
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

void csv_line_parser(head *hd, f_head* f_hd, char* line) {
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
    db->faculty = foreign_key(f_hd, splitLine[1]);
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
            new_no(hd);
        }
    }
    else if (no > hd->cnt) printf("error: This No is out of bounds\n");
}

void sort(head * hd, char * cmd) {
    q_sort_internal(hd->first, hd->last);
}

void q_sort_internal(node * left, node * right) {
    node * last, * current;
    if (left != right) {
        if (left->next == right) {
            if (left->id > right->id)
                swap(left, right);
        } else {
            last = left;
            current = left;
            do {
                current = current->next;
                if (current->id < left->id) {
                    last = last->next;
                    swap(last, current);
                }
            } while (current != right);
            swap(left, last);
            q_sort_internal(left, last);
            if (last != right)
                q_sort_internal(last->next, right);
        }
    }

}

void swap(node * temp0, node * temp1) {
    node * buff;

    buff = (node*)malloc(sizeof(node));

    swap_cpy_internal(buff, temp1);
    swap_cpy_internal(temp1, temp0);
    swap_cpy_internal(temp0, buff);

    free(buff);
}

void swap_cpy_internal(node * buff, node * temp1) {
    buff->name = just_copy(temp1->name);
    buff->faculty = temp1->faculty;
    buff->age = temp1->age;
    buff->id = temp1->id;
    buff->avg_score = temp1->avg_score;
    buff->completion_rate = temp1->completion_rate;
    buff->gia_results[0] = temp1->gia_results[0];
    buff->gia_results[1] = temp1->gia_results[1];
    buff->gia_results[2] = temp1->gia_results[2];
}

f_node * foreign_key(f_head *f_hd, char* fac_name) {
    f_node * node, * res;
    bool found;
    found = 0;
    for(node = f_hd->first; node != NULL && found == 0; node = node->next) {
        if(!strcmp(fac_name, node->name)) {
            found = 1;
            res = node;
        }
    }
    if(!found) {
        make_new_f(f_hd, fac_name);
        res = f_hd->last;
    }
    return res;
}

void make_new_f(f_head * f_hd, char * node_name) {
    f_node * node;
    node = (f_node*)malloc(sizeof(f_node));
    node->name = just_copy(node_name);
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

float fbgets(char *st, FILE *fp) {
    st = malloc(31);
    return (float)atof(bgets(st, 31, fp));
}

bool func_cmp(char * cmd, char * compare) {
    char * temp1, * temp2;
    bool res;
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

void create(head * hd, f_head * f_hd) {
    hd->cnt = 0;
    hd->first = NULL;
    hd->last = NULL;
    f_hd->cnt = 0;
    f_hd->first = NULL;
    f_hd->last = NULL;
}

char* just_copy(const char* st) {
    char * res;
    unsigned long len, i;
    len = strlen(st);
    res = malloc(len);
    for(i = 0; i < len; *(res + i) = *(st + i), i++);
    *(res + i) = '\0';
    return res;
}

void new_no(head * hd) {
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
               "Change <N>                       - to change line #N\n"
               "Sort <column> <a/d>              - to sort column ascending/descending\n" // Not Done
               "Filter <column> <(how)value>     - to get all lines with necessary value\n" // Not Done
               "Delete All                       - to delete all Kartoteka database\n"
               "Delete <N>                       - to delete line #N\n"
               "Delete by <column> <(how)value>  - to delete lines with necessary value\n" // Not Done
               "Quick                            - to quick look data in Kartoteka\n"
               "Clear                            - to clear the screen\n"
               "Help <Command>                   - for documentation\n\n" // Unfinished
               "Use Help <Command> for specific Function documentation\n\n");
    else {
        cmd += 4;
        for(; *cmd == ' '; cmd++);
        if (!strcmp(cmd, "Quit"))
            printf("Quit function is used to terminate Kartoteka\n"
                   "Just type 'Quit' if you had enough.\n\n");
        else if (func_cmp(cmd, "Enter"))
            printf("Enter function is used to fill Kartoteka database from keyboard.\n"
                   "You can fill with 'Line by Line' mode or 'CSV' mode\n"
                   "Command 'Enter' will lead to menu where you can choose between them\n"
                   "However, you can type 'Enter csv' or 'Enter lbl' to get right into necessary mode.\n"
                   "\n"
                   "Usage Example:\n"
                   "Enter csv\none;two;3;4;5;6;7;8;9\n\n");
        else if(func_cmp(cmd, "Show"))
            printf("Show function is used to print all the data from Kartoteka\n"
                   "By Default prints all the lines\n"
                   "You can also give an argument of max amount of lines to print.\n"
                   "\n"
                   "Usage Example:\n"
                   "Show 5\n\n");
        else if(func_cmp(cmd, "Import"))
            printf("Import function is used to get Kartoteka lines from csv line\n"
                   "You can type Import and then choose a file\n"
                   "Or just type Import <name of file>\n"
                   "\n"
                   "Usage Example:\n"
                   "Import example.txt\n\n");
        else if(func_cmp(cmd, "Export"))
            printf("Export function is used to write Kartoteka lines in CSV format into a file.\n"
                   "This file can be later imported in Kartoteka\n"
                   "You can type Export and then choose a file\n"
                   "Or just type Export <name of file>\n\n"
                   "Note: If file with a given name does not exist,\n"
                   "it will be automatically created in Kartoteka folder.\n"
                   "\n"
                   "Usage Example:\n"
                   "Export example.txt\n\n");
        else if(func_cmp(cmd, "Change"))
            printf("Change function is used to change line with a specific No from keyboard\n"
                   "You can type a new line in CSV format or in Line by Line mode.\n"
                   "You can type Change and then pick all the parameters\n"
                   "Or just type Change <No> <csv/lbl>\n"
                   "\n"
                   "Usage Example:\n"
                   "Change 1 csv\n\n");
        else if(func_cmp(cmd, "Delete All"))
            printf("Delete All function is used to delete all Kartoteka database\n"
                   "All the lines and faculties will be deleted.\n\n");
        else if(func_cmp(cmd, "Delete"))
            printf("Delete function is used to delete line with a specific No\n"
                   "You can type Delete and the pick a No\n"
                   "Or just type Delete <No>\n"
                   "\n"
                   "Usage Example:\n"
                   "Delete 2\n\n");
        else if(func_cmp(cmd, "Quick"))
            printf("Quick function is used to quickly Show 5.\n"
                   "Use it if you need to check if the Kartoteka has changed\n\n");
        else if(func_cmp(cmd, "Clear"))
            printf("Clear function is used to clear your terminal.\n\n");
        else if(func_cmp(cmd, "Help"))
            printf("Help function is used to keep documentation\n"
                   "And access it from the program\n"
                   "With no arguments shows all the available Kartoteka commands\n"
                   "Can also show documentation of the specific function\n"
                   "\n"
                   "Usage Example:\n"
                   "Help Enter\n\n");
    }
}