#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define clear system("clear||@cls");
#define COMMAND_LEN 256
#define SAVE_FILE "kartoteka.csv"
/* boolean here is a char type that is used to keep only 1 or 0 (for easier reading) */
#define boolean char

/* Faculties Doubly linked list */
typedef struct fac_struct {
    char * name;
    struct fac_struct* next;
    struct fac_struct* prev;
} f_node;
typedef struct fac_head {
    struct fac_struct * first;
    struct fac_struct * last;
    int cnt;
} f_head;
/* Students Doubly linked list */
typedef struct student_struct {
    char * name;
    f_node * faculty;
    int no;
    int age;
    int id;
    float avg_score;
    float completion_rate;
    int gia_results[3];
    struct student_struct * next;
    struct student_struct * prev;
} node;
typedef struct student_head {
    struct student_struct * first;
    struct student_struct * last;
    int cnt;
} head;


/** Called by User **/
/* Enter New Nodes from Keyboard */
char enter(head * hd, f_head * f_hd, char * cmd);
/* Import Nodes from file */
boolean import(head * hd, f_head * f_hd, char * cmd);
/* Save changes in Kartoteka Save file */
void save(head * hd);
/* Export Kartoteka to a CSV format file */
boolean export(head * hd, char * cmd);
/* Show List (Up to some max number if exists) */
void show(head * hd, char * cmd);
/* Change Some Node */
boolean change(head * hd, f_head * f_hd, char * cmd);
/* Swap Two Nodes */
boolean swap(head * hd, char * cmd);
/* Sort By Any Column */
boolean sort(head * hd, char * cmd);
/* Show Nodes that meet the requirements */
boolean filter_by(head* hd, char * cmd);
/* Delete Everything */
void delete_all(head * hd, f_head * f_hd);
/* Delete One Node */
boolean delete(head * hd, char * cmd);
/* Delete Nodes that meet the requirements */
boolean delete_by(head * hd, char * cmd);
/* Quick Access to List */
void quick_look(head * hd);
/* Documentation */
void help(char * cmd);
/* Source Code link */
void source_code();

/** Internal Functions **/
/* Parse Line and Append to a List */
void csv_line_parser_(head *hd, f_head* f_hd, char * line);
/* Returns Address of Faculty with a Given Name */
f_node * foreign_key_(f_head *f_hd, char * fac_name);
/* Creates New Faculty */
void make_new_f_(f_head * f_hd, char * node_name);
/* Create Dummies of head and f_head */
void create_(head * hd, f_head * f_hd);
/* User Interface */
void UI_(head * hd, f_head * f_hd);
/* Commands Distributor */
boolean cmd_check_(char * cmd, head * hd, f_head * f_hd, boolean * saved);
/* Looks if String is a First Substring */
boolean func_cmp_(char * cmd, char * compare);
/* Copy string (Works with Structure's pointers) */
char * just_copy_(const char * st);
/* Update No's of a List */
void new_no_(head * hd);
/* Delete Given Node */
void delete_node_(head * hd, node * student);
/* Delete Nodes that meet the requirements (for str, int, float)*/
void delete_str_(head * hd, char * (*field)(node*), int how, char * value);
void delete_int_(head * hd, int column, int how, int value);
void delete_float_(head * hd, int column, int how, float value);
/* Output Nodes that meet the requirements (for str, int, float)*/
void filter_int_(head * hd, int column, int how, int value);
void filter_float_(head * hd, int column, int how, float value);
void filter_str_(head * hd, char * (*field)(node*), int how, char * value);
/* Swaps Two Nodes */
void swap_(node * temp0, node * temp1);
/* Copy a Data of Node */
void swap_cpy_(node * temp0, node * temp1);
/* Quick Sort List for Numerous and String */
void q_sort_(node * left, node * right, signed char mode, signed char ad);
void str_q_sort_(node * left, node * right, char * (*field)(node*), signed char ad);
/* Return Name of a Node */
char * get_name_(node * student);
/* Return Faculty name of a Node */
char * get_fac_name_(node * student);
/* Print Node */
void output_(node * student);
/* Returns string with all lowercase */
char * lower_str_(char * string);

/** BFuncs (written while ago) **/
/* Read String from a Keyboard */
char * bgets(char *st, int len, FILE *fp);
/* Read Integer from a Keyboard */
int ibgets(FILE *fp);
/* Read Float from a Keyboard */
float fbgets(FILE *fp);
/* Read Char (as a number, not a symbol) */
char cbgets(FILE * fp);
/* Split String by a Separator */
char ** split(char *line, char sep);
/* Counts Amount of a Substrings in a String */
int strcount(char * in, char * substring);
/* Deletes a Border Symbol at the beginning and at the end of the String */
char * striped(const char *string, char border);


