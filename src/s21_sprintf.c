#include "s21_string.h"

struct sprintf_specifier {
  int flg_minus;
  int flg_plus;
  int flg_space;
  int flg_hash;
  int flg_zero;
  int check_level;
  int width;
  int precision;
  int length;
  int incorrect_specifier;
  int zero_count;
  int space_count;
  int is_negative;
  int float_zero_count;
  int is_width;
  int is_precision;
  int is_zero;
  int precision_for_g;
  int width_from_arg;
  int precision_from_arg;
  char sign;
};

void memory_allocation(char **buffer, char ch, int *length);
void switch_to_specifier(struct sprintf_specifier specifier, char ch,
                         va_list args, char **str_from_arg, int length);
struct sprintf_specifier specifier_parsing(const char *attributes,
                                           int attributes_length, va_list args);
void parsing_flags(struct sprintf_specifier *specifier, char ch);
int s21_stoi(const char *attributes, int *i);
int s21_sprintf(char *str, const char *format, ...);
void s21_int_to_string(char **result, unsigned long int num, int radix,
                       int hash, char type);
void unsigned_logic(struct sprintf_specifier specifier, char **str_from_arg,
                    va_list args, char type);
void o_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 char type, unsigned long int number);
void c_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args);
void s_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args);
void d_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args);
void u_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 char type, unsigned long int number);
void x_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args, char type);
void p_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args, char type);
void efg_logic(struct sprintf_specifier specifier, char **str_from_arg,
               va_list args, char type);
void e_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 long int int_part, long int float_part, long int power,
                 char type);  //
void itos(char **arg, long int number);
void ftos(struct sprintf_specifier specifier, char **str_from_arg,
          long int int_part, long int float_part, long int power, int is_power,
          char type);
int check_negative(long int *number);
void check_flags(struct sprintf_specifier *specifier, int len);
void int_to_string(struct sprintf_specifier *specifier, char **str_number,
                   unsigned long int number, char type);
void final_argument_from_number(struct sprintf_specifier specifier,
                                char **str_from_arg, char *str_number);
int float_part_to_str(struct sprintf_specifier specifier, char **float_str,
                      long int float_part, long int power, int is_power,
                      char type);
void float_to_arg(struct sprintf_specifier *specifier, char **arg,
                  char *float_str, long int int_part, int float_len);
void power_logic(char **float_str, long int power, char type);
void reverse(char **result, int count);
long int how_much_power(long double *number);
long int convert_float_numbers(long double number, int precision);
void add_zeros_and_sign(struct sprintf_specifier specifier, char **str_number,
                        char *arg, char type);
void near_zero_g(struct sprintf_specifier specifier, char **str_from_arg,
                 long double f_f_part, int power, int temp_precision);
void above_one_g(struct sprintf_specifier specifier, char **str_from_arg,
                 long double f_f_part, long int f_int_part, int temp_precision,
                 char type);
void parce_length(struct sprintf_specifier *specifier, char length);

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char ch;
  int length = 0;
  for (int i = 0; (ch = format[i]) != '\0'; i++) {
    if (ch == '%' && format[i + 1] != '%') {
      char *attributes = s21_NULL;
      int attributes_length = 0;
      int j = i + 1;
      while (1) {
        memory_allocation(&attributes, ch, &attributes_length);
        ch = format[j];
        if (s21_strchr("cdieEfgGosuxXpn", ch) || ch == '\0') {
          char *str_from_arg = s21_NULL;
          memory_allocation(&attributes, ch, &attributes_length);
          struct sprintf_specifier specifier =
              specifier_parsing(attributes, attributes_length, args);
          if (specifier.incorrect_specifier) {
            str_from_arg = s21_malloc(s21_strlen(attributes) + 1);
            s21_strncpy(str_from_arg, attributes, s21_strlen(attributes) + 1);
          } else
            switch_to_specifier(specifier, ch, args, &str_from_arg, length);
          if (str_from_arg) {
            s21_strncat(str, str_from_arg, s21_strlen(str_from_arg));
            length += s21_strlen(str_from_arg);
            s21_add_null_ch(str, length);
            s21_free(str_from_arg);
          }
          break;
        }
        j++;
      }
      memory_allocation(&attributes, '\0', &attributes_length);
      i = j;
      s21_free(attributes);
    } else {
      str[length++] = ch;
      s21_add_null_ch(str, length);
      if (ch == '%') i++;
    }
  }
  s21_add_null_ch(str, length);
  va_end(args);
  return s21_strlen(str);
}

