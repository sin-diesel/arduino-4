#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

constexpr int channelNum = 7;
constexpr unsigned long long pipeAddr = 0x1234567890LL;

struct Dir {
    enum Dirs : int {
	FORWARD = 0,
	BACKWARD = 1,
	RIGHT = 2,
	LEFT= 3,
	NO = 4, 
    };
};

inline void setup_radio(RF24 &rad) {
    rad.begin();
    rad.setChannel(channelNum); // Channel (from 0 to 127), 5 - freq 2,405 GHz (only 1 receiver on a single channel and up to 6 transmitters)
    rad.setDataRate     (RF24_1MBPS); // Speed (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS)
    rad.setPALevel      (RF24_PA_HIGH); // Transmitter power (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
}