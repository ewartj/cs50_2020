#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("Please enter name:\n");
    printf("Hello, %s\n.", name);
}