int s21_stoi(const char *attributes, int *i) {
  int stoi = 0, counter = 0;
  char *temp = NULL;
  while (1) {
    if (!(attributes[*i] >= 48 && attributes[*i] <= 57)) break;
    memory_allocation(&temp, attributes[(*i)++], &counter);
  }
  for (int j = 0; j < counter; j++)
    stoi += (temp[j] - 48) * pow(10, counter - j - 1);
  *i -= 1;
  s21_free(temp);
  return stoi;
}

void parsing_flags(struct sprintf_specifier *specifier, char ch) {
  switch (ch) {
    case '-':
      specifier->flg_minus = 1;
      break;
    case '+':
      specifier->flg_plus = 1;
      break;
    case ' ':
      specifier->flg_space = 1;
      break;
    case '#':
      specifier->flg_hash = 1;
      break;
    case '0':
      specifier->flg_zero = 1;
      break;
  }
}

void memory_allocation(char **buffer, char ch, int *length) {
  if (*length == 0)
    *buffer = s21_malloc(*length + 2);
  else
    *buffer = s21_realloc(*buffer, *length + 2);
  (*buffer)[(*length)++] = ch;
  (*buffer)[*length] = '\0';
}

void c_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args) {
  char ch = va_arg(args, int);
  if (!specifier.width) specifier.width = 1;
  (*str_from_arg) = s21_malloc(specifier.width + 1);
  s21_memset(*str_from_arg, 32, specifier.width);
  if (specifier.flg_minus)
    (*str_from_arg)[0] = ch;
  else
    (*str_from_arg)[specifier.width - 1] = ch;
  (*str_from_arg)[specifier.width] = '\0';
}

void s_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args) {
  char *arg = va_arg(args, char *);
  if ((specifier.precision == 0 && !specifier.is_precision) ||
      (specifier.precision > (int)s21_strlen(arg)))
    specifier.precision = s21_strlen(arg);
  if (!specifier.width || (specifier.width < specifier.precision))
    specifier.width = specifier.precision;
  char *blank_part = s21_NULL;
  if (specifier.width != specifier.precision) {
    blank_part = s21_malloc(specifier.width - specifier.precision + 1);
    s21_memset(blank_part, 32, specifier.width - specifier.precision);
    s21_add_null_ch(blank_part, specifier.width - specifier.precision);
  }
  *str_from_arg = s21_malloc(specifier.width + 1);
  (*str_from_arg)[0] = '\0';
  if (specifier.width > specifier.precision) {
    if (specifier.flg_minus) {
      s21_strncat(*str_from_arg, arg, specifier.precision);
      (*str_from_arg)[specifier.precision] = '\0';
      s21_strncat(*str_from_arg, blank_part,
                  specifier.width - specifier.precision);
    } else {
      s21_strncat(*str_from_arg, blank_part,
                  specifier.width - specifier.precision);
      (*str_from_arg)[specifier.width - specifier.precision] = '\0';
      s21_strncat(*str_from_arg, arg, specifier.precision);
    }
  } else
    s21_strncpy(*str_from_arg, arg, specifier.precision);
  (*str_from_arg)[specifier.width] = '\0';
  s21_free(blank_part);
}

