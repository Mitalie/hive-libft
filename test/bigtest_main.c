#include "ft_printf.h"
#include "utils.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define test(fmt, ...) \
do {                                                                                      \
	mock_write(STDOUT_FILENO);                                                            \
	int ft_ret = ft_printf(fmt, ##__VA_ARGS__);                                           \
	void *ft_out;                                                                         \
	size_t ft_len = unmock_write(STDOUT_FILENO, &ft_out);                                 \
	void *std_out;                                                                        \
	int std_ret = asprintf((char **)&std_out, fmt, ##__VA_ARGS__);                        \
	size_t std_len = std_ret;                                                             \
	total++;                                                                              \
	if (ft_ret == std_ret && ft_len == std_len && !memcmp(ft_out, std_out, ft_len))       \
	{                                                                                     \
		success++;                                                                        \
		/* printf("\e[32m ✓ printf(\"%s\", %s)\n\e[0m", fmt, #__VA_ARGS__); */            \
	}                                                                                     \
	else if (total - success == 51)                                                       \
		printf("\e[33mMore than 50 errors, not printing additional ones\n\e[0m");         \
	else if (total - success <= 50 )                                                      \
	{                                                                                     \
		printf("\e[31m ✗ printf(\"%s\", %s)\n\e[0m", fmt, #__VA_ARGS__);                  \
		if (ft_ret != std_ret)                                                            \
			printf("  \e[91mft returned %d, std returned %d\n\e[0m", ft_ret, std_ret);    \
		if (ft_len != std_len || memcmp(ft_out, std_out, ft_len))                         \
		{                                                                                 \
			printf("  \e[91mft wrote %zu bytes:\n\e[95m", ft_len);                        \
			fflush(stdout);                                                               \
			dump_buffer(ft_out, ft_len, 4);                                               \
			printf("  \e[91mstd wrote %zu bytes:\n\e[94m", std_len);                      \
			fflush(stdout);                                                               \
			dump_buffer(std_out, std_len, 4);                                             \
			printf("\e[0m");                                                              \
		}                                                                                 \
	}                                                                                     \
	free(ft_out);                                                                         \
	free(std_out);                                                                        \
	fflush(stdout);                                                                       \
} while (0)

const char *flags[] = {
	#include "gen/test_flags.inc"
};

int	main(void)
{
	char	fmt[13];
	char	widthstr[3];
	char	precstr[4];
	size_t	total;
	size_t	success;

	total = 0;
	success = 0;
	for (int width = 0; width < 12; width++)
	{
		if (total > 0)
			printf("%zu tests completed...\n", total);
		if (width == 0)
			strcpy(widthstr, "");
		else
			sprintf(widthstr, "%d", width);
		for (int prec = -2; prec < 12; prec++)
		{
			if (prec == -2)
				strcpy(precstr, "");
			else if (prec == -1)
				strcpy(precstr, ".");
			else
				sprintf(precstr, ".%d", prec);
			for (size_t flagidx = 0; flagidx < sizeof flags / sizeof flags[0]; flagidx++)
			{
				#pragma GCC diagnostic push
				#pragma GCC diagnostic ignored "-Wformat"
				#include "gen/test_calls.inc"
				#pragma GCC diagnostic pop
			}
		}
	}
	if (success == total)
		printf("\e[32m ✓ %zu out of %zu tests passed\n\e[0m", success, total);
	else
		printf("\e[31m ✗ %zu out of %zu tests passed\n\e[0m", success, total);
}
