#include "AudioPA.hpp"
#include <iostream>

AudioPA::AudioPA() {
  if ((this->err = Pa_Initialize()) != paNoError)
    std::cout << "Error :" << Pa_GetErrorText(err) << std::endl;
  this->state = PA_OFF;
  this->inputParameters.device = Pa_GetDefaultInputDevice();
  this->inputParameters.channelCount = 2;
  this->inputParameters.sampleFormat = paFloat32;
  this->inputParameters.suggestedLatency =
      Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
  this->inputParameters.hostApiSpecificStreamInfo = NULL;
  this->outputParameters.device = Pa_GetDefaultOutputDevice();
  this->outputParameters.channelCount = 2;
  this->outputParameters.sampleFormat = paFloat32;
  this->outputParameters.suggestedLatency =
      Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
  this->outputParameters.hostApiSpecificStreamInfo = NULL;
  this->inputSamples = new float[SAMPLE_RATE * NUM_CHANNELS];
  this->outputSamples = NULL;
}

AudioPA::~AudioPA() {
  if ((this->err = Pa_IsStreamActive(this->stream)) == 1)
    Pa_CloseStream(this->stream);
  Pa_Terminate();
}

bool AudioPA::sendAudioFrames(float *data) {
  this->outputSamples = (SAMPLE *)data;
  return (true);
}

int AudioPA::callBackFunction(const void *&inputBuffer, void *&outputBuffer,
                              unsigned long &framesPerBuffer,
                              const PaStreamCallbackTimeInfo *&timeInfo,
                              PaStreamCallbackFlags &statusFlags) {
  const SAMPLE *rptr = (const SAMPLE *)inputBuffer;
  SAMPLE *wptr = this->inputSamples;

  if (inputBuffer == NULL) {
    for (unsigned int i = 0; i < framesPerBuffer; i++) {
      *wptr++ = 0;
      if (NUM_CHANNELS == 2)
        *wptr++ = 0;
    }
  } else {
    for (unsigned int i = 0; i < framesPerBuffer; i++) {
      *wptr++ = *rptr++;
      if (NUM_CHANNELS == 2)
        *wptr++ = *rptr++;
    }
  }
  rptr = this->outputSamples;
  wptr = (SAMPLE *)outputBuffer;
  if (this->outputSamples == NULL) {
    for (unsigned int i = 0; i < framesPerBuffer; i++) {
      *wptr++ = 0;
      if (NUM_CHANNELS == 2)
        *wptr++ = 0;
    }
  } else {
    for (unsigned int i = 0; i < framesPerBuffer; i++) {
      *wptr++ = *rptr++;
      if (NUM_CHANNELS == 2)
        *wptr++ = *rptr++;
    }
  }
  if (this->state == PA_ON)
    return paContinue;
  else
    return paComplete;
}

SAMPLE *AudioPA::getAudioFrames() { return (this->inputSamples); }

static int Pa_callBack(const void *inputBuffer, void *outputBuffer,
                       unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo *timeInfo,
                       PaStreamCallbackFlags statusFlags, void *userData) {
  AudioPA *audio = reinterpret_cast<AudioPA *>(userData);
  return audio->callBackFunction(inputBuffer, outputBuffer, framesPerBuffer,
                                 timeInfo, statusFlags);
}
bool AudioPA::startAudio() {
  Pa_OpenStream(&this->stream, &this->inputParameters, &this->outputParameters,
                SAMPLE_RATE, 240, paClipOff, Pa_callBack, this);
  Pa_StartStream(this->stream);
  this->state = PA_ON;
  return (true);
}

bool AudioPA::stopAudio() {
  this->state = PA_OFF;
  Pa_CloseStream(this->stream);
  return (true);
}