void check_flags(struct sprintf_specifier *specifier, int len) {
  if (specifier->is_negative) {
    specifier->flg_plus = 1;
    specifier->sign = '-';
  }
  if (specifier->flg_space && specifier->sign == '+') {
    specifier->sign = ' ';
    specifier->flg_plus = 1;
  }
  if (specifier->precision < len)
    specifier->precision = len;
  else
    specifier->zero_count = specifier->precision - len;

  if (specifier->width > specifier->precision + specifier->flg_plus)
    specifier->space_count =
        specifier->width - specifier->precision - specifier->flg_plus;
  else
    specifier->width = specifier->precision + specifier->flg_plus;
  if (specifier->flg_zero) {
    specifier->zero_count += specifier->space_count;
    specifier->space_count = 0;
  }
}

void int_to_string(struct sprintf_specifier *specifier, char **str_number,
                   unsigned long int number, char type) {
  char *arg = s21_NULL;
  if (number == 0) specifier->is_zero = 1;
  if (specifier->is_zero && specifier->is_precision &&
      specifier->precision == 0 && s21_strchr("duxX", type))
    check_flags(specifier, 0);
  else {
    if (type == 'd' || type == 'f')
      itos(&arg, number);
    else if (type == 'u')
      s21_int_to_string(&arg, number, 10, specifier->flg_hash, type);
    else if (type == 'o')
      s21_int_to_string(&arg, number, 8, specifier->flg_hash, type);
    else if (s21_strchr("pxX", type))
      s21_int_to_string(&arg, number, 16, specifier->flg_hash, type);
    check_flags(specifier, s21_strlen(arg));
  }
  if (specifier->flg_plus && type == 'p') specifier->zero_count--;
  if (specifier->flg_zero && specifier->flg_hash && number != 0 &&
      s21_strchr("pxX", type))
    specifier->zero_count -= 2;
  if (specifier->width > specifier->precision && specifier->flg_hash &&
      number != 0 && s21_strchr("pxX", type)) {
    specifier->space_count -= 2;
    if (specifier->space_count < 0) specifier->space_count = 0;
  }
  add_zeros_and_sign(*specifier, str_number, arg, type);
  if ((specifier->flg_hash && s21_strchr("xX", type)) || type == 'p') {
    char *temp_string =
        s21_malloc(s21_strlen(*str_number) + 3 + specifier->flg_plus + 5);
    s21_add_null_ch(temp_string, 0);
    if (specifier->flg_plus && type == 'p') {
      temp_string[0] = specifier->sign;
      s21_add_null_ch(temp_string, 1);
    }
    if ((type == 'x' && number != 0) || type == 'p')
      s21_strncat(temp_string, "0x", 2);
    if (type == 'X' && number != 0) s21_strncat(temp_string, "0X", 2);
    s21_add_null_ch(temp_string, 2 + specifier->flg_plus);
    s21_strncat(temp_string, *str_number, s21_strlen(*str_number));
    (*str_number) = s21_realloc(*str_number, s21_strlen(temp_string) + 1);
    s21_strncpy(*str_number, temp_string, s21_strlen(temp_string));
    (*str_number)[s21_strlen(temp_string)] = '\0';
    s21_free(temp_string);
  }
  s21_free(arg);
}

void add_zeros_and_sign(struct sprintf_specifier specifier, char **str_number,
                        char *arg, char type) {
  int counter = 0;
  *str_number = s21_malloc(specifier.width - specifier.space_count + 1);
  if (specifier.flg_plus && type != 'p')
    (*str_number)[counter++] = specifier.sign;
  for (; counter < specifier.zero_count + specifier.flg_plus; counter++)
    (*str_number)[counter] = '0';
  (*str_number)[counter] = '\0';
  if (arg) {
    s21_strncat(*str_number, arg, s21_strlen(arg));
    (*str_number)[specifier.width - specifier.space_count] = '\0';
  }
}

void s21_int_to_string(char **result, unsigned long int num, int radix,
                       int hash, char type) {
  if (radix != 0) {
    int count = 0;
    char sign = 'a';
    if (type == 'X') sign = 'A';
    while (num != 0) {
      int remainder = num % radix;
      if (remainder < 10)
        memory_allocation(result, remainder + '0', &count);
      else
        memory_allocation(result, remainder - 10 + sign, &count);
      num /= radix;
    }
    if (*result) (*result)[count] = '\0';
    if (hash && radix == 8) memory_allocation(result, '0', &count);
    if (*result) (*result)[count] = '\0';
    reverse(result, count);
    if (num == 0 && count == 0) {
      memory_allocation(result, '0', &count);
    }
    if (*result) (*result)[count] = '\0';
  }
}

