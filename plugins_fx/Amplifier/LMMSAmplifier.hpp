#include "DistrhoPlugin.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class LMMSAmplifier : public Plugin
{
public:
    enum Parameters {
		kParameterVol,
		kParameterPan,
		kParameterLeft,
		kParameterRight,

        kParameterCount
    };
    
    enum Programs {
        kProgramDefault
    };
    
    LMMSAmplifier();

protected:
    // -------------------------------------------------------------------
    // Information

    const char* getLabel() const noexcept override
    {
        return "DVc LMMS Amplifier";
    }

    const char* getDescription() const override
    {
        return "";
    }

    const char* getMaker() const noexcept override
    {
        return "SatyrDiamond";
    }

    const char* getHomePage() const override
    {
        return "";
    }

    const char* getLicense() const noexcept override
    {
        return "GPL";
    }

    uint32_t getVersion() const noexcept override
    {
        return d_version(0, 1, 0);
    }

    int64_t getUniqueId() const noexcept override
    {
        return d_cconst('L', 'M', 'c', 'A');
    }

    // -------------------------------------------------------------------
    // Init

    void initAudioPort(bool input, uint32_t index, AudioPort& port) override;
    void initParameter(uint32_t index, Parameter& parameter) override;
    void initProgramName(uint32_t index, String& programName) override;

    // -------------------------------------------------------------------
    // Internal data

    float getParameterValue(uint32_t index) const override;
    void  setParameterValue(uint32_t index, float value) override;
    void  loadProgram(uint32_t index) override;

    // -------------------------------------------------------------------
    // Process

    void run(const float** inputs, float** outputs, uint32_t frames) override;

    // -------------------------------------------------------------------

private:
    /// Array of our plugin's parameters.
    float parameters[kParameterCount];

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LMMSAmplifier)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
