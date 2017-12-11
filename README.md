# HC-SR04 for Omega2 - onion.io

Thanks to Patryk27 for simple Omega 2 GPIO management library https://github.com/Patryk27/Omega2-GPIO

I have successfully tested this app with Omega2 Plus and HC-SR04+ (version support 3.3v)

At the moment PIN's are hardcoded:
TRIGGER = PIN 3
ECHO = PIN 2

Install app using opkg. App will be placed in /bin

Use: Omega2HCSR04 -t 1 -e 2
