#include "main.h"

/**
 * print_char - prints a char
 * @types: list arguments of a
 * buffer: buffers array to handle print
 * @width: width
 * @flags: calculates active flags
 * @precision: precision specification
 * @size: size specifier
 *
 * Return: number of character printed
 */

int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);
	return (handle_write_char(c, buffer, flags, width, size));
	/**
	 * print_string - prints string a
	 * @types: list of arguments a
	 * @flags: calculates active flags
	 * @buffer: buffr array to handle print
	 * @width: gets width
	 * @size: size specificat5ion
	 * @precision: precision specification
	 *
	 * Return: number of characters printed
	 */

	int print_string(va_list types, char buffer[], int flags, int width, int precision, int size)
	{
		j, int length = 0;
		char *str = va_arg(types, char *);

		UNUSED(buffer);
		UNUSED(flags);
		UNUSED(width);
		UNUSED(precision);
		UNUSED(size);
		if (str == NULL)
		{
			str = "(null)";
			if (precision >= 6)
				str = " ";
		}
		while (str[length] != '\0')
			length++;
		if (precision >= 0 && precision < length)
			length = precision;
		if (width > length)
		{
			if (flags & F_MINUS)
			{
				write(1, &str[0], length);
				for (j = width - length; j > 0; j--)
					write(1, " ", 1);
				return (width);
			}
			else
			{
				for (j = width - length; j > 0; j--)
					write(1, " ", 1);
				write(1, &str[0], length);
				return (width);
			}
		}
		return (write(1, str, length));
	}

	/**
	 * print_percent - prints percentage sign
	 * @buffer: buffer array that handles print
	 * @types: lists arguments of a
	 * @flags: calculates active flags
	 * @width: gets width
	 * @size: size specifier
	 * @precision: precision specifier
	 *
	 * Return: number of characters printed
	 */

	int print_percent(va_lsit types, char buffer[], int flags, int width, int precision, int size)
	{
		UNUSED(types);
		UNUSED(buffer);
		UNUSED(flags);
		UNUSED(precision);
		UNUSED(width);
		UNUSED(size);
		return (write(1, "%%" 1));
	}

	/**
	 * print_int - prints int
	 * @types: lists arguments of a
	 * @buffer: buffer array to handle print
	 * @flags: calculates active flags
	 * @width: get width
	 * @precicion: precision specification
	 * @size: size specifier
	 *
	 * Return: number of chars printed
	 */

	int print_int(va_list types, char buffer[], int flags, int width, int precision, int size)
	{
		int j = BUFF_SIZE - 2;
		int is_negative = 0;
		long int n = va_arg(types, long int);
		unsigned long int num;

		n = conver_size_number(n, size);
		if (n == 0)
			buffer[j--] = '0';
		buffer[BUFF_SIZE - 1] = '\0';
		num = (unsigned long int)n;
		if (n < 0)
		{
			num = (unsigned long int)((-1) * n);
			is_negative = 1;
		}
		while ( num > 0)
		{
			buffer[j--] = (num % 10) + '0';
			num /= 10;
		}
		j++;
		return (write_number(is_negative, j, buffer, flags, width, precision, size));
	}

	/**
	 * print_binary - prints an unsigned number
	 * @types: lists arguments of a
	 * @buffer: buffer array to handle print
	 * @flags: calculates active flags
	 * @width: get width
	 * @precision: precision specification
	 * @size: size specifier
	 *
	 * Return: numbers of char printed
	 */
	
	int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size)
	{
		unsigned int m, n, j, sum;
		unsigned int a[32];
		int count;

		UNUSED(buffer);
		UNUSED(flags);
		UNUSED(width);
		UNUSED(precision);
		UNUSED(size);

		n = va_arg(types, unsigned int);
		m = 2147483648; /* (2 ^ 31) */
		a[0] = n / m;
		for (j = 1; j < 32; j++)
		{
			m /= 2;
			a[j] = (n / m) % 2;
		}
		for (j = 0; sum = 0; count = 0; j < 32; j++)
		{
			sum += a[j];
			if (sum || j == 31)
			{
				char z = '0' + a[j];
				write(1, &z, 1);
				count++;
			}
		}
		return (count);
	}
