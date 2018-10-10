// Created by Domin568
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
int main (int argc, char ** argv)
{
        FILE * f = fopen (argv[1],"rb");
		if (f == NULL)
		{
			printf ("Nie mozna otworzyc pliku \n");
			return -1;
		}
		fseek (f,0,SEEK_END);
		int size = ftell(f);
		fseek (f,0,SEEK_SET);
		void * buf = mmap (NULL,0x1000,PROT_EXEC|PROT_READ|PROT_WRITE,MAP_PRIVATE,fileno(f),0);
		if (buf == MAP_FAILED)
		{
			printf("Cannot alloc memory \n");
			return -2;
		}

		printf ("\n\033[22;36mCode loaded at 0x%.08x (%d bytes)\033[0m\n\n",buf,size);
        void (*pshellcode)(void) = (void(*)(void))buf;
        pshellcode();
        return 0;
}
