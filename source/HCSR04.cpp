#include <iostream>
#include <unistd.h>
#include <math.h>
#include "gpio.h"
#include <chrono>
#include <thread>

using namespace std::chrono;
typedef std::chrono::steady_clock Clock;

const uint8_t TRIG_PIN = 3;         // Associate pin 3 to TRIG
const uint8_t ECHO_PIN = 2;         // Associate pin 2 to ECHO

// Max measurable length = 400cm ~ 23280 microseconds
// Min measurable length = 2cm ~ 58 microseconds
// The speed of sound is 340 m/s or 1cm = 29 microseconds
microseconds maxDistance{23280};
microseconds minDistance{58};

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
            show_usage(argv[0]);                                // Show help

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
                //std::this_thread::sleep_for(microseconds{10});    // Sleep for 10 microseconds
                nsleep(10000);                                  // I use this because it's more precise


                Gpio::digitalWrite( TRIG_PIN, false );

                auto maxDistanceCheck = Clock::now();

                // Check whether the ECHO is LOW
                while ( !Gpio::digitalRead(ECHO_PIN) )
                {
                    if (Clock::now() - maxDistanceCheck >= maxDistance )
                    {
                        std::cout << "Out Of Range (max) \n" << std::endl;
                        return 0;
                    }

                }
                auto pulseStart = Clock::now();                 // Mark pulseStart

                while ( Gpio::digitalRead(ECHO_PIN) ) {}        // Check whether the ECHO is HIGH
                auto pulseEnd = Clock::now();                   // Mark pulseEnd

                // TODO: distance needs calibration - it measures linear less as length grows
                auto timeDiff = (pulseEnd - pulseStart);

                using fdistance = duration<float>;
                auto distance = duration_cast<fdistance>(timeDiff * 1e6 / 29.1 / 2 ).count();

                distance = roundf( distance * 100 ) / 100;      // Round to two decimal points

                // Check whether the distance is within range
                if ( ( distance > 2 ) && ( distance < 400 ) )
                {
                    std::cout << "Delta pulse_end-pulse_start: \n"
                              << timeDiff.count() << " microseconds.\n"
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