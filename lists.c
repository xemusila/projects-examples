// Ввод данных, обработка списка отдельно для заданий II и III, а также вывод списка на экран оформляются как отдельные функции. Анализ существования результата производится в главной функции. 
// При выделении и освобождении памяти использовать malloc и free. 
// При вводе данных и выводе результата использовать fscanf, fgets и fprintf, fputs.
// I.	Создать связанный список для хранения целых чисел. Число записей неизвестно, данные читаются из файла, имя которого задает пользователь. Имя выходного файла также задается пользователем. Входной файл содержит данные для исходного списка, выходной – для конечного списка. Организовать очередь.
// II.	Для исходного списка решить следующую задачу: удалить все элементы, равные минимальному элементу списка.
// III.	Для полученного списка решить следующую задачу: выбрать из списка ненулевые элементы и сформировать из них новую очередь.
// ЗАМЕЧАНИЕ. Все части оформить в одной программе, для каждой части написать отдельную функцию. Предусмотреть вывод списка после выполнения каждого задания с помощью отдельной функции. По завершении работы программы необходимо освободить память, занятую списком.




#include <stdio.h>
#include <stdlib.h>
#define lmax 200


struct node
{
    struct node *next;
    int info;
};

struct node *queue(char *filename1, char *filename2)
{
    FILE *file1;
    int n;
    struct node *add, *last, *first = NULL;
    puts("Введите название входного файла: ");
    gets(filename1);
    puts("Введите название выходного файла: ");
    gets(filename2);
    file1 = fopen(filename1, "r");
    if (file1 == NULL)
    {
        puts("Ошибка открытия файла");
        return first;
    }

    if (fscanf(file1, "%d", &n) == EOF) 
        return first;
    else
    {
        first = (struct node *)malloc(sizeof(struct node));
        first -> info = n;
        last = first;
        while (fscanf(file1, "%d", &n) != EOF)
        {
            add = (struct node *)malloc(sizeof(struct node));
            add -> info = n;
            last -> next = add;
            last = add;
        }
        last -> next = NULL;
        return first;
    }
    fclose(file1);
}


struct node *task1(char filename2[], struct node *first)
{
    int min;
    struct node *curr, *prev;

    curr = first -> next;
    min = first -> info;
    while (curr)
    {
        if (curr -> info < min)
            min = curr -> info;
        curr = curr -> next;
    }

    curr = first;
    prev = first;
    while (curr)
    {
        if (curr -> info == min)
        {
            if (curr == first)
            {
                curr = curr -> next;
                free(first);
                first = curr;
                prev = curr;
            }
            else
            {
                prev -> next = curr -> next;
                free(curr);
                curr = prev -> next;
            }
        }
        else
        {
            prev = curr;
            curr = curr -> next;
        }
    }
    return first;
}


struct node *task2(struct node *first, int *flag)
{
    struct node *curr = first, *new_first = NULL, *new_curr, *new_last;
    while (curr)
    {
        if (curr -> info != 0)
        {
            if (new_first == NULL)
            {
                new_first = (struct node *)malloc(sizeof(struct node));
                new_last = new_first;
            }
            new_curr = new_last;
            new_last = (struct node *)malloc(sizeof(struct node));
            new_curr -> info = curr -> info;
            new_curr -> next = new_last;
        }
        else *flag = 1;
        curr = curr -> next;
    }
    if (new_first)
    {
        new_curr -> next = NULL;
        free(new_last);
    }
    return new_first;
}


void output_origin(struct node *first, char filename[])
{
    FILE *file;
    struct node *curr = first;
    file = fopen(filename, "w");
    fputs("Исходный список:\n", file);
    while(curr)
    {
        fprintf(file, "%7d", curr -> info);
        curr = curr -> next;
    }
    fprintf(file, "\n");
    fclose(file);
}


void output_task1(struct node *first, char filename[])
{
    FILE *file;
    struct node *curr = first;
    file = fopen(filename, "a");
    fputs("Задание 1:\n", file);
    while(curr)
    {
        fprintf(file, "%7d", curr -> info);
        curr = curr -> next;
    }
    fprintf(file, "\n");
    fclose(file);
}


void output_task2(struct node *first, char filename[])
{
    FILE *file;
    struct node *curr = first;
    file = fopen(filename, "a");
    fputs("Задание 2:\n", file);
    while(curr)
    {
        fprintf(file, "%7d", curr -> info);
        curr = curr -> next;
    }
    fprintf(file, "\n");
    fclose(file);
}


void free_memory(struct node *first) 
{
    struct node *curr = first, *next = first;
    while (next)
    {
        next = curr -> next;
        free(curr);
        curr = next;
    }
}

int main()
{
    FILE *file;
    char filename1[lmax], filename2[lmax];
    struct node *lst, *new_lst;
    int flag = 0;

    lst = queue(filename1, filename2);
    if (!lst)
    {
        file = fopen(filename2, "w");
        fputs("Исходный список пуст", file);
        fclose(file);
    }
    else
    {
        output_origin(lst, filename2);
        lst = task1(filename2, lst);
        if (!lst)
        {
            file = fopen(filename2, "a");
            fputs("Список полностью удалён", file);
            fclose(file);
        }
        else
        {
            output_task1(lst, filename2);
            new_lst = task2(lst, &flag);
            if (!flag)
            {
                file = fopen(filename2, "a");
                fputs("Список не изменился", file);
                fclose(file);
            }
            else
                output_task2(new_lst, filename2);
            free_memory(lst);
            free_memory(new_lst);
        }
    }
    return 0;
}