/* main.c - main function file
* Copyright (C) 2014 Adrian Alonso <aalonso00@gmail.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with self library; if not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
* Boston, MA 02110-1301, USA.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>

int
main(int argc, char **argv)
{
	int fd, idx=0, lastEnter=0, counter=0;
	char *file = NULL;
	unsigned char buff[16];
	struct stat newFile;
	int lineNum = 0, len=0;

	if(argc != 2)
	{
		printf ("Usage: %s <file>\n", argv[0]);
		exit (1);
	}

	file = argv[1];

	fd = open(file, O_RDONLY);

	if(fd < 0)
	{
		printf ("Error");
		exit(1);
	}
	/* Print complete file content following od hex format */
	/* od -A x -t x1z -v file.dat */
	/* My function begins here -->> Gaby */
        if(fstat(fd,&newFile) < 0){ 
		exit(1); 
	}
	len = newFile.st_size;
	while(len >= 0)
	{
		lastEnter = 0;
		counter = 0;	
		read(fd,buff,16);
		printf("%06x ",lineNum); /*Print line number*/
		lineNum += 16;
		for(idx=0; idx<16; idx++){
			printf("%02x ",buff[idx]); /*Print HEX*/
			if(10 == buff[idx]){
				buff[idx]=46; /*Replace with -.-*/	
				lastEnter = 1;	
			}
			if(32 != buff[idx]){
				counter++;
			}
		}
		printf(">%s<\n",buff); /*Print string*/	
		for(idx=0; idx<16; idx++){
			buff[idx] = 32; /*Clean buff*/
		}
		len -= 16;
	}
	if(lastEnter){
		lineNum = lineNum -16 + counter;
		printf("%06x \n",lineNum);
	}
	close (fd);
	return 0;
}

