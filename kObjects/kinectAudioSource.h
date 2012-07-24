#ifndef KINECTAUDIOSOURCE_H
#define KINECTAUDIOSOURCE_H

#include "kObject.h"
#include "../other/kEventHandler.h"
#include "../other/beamAngleChangedEventArgs.h"
#include "../other/soundSourceAngleChangedEventArgs.h"

class KinectAudioSource : public KObject
{
	public:
		KinectAudioSource(int id = -1) :
			KObject("KinectAudioSource", id),
			_beamAngleChangedCb(0),
			_soundSourceAngleChangedCb(0)
		 {}

		/* Properties */
		bool getAutomaticGainControlEnabled(void) const							{ return (bool)getQuery<int>(__func__); }
		void setAutomaticGainControlEnabled(bool automaticGainControlEnabled)
		{
			int intValue = (int)automaticGainControlEnabled;
			setQuery<int>(__func__, intValue);
		}
		double getBeamAngle(void) const											{ return getQuery<double>(__func__); }
		BeamAngleMode getBeamAngleMode(void) const								{ return (BeamAngleMode)getQuery<int>(__func__); }
		void setBeamAngleMode(BeamAngleMode beamAngleMode)
		{
			int intValue = (int)beamAngleMode;
			setQuery<int>(__func__, intValue);
		}
		EchoCancellationMode getEchoCancellationMode(void) const				{ return (EchoCancellationMode)getQuery<int>(__func__); }
		void setEchoCancellationMode(EchoCancellationMode echoCancellationMode)
		{
			int intValue = (int)echoCancellationMode;
			setQuery<int>(__func__, intValue);
		}
		int getEchoCancellationSpeakerIndex(void) const							{ return getQuery<int>(__func__); }
		void setEchoCancellationSpeakerIndex(int echoCancellationSpeakerIndex)	{ setQuery<int>(__func__, echoCancellationSpeakerIndex); }
		double getManualBeamAngle(void) const									{ return getQuery<double>(__func__); }
		void setManualBeamAngle(double manualBeamAngle)							{ setQuery<double>(__func__, manualBeamAngle); }
		double getMaxBeamAngle(void) const										{ return getQuery<double>(__func__); }
		double getMaxSoundSourceAngle(void) const								{ return getQuery<double>(__func__); }
		double getMinBeamAngle(void) const										{ return getQuery<double>(__func__); }
		double getMinSoundSourceAngle(void) const								{ return getQuery<double>(__func__); }
		bool getNoiseSuppression(void) const									{ return (bool)getQuery<int>(__func__); }
		void setNoiseSuppression(bool noiseSuppression)
		{
			int intValue = (int)noiseSuppression;
			setQuery<int>(__func__, intValue);
		}
		double getSoundSourceAngle(void) const									{ return getQuery<double>(__func__); }
		double getSoundSourceAngleConfidence(void) const						{ return getQuery<double>(__func__); }

		/* Methods */
		void enable(void) const													{}

		/* Events */
		kEventHandler<BeamAngleChangedEventArgs&> beamAngleChangedCb(void) const				{ return _beamAngleChangedCb; }
		void setBeamAngleChangedCb(kEventHandler<BeamAngleChangedEventArgs&> cb)
		{
			processQuery(buildQuery("BeamAngleChanged"));
			_beamAngleChangedCb = cb;
		}
		kEventHandler<SoundSourceAngleChangedEventArgs&> soundSourceAngleChangedCb(void) const	{ return _soundSourceAngleChangedCb; }
		void setSoundSourceAngleChangedCb(kEventHandler<SoundSourceAngleChangedEventArgs&> cb)
		{
			processQuery(buildQuery("SoundSourceAngleChanged"));
			_soundSourceAngleChangedCb = cb;
		}

	protected:
		kEventHandler<BeamAngleChangedEventArgs&> _beamAngleChangedCb;
		kEventHandler<SoundSourceAngleChangedEventArgs&> _soundSourceAngleChangedCb;
};

#endif
