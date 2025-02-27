#include "s21_string.h"
#define MAX_WIDTH 4096
#define HEX 16
#define OCTAL 8
#define DECIMAL 10
#define UNKNOWN_SYSTEM 0

typedef struct {
  int str_offset;
  long double result;
  int e_mode;
  int sign;
  int sign_char;
  int e_sign;
} atof_ops;

typedef struct {
  int lenght;
  int width;
  int skip;
  int success_counter;
  int global_counter;
  int process;
  int format_len;
  int str_len;
} ops;

int s21_sscanf(const char *str, const char *format, ...);
int s21_parse_width(char *format, ops *options);
int s21_parse_format(char *str, char *format, va_list args);
int s21_parse_specifier(const char *format, char *str, va_list args,
                        ops *options);
int s21_parse_digits(int width, atof_ops *ops, char *str, long double *result);
int s21_atoi(char *str, va_list args, ops *options, int base);
int s21_atoc(const char *str, va_list args, ops *options);
int s21_atof(char *str, va_list args, ops *options);
int s21_atos(char *str, va_list args, ops *options);
int s21_atows(char *str, va_list args, ops *options);
int s21_aton(va_list args, const ops *options);
int s21_atou(char *str, va_list args, ops *options, int base, int ptr);
int s21_is_space(char ch);
int s21_is_digit(char ch);
int s21_is_hex(char ch);
int s21_sign(char ch, int *sign);
int s21_convert_hex(char ch);
void s21_calc_result(atof_ops *aops, long double left_nums,
                     long double right_nums, int power);
int s21_process_str(atof_ops *aops, char *str);

int s21_sscanf(const char *str, const char *format, ...) {
  setlocale(LC_ALL, "");
  setlocale(LC_NUMERIC, "en_US.UTF-8");
  char *str_tmp = s21_calloc(s21_strlen(str) + 1, sizeof(char));
  s21_strncpy(str_tmp, str, s21_strlen(str));
  s21_add_null_ch(str_tmp, s21_strlen(str));
  char *format_tmp = s21_calloc(s21_strlen(format) + 1, sizeof(char));
  s21_strncpy(format_tmp, format, s21_strlen(format));
  s21_add_null_ch(format_tmp, s21_strlen(format));
  va_list args;
  va_start(args, format);
  int result = s21_parse_format(str_tmp, format_tmp, args);
  va_end(args);
  s21_free(str_tmp);
  s21_free(format_tmp);
  return result;
}

int s21_parse_format(char *str, char *format, va_list args) {
  ops options = {0};
  options.format_len = s21_strlen(format);
  options.str_len = s21_strlen(str);
  int format_counter = 0, str_counter = 0;
  do {
    if (*format != '%' && !options.process && !options.skip) {
      while (*format != '%' && format_counter < options.format_len &&
             str_counter < options.str_len) {
        if (*format == *str) {
          options.global_counter++;
        }
        format++;
        format_counter++;
        str_counter++;
        str++;
      }
    } else if (*format == '%' && options.process) {
      options.process = 0;
      format++;
      format_counter++;
    } else {
      options.process = 1;
      format++;
      format_counter++;
      if (*format > 47 && *format <= 58) {
        int result = s21_parse_width(format, &options);
        for (int i = 0; i < result; i++) {
          format++;
          format_counter++;
        }
      }
      if (!options.width) options.width = MAX_WIDTH;
      int offset = s21_parse_specifier(format, str, args, &options);
      if (offset) {
        options.skip = 0, options.process = 0, options.lenght = 0;
        options.width = 0;
        format++;
        format_counter++;
      }
      for (int i = 0; i < offset; i++) {
        str_counter++;
        str++;
      }
      options.global_counter += offset;
    }
  } while (format_counter < options.format_len &&
           str_counter < options.str_len);
  return options.success_counter;
}

