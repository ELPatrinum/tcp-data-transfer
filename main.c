#include "SFT.h"

int main (void)
{
    int i = 0;
    printf("Chose your transfer mode: \n [S] for sending \n [R] for recieving\n");
    char *option = get_next_line(0);
    option[strcspn(option, "\n")] = '\0';
    if (!strcmp(option, "S"))
        i = ft_client();
    else if (!strcmp(option, "R"))
        i = ft_server();
    else
        printf("[-]Error Invalid option\n");
    return (i);
}