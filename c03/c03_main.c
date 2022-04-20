#include <stdio.h>
#include <string.h>
#include "ex00/ft_strcmp.c"
#include "ex01/ft_strncmp.c"
#include "ex02/ft_strcat.c"
#include "ex03/ft_strncat.c"


int	main()
{
	//ex00
	printf("ex00\n");
	char ex00_s1[] = "hella world!";
	char ex00_s2[] = "hello world!";
	printf("s1 : %s\ns2 : %s\n", ex00_s1, ex00_s2);
	printf("strcmp : %d\nft_strcmp : %d\n\n\n", strcmp(ex00_s1,ex00_s2), ft_strcmp(ex00_s1, ex00_s2));

	//ex01
	printf("ex01\n");
	printf("s1 : %s\ns2 : %s\n", ex00_s1, ex00_s2);
	printf("strncmp, n=5 : %d\nstrncmp, n=8 : %d\n", strncmp(ex00_s1,ex00_s2, 5), strncmp(ex00_s1, ex00_s2, 8));
	printf("ft_strncmp, n=5 : %d\nft_strncmp, n=8 : %d\n\n\n", ft_strncmp(ex00_s1,ex00_s2, 5), ft_strncmp(ex00_s1, ex00_s2, 8));

	//ex02
	printf("ex02\n");
	char ex02_dest1[50] = "Hi my name is ";
	char ex02_src1[50] = "sanghwal!!";
	char ex02_dest2[50] = "Hi my name is ";
	char ex02_src2[50] = "sanghwal!!";
	printf("dest : %s\nsrc : %s\n", ex02_dest1, ex02_src1);
	printf("strcat : %s\nft_strcat : %s\n\n\n", strcat(ex02_dest1, ex02_src1), ft_strcat(ex02_dest2, ex02_src2));

//ex03
	printf("ex03\n");
	char ex03_dest1[50] = "Hi my name is ";
	char ex03_src1[50] = "sanghwal!!";
	char ex03_dest2[50] = "Hi my name is ";
	char ex03_src2[50] = "sanghwal!!";
	char ex03_dest3[50] = "Hi my name is ";
	char ex03_src3[50] = "sanghwal!!";
	char ex03_dest4[50] = "Hi my name is ";
	char ex03_src4[50] = "sanghwal!!";
	printf("dest : %s\nsrc : %s\n", ex03_dest1, ex03_src1);
	printf("strncat, n=5 : %s\nstrncat, n=8 : %s\n", strncat(ex03_dest1,ex03_src1, 5), strncat(ex03_dest2, ex03_src2, 8));
	printf("ft_strncat, n=5 : %s\nft_strncat, n=8 : %s\n\n\n", ft_strncat(ex03_dest3,ex03_src3, 5), ft_strncat(ex03_dest4, ex03_src4, 8));

}