int s21_parse_width(char *format, ops *options) {
  int *numbers = 0;
  int counter = 0;
  int result = 0;
  while ((int)*format > 47 && (int)*format <= 58) {
    counter++;
    numbers = s21_realloc(numbers, sizeof(int) * counter);
    numbers[counter - 1] = (int)(*format) - 48;
    format++;
  }
  int power = counter - 1;
  for (int i = 0; i < counter; i++) {
    result += numbers[i] * powl(10, power);
    power--;
  }
  s21_free(numbers);
  options->width = result;
  return counter;
}

int s21_parse_specifier(const char *const format, char *str, va_list args,
                        ops *options) {
  int result = 0;
  if (*format == 'd')
    result = s21_atoi(str, args, options, DECIMAL);
  else if (*format == 'i')
    result = s21_atoi(str, args, options, UNKNOWN_SYSTEM);
  else if (*format == 'o')
    result = s21_atou(str, args, options, OCTAL, 0);
  else if (*format == 'u')
    result = s21_atou(str, args, options, DECIMAL, 0);
  else if (*format == 'p')
    result = s21_atou(str, args, options, HEX, 1);
  else if (*format == 'x' || *format == 'X')
    result = s21_atou(str, args, options, HEX, 0);
  else if (*format == 'f' || *format == 'g' || *format == 'G' ||
           *format == 'e' || *format == 'E')
    result = s21_atof(str, args, options);
  else if (*format == 'c')
    result = s21_atoc(str, args, options);
  else if (*format == 's' && !options->lenght)
    result = s21_atos(str, args, options);
  else if (*format == 's' && options->lenght)
    result = s21_atows(str, args, options);
  else if (*format == 'n')
    result = s21_aton(args, options);
  else if (*format == 'h')
    options->lenght = 1;
  else if (*format == 'l')
    options->lenght = 2;
  else if (*format == 'L')
    options->lenght = 3;
  else if (*format == '*')
    options->skip = 1;
  return result;
}

int s21_atoc(const char *str, va_list args, ops *options) {
  if (!options->skip) {
    if (!options->lenght) {
      *(char *)va_arg(args, void *) = *str;
    } else if (options->lenght == 2) {
      mbtowc((wchar_t *)va_arg(args, void *), str, 2);
    }
    options->success_counter += 1;
  }
  return 1;
}

int s21_aton(va_list args, const ops *options) {
  if (!options->skip) *(int *)va_arg(args, void *) = options->global_counter;
  return 1;
}

int s21_atof(char *str, va_list args, ops *options) {
  atof_ops aops = {0};
  if (s21_sign(*str, &aops.sign)) {
    str++;
    aops.sign_char = 1;
  }
  long double left_nums = 0, right_nums = 0, exp_nums = 0;
  int counter = s21_parse_digits(options->width, &aops, str, &left_nums);
  for (; counter > 0; counter--) str++;
  if (aops.str_offset >= options->width) {
    while (*str != 'E' && *str != '.' && *str != 'e') {
      aops.str_offset++;
      str++;
    }
  }
  if (*str == 'E' || *str == 'e') aops.e_mode = 1;
  str++;
  aops.str_offset++;
  aops.e_sign = 1;
  if (s21_sign(*str, &aops.e_sign)) {
    str++;
    aops.str_offset++;
  }
  counter = s21_parse_digits(options->width, &aops, str, &right_nums);
  s21_calc_result(&aops, left_nums, right_nums, counter);
  for (; counter > 0; counter--) str++;
  if (*str == 'E' || *str == 'e') {
    aops.e_mode = 1;
    str++;
    aops.str_offset++;
    if (s21_sign(*str, &aops.e_sign)) {
      str++;
      aops.str_offset++;
    }
    counter = s21_parse_digits(options->width, &aops, str, &exp_nums);
    for (; counter > 0; counter--) str++;
    s21_calc_result(&aops, aops.result, exp_nums, counter);
  }
  for (int i = 0; i < s21_process_str(&aops, str); i++) str++;
  aops.result *= aops.sign;
  if (!options->lenght && !options->skip)
    *(float *)va_arg(args, void *) = (float)aops.result;
  else if (options->lenght == 2 && !options->skip)
    *(double *)va_arg(args, void *) = (double)aops.result;
  else if (options->lenght == 3 && !options->skip)
    *(long double *)va_arg(args, void *) = aops.result;
  if (aops.sign_char) aops.str_offset++;
  if (!options->skip) options->success_counter += 1;
  return aops.str_offset;
}

