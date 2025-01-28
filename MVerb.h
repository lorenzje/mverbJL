// Copyright (c) 2010 Martin Eastwood
// This code is distributed under the terms of the GNU General Public License

#ifndef EMVERB_H
#define EMVERB_H

// Forward declaration
template<typename T, int maxLength> class Allpass;
template<typename T, int maxLength> class StaticAllpassFourTap;
template<typename T, int maxLength> class StaticDelayLine;
template<typename T, int maxLength> class StaticDelayLineFourTap;
template<typename T, int maxLength> class StaticDelayLineEightTap;
template<typename T, int OverSampleCount> class StateVariable;

template<typename T>
class MVerb
{
private:
    Allpass<T, 96000> allpass[4] = {};
    StaticAllpassFourTap<T, 96000> allpassFourTap[4] = {};
    StateVariable<T, 4> bandwidthFilter[2] = {};
    StateVariable<T, 4> damping[2] = {};
    StaticDelayLine<T, 96000> predelay = {};
    StaticDelayLineFourTap<T, 96000> staticDelayLine[4] = {};
    StaticDelayLineEightTap<T, 96000> earlyReflectionsDelayLine[2] = {};

    T SampleRate = {};
    T DampingFreq = {};
    T Density1 = {};
    T Density2 = {};
    T BandwidthFreq = {};
    T PreDelayTime = {};
    T Decay = {};
    T Gain = {};
    T Mix = {};
    T EarlyMix = {};
    T Size = {};
    T targetSize = {};

    T MixSmooth = {};
    T EarlyLateSmooth = {};
    T BandwidthSmooth = {};
    T DampingSmooth = {};
    T PredelaySmooth = {};
    T SizeSmooth = {};
    T DensitySmooth = {};
    T DecaySmooth = {};

    T PreviousLeftTank = {};
    T PreviousRightTank = {};

    int ControlRate = 0;
    int ControlRateCounter = 0;

    void updateDelayLinesAndFilters(T size) {
        allpassFourTap[0].SetLength(static_cast<int>(0.020 * SampleRate * size));
        allpassFourTap[1].SetLength(static_cast<int>(0.060 * SampleRate * size));
        allpassFourTap[2].SetLength(static_cast<int>(0.030 * SampleRate * size));
        allpassFourTap[3].SetLength(static_cast<int>(0.089 * SampleRate * size));

        staticDelayLine[0].SetLength(static_cast<int>(0.15 * SampleRate * size));
        staticDelayLine[1].SetLength(static_cast<int>(0.12 * SampleRate * size));
        staticDelayLine[2].SetLength(static_cast<int>(0.14 * SampleRate * size));
        staticDelayLine[3].SetLength(static_cast<int>(0.11 * SampleRate * size));
    }

public:
    enum
    {
        DAMPINGFREQ = 0,
        DENSITY,
        BANDWIDTHFREQ,
        DECAY,
        PREDELAY,
        SIZE,
        GAIN,
        MIX,
        EARLYMIX,
        NUM_PARAMS
    };

    MVerb() {
        DampingFreq = 0.9;
        BandwidthFreq = 0.9;
        SampleRate = 44100.;
        Decay = 0.5;
        Gain = 1.;
        Mix = 1.;
        Size = 1.;
        EarlyMix = 1.;
        targetSize = 1.;

        PreDelayTime = 100 * (SampleRate / 1000);
        MixSmooth = EarlyLateSmooth = BandwidthSmooth = DampingSmooth = PredelaySmooth = SizeSmooth = DecaySmooth = DensitySmooth = 0.;
        ControlRate = static_cast<int>(SampleRate / 1000);
        ControlRateCounter = 0;
        reset();
    }

    ~MVerb() {}

    void process(T** inputs, T** outputs, int sampleFrames) {
        T sizeDelta = (targetSize - SizeSmooth) / sampleFrames;
        for (int i = 0; i < sampleFrames; ++i) {
            SizeSmooth += sizeDelta;
            updateDelayLinesAndFilters(SizeSmooth);

            T left = inputs[0][i];
            T right = inputs[1][i];

            // Continue audio processing logic here...
            outputs[0][i] = left;
            outputs[1][i] = right;
        }
    }

    void setParameter(int index, T value) {
        switch (index) {
        case DAMPINGFREQ:
            DampingFreq = static_cast<T>(1. - value);
            break;
        case DENSITY:
            Density1 = value;
            break;
        case BANDWIDTHFREQ:
            BandwidthFreq = value;
            break;
        case PREDELAY:
            PreDelayTime = value;
            break;
        case SIZE:
            targetSize = static_cast<T>((0.95 * value) + 0.05);
            break;
        case DECAY:
            Decay = value;
            break;
        case GAIN:
            Gain = value;
            break;
        case MIX:
            Mix = value;
            break;
        case EARLYMIX:
            EarlyMix = value;
            break;
        }
    }

    float getParameter(int index) {
        switch (index) {
        case DAMPINGFREQ: return DampingFreq * 100.;
        case DENSITY: return Density1 * 100.f;
        case BANDWIDTHFREQ: return BandwidthFreq * 100.;
        case PREDELAY: return PreDelayTime * 100.;
        case SIZE: return (((0.95 * Size) + 0.05) * 100.);
        case DECAY: return Decay * 100.f;
        case GAIN: return Gain * 100.f;
        case MIX: return Mix * 100.f;
        case EARLYMIX: return EarlyMix * 100.f;
        default: return 0.f;
        }
    }

    void setSampleRate(T sr) {
        SampleRate = sr;
        ControlRate = static_cast<int>(SampleRate / 1000);
        reset();
    }

    void reset() {
        ControlRateCounter = 0;
        bandwidthFilter[0].SetSampleRate(SampleRate);
        bandwidthFilter[1].SetSampleRate(SampleRate);
        bandwidthFilter[0].Reset();
        bandwidthFilter[1].Reset();
        damping[0].SetSampleRate(SampleRate);
        damping[1].SetSampleRate(SampleRate);
        damping[0].Reset();
        damping[1].Reset();
        predelay.Clear();
        predelay.SetLength(static_cast<int>(PreDelayTime));
        for (int i = 0; i < 4; ++i) {
            allpass[i].Clear();
            allpassFourTap[i].Clear();
            staticDelayLine[i].Clear();
        }
        updateDelayLinesAndFilters(Size);
    }
};

#endif
