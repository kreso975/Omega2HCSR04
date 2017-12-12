#include <iostream>
#include <unistd.h>
#include <string>
#include <math.h>
#include <ctime>
#include "gpio.h"
#include <chrono>
#include <thread>

using namespace std::chrono;
typedef std::chrono::steady_clock Clock;

const uint8_t TRIG_PIN = 3;         // Associate pin 3 to TRIG
const uint8_t ECHO_PIN = 2;         // Associate pin 2 to ECHO


static void show_usage( std::string argv )
{
    std::cerr    << "Usage: <option> [<STRING> <STRING>]\n"
                 << "Options:\n"
                 << "\t-h, --help\t\tShow this help message\n"
                 << "\t-t <PIN> -e <PIN>\t\t -t = Trigger , -e = echo"
                 << std::endl;
}

void nsleep(long us)
{
    struct timespec wait;

    wait.tv_sec = us / (1000 * 1000);
    wait.tv_nsec = (us % (1000 * 1000)) * 1000;
    nanosleep(&wait, NULL);
}

int main( int argc, char* argv[] )
{
    if ( argc > 1 )
    {
        Gpio::initialize();

        std::string arg = argv[1];
        std::string arg3 = argv[3];

        if ( ( arg == "-h" ) || ( arg == "--help" ) )
            show_usage(argv[0]); // Show help

        else if ( ( arg == "-t" ) && ( arg3 == "-e" ) )
        {
            // HC-SR04

            // TODO use arg values for GPIO PINs
            Gpio::pinMode( TRIG_PIN, GPD_OUTPUT );
            Gpio::pinMode( ECHO_PIN, GPD_INPUT );

            while ( true )
            {
                Gpio::digitalWrite( TRIG_PIN, false );
                std::this_thread::sleep_for(seconds{1});        // Delay of 1 seconds

                Gpio::digitalWrite( TRIG_PIN, true );
                //nsleep(10000);                                  // I used this because it's more precise
                std::this_thread::sleep_for(microseconds{10});    // Sleep for 10 microseconds

                Gpio::digitalWrite( TRIG_PIN, false );

                // TODO, add break for value greater then 400cm as out of range here
                // Max measurable length = 400cm ~ 23280 microseconds - 23280us
                microseconds maxDistance{23280};
                //|| Clock::now() >= maxDistance // needs a work on it
                while ( !Gpio::digitalRead(ECHO_PIN) ) {}      // Check whether the ECHO is LOW
                Clock::time_point pulseStart = Clock::now();    // Mark pulseStart

                while ( Gpio::digitalRead(ECHO_PIN) )  {}       // Check whether the ECHO is HIGH
                Clock::time_point pulseEnd = Clock::now();      // Mark pulseEnd

                auto timeDiff = (pulseEnd - pulseStart);
                //auto distance = duration_cast<duration<float>>(timeDiff * 1000000 / 29.1 / 2 ).count();
                using distance = duration_cast<duration<float>;
                auto distance = (timeDiff * 1000000 / 29.1 / 2 ).count();

                // TODO: distance needs calibration - it measures linear less as length grows
                distance = roundf( distance * 100 ) / 100;        // Round to two decimal points

                if ( ( distance > 2 ) && ( distance < 400 ) )   // Check whether the distance is within range
                {
                    std::cout << "Delta pulse_end-pulse_start: \n"
                              << timeDiff.count() << " microseconds.\n"
                              << ((pulseEnd - pulseStart) / 29.1 / 2).count() << " cm. \n"
                              << duration_cast<duration<float>>(timeDiff).count() << " float\n"
                              << duration_cast<duration<float>>(timeDiff * 1000000 / 29.1 / 2).count() << " cm\n"
                              << distance << " cm rounded\n\n" << std::endl;
                }
                else
                {
                    std::cout << "Out Of Range \n" << std::endl;
                }

            }

        }
    }
    else
    {
        show_usage( argv[0] );
        return 0;
    }

    return 0;
}