void reverse(char **result, int count) {
  for (int i = 0; i < count / 2; i++) {
    char tmp = (*result)[i];
    (*result)[i] = (*result)[count - i - 1];
    (*result)[count - i - 1] = tmp;
  }
}

void final_argument_from_number(struct sprintf_specifier specifier,
                                char **str_from_arg, char *str_number) {
  *str_from_arg =
      s21_malloc(specifier.space_count + s21_strlen(str_number) + 1);
  (*str_from_arg)[0] = '\0';
  if (specifier.flg_minus) {
    int counter = 0;
    s21_strncat(*str_from_arg, str_number, s21_strlen(str_number));
    (*str_from_arg)[s21_strlen(str_number)] = '\0';
    for (counter = s21_strlen(str_number); counter < specifier.width; counter++)
      (*str_from_arg)[counter] = ' ';
  } else {
    s21_memset(*str_from_arg, ' ', specifier.space_count);
    (*str_from_arg)[specifier.space_count] = '\0';
    s21_strncat(*str_from_arg, str_number, s21_strlen(str_number));
  }
  (*str_from_arg)[specifier.space_count + s21_strlen(str_number)] = '\0';
}

void d_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args) {
  long int number = va_arg(args, long int);
  if (specifier.length == 1)
    number = (short int)number;
  else if (specifier.length != 2)
    number = (int)number;
  specifier.is_negative += check_negative(&number);
  char *str_number = s21_NULL;
  int_to_string(&specifier, &str_number, number, 'd');
  final_argument_from_number(specifier, str_from_arg, str_number);
  s21_free(str_number);
}

void o_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 char type, unsigned long int number) {
  char *str_number = s21_NULL;
  if (specifier.is_precision) specifier.flg_zero = 0;
  int_to_string(&specifier, &str_number, number, type);
  final_argument_from_number(specifier, str_from_arg, str_number);
  s21_free(str_number);
}

void u_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 char type, unsigned long int number) {
  specifier.flg_hash = 0;
  char *str_number = s21_NULL;
  int_to_string(&specifier, &str_number, number, type);
  final_argument_from_number(specifier, str_from_arg, str_number);
  s21_free(str_number);
}

void unsigned_logic(struct sprintf_specifier specifier, char **str_from_arg,
                    va_list args, char type) {
  unsigned long int number = va_arg(args, unsigned long int);
  if (specifier.length == 1)
    number = (unsigned short int)number;
  else if (specifier.length != 2)
    number = (unsigned int)number;
  specifier.flg_plus = 0;
  specifier.flg_space = 0;
  if (type == 'u') u_specifier(specifier, str_from_arg, type, number);
  if (type == 'o' || type == 'x' || type == 'X')
    o_specifier(specifier, str_from_arg, type, number);
}

void p_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 va_list args, char type) {
  void *number = 0;
  number = va_arg(args, void *);
  specifier.flg_hash = 1;
  o_specifier(specifier, str_from_arg, type, (unsigned long int)number);
}

void itos(char **arg, long int number) {
  int length = 1;
  if (number) length = floor(log10(labs(number))) + 1;
  *arg = s21_malloc(length + 1);
  for (int i = 0; i < length; i++) {
    long int cur_number = number % 10;
    number = number / 10;
    (*arg)[length - i - 1] = cur_number + '0';
  }
  (*arg)[length] = '\0';
}

long int how_much_power(long double *number) {
  long int power = 0;
  if (*number >= 1.0)
    while (*number >= 10.0) {
      *number /= 10;
      power++;
    }
  else
    while (*number < 1.0 && *number != 0) {
      *number *= 10;
      power--;
    }
  return power;
}

long int convert_float_numbers(long double number, int precision) {
  number = roundl(number * powl(10, precision));
  return (long int)number;
}

