#include "koukaamtype.h"
#include "koukaamlibc.h"

//--------------------------------------------------------------------------
int kstrlen(char *s)
{
    u16_t l;

    for (l = 0; s[l] != '\0'; l++) ;
    return l;
}

//--------------------------------------------------------------------------
int kstrcmp(char *s1, char *s2)
{
    u16_t l;

    // compare strings
    for (l = 0; (s1[l] != '\0') && (s2[l] != '\0'); l++)
    {
      if (s1[l] != s2[l])
            return -1;
    }

    if (l == 0)
        return -1;

    // are both strings the same length? if not, return -1
    if ((s1[l] == '\0') && (s2[l] == '\0'))
        return 0;
    else
        return -1;
    
}

//--------------------------------------------------------------------------
int kstrcpy(char *s1, char *s2)
{
    u16_t l;

    for (l = 0; s2[l] != '\0'; l++)
        s1[l] = s2[l];
    s1[l] = '\0';
    return l;
}

//--------------------------------------------------------------------------
int kstrncpy(char *s1, char *s2, u16_t num)
{
    u16_t l;

    for (l = 0; s2[l] != '\0' && l < num; l++)
        s1[l] = s2[l];
    s1[l] = '\0';
    return l;
}

//--------------------------------------------------------------------------
int kstrcat(char *s1, char *s2)
{
    u16_t l;
    u16_t l2;

    for (l = 0; s1[l] != '\0'; l++) ;
    for (l2 = 0; s2[l2] != '\0'; l2++)
        s1[l + l2] = s2[l2];
    s1[l + l2] = '\0';
    return l + l2;
}

//--------------------------------------------------------------------------
int katoi(char *s)
{
    int num = 0, flag = 0;
    u16_t i;

    for (i = 0; i <= kstrlen(s); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            num = num * 10 + s[i] - '0';
        else if (s[0] == '-' && i == 0)
            flag = 1;
        else
            break;
    }
    if (flag == 1)
        num *= -1;

    return num;
}

//--------------------------------------------------------------------------
unsigned int katoui(char *s)
{
    unsigned int num = 0;
    u16_t i;

    for (i = 0; i <= kstrlen(s); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            num = num * 10 + s[i] - '0';
        else
            break;
    }

    return num;
}

//--------------------------------------------------------------------------
int ksprintui(char *str, u16_t u, u8_t b)
{
    char print_buf[8];
    char *s;
    u8_t t;

    s = print_buf + sizeof(print_buf) - 1;

    *s = '\0';

    if (!u)
    {
        kstrcpy(str, "0");
        return kstrlen(str);
    }

    while (u)
    {
        t = u % b;
        if (t >= 10)
            t += 'a' - '0' - 10;
        *--s = t + '0';
        u /= b;
    }

    kstrcpy(str, s);
    return kstrlen(str);
}

//--------------------------------------------------------------------------
// Convet HEX char string to unsigne dint
unsigned int katox(char *s)
{
    u16_t num = 0;
    u16_t i;

    for (i = 0; i <= kstrlen(s); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            num = num * 16 + s[i] - '0';
        else if (s[i] >= 'A' && s[i] <= 'Z')
            num = num * 16 + 10 + (s[i] - 'A');
        else if (s[i] >= 'a' && s[i] <= 'z')
            num = num * 16 + 10 + (s[i] - 'a');
        else
            break;
    }

    return num;

}

//--------------------------------------------------------------------------
