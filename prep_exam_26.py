'''На складе хранятся кубические контейнеры различного размера.
Чтобы сократить занимаемое при хранении место, контейнеры вкладывают друг в друга.
Один контейнер можно вложить в другой, если размер стороны внешнего контейнера
превышает размер стороны внутреннего на 5 и более условных единиц. Группу вложенных
друг в друга контейнеров называют блоком. Количество контейнеров в блоке может быть
любым. Каждый блок, независимо от количества и размера входящих в него контейнеров,
а также каждый одиночный контейнер, не входящий в блоки, занимает при хранении одну
складскую ячейку.
Зная количество контейнеров и их размеры, определите минимальное количество ячеек
для хранения всех контейнеров и максимально возможное количество контейнеров в одном
блоке.
Входные данные
Первая строка входного файла содержит целое число N – общее количество контейнеров.
Каждая из следующих N строк содержит натуральное число, не превышающее
10 000, – размер контейнера в условных единицах.
В ответе запишите два целых числа: сначала минимальное количество ячеек
для хранения всех контейнеров, затем максимально возможное количество контейнеров
в одном блоке.'''


n = 1000
with open('26.txt') as f:
    s = f.readlines()
a = []
for i in s:
    a.append(int(i))
a.sort()
m = 0
k = 1
count = 0
while len(a) > 0:
    box = a[0]
    i = 1
    k = 1
    while len(a) > 0 and i < len(a):
        if a[i] - box >= 5:
            k += 1
            box = a[i]
            del a[i]
        else:
            i += 1
    m = max(m, k)
    count += 1
    del a[0]
m = max(m, k)
print(count, m)
        
