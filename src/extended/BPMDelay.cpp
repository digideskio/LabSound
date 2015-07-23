
#include "LabSound/extended/BPMDelay.h"

#include "LabSound/core/AudioNodeInput.h"
#include "LabSound/core/AudioNodeOutput.h"
#include "LabSound/core/AudioProcessor.h"
#include "LabSound/extended/AudioContextLock.h"
#include "internal/AudioBus.h"

#include <iostream>
#include <vector>

using namespace WebCore;

namespace LabSound 
{
	int TempoSyncToIndex(TempoSync in)
	{
		switch(in)
		{
			case TS_32: return 0;
			case TS_16T: return 1;
			case TS_32D: return 2;
			case TS_16: return 3;
			case TS_8T: return 4;
			case TS_16D: return 5;
			case TS_8: return 6;
			case TS_4T: return 7;
			case TS_8D: return 8;
			case TS_4: return 9;
			case TS_2T: return 10;
			case TS_4D: return 11;
			case TS_2: return 12;
			case TS_2D: return 13;
			default: return 0;
		}
	}

    BPMDelay::BPMDelay(float sampleRate, float tempo) : WebCore::DelayNode(sampleRate, 8.0f), tempo(tempo)
    {
        setNodeType((AudioNode::NodeType) LabSound::NodeType::NodeTypeBPMDelay);

        //addInput(std::unique_ptr<AudioNodeInput>(new WebCore::AudioNodeInput(this)));
        //addOutput(std::unique_ptr<AudioNodeOutput>(new WebCore::AudioNodeOutput(this, 2)));

		times = 
		{
			1.f / 8.f,
			(1.f / 4.f) * 2.f / 3.f,
			(1.f / 8.f) * 3.f / 2.f,
			1.f / 4.f,
			(1.f / 2.f) * 2.f / 3.f, 
			(1.f / 4.f) * 3.f / 2.f,
			1.f / 2.f, 
			1.f * 2.f / 3.f,
			(1.f / 2.f) * 3.f / 2.f, 
			1.0f, 
			2.f * 2.f / 3.f, 
			1.f * 3.f / 2.f, 
			2.f, 
			3.f
		};

		SetDelayIndex(TempoSync::TS_8);

        //initialize();
    }
    
    BPMDelay::~BPMDelay()
    {
        //uninitialize();
    }

	void BPMDelay::SetDelayIndex(TempoSync value)
	{
		if (value >= TempoSync::TS_32 && value <= TempoSync::TS_2D)
		{
			noteDivision = TempoSyncToIndex(value);
			recomputeDelay(); 
		}
		else 
			throw std::invalid_argument("Delay index out of bounds");
	}


} // end namespace LabSound

