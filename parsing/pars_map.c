/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:58:53 by abdo              #+#    #+#             */
/*   Updated: 2025/08/13 10:08:58 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


int check_arg(char *s)
{
    char *str;
    str = ft_strrchr(s,'.');
    if (strcmp(str, ".cub") == 0) //should use our strcmp
        return 1;
    return -1;
}

char *read_line(char *s)
{
    char buf[10];
    int fd;
    int rbyt = 1;
    char *str = NULL;
    if (!s)
        return NULL;
    fd = open(s,O_RDONLY,640);
    if (fd == -1)
        return NULL;
    while (rbyt != 0)
    {
        rbyt = read(fd,buf, 10);
        if (rbyt  == 0)
            break;
        str = ft_strjoin(str, buf);
        ft_memset(buf,0,10);
    }
    close(fd);
    return str;
}
int ft_whitespace(int c)
{
    if (c == ' ' || c == '\n' || c == '\t')
        return 1;
    return 0;
}
int ft_identif(int c)
{
    if (c == 'S' || c == 'W' || c == 'N' || c == 'E' ||
        c == 'F' || c == 'C')
        return 1;
    return 0;
}
int iswhitespace(char *s)
{
    while (*s)
    {
       if(*s != ' ')
        return 0;
        s++;
    }
    return 1;
}

// int check_map_recursive(char *str, int count)
// {
//     if (count == 6)
//     {
//         while (*str && ft_whitespace(*str))
//             str++;
//         if (*str == '1')
//             return 1;
//         else
//             return 0;
//     }
//     while (*str && ft_whitespace(*str))
//         str++;
//     if (*str == '\0' || !ft_identif(*str))
//         return 0;
//     while (*str && *str != '\n')
//         str++;
//     return check_map_recursive(str, count + 1);
// }

// int check_map(char *s)
// {
//    char *str = read_line(s);
//     if (!str ||*str == '\0' )
//         return 0;
//     return check_map_recursive(str, 0);
// }

// int check_map(char *s)
// {
//     char *str;
//     int count = 0;
//     int line;
//     if (!*s)
//         return 0;
    
//     str = read_line(s);
//     if (*str)
//     {
//        while (*str && ft_whitespace(*str))
//             str++;
        
//         if (ft_identif(*str))
//         {
//             while (*str && *str != '\n')
//                 str++;
//             while (*str && ft_whitespace(*str)) str++; 
//             if (ft_identif(*str))
//             {
//                 while (*str && *str != '\n')
//                     str++;
//                 while (*str && ft_whitespace(*str)) str++;                           
//                 if (ft_identif(*str))
//                 {
//                     while (*str && *str != '\n')
//                         str++;
//                     while (*str && ft_whitespace(*str)) str++;
//                     if (ft_identif(*str))
//                     {
//                         while (*str && *str != '\n')
//                             str++;
//                         while (*str && ft_whitespace(*str)) str++;
//                         if (ft_identif(*str))
//                         {
//                             while (*str && *str != '\n')
//                                 str++;
//                             while (*str && ft_whitespace(*str)) str++;
//                             if (ft_identif(*str))
//                             {
//                                 while (*str && *str != '\n')
//                                 str++;
//                                 while (*str && ft_whitespace(*str)) str++;
//                                 printf("f : %c f1:%c\n",*str,*(str+1));
//                                 if(*str == '1')
//                                     return 1;
//                                 else
//                                     return 0;
//                             }
//                             else
//                                 return 0;
//                         }
//                         else
//                                 return 0;
//                     }
//                     else
//                                 return 0;   
//                 }
//                 else
//                                 return 0; 
//             }
            
//         }
//         else
//             return 0;
//     }
//     return 0;
//}

int is_valid(int c)
{
    if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
        return 1;
    return 0;
}
int check_inside_map(char *str)
{
    int i;
    i = 0;
    while (*str)
    {
        while (is_valid(*str) && *str != '\n')
            str++;
        if(*str != '\0' && *str != '\n' && !is_valid(*str))
            return 0;
        str++;
        if (*str == '\n')
        {
            while (*str && ft_whitespace(*str))
                str++;
            if (*str == '\0')
                return 1;
            return 0;
        }
        
    }
    return 1;
}
int check_map(char *s)
{
    int count = 0;
    char *str = ft_strdup(s);
    while(*str)
    {
        while (*str && ft_whitespace(*str))
            str++;
        if (*str == '\0' || !ft_identif(*str))
            return 0;
        
        while (*str && *str != '\n')
            str++;
        while (*str && ft_whitespace(*str))
            str++;
        count++;
        if (count == 6)
        {
            if(*str == '1' && check_inside_map(str))
                return 1;
            return 0;
        }
    }
    return (0);
}

int checkup_down(char *s)
{
    int i = 0;
    
    while (s[i])
    {
        if (s[i] != ' ' &&  s[i] != '1')
            return 0;
        i++;
    }
    return 1; 
}
int ft_side(char *s)
{
    int i =0;
    if (!s || !*s)
        return 0;
    while (s[i] == ' ')
        i++;
    if (s[i] != '1')
        return 0;
    while (s[i])
    {
        if(s[i + 1] != ' ' && s[i] != '1')
            return 1;
        i++;
    }
    return 0;
}
int check_side(char **str)
{
    int i = 1;
    int  j;
    while (str[i])
    {
        if (!ft_side(str[i]))
            return 0;
        i++;
    }
    return 1;
}
int find_one(char **map)
{
    int i;
    int j;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j] == ' ')
            j++;
        if(map[i][j] == '1')
            return i;
        i++;
    }
    return 0;
    
}

int ft_direction(int c)
{
    if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
        return 1;
    return 0;
}
int duplicatID(char **str)
{
    int i;
    int x;
    int y;
    int j;
    int count;
    char dir;
    i = 0;
    count  = 0;
    while (str[++i])
    {
        j = 0;
        while (str[i][++j])
        {
            if(ft_direction(str[i][j]))
            {
                count++;
                x = i; //position of player
                y = j;  //position of player
                dir = str[i][j]; // derection of player
            }
        }
    }
    if (count > 1)
        return 0;
    return 1;
}
int check_in_map(char **map)
{
    char **str;
    int n = 0;
    n = find_one(map);
    if(n == 0)
        return 0;
    str = map + n;
    int i = 0;
    if (!str || !*str)
        return 0;
    
    while (str[i] != NULL)
        i++;
    if (i > 0 && (!checkup_down(str[0]) || !checkup_down(str[i - 1])  || !check_side(str)))
        return 0;
    if (!duplicatID(str))
        return 0;
    return 1;        
}
int path_checker(char *s)
{
    int i = 3;
    int start = 0;
    char *path = NULL;
    int fd;
    while (s[i] == ' ')
        i++;
    start = i;
    if (s[i] == '\0')
        return 0;
    while (s[i] && s[i] != ' ')
            i++;
    path = ft_substr(s,start, i - start);
    fd = open(path,O_RDONLY);
    if (fd == -1)
        return 0;
   while (s[i] && s[i] == ' ')
            i++;
    if (s[i] != '\0')
        return 0;
    free(path);
    return 1;
}
int identif_checker(char *s1,char *s2)
{
    int i;
     
    i = 0;
    while (*s1 == ' ')
        s1++;
    
    if (*s1 == *s2)
    {
        if (ft_strncmp(s1, s2, 3))
            return 0;
        if (!path_checker(s1))
            return 0;
    }
    return 1;
}
int ft_atoichecker(char **s)
{
    int i;
    i = 0;
    int n;
    while (s[i])
    {
        n = ft_atoi(s[i]);
        if (n < 0 || n > 255)
            return 0;
        i++;
    }
    if (i != 3)
        return 0;
    return 1;
}
int check_range(char *s)
{
    int  i;
    int start;
    char **arr;
    char *range = NULL;
    i = 0;
    start = 0;
    while (s[i] && s[i] == ' ')
        i++;
    start = i;
    if (s[i] == '\0')
        return 0;
    while (s[i] && s[i] != ' ')
        i++;
    range = ft_substr(s,start, i - start);
    start = 0;
    
    while(range[start])
    {
        if (!ft_isdigit(range[start]) && range[start] != ',')
            return 0;
        start++;
    }
    arr = ft_split(range, ',');
    if (!ft_atoichecker(arr))
        return 0;
    while (s[i] && s[i] == ' ')
        i++;
    if(s[i] != '\0')
        return 0;
    free(range);
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
    return 1;
}
int check_singlid(char *s)
{
    while (*s && *s == ' ')
        s++;
    if(*s == 'F')
    {
        if(ft_strncmp(s,"F ", 2))
            return 0;
        if (!check_range(s+2))
            return 0;
    }
    if(*s == 'C')
    {
        if(ft_strncmp(s,"C ", 2))
            return 0;
        if (!check_range(s+2))
            return 0;
    }
   return 1;
}
char *ft_idchar(char c)
{
    if (c == 'S')
        return (ft_strdup("SO "));
    if (c == 'N')
        return (ft_strdup("NO "));
    if (c == 'W')
        return (ft_strdup("WE "));
    if (c == 'E')
        return (ft_strdup("EA "));
    return NULL;  
}

int ft_valid_id(char *str)
{
    int i;
    char *identif = NULL;
    i = 0;
    
    while (str[i] && str[i] == ' ')
        i++;
    //should check null terminator here
    if (ft_identif(str[i]))
    {
        
        if (str[i] == 'S' || str[i] == 'W' || str[i] == 'N' || str[i] == 'E')
        {
            identif = ft_idchar(str[i]);
            if (!identif_checker(str, identif))
            {
                free(identif);
                return 0;
            }
                
        }
        if (str[i] == 'F' || str[i] == 'C')
        {
            if(!check_singlid(str))
                return 0;
        }
    }
    if (identif)
        free(identif);
    return 1;
}
int main(int argc, char **argv)
{
    int fd;
    char *str;
    char  **map;
    if (argc != 2)
        return 1;
    if (check_arg(argv[1]) == -1)
    {
        printf("Error\n");
        return 1;
    }
    str = read_line(argv[1]);
    if (!check_map(str))
    {
        printf("Error: unexcepted in map\n");
        return 1;
    }
    map = ft_split(str, '\n');
    if (!map)
        return 1;
    for (int i = 0; map[i] != NULL; i++)
    {
        printf("%s\n", map[i]);
        if (!ft_valid_id(map[i]))
        {
            printf("Error: identifier");
            return 1;
        }
    }
        
    if (!check_in_map(map))
    {
        printf("issue inside map");
        return 1;
    }
    printf("seccess!");
    return 0;
}
