// Даны символьные строки (количество строк задает пользователь). Требуется:
// I.	Выделить из каждой строки и напечатать подстроки, не содержащие знаков «больше», «меньше», «равно».
// ПРИМЕЧАНИЕ. Каждую подстроку печатать с новой строки. Пустые подстроки не выделять и не печатать. 
// II.	Среди выделенных подстрок найти подстроку, содержащую минимальное число цифр 0, 2, 4, 6, 8.
// ПРИМЕЧАНИЕ. Если таких подстрок несколько, выбирается первая из них. 
// III.	Преобразовать исходную строку, которой принадлежит найденная подстрока, следующим образом: удалить русские буквы, расположенные в конце строки.


#include <iostream>
#include <string>
#include <limits.h>
#define lmax 200
using namespace std;


bool no_compare(int n, string strings[], int *new_n, string new_strings[], int string_number[])
{
    int curr_length, j, start;
    string signs = "<>=";
    bool flag = false;
    for (int i = 0; i < n; i ++)
    {
        curr_length = strings[i].length();
        j = 0;
        start = -1;
        while (j < curr_length)
        {
            if (start != -1 and signs.find(strings[i][j]) != -1)
            {
                string_number[*new_n] = i;
                new_strings[(*new_n)++].assign(strings[i], start, j - start);
                start = -1;
                flag = true;
            }
            else
                if (start == -1 and signs.find(strings[i][j]) == -1)
                    start = j;
            j ++;
        }
        if (start != -1 and signs.find(strings[i][j]) == -1)
        {
            string_number[*new_n] = i;
            new_strings[(*new_n)++].assign(strings[i], start, j - start);
        }
    }
    return flag;
}


int min_numbers(int new_n, string new_strings[], int *min_numb_ind)
{
    int curr_length, min_number = INT_MAX, count;
    string numbers = "02468";
    for (int i = 0; i < new_n; i ++)
    {
        curr_length = new_strings[i].length();
        count = 0;
        for (int j = 0; j < curr_length and count < min_number; j ++)
        {
            if (numbers.find(new_strings[i][j]) != -1)
                count ++;
        }
        if (count < min_number and count > 0 or count == INT_MAX)
        {
            min_number = count;
            *min_numb_ind = i;
        }
    }
    return min_number;
}

bool delete_russian_letters(string &str)
{
    bool flag = false;
    int length = str.length(), i;
    string russian_letters = "йцукенгшщзхъёэждлорпавыфячсмитьбюЙЦУКЕНГШЩЗХЪЁЭЖДЛОРПАВЫФЯЧСМИТЬБЮ";
    for (i = length - 1; i >= 0 and russian_letters.find(str[i]) != -1; i --);
    if (i < length - 1)
    {
        flag = true;
        str.erase(i + 1, length - i - 1);
    }
    return flag;
}


int main()
{
    int n = 0, new_n = 0, i, min_numb_ind, string_number[lmax];
    string strings[lmax], s, new_strings[lmax];
    bool flag = true;

    do
    {
        cout << "Введите число символьнвых строк: ";
        cin >> n;
        if (cin.fail())
            cin.clear();
        getline(cin, s);
    }
    while (n <= 0);

    cout << "Введите " << n << " символьных строк:" << endl;
    for (i = 0; i < n; i ++)
        getline(cin, strings[i]);


    flag = no_compare(n, strings, &new_n, new_strings, string_number);
    if (new_n == 0)
        cout << "Нет подстрок, не содержащих знаков <, >, =" << endl;
    else
    {
        if (flag == false)
            cout << "Ничего не изменилось" << endl;
        else
        {
            cout << "Искомые подстроки, не содержащие знаки <, >, =" << endl;
            for (i = 0; i < new_n; i ++)
            {
                cout << new_strings[i] << endl;
            }
        }
        
        if (min_numbers(new_n, new_strings, &min_numb_ind) == INT_MAX)
            cout << "Подстроки не содержат данных цифр" << endl;
        else
        {
            cout << "Первая подстрока, содержащая минимальное число цифр 0, 2, 4, 6, 8:" << endl;
            cout << new_strings[min_numb_ind] << endl;
            if (delete_russian_letters(strings[string_number[min_numb_ind]]))
            {
                cout << "Преобразованная исходная строка:" << endl;
                cout << strings[string_number[min_numb_ind]];
            }
            else
                cout << "В конце исходной строки нет русских букв";
        }
    }

    return 0;
}
