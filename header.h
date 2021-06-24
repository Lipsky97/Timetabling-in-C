
#ifndef CREATE_TIMETABLE_HEADER_H
#define CREATE_TIMETABLE_HEADER_H
#define ARRAY_SIZE 1000
#define DAYS_OF_WEEK 7
#define MAX_LECTURES 9
#define M_CODE_LENGTH 8
#define S_CODE_LENGTH 20

typedef struct module_list {
    char module_code[M_CODE_LENGTH];
    int semester;
    int l_hours;
    int l_length;
    int p_hours;
    int p_length;
} module ;

typedef struct degree_schemes {
    char scheme_code[S_CODE_LENGTH];
    int year;
    int students;
    int modules_number;
    module *codes[11];
} scheme ;

typedef struct time_table {
    module *weekdays[DAYS_OF_WEEK][MAX_LECTURES];
    int hours_taken[DAYS_OF_WEEK];
} timetable ;

scheme *s_array[ARRAY_SIZE];
module *m_array[ARRAY_SIZE];
int teaching_hours[DAYS_OF_WEEK][MAX_LECTURES];

int read_modules();
int read_schemes();

timetable *add_timetable();
timetable *create_timetable(char *ans, int *hours, int sem, int n_modules);

module *search(char module[]);
module *add_module();

scheme *add_scheme();

void fill_module(module *new_module, char code[M_CODE_LENGTH], int sem, int l_h, int l_l, int p_h, int p_l);
int output_modules(char *ans, int schemes);
void print_module(module *m, int *schemes, int c_scheme);
void fill_scheme(scheme *s, char *cod, int year, int students, module **mods, int n_mods);
void print_timetable(timetable *t, char *ans);

#endif //CREATE_TIMETABLE_HEADER_H