void efg_logic(struct sprintf_specifier specifier, char **str_from_arg,
               va_list args, char type) {
  int temp_precision = specifier.precision;
  if ((type == 'g' || type == 'G') && specifier.precision == 0 &&
      specifier.is_precision == 1)
    specifier.precision = 1;
  if (!specifier.precision && !specifier.is_precision) specifier.precision = 6;
  long double f_f_part = 0, number = 0;
  if (specifier.length != 3) {
    number = (double)number;
    number = va_arg(args, double);
  } else
    number = va_arg(args, long double);
  if (number < 0) {
    specifier.is_negative = 1;
    number *= -1;
  }
  long int f_int_part = (long int)number;
  f_f_part = number - f_int_part;
  if (type == 'f')
    ftos(specifier, str_from_arg, f_int_part,
         convert_float_numbers(f_f_part, specifier.precision), 0, 0, type);
  else {
    long double e_f_part = 0;
    long int power = 0;
    power = how_much_power(&number);
    long int e_int_part = (long int)number;
    e_f_part = number - e_int_part;
    if (temp_precision == 0 && specifier.is_precision == 0 &&
        (type == 'g' || type == 'G'))
      specifier.precision_for_g = 0;
    if (specifier.is_precision && specifier.precision == 0 && e_f_part >= 0.5)
      e_int_part++;
    if (type == 'e' || type == 'E' || power < -4 ||
        power >= specifier.precision) {
      if (type == 'g' || type == 'G') specifier.precision--;
      e_specifier(specifier, str_from_arg, e_int_part,
                  convert_float_numbers(e_f_part, specifier.precision), power,
                  type);
    } else {
      if (f_int_part == 0 && f_f_part < 1 && f_f_part > 0)
        near_zero_g(specifier, str_from_arg, f_f_part, power, temp_precision);
      else
        above_one_g(specifier, str_from_arg, f_f_part, f_int_part,
                    temp_precision, type);
    }
  }
}

void above_one_g(struct sprintf_specifier specifier, char **str_from_arg,
                 long double f_f_part, long int f_int_part, int temp_precision,
                 char type) {
  int length = 1;
  if (f_int_part) length = floor(log10(labs(f_int_part))) + 1;
  specifier.precision -= length;
  if (specifier.precision < 0) {
    if (temp_precision == 0 || length >= specifier.width)
      specifier.precision = 0;
    else
      specifier.precision = 1;
  }
  long int f_float_part = convert_float_numbers(f_f_part, specifier.precision);
  if (!f_f_part && temp_precision == 1) specifier.precision--;
  if (!f_f_part && temp_precision == 0 && specifier.is_precision)
    specifier.precision = 0;
  if (f_float_part && !specifier.is_precision) {
    while (1) {
      long int cur_number = f_float_part % 10;
      if (cur_number != 0) break;
      specifier.precision--;
      f_float_part /= 10;
    }
  }
  if (specifier.precision < 0) specifier.precision = 0;
  ftos(specifier, str_from_arg, f_int_part, f_float_part, 0, 0, type);
}

void near_zero_g(struct sprintf_specifier specifier, char **str_from_arg,
                 long double f_f_part, int power, int temp_precision) {
  long int f_float_part = convert_float_numbers(f_f_part, (power * -2) - 1);
  char *g_float_part = s21_NULL;
  char *str_number = s21_NULL;
  if (temp_precision == 0 && !specifier.flg_hash) specifier.precision = 0;
  if (specifier.precision > 0) specifier.precision--;
  char *arg = s21_malloc(3 - power + specifier.precision);
  itos(&g_float_part, f_float_part);
  reverse(&g_float_part, -power);
  s21_strncpy(arg, "0.", 3);
  s21_strncat(arg, g_float_part, 1 - power);
  for (int i = 0; i < specifier.precision; i++) s21_strncat(arg, "0", 2);
  check_flags(&specifier, s21_strlen(arg));
  add_zeros_and_sign(specifier, &str_number, arg, 'g');
  final_argument_from_number(specifier, str_from_arg, str_number);
  s21_free(g_float_part);
  s21_free(arg);
  s21_free(str_number);
}

