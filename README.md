# HC-SR04 for Omega2 - onion.io

Thanks to Patryk27 for simple Omega 2 GPIO management library https://github.com/Patryk27/Omega2-GPIO

I have successfully tested this app with Omega2 Plus and HC-SR04+ (version support 3.3v)

Current version needs some measure adjustment.

At the moment PIN's are hardcoded:

TRIGGER = PIN 3

ECHO = PIN 2

Install app using opkg. App will be placed in /bin

Use: Omega2HCSR04 -t 1 -e 2

Stop: ctrl + C

----------------------------------------------------------------------------
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
