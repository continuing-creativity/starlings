#pragma once

#include "daisy.h"

using namespace daisy;

namespace sig {
namespace libdaisy {
    class Board {
        public:
            System system;
            SdramHandle sdram;
            QSPIHandle qspi;
            AudioHandle audio;
            AdcHandle adc;
            DacHandle dac;
            UsbHandle usb;
            dsy_gpio userLED;
            float callbackRate;

            virtual void Init(size_t blockSize, float sampleRate) = 0;

            SaiHandle::Config::SampleRate sampleRateFromFloat(float sr) {
                SaiHandle::Config::SampleRate sai_sr;
                switch(int(sr)) {
                    case 8000:
                        sai_sr = SaiHandle::Config::SampleRate::SAI_8KHZ;
                        break;
                    case 16000:
                        sai_sr = SaiHandle::Config::SampleRate::SAI_16KHZ;
                        break;
                    case 32000:
                        sai_sr = SaiHandle::Config::SampleRate::SAI_32KHZ;
                        break;
                    case 48000:
                        sai_sr = SaiHandle::Config::SampleRate::SAI_48KHZ;
                        break;
                    case 96000:
                        sai_sr = SaiHandle::Config::SampleRate::SAI_96KHZ;
                        break;
                    default:
                        sai_sr = SaiHandle::Config::SampleRate::SAI_48KHZ;
                        break;
                }

                return sai_sr;
            }

            void SetAudioSampleRate(float sr) {
                SaiHandle::Config::SampleRate sai_sr = sampleRateFromFloat(sr);
                audio.SetSampleRate(sai_sr);
                callbackRate = audio.GetSampleRate() /
                    audio.GetConfig().blocksize;
            }

    };
};
};