int s21_atos(char *str, va_list args, ops *options) {
  int counter = 0;
  int str_len = (int)s21_strlen(str);
  if (str_len < (int)s21_strlen(str)) str_len = (int)s21_strlen(str) - str_len;
  char *new_str = s21_NULL;
  if (!options->skip) new_str = va_arg(args, char *);
  while (!s21_is_space(*str) && counter < str_len) {
    if (counter < options->width && !options->skip) {
      new_str[counter] = *str;
    }
    counter++;
    str++;
  }
  if (!options->skip) {
    new_str[counter] = '\0';
    options->success_counter += 1;
  }
  return counter;
}

int s21_atows(char *str, va_list args, ops *options) {
  int counter = 0;
  wchar_t *new_str;
  if (!options->skip) new_str = va_arg(args, wchar_t *);
  while (!s21_is_space(*str) && counter < (int)s21_strlen(str)) {
    if (counter < options->width && !options->skip) {
      mbtowc(&new_str[counter], &str[counter], 2);
    }
    counter++;
    str++;
  }
  if (!options->skip) options->success_counter += 1;
  return counter;
}

int s21_atou(char *str, va_list args, ops *options, int base, int ptr) {
  int sign = 0, sign_char = 0;
  if (s21_sign(*str, &sign)) {
    sign_char = 1;
    str++;
  }
  int *number_array = 0;
  int counter = 0;
  unsigned long result = 0;
  int base_symbols = 0;
  if ((base == HEX || base == OCTAL) && *str == '0') {
    base_symbols++;
    str++;
    if (base == HEX && (*str == 'x' || *str == 'X')) {
      base_symbols++;
      str++;
    }
  }
  while ((s21_is_digit(*str) || (s21_is_hex(*str) && base == HEX)) &&
         counter + base_symbols < options->width) {
    counter++;
    number_array = s21_realloc(number_array, sizeof(int) * counter);
    number_array[counter - 1] =
        s21_is_hex(*str) ? s21_convert_hex(*str) : (int)(*str) - 48;
    str++;
  }
  int power = counter - 1;
  for (int i = 0; i < counter; i++) {
    result += (long)(roundl(number_array[i] * powl(base, power)));
    power--;
  }
  s21_free(number_array);
  result = sign ? result * sign : result;
  if (!options->skip) {
    if (!options->lenght && !ptr)
      *(unsigned int *)va_arg(args, void *) = (unsigned int)result;
    else if (options->lenght == 1 && !ptr)
      *(unsigned short *)va_arg(args, void *) = (unsigned short)result;
    else if ((options->lenght == 2 || options->lenght == 3) && !ptr)
      *(unsigned long *)va_arg(args, void *) = result;
    else if (ptr)
      *(unsigned long *)va_arg(args, void *) = result;
    options->success_counter += 1;
  }
  counter += base_symbols;
  return counter + sign_char;
}