int main() {
    char * line;
    f_head * f_hd;
    head * hd;
    FILE * save;
    printf("Welcome to Kartoteka v1.0\n"
           "Kartoteka is an open-source project made by Maksim Trostin\n"
           "Kartoteka Source Code is licensed under the Creative Commons Zero v1.0 Universal\n\n"
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
    /* Allocating Memory & Create dummies of heads */
    f_hd = (f_head*)malloc(sizeof(f_head));
    if(f_hd == NULL) {
        printf("fatal error: Unable to Allocate Memory (main: f_hd)\n\n");
        exit(1);
    }
    hd = (head*)malloc(sizeof(head));
    if(hd == NULL) {
        printf("fatal error: Unable to Allocate Memory (main: hd)\n\n");
        exit(1);
    }
    create_(hd, f_hd);
    /* Loading from Save File */
    save = fopen(SAVE_FILE, "r+");
    if(save == NULL) {
        printf("warning: %s not found.\nCreating an empty one.\n\n", SAVE_FILE);
        save = fopen(SAVE_FILE, "w");
        if(save == NULL) {
            printf("fatal error: Can not access and create %s file", SAVE_FILE);
            exit(1);
        }
        fclose(save);
    } else {
        line = malloc(128);
        while (bgets(line, 128, save) != NULL) {
            csv_line_parser_(hd, f_hd, line);
        }
        free(line);
        fclose(save);
    }

    /* Launching User Interface */
    UI_(hd, f_hd);
    /* Free Allocated memory before Quitting */
    free(hd);
    free(f_hd);
    return 0;
}

void UI_(head * hd, f_head * f_hd) {
    char * cmd;
    char ** cmd_arr;
    int ampersands, i;
    boolean quit, q, saved;
    quit = 0;
    cmd = malloc(COMMAND_LEN);
    if(cmd == NULL) {
        printf("fatal error: Unable to Allocate Memory (UI_: cmd)\n\n");
        exit(1);
    }
    quick_look(hd);
    saved = 1;
    while (!quit) {
        printf("\nType Help to see what Kartoteka can do\n"
               "Type Quit to quit\n\n");
        printf(">>> ");
        bgets(cmd, COMMAND_LEN - 1, stdin);
        ampersands = strcount(cmd, "&");
        /* Only One Command */
        if (ampersands == 0)
            quit = cmd_check_(striped(cmd, ' '), hd, f_hd, &saved);
        else {
            /* A Bunch of commands */
            cmd_arr = split(cmd, '&');
            for(i = 0; i <= ampersands; i++) {
                q = cmd_check_(striped(cmd_arr[i], ' '), hd, f_hd, &saved);
                /* If Quit Command is in the Middle of a Command */
                if(q) quit = 1;
            }
            free(cmd_arr);
        }
        if(quit == 1) {
            if(saved == 0) {
                printf("Looks like your Kartoteka has changed since last save.\nAre you sure you want to Quit? (Y - Yes, C - Cancel, S - Save and Quit)\n(Y/C/S): ");
                bgets(cmd, 4, stdin);
                if(*cmd != 'Y') {
                    if(*cmd == 'S') save(hd);
                    else quit = 0;
                }
            }
        }
    }
    free(cmd);
    printf("Thank You for using Kartoteka\n");
}

boolean cmd_check_(char * cmd, head * hd, f_head * f_hd, boolean * saved) {
    char * g;
    boolean q, canceled;
    q = 0;
    canceled = 0;
    if(*cmd == '\0') {
        /* To prevent '&&' Quitting the Program */
    }
    else if(func_cmp_(cmd, "Quit")) {
        q = 1;
    }
    else if(func_cmp_(cmd, "Save")) {
        save(hd);
        printf("Done.\n");
        *saved = 1;
    }
    else if(func_cmp_(cmd, "Enter")) {
        clear
        canceled = enter(hd, f_hd, cmd);
        if(!canceled) {
            clear
            printf("Done.\n");
            *saved = 0;
        } else {
            printf("Canceled.\n");
        }
    }
    else if(func_cmp_(cmd, "Import")) {
        canceled = import(hd, f_hd, cmd);
        if(!canceled) {
            printf("Done.\n");
            *saved = 0;
        } else {
            printf("Canceled.\n");
        }
    }
    else if(func_cmp_(cmd, "Export")) {
        canceled = export(hd, cmd);
        if(!canceled) printf("Done.\n");
        else printf("Canceled.\n");
    }
    else if(func_cmp_(cmd, "Delete All")) {
        delete_all(hd, f_hd);
        printf("Done.\n");
        *saved = 0;
    }
    else if(func_cmp_(cmd, "Delete By")) {
        canceled = delete_by(hd, cmd);
        if(!canceled) {
            printf("Done.\n");
            *saved = 0;
        } else {
            printf("Canceled.\n");
        }
    }
    else if(func_cmp_(cmd, "Delete")) {
        canceled = delete(hd, cmd);
        if(!canceled) {
            printf("Done.\n");
            *saved = 0;
        } else {
            printf("Canceled.\n");
        }
    }
    else if(func_cmp_(cmd, "Show")) {
        show(hd, cmd);
    }
    else if(func_cmp_(cmd, "Sort")) {
        canceled = sort(hd, cmd);
        if(!canceled) {
            printf("Done.\n");
            *saved = 0;
        } else {
            printf("Canceled.\n");
        }
    }
    else if(func_cmp_(cmd, "Change")) {
        canceled = change(hd, f_hd, cmd);
        if(!canceled) {
            printf("Done.\n");
            *saved = 0;
        } else {
            printf("Canceled.\n");
        }
    }
    else if(func_cmp_(cmd, "Swap")) {
        canceled = swap(hd, cmd);
        if(!canceled) {
            printf("Done.\n");
            *saved = 0;
        } else {
            printf("Canceled.\n");
        }
    }
    else if(func_cmp_(cmd, "Filter")) {
        filter_by(hd, cmd);
    }
    else if(func_cmp_(cmd, "Quick")) {
        quick_look(hd);
    }
    else if(func_cmp_(cmd, "Help")) {
        help(cmd);
    }
    else if(func_cmp_(cmd, "Clear")) clear
    else if(func_cmp_(cmd, "Source")) {
        source_code();
    }
    else {
        printf("typo error: Command not found: %s\n", cmd);
        printf("Type 'Help' to see commands available\n");
        lower_str_(cmd);
        if(func_cmp_(cmd, "delete all") || func_cmp_(cmd, "delete by")) {
            *cmd -= 32;
            for(g = cmd; *g != ' ' && *g != '\0'; g++);
            g++; *g-= 32;
            for(; *g != ' ' && *g != '\0'; g++);
            *g = '\0';
            printf("Maybe You Meant '%s'?\n\n", cmd);
        }
        else if( func_cmp_(cmd, "quit") || func_cmp_(cmd, "save") || func_cmp_(cmd, "enter") ||
            func_cmp_(cmd, "import") || func_cmp_(cmd, "export") || func_cmp_(cmd, "delete") ||
            func_cmp_(cmd, "show") || func_cmp_(cmd, "sort") || func_cmp_(cmd, "change") ||
            func_cmp_(cmd, "swap") || func_cmp_(cmd, "filter") || func_cmp_(cmd, "quick") ||
            func_cmp_(cmd, "help") || func_cmp_(cmd, "clear") || func_cmp_(cmd, "source") ) {
            for(g = cmd; *g != ' ' && *g != '\0'; g++);
            *g = '\0';
            *cmd -= 32;
            printf("Maybe You Meant '%s'?\n\n", cmd);
        }
        else printf("\n");
    }
    return q;
}

void save(head * hd) {
    node * temp;
    FILE * save;
    save = fopen(SAVE_FILE, "w");
    if(save == NULL) {
        printf("fatal error: Can not neither access neither create %s (aka save_file) file", SAVE_FILE);
        exit(1);
    }
    for (temp = hd->first; temp != NULL; temp = temp->next) {
        fprintf(save, "%s;%s;%d;%d;%.3f;%.2f;%d;%d;%d",
                temp->name,
                temp->faculty->name, temp->age, temp->id,
                temp->avg_score, temp->completion_rate,
                temp->gia_results[0], temp->gia_results[1], temp->gia_results[2]);
        if (temp->next != NULL) fprintf(save, "\n");
    }
    fclose(save);
}

boolean enter(head * hd, f_head * f_hd, char * cmd) {
    char * mode, * temp, * yn;
    boolean canceled;
    node * student;
    int i;
    mode = malloc(6);
    if(mode == NULL) {
        printf("fatal error: Unable to Allocate Memory (enter: mode)\n\n");
        exit(1);
    }
    *mode = 0;
    canceled = 0;
    /* Looking For Arguments in Command */
    if (*(cmd+5) != '\0') {
        cmd += 5;
        for(;*cmd == ' '; cmd++);
        if(!strcmp(cmd, "csv")) *mode = 'c';
        else if(!strcmp(cmd, "lbl")) *mode = 'l';
        else { printf("typo error: Mode %s not found\n", cmd); *mode = 0; }
        *(mode+1) = 0;
    }
    /* If Arguments not found */
    while (*mode == 0) {
        printf("How would you like to print data?\n1 - Line by line\n2 - CSV Format\n0 - Cancel\n\n");
        bgets(mode, 5, stdin);
        if (*mode == '1' && *(mode + 1) == 0) *mode = 'l';
        else if (*mode == '2' && *(mode + 1) == 0) *mode = 'c';
        else if (*mode == '0' && *(mode + 1) == 0) *mode = 'a';
        else *mode = 0;
        if (*mode == 0) printf("typo error: Unexpected input. Write only '1', '2' or '0'.\n");
        fflush(stdin);
    }
    /* yn - If User Picked Yes or No to add a Node */
    yn = malloc(4);
    if(yn == NULL) {
        printf("fatal error: Unable to Allocate Memory (enter: yn)\n\n");
        exit(1);
    }
    *yn = 'Y'; *(yn+1) = 0;
    /* Line by Line Mode */
    if (*mode == 'l') {
        while(*yn == 'Y' || *yn == 'y') {
            temp = malloc(41);
            if(temp == NULL) {
                printf("fatal error: Unable to Allocate Memory (enter: temp)\n\n");
                exit(1);
            }
            student = (node*)malloc(sizeof(node));
            if(student == NULL) {
                printf("fatal error: Unable to Allocate Memory (enter: student)\n\n");
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
    /* CSV mode */
    else if (*mode == 'c') {
        temp = malloc(128);
        if(temp == NULL) {
            printf("fatal error: Unable to Allocate Memory (enter: temp)\n\n");
            exit(1);
        }
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
    if (*mode == 'a') {
        canceled = 1;
    }
    return canceled;
}

boolean import(head * hd, f_head * f_hd, char * cmd) {
    FILE * fp = NULL;
    char * file_name, * line;
    boolean cancel;
    file_name = malloc(32);
    if(file_name == NULL) {
        printf("fatal error: Unable to Allocate Memory (import: file_name)\n\n");
        exit(1);
    }
    /* Looking For Arguments in Command */
    if(*(cmd+6) != '\0') {
        for(cmd += 6; *cmd == ' '; cmd++);
        file_name = just_copy_(cmd);
    } else {
        /* If Arguments not found */
        printf("Type File Name to import from (Just hit Enter to cancel): ");
        bgets(file_name, 31, stdin);
    }

    cancel = 0;
    if(*file_name != '\0') fp = fopen(file_name, "r");
    else cancel = 1;
    /* If File not found */
    while(fp == NULL && cancel == 0) {
        printf("typo error: Can not open file '%s'. Maybe that file does not exist?\n"
               "Type file name once again (Just hit Enter to cancel): ", file_name);
        bgets(file_name, 31, stdin);
        if(*file_name != '\0') fp = fopen(file_name, "r");
        else cancel = 1;
    }

    if(!cancel) {
        line = malloc(128);
        if(line == NULL) {
            printf("fatal error: Unable to Allocate Memory (import: line)\n\n");
            exit(1);
        }
        while (bgets(line, 128, fp) != NULL) {
            csv_line_parser_(hd, f_hd, line);
        }
        fclose(fp);
    }

    return cancel;
}

boolean export(head * hd, char * cmd) {
    FILE * fp = NULL;
    char * file_name, * yn;
    node * temp;
    unsigned long i;
    boolean cancel;
    cancel = 0;
    /* If List is Empty give a Warning */
    if(hd->cnt == 0) {
        printf("warning: Kartoteka is empty.\n"
               "Are you sure you want to continue? (Y/N): ");
        yn = malloc(3);
        if(yn == NULL) {
            printf("fatal error: Unable to Allocate Memory (export: yn)\n\n");
            exit(1);
        }
        bgets(yn, 11, stdin);
        cancel = 1;
        if((*yn == 'Y' || *yn == 'y') && *(yn+1) == '\0') cancel = 0;
    }
    if(!cancel) {
        file_name = malloc(32);
        if(file_name == NULL) {
            printf("fatal error: Unable to Allocate Memory (export: file_name)\n\n");
            exit(1);
        }
        /* Looking For Arguments in Command */
        if (*(cmd + 6) != '\0') {
            for(cmd += 6; *cmd == ' '; cmd++);
            file_name = just_copy_(cmd);
        } else {
            /* If Arguments not found */
            printf("Type File Name to export to (Just hit Enter to cancel): ");
            bgets(file_name, 31, stdin);
        }

        /* Open File in Reading Mode to See if it Exists */
        if (*file_name != '\0') fp = fopen(file_name, "r");
        else cancel = 1;
        /* If File Exists give a Warning */
        if (fp != NULL) {
            yn = malloc(3);
            if(yn == NULL) {
                printf("fatal error: Unable to Allocate Memory (export: yn)\n\n");
                exit(1);
            }
            cancel = 1;
            printf("warning: File '%s' already exists.\n"
                   "This will overwrite file\n"
                   "Are you sure you want to continue? (Y/N): ", file_name);
            bgets(yn, 11, stdin);
            if ((*yn == 'Y' || *yn == 'y') && *(yn + 1) == '\0') cancel = 0;
            fclose(fp);
        }

        if (!cancel) {
            fp = fopen(file_name, "w");
            if (fp == NULL) {
                printf("error: Can not neither access neither create %s file", file_name);
            } else {
                for (temp = hd->first, i = 0; temp != NULL; temp = temp->next, i++) {
                    fprintf(fp, "%s;%s;%d;%d;%.3f;%.2f;%d;%d;%d",
                            temp->name,
                            temp->faculty->name, temp->age, temp->id,
                            temp->avg_score, temp->completion_rate,
                            temp->gia_results[0], temp->gia_results[1], temp->gia_results[2]);
                    if (temp->next != NULL) fprintf(fp, "\n");
                }
                fclose(fp);
            }
        }
    }

    return cancel;
}

void quick_look(head * hd) {
    unsigned long count;
    int i;
    node * temp;
    count = 0;
    if (!hd->cnt) printf("Kartoteka is empty for now.\n"
                         "Use Enter or Import to fill it.\n");
    else {
        /* Print Table Header */
        printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age", "Score", "C.R.","GIA Results");
        for (temp = hd->first; temp != NULL && count < 5; temp = temp->next, count++) {
            /* Print 5 Nodes */
            output_(temp);
        }
        /* If More than 5 Nodes Print how much is Hidden */
        if(hd->cnt - 5 > 0) { for(i = 0; i <= 85; i++) printf("-"); printf("\n| Hidden : %-5d %68s|\n", hd->cnt - 5, " "); }
    }

}

void show(head * hd, char * cmd) {
    int maks;
    unsigned int i;
    char * st = NULL;
    node * temp;
    maks = 0;
    /* Looking For Arguments in Command */
    if(*(cmd+4) != '\0') {
        for(st = cmd + 4; *st == ' '; st++);
        if(*st > '9' || *st < '0')
            while (maks == 0) {
                printf("typo error: Argument of Show function should be a number.\n"
                       "Print number of max lines (0 if no bounds, -1 to cancel): ");
                maks = ibgets(stdin);
            }
        else maks = (int)strtol(st, NULL, 10);
    }
    /* If Arguments not found Print All */
    if (maks != -1) {
        if (!hd->cnt)
            printf("Kartoteka is empty for now.\n"
                   "Use Enter or Import to fill it.\n");
        else {
            printf("| %-2s | %-2s | %-23s | %-7s | %-3s | %3s | %2s | %-15s |\n", "No", "ID", "Name", "Faculty", "Age",
                   "Score", "C.R.", "GIA Results");
            for (temp = hd->first, i = 0; temp != NULL && (i < maks || maks == 0); temp = temp->next, i++) {
                output_(temp);
            }
            if (hd->cnt - maks > 0 && maks > 0) {
                for (i = 0; i <= 85; i++) printf("-");
                printf("\n| Hidden : %-5d %68s|\n", hd->cnt - maks, " ");
            }
        }
    }
}

boolean change(head * hd, f_head * f_hd, char * cmd) {
    int no, num_len, i, line;
    char * mode, * temp, ** splitLine;
    node * student;
    boolean cancel;
    mode = malloc(3);
    cancel = 0;
    if(mode == NULL) {
        printf("fatal error: Unable to Allocate Memory (change: mode)\n\n");
        exit(1);
    }
    if(mode == NULL) {
        printf("fatal error: Unknown Memory Error while allocating memory in Change. (mode)\n");
        exit(1);
    }
    *mode = 0;
    /* Looking For Arguments in Command */
    if(*(cmd + 6) != '\0') {
        cmd += 6;
        /* First Argument is a Number */
        for(;*cmd == ' '; cmd++);
        if(*cmd < '9' && *cmd > '0') {
            no = (int)strtol(cmd, NULL, 10);
            if(no > 0) {
                /* Looking how many Symbols Number took */
                num_len = 0;
                for (i = no; i; i /= 10, num_len++);
                cmd += num_len;
                /* First Argument is a Operation Mode (csv/lbl) */
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
        /* If Arguments not found */
        printf("Print No of element to change (0 to cancel): ");
        no = ibgets(stdin);
    }
    if(no > 0 && no <= hd->cnt) {
        /* If Mode is not Given yet */
        while(*mode == 0) {
            printf("How would you like to print data?\n1 - Line by line\n2 - CSV Format\n0 - Cancel\n");
            line = ibgets( stdin);
            if(line == 1) *mode = 'l';
            else if(line == 2) *mode = 'c';
            else if(line == 0) *mode = 'q';
            else printf("typo error: Unexpected input. Write only '1', '2' or '0'.\n");
        }
        if(*mode != 'q') {
            /* Looking for a Node with Given No */
            for (student = hd->first; student != NULL && student->no != no; student = student->next);
            if (student == NULL) printf("error: Element with No %d not found\n", no);
            else {
                if (*mode == 'l') {
                    /* Line by Line Mode */
                    temp = malloc(41);
                    if(temp == NULL) {
                        printf("fatal error: Unable to Allocate Memory (change: temp)\n\n");
                        exit(1);
                    }
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
                    /* CSV Mode */
                    temp = malloc(128);
                    if(temp == NULL) {
                        printf("fatal error: Unable to Allocate Memory (change: temp)\n\n");
                        exit(1);
                    }
                    bgets(temp, 127, stdin);
                    if(strcount(temp, ";") != 8) {
                        printf("typo error: Wrong Amount of Members in CSV\n"
                               "Input Should be something like 'one;two;3;4;5;6;7;8;9'\n"
                               "\n");
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
                        student->avg_score = (float)strtod(splitLine[4], NULL);
                        student->completion_rate = (float)strtod(splitLine[5], NULL);
                        for (i = 0; i < 3; i++) student->gia_results[i] = (int) strtol(splitLine[6 + i], NULL, 10);
                        free(splitLine);
                    }
                }
            }
        }
    } else {
        if (no > hd->cnt) printf("error: This No is out of bounds\n");
        cancel = 1;
    }
    return cancel;
}

void csv_line_parser_(head *hd, f_head* f_hd, char * line) {
    int j;
    node *db, *temp;
    char **splitLine;
    db = (node*)malloc(sizeof(node));
    if(db == NULL) {
        printf("fatal error: Unable to Allocate Memory (csv_line_parser_: db)\n\n");
        exit(1);
    }
    splitLine = split(line, ';');
    if(splitLine == NULL) {
        printf("fatal error: Unable to Allocate Memory (csv_line_parser_: splitLine)\n\n");
        exit(1);
    }

    db->name = splitLine[0];
    db->faculty = foreign_key_(f_hd, splitLine[1]);
    db->age = (int)strtol(splitLine[2], NULL, 10);
    db->id = (int)strtol(splitLine[3], NULL, 10);
    db->avg_score = (float)strtod(splitLine[4], NULL);
    db->completion_rate = (float)strtod(splitLine[5], NULL);
    for(j = 0; j < 3; j++) db->gia_results[j] = (int)strtol(splitLine[6+j], NULL, 10);
    db->next = NULL;
    db->no = ++hd->cnt;
    if (hd->cnt < 1) {printf("fatal error: Unknown Error Negatives in counter (Parser: hd->cnt < 0)"); exit(1);}
    if(hd->cnt == 1) {
        /* If it is First Node */
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
            /* If not only one Node */
            /* If we go up to temp == NULL we will not be able to delete last Node */
            for (temp = temp->next; temp->next != NULL; free(temp->prev), temp = temp->next);
            free(temp->prev);
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

char delete(head * hd, char * cmd) {
    int no;
    node * student;
    boolean cancel;
    cancel = 0;
    /* Looking for Arguments in Command */
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
        /* If Arguments not found */
        printf("Print No of element to delete (0 to cancel): ");
        no = ibgets(stdin);
    }
    if(no > 0 && no <= hd->cnt) {
        for(student = hd->first; student != NULL && student->no != no; student = student->next);
        if (student == NULL) printf("error: Element with No %d not found\n", no);
        else delete_node_(hd, student);
    }
    else {
        if (no > hd->cnt) printf("error: This No is out of bounds\n");
        cancel = 1;
    }
    return cancel;
}

boolean delete_by(head* hd, char * cmd) {
    int column, how;
    char * line_value;
    int int_value;
    float float_value;
    boolean done, cancel;
    done = 0;
    cancel = 0;
    column = -3;
    /* Looking for Arguments in Command */
    if(*(cmd+9) != '\0') {
        for(cmd+=9; *cmd == ' '; cmd++);
        /* First Argument - Column */
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
            /* Second Argument */
            if(func_cmp_(cmd, "==")) { how = 4; cmd+=2;}
            else if(func_cmp_(cmd, "=")) { how = 1; cmd++;}
            else if(func_cmp_(cmd, ">=")) { how = 3; cmd+=2;}
            else if(func_cmp_(cmd, ">")) { how = 2; cmd++;}
            else if(func_cmp_(cmd, "<=")) { how = -2 ; cmd+=2;}
            else if(func_cmp_(cmd, "<")) { how = -1; cmd++;}
            if(*cmd != '\0' && how != 0) {
                for(;*cmd == ' '; cmd++);
                /* Third Argument - Value (Type Depends on Column) */
                if(column < 0) {
                    line_value = malloc(32);
                    if(line_value == NULL) {
                        printf("fatal error: Unable to Allocate Memory (delete_by: line_value)\n\n");
                        exit(1);
                    }
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
                    float_value = (float)strtod(cmd, NULL);
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
    /* Function Could be Deployed while Looking for Arguments.
     * If not then not all Arguments were given */
    if(!done) {
        while (column == -3) {
            /* First Argument */
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
            /* Second Argument */
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
            if(line_value == NULL) {
                printf("fatal error: Unable to Allocate Memory (delete_by: line_value)\n\n");
                exit(1);
            }
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
        } else {
            cancel = 1;
        }
    }
    return cancel;
}

void delete_node_(head * hd, node * student) {
    /* If Node is First of the list */
    if(hd->first == student) {
        hd->first = student->next;
        hd->first->prev = NULL;
        free(student);
    }
    /* If last */
    else if(hd->last == student) {
        hd->last = student->prev;
        hd->last->next = NULL;
        free(student);
    }
    /* If in the Middle */
    else {
        student->prev->next = student->next;
        student->next->prev = student->prev;
        free(student);
    }
    hd->cnt--;
    new_no_(hd);
}

void delete_str_(head * hd, char * (*field)(node*), int how, char * value) {
    node * student;
    boolean printed;
    printed = 0;
    /* how == 4 -> == (Exact match)*/
    if(how == 4) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (!strcmp(field(student), value)) {
                delete_node_(hd, student);
            }
        }
    }
    /* how == 1 -> = (First Substring) */
    else if(how == 1) {
        for (student = hd->first; student != NULL; student = student->next) {
            if (func_cmp_(field(student), value)) {
                delete_node_(hd, student);
            }
        }
    }
}

void delete_int_(head * hd, int column, int how, int value) {
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

void delete_float_(head * hd, int column, int how, float value) {
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

boolean filter_by(head* hd, char * cmd) {
    /* Operates Similar to a 'Delete By' function
     * (Would be too complicated and unreadable to use function pointers, but maybe?) */
    int column, how;
    char * line_value;
    int int_value;
    float float_value;
    boolean done, cancel;
    done = 0;
    cancel = 0;
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
                    float_value = (float)strtod(cmd, NULL);
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
            printf("Choose Column to filter_by\n"
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
            if(line_value == NULL) {
                printf("fatal error: Unable to Allocate Memory (filter_by: line_value)\n\n");
                exit(1);
            }
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
        } else cancel = 1;
    }
    return cancel;
}

void filter_str_(head * hd, char * (*field)(node*), int how, char * value) {
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

void filter_int_(head * hd, int column, int how, int value) {
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

void filter_float_(head * hd, int column, int how, float value) {
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
    /* Basic Format of Output */
    printf("| %-2d | %-2d | %-23s | %-7s | %-3d | %.3f | %.2f | %-3d | %-3d | %-3d |\n",
           student->no, student->id, student->name,
           student->faculty->name, student->age,
           student->avg_score, student->completion_rate,
           student->gia_results[0], student->gia_results[1], student->gia_results[2]);
}

char sort(head * hd, char * cmd) {
    signed char mode, ad;
    boolean cancel;
    mode = 0; ad = 0; cancel = 0;
    /* Looking for arguments in Command */
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
    /* If Arguments not found */
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
        mode = cbgets(stdin);
        mode -= 2;
        if (mode <= 0) mode -= 1;
        if(mode < -3 || mode > 7) { mode = 0; printf("typo error: column not found.\n"); }
    }
    while(ad == 0 && mode != -3 && ad != -3) {
        printf("How to sort?\n0 - Cancel\n1 - Ascending\n2 - Descending\n\nMode: ");
        ad = (char)ibgets(stdin);
        if(ad == 0) ad = -3;
        else if(ad > 2 || ad < 0) {printf("error: sort mode not found\n"); ad = 0;}
        else if(ad == 2) ad = -1;
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
    else cancel = 1;
    return cancel;
}

void q_sort_(node * left, node * right, signed char mode, signed char ad) {
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

/* To reach both student->name and student->faculty->name in one function */
char * get_name_(node * student) { return student->name; }
char * get_fac_name_(node * student) { return student->faculty->name; }

void str_q_sort_(node * left, node * right, char * (*field)(node*), signed char ad) {
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

/* Internal Function. Don't Confuse with swap() */
void swap_(node * temp0, node * temp1) {
    node * buff;
    buff = (node*)malloc(sizeof(node));
    if(buff == NULL) {
        printf("fatal error: Unable to Allocate Memory (swap_: buff)\n\n");
        exit(1);
    }
    swap_cpy_(buff, temp1);
    swap_cpy_(temp1, temp0);
    swap_cpy_(temp0, buff);

    free(buff);
}

void swap_cpy_(node * temp0, node * temp1) {
    temp0->name = just_copy_(temp1->name);
    temp0->faculty = temp1->faculty;
    temp0->age = temp1->age;
    temp0->id = temp1->id;
    temp0->avg_score = temp1->avg_score;
    temp0->completion_rate = temp1->completion_rate;
    temp0->gia_results[0] = temp1->gia_results[0];
    temp0->gia_results[1] = temp1->gia_results[1];
    temp0->gia_results[2] = temp1->gia_results[2];
}


boolean swap(head * hd, char * cmd) {
    int no1, no2;
    node * student1, * student2;
    boolean err, cancel;
    no1 = no2 = 0;
    err = 0; cancel = 0;
    /* Looking for Arguments in Command */
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
    /* If Arguments not found */
    if(err == 1 || no1 == 0 || no2== 0) {
        while (no1 == 0 && !cancel) {
            printf("Type no of first string to swap (0 to cancel): ");
            no1 = ibgets(stdin);
            if(no1 < 0) { printf("typo error: No should be a positive number\n"); no1 = 0; }
            else if (no1 == 0) cancel = 1;
        }
        while (no2 == 0 && !cancel) {
            printf("Type no of second string to swap (0 to cancel): ");
            no2 = ibgets(stdin);
            if(no2 < 0) { printf("typo error: No should be a positive number\n"); no1 = 0; }
            else if (no2 == 0) cancel = 1;
        }
    }
    if(!cancel) {
        for (student1 = hd->first; student1 != NULL && student1->no != no1; student1 = student1->next);
        if (student1 == NULL) {
            printf("error: Element with No %d not found\n", no1);
        } else {
            for (student2 = hd->first; student2 != NULL && student2->no != no2; student2 = student2->next);
            if (student2 == NULL) printf("error: Element with No %d not found\n", no2);
            else swap_(student1, student2);
        }
    }
    return cancel;
}

f_node * foreign_key_(f_head *f_hd, char * fac_name) {
    f_node * node, * res;
    boolean found;
    found = 0;
    /* Looking for Faculty with a Given Name */
    for(node = f_hd->first; node != NULL && found == 0; node = node->next) {
        if(!strcmp(fac_name, node->name)) {
            found = 1;
            res = node;
        }
    }
    /* If Faculty was not found make append new Node */
    if(!found) {
        make_new_f_(f_hd, fac_name);
        res = f_hd->last;
    }
    return res;
}

void make_new_f_(f_head * f_hd, char * node_name) {
    f_node * node;
    node = (f_node*)malloc(sizeof(f_node));
    if(node == NULL) {
        printf("fatal error: Unable to Allocate Memory (make_new_f_: node)\n\n");
        exit(1);
    }
    node->name = just_copy_(node_name);
    node->next = NULL;
    if(!f_hd->cnt) {
        /* If it is first Node */
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

char ** split(char * line, const char sep) {
    int separators_in_line, i, k, m;
    char ** result_array = NULL;
    /* Looking amount of separators for Memory Allocation */
    for (i = 0, separators_in_line = 0; i < strlen(line); i++)
        if(line[i] == sep) separators_in_line++;

    result_array = (char**)malloc((separators_in_line + 1) * sizeof (char*));
    if(result_array == NULL) {
        printf("fatal error: Unable to Allocate Memory (split: result_array)\n\n");
        exit(1);
    }
    /* Allocating Memory for each String Element */
    for(i = 0; i < separators_in_line + 1; i++) {
        if(result_array != NULL) {
            result_array[i] = (char*)malloc(strlen(line) * sizeof(char));
            if (result_array[i] == NULL) result_array = NULL;
        } else i = separators_in_line + 1;
    }
    if(result_array == NULL) {
        printf("fatal error: Unable to Allocate Memory (split: result_array)\n\n");
        exit(1);
    }
    /* Splitting */
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
        result_array[m][i - k] = '\0';
    }

    return result_array;
}

char * bgets(char *st, int const len, FILE *fp) {
    unsigned long str_len;
    st = fgets(st, len, fp);
    /* Getting rid of Possible \r\n not to think about them */
    if(st != NULL) {
        str_len = strlen(st);
        if (st[str_len - 1] == '\n') {
            if (st[str_len - 2] == '\r')
                st[str_len - 2] = '\0';
            else
                st[str_len - 1] = '\0';
        }
    }
    return st;
}

int ibgets(FILE *fp) {
    char * st;
    /* Max int is 10 digit long */
    st = malloc(11);
    if(st == NULL) {
        printf("fatal error: Unable to Allocate Memory (ibgets: st)\n\n");
        exit(1);
    }
    return (int)strtol(bgets(st, 11, fp), NULL, 10);
}

float fbgets(FILE *fp) {
    char * st;
    /* Max float digit counter is 31 */
    st = malloc(32);
    if(st == NULL) {
        printf("fatal error: Unable to Allocate Memory (fbgets: st)\n\n");
        exit(1);
    }
    return (float)strtod(bgets(st, 31, fp), NULL);
}

char cbgets(FILE * fp) {
    char * st;
    /* Max char is 3 digit long */
    st = malloc(4);
    if(st == NULL) {
        printf("fatal error: Unable to Allocate Memory (cbgets: st)\n\n");
        exit(1);
    }
    return (char)strtol(bgets(st, 4, fp), NULL, 10);
}

boolean func_cmp_(char * cmd, char * compare) {
    char * temp1, * temp2;
    boolean res;
    res = 1;
    /* Looking if compare is a first substring of cmd */
    for(temp1 = cmd, temp2 = compare; *temp1 != '\0' && *temp2 != '\0' && res == 1; temp1++, temp2++) {
        if (*temp1 != *temp2) res = 0;
    }
    if(*temp1 == '\0' && *temp2 != '\0') res = 0;
    return res;
}

int strcount(char * in, char * substring) {
    int count;
    unsigned long substring_len;
    char * st0;
    count = 0;
    substring_len = strlen(substring);
    /* Looking for substring in String */
    st0 = strstr(in, substring);
    while(st0 != NULL) {
        /* If found go once again and count */
        count++;
        st0 += substring_len;
        st0 = strstr(st0, substring);
    }
    return count;
}

char * striped(const char *string, char border) {
    unsigned int i, j, k, k1, string_len;
    char *result;
    string_len = strlen(string);
    /* Crushes without this check */
    if(*string != '\0' && string_len > 1) {
        /* Index of a First 'useful' char */
        for (i = 0; string[i] == border; i++);
        /* Index of a Last 'useful' char */
        for(j = string_len-1; string[j] == border && j > 0; j--);
        /* If String consists only from Border j<=i */
        if(j > i) {
            result = malloc(i + j + 1);
            if(result == NULL) {
                printf("fatal error: Unable to Allocate Memory (striped: result)\n\n");
                exit(1);
            }
            for (k = i, k1 = 0; k <= j; k++, k1++) {
                result[k1] = string[k];
            }
            result[k1] = '\0';
        } else {
            /* Returns string \0 if String consists only from Border */
            result = malloc(1);
            if(result == NULL) {
                printf("fatal error: Unable to Allocate Memory (striped: result)\n\n");
                exit(1);
            }
            *result = 0;
        }
    }
    else {
        if(*string == border) {
            /* Returns string \0 if input is \0 */
            result = malloc(1);
            if(result == NULL) {
                printf("fatal error: Unable to Allocate Memory (striped: result)\n\n");
                exit(1);
            }
            *result = 0;
        } else {
            result = malloc(2);
            if(result == NULL) {
                printf("fatal error: Unable to Allocate Memory (striped: result)\n\n");
                exit(1);
            }
            *result = *string;
            *(result+1) = 0;
        }
    }
    return result;
}

void create_(head * hd, f_head * f_hd) {
    hd->cnt = 0;
    hd->first = NULL;
    hd->last = NULL;
    f_hd->cnt = 0;
    f_hd->first = NULL;
    f_hd->last = NULL;
}

char * lower_str_(char * string) {
    char * gol;
    for(gol = string; *gol != '\0'; gol++) {
        if(*gol <= 'Z' && *gol >= 'A') *gol += 32;
    }
    return gol;
}

char * just_copy_(const char * st) {
    char * res;
    unsigned long len, i;
    /* strcpy() from string.h does not like pointers to a structure member in some cases */
    len = strlen(st);
    res = malloc(len);
    if(res == NULL) {
        printf("fatal error: Unable to Allocate Memory (just_copy_: res)\n\n");
        exit(1);
    }
    for(i = 0; i < len; *(res + i) = *(st + i), i++);
    *(res + i) = '\0';
    return res;
}

void new_no_(head * hd) {
    node * student;
    int i;
    /* Refreshes No's of list, since they are designed to always be ascending and continuous */
    for(i = 0, student = hd->first; student != NULL; student->no = ++i, student = student->next);
}

void help(char * cmd) {
    /* Documentation */

    /* If no Arguments */
    if (!strcmp(cmd, "Help"))
        printf("Available Commands:\n"
               "Quit                             - to quit\n"
               "Enter <csv/lbl>                  - to fill Kartoteka from keyboard\n"
               "Import <file name>               - to fill Kartoteka from file\n"
               "Export <file name>               - to make file from Kartoteka data\n"
               "Show <max amount>                - to show up to positive max amount of lines\n"
               "Change <No> <csv/lbl>            - to change line #N from keyboard\n"
               "Swap <No1> <No2>                 - to swap lines with no N1 and N2\n"
               "Sort <Column> <a/d>              - to sort column ascending/descending\n"
               "Filter <Column> <(how)value>     - to show all lines with necessary value\n"
               "Delete All                       - to delete all Kartoteka database\n"
               "Delete <No>                      - to delete line #N\n"
               "Delete By <Column> <(how)value>  - to delete lines with necessary value\n"
               "Quick                            - to quick look data in Kartoteka\n"
               "Clear                            - to clear the screen\n"
               "<Command> & <Command> . . .      - to deploy several Commands\n"
               "Source                           - to show a link on a source code.\n"
               "Help <Command>                   - for documentation\n\n"
               "Use Help <Command> for specific Function documentation\n\n");
    else {
        /* If found an Argument */
        cmd += 4;
        for(; *cmd == ' '; cmd++);
        if (!strcmp(cmd, "Quit"))
            printf("Quit function is used to terminate Kartoteka\n"
                   "Just type 'Quit' if you had enough.\n\n");
        else if(func_cmp_(cmd, "Save")) {
            printf("Save function is used to save your Kartoteka and access it on the next start of the program\n\n");
        }
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
        else if(func_cmp_(cmd, "&"))
            printf("& Helps you to deploy several Commands in one.\n"
                   "\n"
                   "Usage Example:\n"
                   "Sort Age a & Delete 1 & Show\n\n");
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
        else if(func_cmp_(cmd, "Source"))
            source_code();
        else
            printf("Function %s not found\n\n", cmd);
    }
}

void source_code() {
    printf("Kartoteka is an open-source project made by Maksim Trostin\n"
           "Source Code: https://github.com/Argentusz/Semestralna_II\n\n"
           "Kartoteka Source Code is licensed under the Creative Commons Zero v1.0 Universal\n\n");
}