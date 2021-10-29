
/*                     IZP project 1
*   @Name: pwcheck.c
*   @Author: Matous Cermak 
*   @Login:xcerma43
*   @subject: IZP
*   @Date 2021-10-28
*/

/*
needed libraries
    stdio
    stdlib
    stdbool
*/

//includes
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//definitions
#define MAX_LENGHT 101
#define MAX_ASCII_VALUE 129
#define MIN_ARGC 3
#define MAX_ARGC 4
#define MIN_LEVEL 1
#define MAX_LEVEL 4
#define MIN_PARAM 1
#define STATS_POSITION 4
#define MAX_GROUPS 4

//util functions
/*
measures length of string
@param measured string max 101 chars
@return int = number of characters in the string 
*/
int str_len(char in1[])
{
    int len = 0;
    for (int i = 0; in1[i] != '\0'; i++)

    {
        len++;
    }
    return len;
}
/*
compares two strings
@param char in1[101] 
@param char in2[101] 
@return bool=  true if the string are the same 
*/
bool compare_str(char in1[MAX_LENGHT], char in2[MAX_LENGHT])
{

    if (str_len(in1) == str_len(in2))
    {
        for (int i = 0; in1[i] != 0; i++)
        {
            if (in1[i] != in2[i])
                return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}
/*
desides if character is alpha 
@param char in = character to be judged 
@param bool alpha_case = 0 lower case /1 upper case 
@return bool
*/
bool is_alpha(char in, bool alpha_case)
{

    if (alpha_case)
    {
        return (in >= 'A' && in <= 'Z');
    }
    else
    {
        return (in >= 'a' && in <= 'z');
    }
}
/*
checks if a character is a number 
@param char in checked character 
@return bool 
*/
bool is_number(char in)
{

    return (in >= '0' && in <= '9');
}

/*
checks if a character is a special character 
@param char in checked character 
@return bool 
*/
bool is_special(char in)
{
    return ((in >= ' ' && in <= '/') || (in >= ':' && in <= '@') || (in >= '[' && in <= '`') || (in >= '{' && in <= '~'));
}

//check password functions

/*
checks if a string has at least one uppercase and lowercase letter  
@param char in[101] = checked string 
@return bool
*/
bool lv_1_check(char in[MAX_LENGHT])
{
    bool has_upper, has_lower;
    for (int i = 0; in[i] != '\0'; i++)
    {
        if (is_alpha(in[i], false))
        {
            has_lower = true;
            break;
        }
    }
    for (int i = 0; in[i] != '\0'; i++)
    {
        if (is_alpha(in[i], true))
        {
            has_upper = true;
            break;
        }
    }
    return (has_lower && has_upper);
}

/*checks if there are characters from groups: 
    a-z, A-Z 0-9 and special characters 
@Param char in[101]= checket string
@Param int need_groups= hom many groups it needs to contain 
    if param is higher than 4 4 is enough 
@return bool     
*/

bool lv_2_check(char in[MAX_LENGHT], int need_groups)
{
    int has_groups = 0;

    if (need_groups > MAX_GROUPS)
    {
        need_groups = MAX_GROUPS;
    }
    for (int i = 0; in[i] != '\0'; i++)
    {

        if (is_number(in[i]))
        {
            has_groups++;

            break;
        }
    }

    for (int i = 0; in[i] != '\0'; i++)
    {

        if (is_special(in[i]))
        {
            has_groups++;

            break;
        }
    }

    for (int i = 0; in[i] != '\0'; i++)
    {

        if (is_alpha(in[i], false))
        {
            has_groups++;

            break;
        }
    }
    for (int i = 0; in[i] != '\0'; i++)
    {

        if (is_alpha(in[i], true))
        {
            has_groups++;

            break;
        }
    }

    return (has_groups >= need_groups);
}
/*
checks for same consecautive characters in a string 
@param char in[101]= checked string 
@param int count_in = count for the characterst if eaqul return false   
@return bool
*/
bool lv_3_check(char in[MAX_LENGHT], int count_in)
{

    for (int i = 0; in[i] != '\0'; i++)
    {
        int seq = 1;
        for (int j = i; in[j] != '\0'; j++)
        {
            if (seq == count_in)
                return false;
            if (in[j] == in[j + 1])
            {
                seq++;
            }
            else
            {
                break;
            }
        }
    }
    return true;
}
/*
checks if there are any identical substrings in the submitted string 
@param char in[] = checked string 
@param int count_in= lenght of substrings 
@return bool 
*/
bool lv_4_check(char in[], int count_in)
{
    int seq = 0;
    for (int i = 0; in[i] != '\0'; i++)
    {
        if (seq >= count_in)
        {
            return false;
        }
        for (int j = i + 1; in[j] != '\0'; j++)
        {
            if (seq >= count_in)
            {
                return false;
            }
            if (in[i] == in[j])
            {

                for (int k = 0; k < count_in; k++)
                {
                    if ((j + k) > str_len(in))
                    {
                        seq = 0;
                        break;
                    }

                    if (in[j + k] != in[i + k])
                    {
                        seq = 0;
                        break;
                    }
                    else
                    {
                        seq++;
                    }
                }
            }
        }
    }

    return true;
}
/*
checks if given string passes all checks based on given level and parameter 
@param char str_in[] = checked string  
@param int level = level that the string needs to pass
@param int param =  parameter for the check functions 
@return bool 
*/

bool pw_check(char str_in[MAX_LENGHT], int level, int param)
{
    switch (level)
    {
    case 1:
        return lv_1_check(str_in);
        break;
    case 2:
        return (lv_1_check(str_in) && lv_2_check(str_in, param));
        break;
    case 3:
        return (lv_3_check(str_in, param) && lv_2_check(str_in, param) && lv_1_check(str_in));
        break;
    case 4:
        return (lv_1_check(str_in) && lv_2_check(str_in, param) && lv_3_check(str_in, param) && lv_4_check(str_in, param));
        break;
    default:
        fprintf(stderr, "fault in level parametre");
        return false;
        break;
    }
}

// data work function
/*
checks for the right amount of parameters and if they are the right value 
@param int argc = give argc from main() 
@param const char *argv[] = give argv from main()
@return bool  
*/
bool arg_check(int argc, char const *argv[])
{
    bool test = ((argc < MIN_ARGC || argc > MAX_ARGC));
    if (argc < MIN_ARGC || argc > MAX_ARGC)
    {
        fprintf(stderr, "wrong number of arguments");
        return false;
    }
    else
    {
        int level = atoi(argv[1]);
        if (!(level >= MIN_LEVEL && level <= MAX_LEVEL))
        {

            fprintf(stderr, "wrong level argument");
            return false;
        }
        else
        {
            int arg_in = atoi(argv[2]);
            if (arg_in < MIN_PARAM)
            {
                fprintf(stderr, "wrong parametre argument");
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}
        //functions for the statistic write 
/*
writes the statistic on stdout 
@param int min = minimum length from the passwords
@param float avg= average length of a password  
@param int nchats= unique characters in all passwords  
*/
void stats_write(int min, float avg, int nchars)
{
    printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", nchars, min, avg);
}

int main(int argc, char const *argv[])
{

    if (arg_check(argc, argv))
    {
        char str_in[MAX_LENGHT];
        int level = atoi(argv[1]);
        int param = atoi(argv[2]);
        //          variables for statistic
        int unique[MAX_ASCII_VALUE] = {0};
        int min = MAX_LENGHT;
        int sum = 0;
        int count = 0;

        while (fgets(str_in, MAX_LENGHT, stdin))
        {

            if (pw_check(str_in, level, param))
            {
                printf("%s", str_in);
            }

            //statistic
            if (argc == STATS_POSITION)
            {

                //----------------------------------------------------------
                for (int i = 0; str_in[i] != '\0'; i++)
                {
                    if (str_in[i] == '\n')
                        continue;

                    unique[(int)str_in[i]] = 1;
                }
                // min
                //---------------------------------------------------------
                int test = str_len(str_in);
                {
                    min = str_len(str_in) - 1;
                }
                //avrage
                //---------------------------------------------------------

                count++;
                sum += str_len(str_in) - 1;
            }
        }
        if (argc == STATS_POSITION)
        {

            // uniqe chars
            //----------------------------------------------------------
            int nchars = 0;
            for (int i = 0; i < MAX_ASCII_VALUE; i++)
            {
                nchars += unique[i];
            }
            //avrages
            //----------------------------------------------------------
            float avg = (float)sum / (float)count;

            stats_write(min, avg, nchars);
        }
    }

    else
    {
        return 1;
    }

    return 0;
}