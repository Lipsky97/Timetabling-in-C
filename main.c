#include <stdio.h>
#include <string.h>
#include "header.h"

int main() {
    int number_of_schemes;
    int number_of_modules;

    number_of_modules = read_modules();
    number_of_schemes = read_schemes();

    FILE *fp;
    char day[11];
    int n_hours[DAYS_OF_WEEK];

    //program won't ask user for directory where files live, they have to be in the same directory as program
    fp = fopen("times.txt", "r");

    if (fp == NULL) {
        perror("Error in opening 'times.txt' file");
        return 0;
    }

    //reading "times.txt" file and putting number of available hours in 2D array
    for (int a = 0; a < DAYS_OF_WEEK; a++) {
        fscanf(fp, "%s %d", day, &n_hours[a]);
        for (int l = 0; l < n_hours[a]; l++) {
            fscanf(fp, "%d", &teaching_hours[a][l]);
        }
        if (feof(fp)) break;
    }

    while (1) {
        printf("Welcome to the timetabling program please type your module, or type 'exit' to close program\n");
        char ans[9];
        scanf("%s", ans);
        int compare = strcmp(ans, "exit");
        if (compare == 0) return 0;
        int err = output_modules(ans, number_of_schemes);
        if (err == 0)return 0;
        int sem;
        printf("Select semester to timetable, to exit type 'exit' to close program\n");
        scanf("%d", &sem);
        printf("Select degree scheme: \n");
        scanf("%s", ans);
        compare = strcmp(ans, "exit");
        if (compare == 0) return 0;
        timetable *t = create_timetable(ans, n_hours, sem, number_of_modules);
        if (t == NULL) {
            printf("Timetable couldn't be created, try with different scheme");
            continue;
        }
        print_timetable(t, ans);
    }
}