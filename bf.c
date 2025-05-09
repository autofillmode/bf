#include <stdio.h>
#include <stdlib.h>

/* global variables for a simpler stack */
long stack[255];
int stackp;

long pop (void);
long peek (void);
void push (long);

int
main (int argc, char *argv[])
{
  int c;
  FILE *fp;
  unsigned char *array, *dp;

  array = calloc (30000, sizeof (unsigned char));

  dp = array;
  stackp = 0;

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

  while ((c = fgetc (fp)) != EOF)
    {
      switch (c)
        {
        case '[':
          {
            if (*dp == 0)
              {
                int inside = 1;
                while (inside > 0 && (c = fgetc (fp) != EOF))
                  {
                    if (c == '[')
                      inside++;
                    else if (c == ']')
                      inside--;
                  }
              }
            else
              push (ftell (fp));
          }
          break;
        case ']':
          {
            if (*dp != 0)
              {
                fseek (fp, peek (), SEEK_SET);
              }
            else
              pop ();
          }
          break;
        case '>':
          dp++;
          break;
        case '<':
          dp--;
          break;
        case '+':
          (*dp)++;
          break;
        case '-':
          (*dp)--;
          break;
        case '.':
          putchar (*dp);
          break;
        case ',':
          *dp = getchar ();
          break;
        }
    }

  free (array);
  fclose (fp);

  return 0;
}

void
push (long value)
{
  if (stackp == 255)
    return;

  stack[stackp] = value;
  stackp++;
}

long
pop (void)
{
  if (stackp == 0)
    return -1;

  return stack[--stackp];
}

long
peek (void)
{
  if (stackp == 0)
    return -1;
  return stack[stackp - 1];
}