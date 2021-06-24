#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


module *add_module(){
    module *new_module;
    new_module = malloc(sizeof(module));
    return new_module;
}

void fill_module(module *new_module, char code[M_CODE_LENGTH], int sem, int l_h, int l_l, int p_h, int p_l){
    strcpy(new_module->module_code, code);
    new_module->semester = sem;
    new_module->l_hours = l_h;
    new_module->p_hours = p_h;
    new_module->l_length = l_l;
    new_module->p_length = p_l;
}

int read_modules(){
    FILE *fp;
    module *n_module;
    char module[M_CODE_LENGTH];
    int semester;
    char l_hours[4];
    char p_hours[4];
    int size_of_module_array = 0;

    fp = fopen("modules.txt", "r");

    if (fp == NULL){
        perror("Error in opening 'modules.txt' file");
        return (-1);
    }

    int i =0;

    //looping througth every line in txt file to create a struct for every module
    while (1){
        int l_h, l_l, p_h, p_l;
        fscanf(fp, "%s %d %s %s", module, &semester, l_hours, p_hours);
        sscanf(l_hours, "%d", &l_h);
        sscanf(l_hours+2, "%d", &l_l);
        sscanf(p_hours, "%d", &p_h);
        sscanf(p_hours+2, "%d", &p_l);
        n_module = add_module();
        fill_module(n_module, module, semester, l_h, l_l, p_h, p_l);
        m_array[i] = n_module;
        i++;
        size_of_module_array++;
        if (feof(fp)) break;
    }

    fclose(fp);
    return size_of_module_array;
}

void fill_scheme(scheme *s, char *cod, int year, int students, module **mods, int n_modules){
    strcpy(s->scheme_code, cod);
    memcpy(s->codes, mods, sizeof(s->codes));
    s->year = year;
    s->students = students;
    s->modules_number = n_modules;
}

scheme *add_scheme(){
    scheme *new_scheme;
    new_scheme = malloc(sizeof(scheme));
    return new_scheme;
}

int read_schemes(){
    FILE *fp;
    scheme *n_scheme;
    module *n_mod;
    char str[100];
    char code[S_CODE_LENGTH];
    char m_code[M_CODE_LENGTH];
    int year;
    int n_students;
    int n_modules;
    int size_of_scheme_array = 0;

    fp = fopen("schemes.txt", "r");
    if (fp == NULL){
        perror("Error in opening file 'schemes.txt'");
        return (-1);
    }
    int i = 0;
    while(1){
        fscanf(fp, " %[^\n] ", str);

        sscanf(str, "%s %d %d %d", code, &year, &n_students, &n_modules);
        module *scheme_modules[n_modules];
        for (int a = 0; a < n_modules; a++){
            sscanf(str+13+(a*8), "%s", m_code);
            n_mod = search(m_code);
            if (n_mod == NULL){
                perror("This module doesn't exist");
                return (-1);
            } else {
                scheme_modules[a] = n_mod;
            }
        }

        n_scheme = add_scheme();
        fill_scheme(n_scheme, code, year, n_students, scheme_modules, n_modules);
        s_array[i] = n_scheme;
        i++;
        size_of_scheme_array++;

        if (feof(fp)) break;
    }
    return size_of_scheme_array;
}


//linear search function used to make sure that certain module exists
module *search(char *module){
    int i;
    int length = sizeof(m_array)/ sizeof(module);
    for (i = 0; i < length; i++){
        char code[M_CODE_LENGTH];
        strcpy(code, m_array[i]->module_code);
        if (strcmp(module, code) == 0){
            return m_array[i];
        }
    }
    if (i == 100){
        return NULL;
    }
}