#include "utils.h"
#include "../garbage_collector/garbage_collector.h"


static size_t ft_strlen(char *str)
{
	size_t	i;
    
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strdup(const char *s) {
	char	*dest;
	int		i;
    
	dest = gar_col(ALLOC, (ft_strlen((char *)s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *itoa(int n)
{
    long num = n;
    int len = (n <= 0) ? 1 : 0;
    char *str;
	
    while (num) {
        len++;
        num /= 10;
    }
	
    str = gar_col(ALLOC, len + 1);
    if (!str)
        return NULL;
	
    str[len] = '\0';
	
    num = n;
    if (num == 0)
        str[0] = '0';
	
    if (num < 0) {
        str[0] = '-';
        num = -num;
    }
	
    while (num > 0) {
        str[--len] = (num % 10) + '0';
        num /= 10;
    }
	
    return str;
}
