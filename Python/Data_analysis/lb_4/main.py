"""" 
Футболист забивает мяч в ворота, по его словам, в каждом 5-м ударе по воротам. Альтернативная гипотеза тренера - один из 7 ударов. Проверочный объем данных - 100 ударов.

1. Вычислите в программном коде и выведите все диапазоны, имеющие отношение к проверке гипотез.

2. Напишите функцию, делающую проверку гипотезы по введенным данным теста с задаваемым уровнем значимости, равным по умолчанию 5%.

3. Напишите функцию, которая вычисляет мощность проверки по заданным данным теста и заданному значению альтернативной гипотезы.

4. Сформулируйте свою статистическую гипотезу (можно не про спортсменов) и используйте свои функции для ее проверки.
"""

import modul

def main():
    # print("=====================================================")
    # print("Ex_1\nНулевая гипотеза (Каждый 5-ый удар)")
    # modul.ex_1(5)
    # print("\nАльтернативная гипотеза (Каждый 7-ой удар)")
    # modul.ex_1(7)
    # print("=====================================================\n")

    print("=====================================================")
    print("Ex_2\n")
    # measurements = int(input("Введите кол-во измерений: "))
    # itDone = int(input("Введите кол-во выполненых дейсвтий: "))
    # frequency = int(input("Введите частоту дейсвтия: "))
    # modul.ex_2(frequency,measurements,itDone)
    #modul.ex_2(5,1000,150)
    print("=====================================================\n")

    print("=====================================================")
    print("Ex_3\n")
    modul.ex_3(5,1000,7)
    print("=====================================================\n")

    # print("=====================================================")
    # print("Ex_4\n")
    # modul.ex_4()
    # print("=====================================================")

main()