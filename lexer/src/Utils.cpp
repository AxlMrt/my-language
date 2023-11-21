#include "headers/Utils.h"

bool my_isspace(char ch)
{
  return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == '\f';
}

bool my_isdigit(char ch)
{
  return (ch >= '0' && ch <= '9');
}

void my_strcpy(char *dest, const char *src)
{
  while (*src != '\0')
  {
    *dest = *src;
    ++dest;
    ++src;
  }
  *dest = '\0';
}

bool my_isalpha(char ch)
{
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool my_isalnum(char ch)
{
  return my_isalpha(ch) || my_isdigit(ch);
}

int my_strncmp(const char *str1, const char *str2, int n)
{
  for (int i = 0; i < n; ++i)
  {
    if (str1[i] != str2[i])
      return str1[i] - str2[i];
    if (str1[i] == '\0')
      return 0;
  }

  return 0;
}
