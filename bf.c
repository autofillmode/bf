#include <stdio.h>
#include <stdlib.h>

#define MAX_PROG_LEN 65536 /* Maximum length of a program */
#define MEM_SIZE 30000     /* How many bytes of memory the program gets */

int
main (int argc, char *argv[])
{
  FILE *fp;
  int stack[MAX_PROG_LEN], stackp;
  unsigned char storage[MAX_PROG_LEN];
  unsigned char tape[MEM_SIZE];
  int codep, proglength;
  int datap;
  int c;

  /* Holds all square bracket pairs to jump between */
  int loops[MAX_PROG_LEN];

  stackp = 0;
  datap = 0;

  if (argc != 2)
    {
      printf ("USAGE: %s <source> \n", argv[0]);
      exit (EXIT_SUCCESS);
    }

  fp = fopen (argv[1], "r");

  if (!fp)
    {
      printf ("Error opening file %s", argv[1]);
      exit (EXIT_FAILURE);
    }

  proglength = fread (storage, 1, MAX_PROG_LEN, fp);
  fclose (fp);

  for (codep = 0; codep < proglength; codep++)
    {
      if (storage[codep] == '[')
        stack[stackp++] = codep;

      if (storage[codep] == ']')
        {
          if (stackp == 0)
            {
              fprintf (stderr, "byte %d: unmatched ']' !\n", codep);
              exit (EXIT_FAILURE);
            }
          else
            {
              --stackp;
              loops[codep] = stack[stackp]; /* save the ]... */
              loops[stack[stackp]] = codep; /* and then the corresponding [. */
            }
        }
    }

  if (stackp > 0)
    {
      fprintf (stderr, "byte %d: unmatched '[' !\n", stack[stackp--]);
      exit (EXIT_FAILURE);
    }

  for (codep = 0; codep < proglength; codep++)
    {
      switch (storage[codep])
        {
        case '>':
          datap++;
          break;
        case '<':
          datap--;
          break;
        case '+':
          tape[datap]++;
          break;
        case '-':
          tape[datap]--;
          break;
        case '.':
          putchar (tape[datap] == 10 ? '\n' : tape[datap]);
          fflush (stdout);
          break;
        case ',':
          if ((c = getchar ()) != EOF)
            tape[datap] = (c == '\n') ? 10 : c;
          break;
        case '[':
          if (tape[datap] == 0)
            codep = loops[codep];
          break;
        case ']':
          if (tape[datap] != 0)
            codep = loops[codep];
          break;
        }
    }
  return 0;
}