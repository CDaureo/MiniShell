/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simgarci <simgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:32:37 by simgarci          #+#    #+#             */
/*   Updated: 2024/11/18 16:37:22 by simgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	selector(char *format, int *count, va_list args)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c' || *format == 'd' || *format == 'i')
				handle_char_or_ints(va_arg(args, int), format, count);
			else if (*format == 's')
				handle_string(va_arg(args, char *), count);
			else if (*format == 'p')
				handle_pointer(va_arg(args, void *), count);
			else if (*format == 'u' || *format == 'x' || *format == 'X')
				handle_unsigned(va_arg(args, unsigned int), format, count);
			else if (*format == '%')
				*count += write(1, "%", 1);
		}
		else
			*count += write(1, format, 1);
		format++;
	}
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start (args, format);
	selector((char *)format, &count, args);
	va_end(args);
	return (count);
}

//int main() 
//{
//    int count;
//	int count_original;

//	//Int test
//    count = ft_printf("Prueba 1 int (%d): %d\n", -150, -150);
//	count_original = printf("Prueba 2 int (%d): %d\n", -150, -150);
//    printf("Cantidad ft %d cantidad original %d.\n\n", count, count_original);

//    // Str test
//    count = ft_printf("Prueba 1 str (%s):\
//	 %s\n", "Soy una prueba", "Soy una prueba");
//	count_original = printf("Prueba 2 str (%s):\
//	 %s\n", "Soy una prueba", "Soy una prueba");
//    printf("Cantidad ft %d cantidad original %d.\n\n", count, count_original);

//    // Unsigned test
//    count = ft_printf("Prueba 1 unsigned(%u): %u\n", 123124124, 123124124);
//	count_original = printf("Prueba 2 unsigned(%u):\
// %u\n", 123124124, 123124124);
//    printf("Cantidad ft %d cantidad original %d.\n\n", count, count_original);

//    // Hex test
//    count = ft_printf("Prueba 1 hex (%X): %X\n", 123124124, 123124124);
//	count_original = printf("Prueba 2 hex (%X): %X\n", 123124124, 123124124);
//    printf("Cantidad ft %d cantidad original %d.\n\n", count, count_original);

//    count = ft_printf("Prueba 1 int (%p): %p\n", NULL, NULL);
//	count_original = printf("Prueba 2 int (%p): %p\n", NULL, NULL);
//    printf("Cantidad ft %d cantidad original %d.\n\n", count, count_original);

//    // Test with a regular pointer
//    int test_var = 42;
//    count = ft_printf("Prueba 1 (%p):\
//	 %p\n", (void*)&test_var, (void*)&test_var);
//	count_original = printf("Prueba 2 (%p):\
//	 %p\n", (void*)&test_var, (void*)&test_var);	
//    printf("Cantidad ft %d cantidad original %d.\n\n", count, count_original);

//    // Test with special characters
//    count = ft_printf("Testing Special Character 1: %c\n", '\n'); 
//    count_original = printf("Testing Special Character 2: %c\n", '\n');
//    printf("Printed %d characters.\n\n", count);

//    // Test with percent sign
//    count = ft_printf("Testing Percent Sign 1: %%\n");
//	count_original = printf("Testing Percent Sign 2: %%\n");	
//    printf("Cantidad ft %d cantidad original %d.\n\n", count, count_original);

//    return 0;
//}
