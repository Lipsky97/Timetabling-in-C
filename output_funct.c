#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Function used to find all modules that clash with module put it by the user
int output_modules(char *ans, int schemes) {
    module *m;
    int scheme[100];
    int scheme_count = 0;

    for (int i = 0; i < schemes; i++) {
        int mods = s_array[i]->modules_number;
        for (int k = 0; k < mods; k++) {
            int compare = strcmp(ans, s_array[i]->codes[k]->module_code);
            if (compare == 0) {
                scheme[scheme_count] = i;
                scheme_count++;
            }
        }
    }
    m = search(ans);
    if(m == NULL){
        perror("Module you typed does not exist");
        return 0;
    }
    print_module(m, scheme, scheme_count);
}

//Function to print all needed information about certain module
void print_module(module *m, int *schemes, int c_scheme){
    int n_students = 0;
    for(int a = 0; a < c_scheme; a++) {
        n_students = n_students + s_array[schemes[a]]->students;
    }
    printf("Module: %s\n"
                   "Semester: %d\n"
                   "Registered students: %d\n"
                   "Collides with modules: ",
           m->module_code,
           m->semester,
           n_students);
    for(int i = 0; i < c_scheme; i++){
        for(int k = 0; k < s_array[i]->modules_number; k++){
            if (m->semester == s_array[schemes[i]]->codes[k]->semester){
                printf("%s ", s_array[schemes[i]]->codes[k]->module_code);
            }
        }
    }
    printf("\n");
}

timetable *add_timetable(){
    timetable *new_timetable = malloc(sizeof(timetable));
    return new_timetable;
}
//To create a timetable program is using 2 loops separate for lectures and practicals,
//algorithm is considering length of every lecture and practical.
timetable *create_timetable(char *ans, int *hours, int sem, int n_modules){
    int i = 0;
    int module_count[DAYS_OF_WEEK] = {0, 0, 0, 0, 0, 0, 0};
    int scheme_index;
    module *m;
    scheme *s;
    timetable *timetable = add_timetable();

    //loop to see if certain scheme actually exists
    for (i = 0; i < n_modules; i++) {
        int compare = strcmp(ans, s_array[i]->scheme_code);
        if (compare == 0){
            scheme_index = i;
            break;
        }
    }
    if (i == n_modules) return NULL;

    s = s_array[scheme_index];

    int k = 0;
    //timetabling all practicals
    //pick first module from list of modules for this degree scheme
    //if it is running in the semester we are interested in, has more than 0 students,
    //for every practical try to timetable it starting from monday, if that day is already full,
    //then try next day, if you can't timetable practical, return null and print error
    for(int a = 0; a < s->modules_number; a++){
        m = s->codes[a];
        if (m->semester != sem || s->students == 0)continue;
        for (i = 0; i < m->p_hours; i++) {
            for (k = 0; k < DAYS_OF_WEEK; k++) {
                if (m->p_length != 0 || m->p_length <= hours[k]) {
                    timetable->weekdays[k][module_count[k]] = m;
                    hours[k] = hours[k] - m->p_length;
                    module_count[k]++;
                    break;
                }
            }
            if (k == DAYS_OF_WEEK){
                printf("Couldn't timetable practical for module %s\n", m->module_code);
                return NULL;
            }
        }
    }

    //timetabling all lectures
    //algorithm same as with practicals
    for(int a = 0; a < s->modules_number; a++){
        m = s->codes[a];
        if (m->semester != sem || s->students == 0)continue;
        for (i = 0; i < m->l_hours; i++){
            for (k = 0; k < DAYS_OF_WEEK; k++){
                if (m->l_length != 0 || m->l_length <= hours[k]){
                    timetable->weekdays[k][module_count[k]] = m;
                    hours[k] = hours[k] - m->l_length;
                    module_count[k]++;
                    break;
                }
            }
            if (k == DAYS_OF_WEEK){
                printf("Couldn't timetable lecture for module %s\n", m->module_code);
                return NULL;
            }
        }
    }
    return timetable;
}

void print_timetable(timetable *t, char *ans){
    const char *days_of_week[DAYS_OF_WEEK];
    days_of_week[0] = "Monday";
    days_of_week[1] = "Tuesday";
    days_of_week[2] = "Wednesday";
    days_of_week[3] = "Thursday";
    days_of_week[4] = "Friday";
    days_of_week[5] = "Saturday";
    days_of_week[6] = "Sunday";

    printf("Timetable for scheme %s\n\n", ans);

    for (int a = 0; a < DAYS_OF_WEEK; a++) {
        printf("%s: \t", days_of_week[a]);
        for (int b = 0; b < MAX_LECTURES; b++) {
            printf("%s ", t->weekdays[a][b]->module_code);
        }
        printf("\n");
    }
    printf("\n\n\n");
}