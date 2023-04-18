#include "LMMSAmplifier.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

LMMSAmplifier::LMMSAmplifier()
    : Plugin(kParameterCount, 0, 0)
{
    loadProgram(0);
}

// -----------------------------------------------------------------------
// Init

void LMMSAmplifier::initAudioPort(bool input, uint32_t index, AudioPort& port)
{
    port.groupId = kPortGroupStereo;

    Plugin::initAudioPort(input, index, port);
}

void LMMSAmplifier::initParameter(uint32_t index, Parameter& parameter)
{
    parameter.hints      = kParameterIsAutomatable;
    parameter.ranges.min = 0.0f;
    parameter.ranges.max = 1.0f;

    switch (index)
    {
	case kParameterVol:
		parameter.name       = "Volume";
		parameter.symbol     = "volume";
		parameter.ranges.def = 1.0f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 2.0f;
		break;
	case kParameterPan:
		parameter.name       = "Pan";
		parameter.symbol     = "pan";
		parameter.ranges.def = 0.0f;
		parameter.ranges.min = -1.0f;
		parameter.ranges.max = 1.0f;
		break;
	case kParameterLeft:
		parameter.name       = "Left";
		parameter.symbol     = "left";
		parameter.ranges.def = 1.0f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 2.0f;
		break;
	case kParameterRight:
		parameter.name       = "Right";
		parameter.symbol     = "right";
		parameter.ranges.def = 1.0f;
		parameter.ranges.min = 0.0f;
		parameter.ranges.max = 2.0f;
		break;

    }
}

void LMMSAmplifier::initProgramName(uint32_t index, String& programName)
{
    switch(index)
    {
    case kProgramDefault:
        programName = "Default";
        break;
    }
}

// -----------------------------------------------------------------------
// Internal data

float LMMSAmplifier::getParameterValue(uint32_t index) const
{
    return parameters[index];
}

void LMMSAmplifier::setParameterValue(uint32_t index, float value)
{
    parameters[index] = value;
}

void LMMSAmplifier::loadProgram(uint32_t index)
{
    switch(index)
    {
    case kProgramDefault:
		parameters[kParameterVol] = 1.0f;
		parameters[kParameterPan] = 0.0f;
		parameters[kParameterLeft] = 1.0f;
		parameters[kParameterRight] = 1.0f;

        break;
    }
}
// -----------------------------------------------------------------------
// Process

void LMMSAmplifier::run(const float** inputs, float** outputs, uint32_t frames)
{
    float audioLeft, audioRight;
    // Calculate audio.
    for (uint32_t i=0; i<frames; ++i)
    {
        // For footEnv, later.
        audioLeft  = inputs[0][i];
        audioRight = inputs[1][i];

		audioLeft *= parameters[kParameterVol];
		audioRight *= parameters[kParameterVol];
		
		const float left1 = parameters[kParameterPan] <= 0
			? 1.0
			: 1.0 - parameters[kParameterPan];
		const float right1 = parameters[kParameterPan] >= 0
			? 1.0
			: 1.0 + parameters[kParameterPan];
		
		audioLeft *= left1;
		audioRight *= right1;
		
		audioLeft *= parameters[kParameterLeft];
		audioRight *= parameters[kParameterRight];

        outputs[0][i] = audioLeft;
        outputs[1][i] = audioRight;
    }
}

// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new LMMSAmplifier();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