void e_specifier(struct sprintf_specifier specifier, char **str_from_arg,
                 long int int_part, long int float_part, long int power,
                 char type) {
  char *str = s21_NULL;
  if ((type == 'g' || type == 'G') && float_part == 1) int_part++;
  ftos(specifier, &str, int_part, float_part, power, 1, type);
  if (specifier.width < (int)s21_strlen(str)) specifier.width = s21_strlen(str);
  final_argument_from_number(specifier, str_from_arg, str);
  s21_free(str);
}

int float_part_to_str(struct sprintf_specifier specifier, char **float_str,
                      long int float_part, long int power, int is_power,
                      char type) {
  char *temp = s21_NULL;
  int float_len = 0;
  if (float_part) {
    int temp_len = 0;
    itos(&temp, float_part);
    if (temp) temp_len = s21_strlen(temp);
    *float_str = s21_malloc(specifier.precision + temp_len + 2);
    (*float_str)[0] = '.';
    (*float_str)[1] = '\0';
    if (specifier.precision > temp_len) {
      for (int i = 1; i <= specifier.precision - temp_len + 1; i++) {
        if (i == (specifier.precision - temp_len + 1))
          (*float_str)[i] = '\0';
        else
          (*float_str)[i] = '0';
      }
    }
    if (temp) s21_strncat(*float_str, temp, temp_len);
    (*float_str)[specifier.precision + 1] = '\0';
    s21_free(temp);
  } else if ((specifier.precision && specifier.precision_for_g) ||
             specifier.flg_hash) {
    (*float_str) = s21_malloc(specifier.precision + 2);
    s21_memset(*float_str, '0', specifier.precision + 1);
    (*float_str)[0] = '.';
    (*float_str)[specifier.precision + 1] = '\0';
  }
  if (is_power) power_logic(float_str, power, type);
  if (*float_str) float_len = s21_strlen(*float_str);
  return float_len;
}

void power_logic(char **float_str, long int power, char type) {
  char *str_power = s21_NULL;
  char str_e[2] = "e";
  if (type == 'E' || type == 'G') str_e[0] = 'E';
  char str[10] = {0};
  s21_strncat(str, str_e, 2);
  if (power >= 0)
    s21_strncat(str, "+", 2);
  else
    s21_strncat(str, "-", 2);
  check_negative(&power);
  itos(&str_power, power);
  if (power < 10) s21_strncat(str, "0", 2);
  s21_strncat(str, str_power, s21_strlen(str_power));
  str[s21_strlen(str) + 1] = '\0';
  s21_free(str_power);
  if (*float_str) {
    int float_str_len = s21_strlen(*float_str) + s21_strlen(str);
    *float_str = s21_realloc(*float_str, float_str_len + 1);
    s21_strncat(*float_str, str, s21_strlen(str));
    (*float_str)[float_str_len] = '\0';
  } else {
    (*float_str) = s21_malloc(s21_strlen(str) + 2);
    (*float_str)[0] = '.';
    (*float_str)[1] = '\0';
    s21_strncat(*float_str, str, s21_strlen(str));
    (*float_str)[s21_strlen(str) + 2] = '\0';
  }
}

void float_to_arg(struct sprintf_specifier *specifier, char **arg,
                  char *float_str, long int int_part, int float_len) {
  char *int_str = s21_NULL;
  specifier->precision = 0;
  int temp_width = specifier->width;
  specifier->width = specifier->width - float_len;
  int_to_string(specifier, &int_str, int_part, 'f');
  *arg = s21_malloc(s21_strlen(int_str) + float_len +
                    specifier->float_zero_count + 2);
  (*arg)[0] = '\0';
  s21_strncpy(*arg, int_str, s21_strlen(int_str));
  (*arg)[s21_strlen(int_str)] = '\0';
  if (specifier->precision && float_len)
    s21_strncat(*arg, float_str, s21_strlen(float_str));
  (*arg)[s21_strlen(int_str) + float_len + specifier->float_zero_count + 1] =
      '\0';
  if (specifier->width < temp_width) specifier->width = temp_width;
  if (specifier->width < (int)s21_strlen(*arg))
    specifier->width = s21_strlen(*arg);
  specifier->space_count = specifier->width - s21_strlen(*arg);
  s21_free(int_str);
}

