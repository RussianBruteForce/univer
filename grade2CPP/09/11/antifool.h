#ifndef ANTIFOOL_H
#define ANTIFOOL_H

#include <iostream>
#include <string>
#include <limits> // для std::numeric_limits


/*
 * Все функции класса -- статичные (static),
 * т. к. нам не надо создавать класс для их использования.
 * Это именно КЛАСС, а не просто пространство имен (namespace)
 * т. к. нам нужна секция приватных (private) функций.
 * Снаружи класса они не нужны, а нужны только в функциях класса.
 */
class AntiFool
{
public:
    AntiFool() = delete; // запрещаем конструктор класса

    /*
     * Общий темплейт для любых типов.
     * Далее идут конкретные специализации для разных типов
     *
     * Параметр msg по умолчанию всегда будет пустой строкой,
     * так что если нчиего писать при вызове функции не надо,
     * то можно просто не указывать его, а писать просто
     *
     * int x;
     * read (x);
     * string h;
     * read(h);
     *
     * В этом случае ничего выводится на экран не будет.
     */
    template<typename T>
    static void read(T &s, const std::string &msg = "")
    {
        print_msg(msg);
        /*
         * пока cin не скажет, что прочитал то, что надо
         * цикл будет повторяться
         */
        while(!(std::cin >> s)) {
            clear_istdstream();
            print_msg(msg);
        }
    }

    /*
     * Для uint:
     */
    static void read(uint &s, const std::string &msg = "")
    {
        while (true) {
            print_msg(msg);

            /*
             * Создаем буферную строку и читаем туда строку
             * из потока ввода.
             */
            std::string buf;
            std::cin >> buf;

            /*
             * счетчик цифр, 'size_t' это
             * просто другое опеределение (typedef)
             * типа 'unsigned long'
             */
            size_t digits_in_string = 0;
            /*
             * Все очень просто:
             *  смотрим каждый символ в сроке
             *  и если этот символ -- цифра
             *  то увеличиваем счетчик цифр на 1;
             */
            for (auto x : buf) // цикл
                if (isdigit(x)) // проверка на цифру
                    digits_in_string++; // увеличение счетчика
            /*
             * Сравниваем количество символов в строке
             * с количеством цифр, которое насчитали.
             * Если совпадает -- вся наша строка это циферки,
             * а значит в строке -- число;
             */
            if (digits_in_string == buf.size()){
                /*
                 * atol(const char *__nulptr) преобразует массив char
                 * в число типа long. Затем мы используем
                 * статическое приведение типа (static_cast) к типу
                 * 'unsigned int' (uint).
                 *
                 * Функция string::c_str() возвращает нам массив char
                 * от нашей строки buf.
                 *
                 * Мы не используем тут atoi(const char *__nulptr), т. к.
                 * хоть по размеру в памяти int занимает столько же,
                 * сколько и uint, но может хранить положительное значение
                 * меньше чем uint;
                 */
                s = static_cast<uint>(atol(buf.c_str()));
                break; // выходим из цикла, т. к. это успеееееех
            }
            clear_istdstream();
        }
    }

    /*
     * Для double отличия минимальны
     */
    static void read(double &s, const std::string &msg = "")
    {
        while (true) {
            print_msg(msg);

            std::string buf;
            std::cin >> buf;

            size_t digits_in_string = 0;
            /*
             * В отличии от uint, int могут быть отрицательными.
             * Поэтому мы добавляем проверку на минус в начале и
             * если это так, то увеличиваем количество "цифр" на 1,
             * чтобы все совпало.
             */
            if (buf.at(0) == '-')
                digits_in_string++;

            for (auto x : buf)
                if (isdigit(x))
                    digits_in_string++;

            if (digits_in_string == buf.size()){
                /*
                 * Используем atoi для получения числа
                 * типа int из массива char
                 */
                s = atof(buf.c_str());
                break;
            }
            clear_istdstream();
        }
    }

    /*
     * Для int отличия минимальны
     */
    static void read(int &s, const std::string &msg = "")
    {
        while (true) {
            print_msg(msg);

            std::string buf;
            std::cin >> buf;

            size_t digits_in_string = 0;
            /*
             * В отличии от uint, int могут быть отрицательными.
             * Поэтому мы добавляем проверку на минус в начале и
             * если это так, то увеличиваем количество "цифр" на 1,
             * чтобы все совпало.
             */
            if (buf.at(0) == '-')
                digits_in_string++;

            for (auto x : buf)
                if (isdigit(x))
                    digits_in_string++;

            if (digits_in_string == buf.size()){
                /*
                 * Используем atoi для получения числа
                 * типа int из массива char
                 */
                s = atoi(buf.c_str());
                break;
            }
            clear_istdstream();
        }
    }

    /*
     * Для чтения символа типа char все еще проще
     */
    static void read(char &s, const std::string &msg = "")
    {
        while (true) {
            print_msg(msg);

            std::string buf;
            std::cin >> buf;

            /*
             * Все очень просто:
             *  Если считали всеголишь один символ
             *  значит это один символ :)
             */
            if (1 == buf.size()){
                s = buf.at(0); // записываем этот символ в s
                break; // выходим из цикла
            }
            clear_istdstream();
        }
    }

private:
    /*
     * Далее все функции не только статичные (static) но и inline
     * Этим мы говорим конпелятору, что хотели бы
     * чтобы он встроил код этих функций туда, где мы их вызываем
     * вместо вызова этих функций.
     * Это увеличит размер программы, но позволит сэкономить на вызове
     * этих функций.
     *
     * На самом деле, в лабораторке в этом смысла ровно 0,
     * никакого увеличения производительности никто не заметит.
     * Да и конпилятор может послать куда подальше, т. к.
     * 'inline' это лишь совет конпелятору.
     */

    /*
     * Очистка потока вывода в случае ошибок ввода
     */
    static inline void clear_istdstream()
    {
        /*
         * Восстанавливаем поток, если вдруг он в error state
         */
        std::cin.clear();

        /*
         * Отбрасываем максимальное кол-во символов
         * которое может содержать поток
         * до перевода строки (\n) включительно.
         *
         * P. S. Вместо этого мозно использовать конструкцию
         *
         *  cin.ignore(cin.rdbuf()->in_avail());
         *
         * rdbuf() дает нам доступ к буферу чтения, а его спрашиваем
         * сколько символов в нем доступно
         * (для чтения) при помощи in_avail()
         * и игнорируем именно это количество символов.
         */
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

    /*
     * Вывод сообщения в стандартный поток вывода
     */
    static inline void print_msg(const std::string &msg)
    {
        /*
         *  Если переданная строка -- пустая, то просто выходим из функции
         */
        if (msg.empty())
            return;
        /*
         * Иначе выводим её
         */
        std::cout << msg << "\n\t>";
        /*
         * И ждем пока система 100% выведет все это говно на экран
         */
        std::cout.flush();
    }
};

#endif // ANTIFOOL_H
