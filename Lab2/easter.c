#include <stdio.h>

/*
 * This program calculates Easter day for any year between 1582 and 39999,
 *     based on an algorithm by Donald Knuth. 
 *     Input: file with one year per line.
 *     Output: file with a list of year and date pairs formatted 
 *         'YYYY - Month DD' 
 */

int calculate_Easter_date(int input_year);


/*  
 * main:
 *     This function calculates the Easter dates for a number of years in a 
 *     file. Needs input file and returns list as detailed above.
 */

int main(void)
{
    int current_year, data_file;
    int easter_date;

    
    while (1)
    {
        data_file = scanf("%d", &current_year);

        if (data_file == EOF)
            break; 

        easter_date = calculate_Easter_date(current_year);
        if (easter_date == 0)
        {
            fprintf(stderr, 
                    "Year %d out of range, easter date can't be calculated.\n",
                    current_year);
            continue;
        }
        if (easter_date > 0)
        {
            printf("%d - April %d \n", current_year, easter_date);
        }
        else
        {
            easter_date = - easter_date;
            printf("%d - March %d \n", current_year, easter_date);
        }
    } 

    return 0;
}

/*
 * calculate_Easter_date:
 *     This function calculates the date of Easter for a given year based on
 *     Donald Knuth's algorithm using the phases of the moon.
 *     
 *   Argument: Integer year, `input_year`, for which we want to calculate
 *        Easter date.
 *   Returns value: Integer for Easter date of argument input year. If 
 *       `easter_date` is the number of the month. If `easter_date` > 0, 
 *       Easter month is April. If `easter_date` < 0, Easter month is March.
 */

int calculate_Easter_date(int input_year)
{
    int century, golden_number, correction_orbit, skip_leap;
    int epact_moon, calendar_full_moon, day, easter_date;
    
    /* 
     * We need to check that the input year is after 1582 (when new leap 
     *    year rules were implemented) and 39999 so we can calculate the date
     *   for Easter
     */

    if (input_year < 1582 || input_year > 39999)
    {
        return 0;
    }
    
    /* 
     * We first need to calculate a few parameters for the given year: 
     *     `century`, `golden_number`, `correction_orbit`, `skip_leap`.
     * 
     * `golden_number` is the number of years that have passed since the start
     *     of the metonic cycle. The metonic cycle is the 19 year period that
     *     it takes for a day of the year to have the same moon phase. 
     * 
     * `correction_orbit` is a correction factor for the moon's orbit that
     *     accounts for the inexactitude of the "19 year" length of the
     *     metonic cycle.
     * 
     * `skip_leap` determines how many leap years have been skipped due to
     *     that if a leap year is a multiple of 100, it is only a leap year
     *     if it's also a multiple of 400.
     *  
     */

    century = input_year / 100 + 1;
    golden_number = input_year % 19 + 1;
    correction_orbit = (8 * century + 5) / 25 - 5;
    skip_leap = (3 * century) / 4 - 12;
    
    /*
     * We need to calculate the moon phase at the beginning of the year,
     *     `epact_moon`. Based on that, we can calculate when Easter 
     *     `easter_date` is, the first Sunday after the first full moon 
     *     after March 21st.
     */
    
    epact_moon = (11 * golden_number + 20 + correction_orbit - skip_leap) % 30;

    if ((epact_moon == 25 && golden_number > 11 ) || epact_moon == 24)
    {
        ++epact_moon;
    }

    calendar_full_moon = 44 - epact_moon;

    if (calendar_full_moon < 21)
    {
        calendar_full_moon = calendar_full_moon + 30;
    }
    day = (5 * input_year / 4) - skip_leap - 10;
    calendar_full_moon = calendar_full_moon + 7 - (
        (day + calendar_full_moon) % 7);
    
    /* 
     * The value of calendar_full_moon is the number of days since March 1,
     *  so for April we need to calculate the actual day of the month.
     */
    
    if (calendar_full_moon > 31)
    {
        easter_date = + (calendar_full_moon - 31) ;
    }
    else
    {
        easter_date = - calendar_full_moon;
    }

    return easter_date;
}