void ftos(struct sprintf_specifier specifier, char **str_from_arg,
          long int int_part, long int float_part, long int power, int is_power,
          char type) {
  char *float_str = s21_NULL;
  char *arg = s21_NULL;
  int float_len = float_part_to_str(specifier, &float_str, float_part, power,
                                    is_power, type);
  float_to_arg(&specifier, &arg, float_str, int_part, float_len);
  final_argument_from_number(specifier, str_from_arg, arg);
  s21_free(arg);
  s21_free(float_str);
}

void switch_to_specifier(struct sprintf_specifier specifier, char ch,
                         va_list args, char **str_from_arg, int length) {
  if (ch == 'c')
    c_specifier(specifier, str_from_arg, args);
  else if (ch == 'd' || ch == 'i')
    d_specifier(specifier, str_from_arg, args);
  else if (s21_strchr("feEgG", ch))
    efg_logic(specifier, str_from_arg, args, ch);
  else if (ch == 's')
    s_specifier(specifier, str_from_arg, args);
  else if (ch == 'n')
    *(int *)va_arg(args, void *) = (int)length;
  else if (s21_strchr("uoxX", ch))
    unsigned_logic(specifier, str_from_arg, args, ch);
  else if (ch == 'p')
    p_specifier(specifier, str_from_arg, args, ch);
}

struct sprintf_specifier specifier_parsing(const char *attributes,
                                           int attributes_length,
                                           va_list args) {
  struct sprintf_specifier specifier = {0};
  for (int i = 1; i < attributes_length - 1; i++) {
    if (s21_strchr("-+ #0", attributes[i])) {
      if (specifier.check_level)
        specifier.incorrect_specifier = 1;
      else
        parsing_flags(&specifier, attributes[i]);
    } else if ((attributes[i] >= '0' && attributes[i] <= '9') ||
               attributes[i] == '*') {
      if (specifier.check_level >= 1) specifier.incorrect_specifier = 1;
      if (attributes[i] != '*') {
        specifier.width = s21_stoi(attributes, &i);
      } else
        specifier.width_from_arg = 1;
      specifier.check_level = 1;
      specifier.is_width = 1;
    } else if (attributes[i] == '.') {
      if (specifier.check_level >= 2) specifier.incorrect_specifier = 2;
      if (attributes[i + 1] != '*') {
        i++;
        specifier.precision = s21_stoi(attributes, &i);
      } else {
        specifier.precision_from_arg = 1;
        i++;
      }
      specifier.check_level = 2;
      specifier.is_precision = 1;
    } else if (s21_strchr("hlL", attributes[i])) {
      if (specifier.check_level > 2) specifier.incorrect_specifier = 1;
      parce_length(&specifier, attributes[i]);
    } else
      specifier.incorrect_specifier = 1;
  }
  if (specifier.flg_plus) specifier.flg_space = 0;
  if (specifier.flg_minus) specifier.flg_zero = 0;
  if (!specifier.incorrect_specifier) {
    if (specifier.width_from_arg) specifier.width = va_arg(args, int);
    if (specifier.precision_from_arg) specifier.precision = va_arg(args, int);
  }
  specifier.sign = '+';
  specifier.precision_for_g = 1;
  return specifier;
}

int check_negative(long int *number) {
  int is_negative = 0;
  if (*number < 0) {
    is_negative = 1;
    *number = labs(*number);
  }
  return is_negative;
}

void parce_length(struct sprintf_specifier *specifier, char length) {
  if (length == 'h')
    specifier->length = 1;
  else if (length == 'l')
    specifier->length = 2;
  else if (length == 'L')
    specifier->length = 3;
  specifier->check_level = 3;
}