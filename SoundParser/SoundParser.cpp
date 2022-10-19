#include <iostream>
#include <cstdlib>
#include <math.h>

#define PI 3.14159265

static double sine ( int index, double frequency )
{
    return sin ( frequency * index );
}

static void draw ( double data[] )
{
    std::printf ( "\033[2J" );

    for ( int i = 0; i < 75; i++ )
    {
        std::printf ( "\033[%d;%dH%d", (i % 3) + 1, i + 1, i + 1 );

        #ifdef _DEBUG
        std::printf ( "%d %d %d\n", i % 3, i + 1, i );
        #endif

        int point = static_cast<int> ( data[i] * 9 );
        int step = (point > 0) ? -1 : 1;

        for (int i = point; i != step; i += step)
        {
            std::printf ( "\033[%d;%dH%s", (point + 14 - i) + 1, i, "█" );
        }
    }

    for ( int i = 0; i < 19; i++ )
    {
        std::printf ( "\033[%d;77H%d", (i + 5) + 1, 9 - i );
    }
}

int main ( int argv, char** argc )
{
    double data[75];

    for ( int index = 1; index < 76; index++ )
    {
        data[index-1] = sine ( index, PI * 2 * 2.0f / 75 );
    }

    draw ( data );

    return EXIT_SUCCESS;
}