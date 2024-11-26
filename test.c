// test %s

#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

#define TEST_CASE(description, format, ...)                                     \
    do {                                                                       \
        int ret_ft, ret_orig;                                                  \
        printf("\n=== %s ===\n", description);                                 \
        printf("Expected (printf): ");                                         \
        fflush(stdout);                                                        \
        ret_orig = printf(format, ##__VA_ARGS__);                              \
        printf(" | Return: %d\n", ret_orig);                                   \
        printf("Actual (ft_printf): ");                                        \
        fflush(stdout);                                                        \
        ret_ft = ft_printf(format, ##__VA_ARGS__);                             \
        printf(" | Return: %d\n", ret_ft);                                     \
        if (ret_ft != ret_orig) {                                              \
            printf("Mismatch in return values: Expected %d, Got %d\n",         \
                   ret_orig, ret_ft);                                          \
        }                                                                      \
        printf("======================================================\n");    \
    } while (0)

int main(void)
{
    // Test case 1: Simple zero
    TEST_CASE("Test 1: %u with 0", " %u ", 0);

    // Test case 2: %u with LONG_MIN
    TEST_CASE("Test 2: %u with LONG_MIN", " %u ", (unsigned int)LONG_MIN);

    // Test case 3: Multiple %u with various values
    TEST_CASE("Test 3: %u with INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42",
              " %u %u %u %u %u %u %u", 
              INT_MAX, 
              (unsigned int)INT_MIN, 
              (unsigned int)LONG_MAX, 
              (unsigned int)LONG_MIN, 
              (unsigned int)ULONG_MAX, // Explicit cast here
              0, 
              (unsigned int)-42);

    // Test case 4: %x with INT_MAX
    TEST_CASE("Test 4: %x with INT_MAX", " %x ", INT_MAX);

    // Test case 5: %x with 0
    TEST_CASE("Test 5: %x with 0", " %x ", 0);

    // Test case 6: %x with ULONG_MAX
    TEST_CASE("Test 6: %x with ULONG_MAX", " %x ", (unsigned int)ULONG_MAX);

    // Test case 7: %X with INT_MIN
    TEST_CASE("Test 7: %X with INT_MIN", " %X ", (unsigned int)INT_MIN);

    // Test case 8: %X with -42
    TEST_CASE("Test 8: %X with -42", " %X ", (unsigned int)-42);

    return 0;
}



/*
//test %X
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "ft_printf.h" // Ваш ft_printf

// Функция захвата вывода
int capture_output(char **buffer, int (*print_func)(void *), void *arg)
{
    FILE *temp_file = tmpfile(); // Временный файл для вывода
    if (!temp_file)
        return -1;

    // Перенаправляем stdout
    int saved_stdout = dup(fileno(stdout));
    if (dup2(fileno(temp_file), fileno(stdout)) < 0)
    {
        fclose(temp_file);
        return -1;
    }

    // Выполняем печать
    int ret_value = print_func(arg);

    // Возвращаем stdout обратно
    fflush(stdout);
    dup2(saved_stdout, fileno(stdout));
    close(saved_stdout);

    // Читаем вывод из временного файла
    fseek(temp_file, 0, SEEK_END);
    long size = ftell(temp_file);
    fseek(temp_file, 0, SEEK_SET);

    *buffer = malloc(size + 1);
    if (!*buffer)
    {
        fclose(temp_file);
        return -1;
    }

    fread(*buffer, 1, size, temp_file);
    (*buffer)[size] = '\0';

    fclose(temp_file);
    return ret_value;
}

// Функции для печати через printf для %X
int standard_print_X(void *arg)
{
    return printf("%X", *(unsigned int *)arg);
}

// Функции для печати через ft_printf для %X
int ft_print_X(void *arg)
{
    return ft_printf("%X", *(unsigned int *)arg);
}

// Функция для сравнения результатов
void compare_results(const char *label, unsigned int value, int (*std_print)(void *), int (*ft_print)(void *))
{
    char *printf_output = NULL;
    char *ft_printf_output = NULL;

    int printf_ret = capture_output(&printf_output, std_print, &value);
    int ft_printf_ret = capture_output(&ft_printf_output, ft_print, &value);

    // Выводим результаты
    printf("\nTest %-12s:\n", label);
    printf("  printf:    '%-20s' (return: %-3d)\n", printf_output ? printf_output : "(null)", printf_ret);
    printf("  ft_printf: '%-20s' (return: %-3d)\n", ft_printf_output ? ft_printf_output : "(null)", ft_printf_ret);

    if (printf_output && ft_printf_output &&
        strcmp(printf_output, ft_printf_output) == 0 &&
        printf_ret == ft_printf_ret)
        printf("  Result: ✅ Passed\n");
    else
        printf("  Result: ❌ Failed\n");

    free(printf_output);
    free(ft_printf_output);
}

int main(void)
{
    // Заголовок теста
    printf("===== Testing printf vs ft_printf (%%X) =====\n");

    // Тестовые значения
    unsigned int test_values[] = {
        0,
        1,
        15,
        16,
        17,
        UINT_MAX,
        123456,
        255
    };

    const char *test_labels[] = {
        "0", "1", "15", "16", "17", "UINT_MAX", "123456", "255"
    };

    // Запуск тестов для %X
    printf("\n--- Testing %%X ---\n");
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++)
        compare_results(test_labels[i], test_values[i], standard_print_X, ft_print_X);

    return 0;
}




//test %d and %i

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "ft_printf.h" // Ваш ft_printf

// Функция захвата вывода
int capture_output(char **buffer, int (*print_func)(void *), void *arg)
{
    FILE *temp_file = tmpfile(); // Временный файл для вывода
    if (!temp_file)
        return -1;

    // Перенаправляем stdout
    int saved_stdout = dup(fileno(stdout));
    if (dup2(fileno(temp_file), fileno(stdout)) < 0)
    {
        fclose(temp_file);
        return -1;
    }

    // Выполняем печать
    int ret_value = print_func(arg);

    // Возвращаем stdout обратно
    fflush(stdout);
    dup2(saved_stdout, fileno(stdout));
    close(saved_stdout);

    // Читаем вывод из временного файла
    fseek(temp_file, 0, SEEK_END);
    long size = ftell(temp_file);
    fseek(temp_file, 0, SEEK_SET);

    *buffer = malloc(size + 1);
    if (!*buffer)
    {
        fclose(temp_file);
        return -1;
    }

    fread(*buffer, 1, size, temp_file);
    (*buffer)[size] = '\0';

    fclose(temp_file);
    return ret_value;
}

// Функции для печати через printf для %d и %i
int standard_print_d(void *arg)
{
    return printf("%d", *(int *)arg);
}

int standard_print_i(void *arg)
{
    return printf("%i", *(int *)arg);
}

// Функции для печати через ft_printf для %d и %i
int ft_print_d(void *arg)
{
    return ft_printf("%d", *(int *)arg);
}

int ft_print_i(void *arg)
{
    return ft_printf("%i", *(int *)arg);
}

// Функция для сравнения результатов
void compare_results(const char *label, int value, int (*std_print)(void *), int (*ft_print)(void *))
{
    char *printf_output = NULL;
    char *ft_printf_output = NULL;

    int printf_ret = capture_output(&printf_output, std_print, &value);
    int ft_printf_ret = capture_output(&ft_printf_output, ft_print, &value);

    // Выводим результаты
    printf("\nTest %-12s:\n", label);
    printf("  printf:    '%-20s' (return: %-3d)\n", printf_output ? printf_output : "(null)", printf_ret);
    printf("  ft_printf: '%-20s' (return: %-3d)\n", ft_printf_output ? ft_printf_output : "(null)", ft_printf_ret);

    if (printf_output && ft_printf_output &&
        strcmp(printf_output, ft_printf_output) == 0 &&
        printf_ret == ft_printf_ret)
        printf("  Result: ✅ Passed\n");
    else
        printf("  Result: ❌ Failed\n");

    free(printf_output);
    free(ft_printf_output);
}

int main(void)
{
    // Заголовок теста
    printf("===== Testing printf vs ft_printf (%%d and %%i) =====\n");

    // Тестовые значения
    int test_values[] = {
        0,
        -1,
        1,
        INT_MIN,
        INT_MAX,
        42,
        -42,
        123456,
        -123456
    };

    const char *test_labels[] = {
        "0", "-1", "1", "INT_MIN", "INT_MAX", "42", "-42", "123456", "-123456"
    };

    // Запуск тестов для %d
    printf("\n--- Testing %%d ---\n");
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++)
        compare_results(test_labels[i], test_values[i], standard_print_d, ft_print_d);

    // Запуск тестов для %i
    printf("\n--- Testing %%i ---\n");
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++)
        compare_results(test_labels[i], test_values[i], standard_print_i, ft_print_i);

    return 0;
}



// test %p
#include <stdio.h>  // Для стандартного printf
#include <limits.h> // Для LONG_MIN, LONG_MAX и других
#include <string.h> // Для strcmp
#include <stdlib.h> // Для malloc/free
#include "ft_printf.h" // Ваш ft_printf

int capture_output(char **buffer, int (*print_func)(void *), void *arg)
{
    // Открываем временный файл
    FILE *temp_file = tmpfile();
    if (!temp_file)
        return -1;

    // Перенаправляем stdout
    int saved_stdout = dup(fileno(stdout));
    if (dup2(fileno(temp_file), fileno(stdout)) < 0)
    {
        fclose(temp_file);
        return -1;
    }

    // Выполняем функцию печати
    int ret_value = print_func(arg);

    // Возвращаем stdout
    fflush(stdout);
    dup2(saved_stdout, fileno(stdout));
    close(saved_stdout);

    // Читаем вывод из временного файла
    fseek(temp_file, 0, SEEK_END);
    long size = ftell(temp_file);
    fseek(temp_file, 0, SEEK_SET);

    *buffer = malloc(size + 1);
    if (!*buffer)
    {
        fclose(temp_file);
        return -1;
    }

    fread(*buffer, 1, size, temp_file);
    (*buffer)[size] = '\0';

    fclose(temp_file);
    return ret_value;
}


// Печать через printf
int standard_print(void *arg)
{
    return printf("%p", arg);
}

// Печать через ft_printf
int ft_print(void *arg)
{
    return ft_printf("%p", arg);
}

void compare_results(const char *label, void *arg)
{
    char *printf_output = NULL;
    char *ft_printf_output = NULL;

    int printf_ret = capture_output(&printf_output, standard_print, arg);
    int ft_printf_ret = capture_output(&ft_printf_output, ft_print, arg);

    printf("\nTest %s:\n", label);
    printf("  printf:    '%s' (return: %d)\n", printf_output ? printf_output : "(null)", printf_ret);
    printf("  ft_printf: '%s' (return: %d)\n", ft_printf_output ? ft_printf_output : "(null)", ft_printf_ret);

    if (printf_output && ft_printf_output &&
        strcmp(printf_output, ft_printf_output) == 0 &&
        printf_ret == ft_printf_ret)
        printf("  Result: ✅ Passed\n");
    else
        printf("  Result: ❌ Failed\n");

    free(printf_output);
    free(ft_printf_output);
}


int main(void)
{
    // Заголовок теста
    printf("===== Testing printf vs ft_printf =====\n");

    // Тестовые значения
    void *test_values[] = {
        (void *)-1,
        (void *)1,
        (void *)15,
        (void *)16,
        (void *)17,
        (void *)LONG_MIN,
        (void *)LONG_MAX,
        (void *)ULONG_MAX,
        (void *)0
    };

    const char *test_labels[] = {
        "-1", "1", "15", "16", "17", "LONG_MIN", "LONG_MAX", "ULONG_MAX", "0"
    };

    // Запуск тестов
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++)
        compare_results(test_labels[i], test_values[i]);

    return 0;
}
*/