int s21_atoi(char *str, va_list args, ops *options, int base) {
  int sign = 0, sign_char = 0, base_symbols = 0;
  if (s21_sign(*str, &sign)) {
    sign_char = 1;
    str++;
  }
  if (base == UNKNOWN_SYSTEM && *str == '0') {
    str++;
    base_symbols++;
    if (*str == 'x' || *str == 'X') {
      base = HEX;
      str++;
      base_symbols++;
    } else if (s21_is_digit(*str)) {
      base = OCTAL;
    }
  } else {
    base = DECIMAL;
  }
  int *number_array = 0;
  int counter = 0;
  long result = 0;
  while ((s21_is_digit(*str) || (s21_is_hex(*str) && base == HEX)) &&
         counter + base_symbols < options->width) {
    counter++;
    number_array = s21_realloc(number_array, sizeof(int) * counter);
    number_array[counter - 1] =
        s21_is_hex(*str) ? s21_convert_hex(*str) : (int)(*str) - 48;
    str++;
  }
  int power = counter - 1;
  for (int i = 0; i < counter; i++) {
    result += (long)(round(number_array[i] * powl(base, power)));
    power--;
  }
  s21_free(number_array);
  result = sign ? result * sign : result;
  if (!options->skip) {
    if (!options->lenght)
      *(int *)va_arg(args, void *) = (int)result;
    else if (options->lenght == 1)
      *(short *)va_arg(args, void *) = (short)result;
    else if ((options->lenght == 2 || options->lenght == 3))
      *(long *)va_arg(args, void *) = result;
    options->success_counter += 1;
  }
  counter += base_symbols;
  return counter + sign_char;
}

int s21_is_space(char ch) {
  int result = 0;
  if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\f' || ch == '\x0B' ||
      ch == '\r') {
    result = 1;
  }
  return result;
}
int s21_is_digit(char ch) {
  int result = 0;
  if (ch > 47 && ch < 58) result = 1;
  return result;
}

int s21_is_hex(char ch) {
  int result = 0;
  if ((ch > 64 && ch < 71) || (ch > 96 && ch < 103) || ch == 88 || ch == 120)
    result = 1;
  return result;
}

int s21_sign(char ch, int *sign) {
  int result = 0;
  if (ch == '-') {
    *sign = -1;
    result = 1;
  } else if (ch == '+') {
    *sign = 1;
    result = 1;
  } else {
    *sign = 1;
  }
  return result;
}

int s21_convert_hex(char ch) {
  int result = 0;
  if (ch == 'a' || ch == 'A') {
    result = 10;
  } else if (ch == 'b' || ch == 'B') {
    result = 11;
  } else if (ch == 'c' || ch == 'C') {
    result = 12;
  } else if (ch == 'd' || ch == 'D') {
    result = 13;
  } else if (ch == 'e' || ch == 'E') {
    result = 14;
  } else if (ch == 'f' || ch == 'F') {
    result = 15;
  }
  return result;
}

void s21_calc_result(atof_ops *aops, long double left_nums,
                     long double right_nums, int power) {
  if (aops->e_mode) {
    if (aops->e_sign == 1) {
      aops->result = left_nums * powl(10, right_nums);
    } else {
      right_nums *= aops->e_sign;
      aops->result = left_nums * powl(10, right_nums);
    }
  } else {
    right_nums /= powl(10, power);
    aops->result = left_nums + right_nums;
  }
}

int s21_process_str(atof_ops *aops, char *str) {
  int counter = 0;
  while (s21_is_digit(*str)) {
    aops->str_offset++;
    str++;
    counter++;
  }
  if (aops->sign == -1) {
    aops->str_offset++;
    counter++;
    aops->result *= aops->sign;
  }
  return counter;
}

int s21_parse_digits(int width, atof_ops *ops, char *str, long double *result) {
  int *nums = 0;
  int counter = 0;
  while (s21_is_digit(*str) && ops->str_offset < width) {
    counter++;
    ops->str_offset++;
    nums = s21_realloc(nums, sizeof(int) * counter);
    nums[counter - 1] = (int)(*str) - 48;
    str++;
  }
  int power = counter - 1;
  for (int i = 0; i < counter; i++) {
    *result += roundl(nums[i] * powl(10, power));
    power--;
  }
  s21_free(nums);
  return counter;
}
