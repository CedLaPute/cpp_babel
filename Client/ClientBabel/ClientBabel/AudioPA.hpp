#ifndef AUDIOPA_HPP
#define AUDIOPA_HPP_

#include <portaudio.h>
typedef float SAMPLE;
#define SAMPLE_RATE (24000)
#define NUM_CHANNELS (2)

enum { PA_OFF = 0, PA_ON };

class AudioPA {
private:
  PaStreamParameters inputParameters;
  PaStreamParameters outputParameters;
  int err;
  int state;
  SAMPLE *inputSamples;
  SAMPLE *outputSamples;

public:
  int callBackFunction(const void *&, void *&, unsigned long &,
                       const PaStreamCallbackTimeInfo *&,
                       PaStreamCallbackFlags &);
  PaStream *stream;
  AudioPA();
  ~AudioPA();
  SAMPLE *getAudioFrames();
  bool sendAudioFrames(float *data);
  bool startAudio();
  bool stopAudio();
};

#endif /* AUDIOPA_HPP_ */
