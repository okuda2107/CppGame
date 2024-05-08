#include <stdlib.h>
#include <alut.h>

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "alut.lib")

int main (int argc, char **argv)
{
  ALuint helloBuffer, helloSource;
  alutInit (&argc, argv);
  helloBuffer = alutCreateBufferHelloWorld ();
  alGenSources (1, &helloSource);
  alSourcei (helloSource, AL_BUFFER, helloBuffer);
  alSourcePlay (helloSource);
  alutSleep (1);
  alutExit ();
  return EXIT_SUCCESS;
}
