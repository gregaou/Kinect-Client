#ifndef KINECTAUDIOSOURCE_H
#define KINECTAUDIOSOURCE_H

/**
 * \file kinectAudioSource.h
 * \brief C++ version of C# KinectAudioSource
 * \author Gaëtan Champarnaud
 *
 * Captures Kinect audio and provides access to sound source localization.
 */

#include "kObject.h"
#include "../other/kEventHandler.h"
#include "../other/beamAngleChangedEventArgs.h"
#include "../other/soundSourceAngleChangedEventArgs.h"

class KinectAudioSource : public KObject
{
	public:
		/** \param id The sensor id (index in the sensors collection) */
		KinectAudioSource(int id = -1) :
			KObject("KinectAudioSource", id),
			_beamAngleChangedCb(0),
			_soundSourceAngleChangedCb(0)
		 {}

		/* Properties */
		/** \brief Gets a boolean value that determines whether the KinectAudio DMO performs automatic gain control.
		 *  \return The AutomaticGainControlEnabled of the KinectAudioSource */
		bool getAutomaticGainControlEnabled(void) const							{ return (bool)getQuery<int>(__func__); }
		/** \brief Sets a boolean value that determines whether the KinectAudio DMO performs automatic gain control.
		 *  \param automaticGainControlEnabled The AutomaticGainControlEnabled of the KinectAudioSource */
		void setAutomaticGainControlEnabled(bool automaticGainControlEnabled)
		{
			int intValue = (int)automaticGainControlEnabled;
			setQuery<int>(__func__, intValue);
		}
		/** \brief Gets the beam angle (in degrees), which is the direction the audio beam is pointing. The center value is zero, negative values are right of the Kinect device (left of user), and positive values are left of the Kinect device (right of user).
		 *  \return The BeamAngle of the KinectAudioSource */
		double getBeamAngle(void) const											{ return getQuery<double>(__func__); }
		/** \brief Gets the beam angle mode, which determines how the beam angle is determined.
		 *  \return The BeamAngleMode of the KinectAudioSource */
		BeamAngleMode getBeamAngleMode(void) const								{ return (BeamAngleMode)getQuery<int>(__func__); }
		/** \brief Sets the beam angle mode, which determines how the beam angle is determined.
		 *  \param beamAngleMode The BeamAngleMode of the KinectAudioSource */
		void setBeamAngleMode(BeamAngleMode beamAngleMode)
		{
			int intValue = (int)beamAngleMode;
			setQuery<int>(__func__, intValue);
		}
		/** \brief Gets the echo cancellation and suppression mode. The default value is None.
		 *  \return The EchoCancellationMode of the KinectAudioSource */
		EchoCancellationMode getEchoCancellationMode(void) const				{ return (EchoCancellationMode)getQuery<int>(__func__); }
		/** \brief Sets the echo cancellation and suppression mode. The default value is None.
		 *  \param echoCancellationMode The EchoCancellationMode of the KinectAudioSource */
		void setEchoCancellationMode(EchoCancellationMode echoCancellationMode)
		{
			int intValue = (int)echoCancellationMode;
			setQuery<int>(__func__, intValue);
		}
		/** \brief Gets the index of the speaker used to identify the sound produced, in order to perform echo cancellation.
		 *  \return The EchoCancellationSpeakerIndex of the KinectAudioSource */
		int getEchoCancellationSpeakerIndex(void) const							{ return getQuery<int>(__func__); }
		/** \brief Sets the index of the speaker used to identify the sound produced, in order to perform echo cancellation.
		 *  \param echoCancellationSpeakerIndex The EchoCancellationSpeakerIndex of the KinectAudioSource */
		void setEchoCancellationSpeakerIndex(int echoCancellationSpeakerIndex)	{ setQuery<int>(__func__, echoCancellationSpeakerIndex); }
		/** \brief Gets the beam angle manually by the user, which is the direction the audio beam is pointing.
		 *  \return The ManualBeamAngle of the KinectAudioSource */
		double getManualBeamAngle(void) const									{ return getQuery<double>(__func__); }
		/** \brief Sets the beam angle manually by the user, which is the direction the audio beam is pointing.
		 *  \param manualBeamAngle The ManualBeamAngle of the KinectAudioSource */
		void setManualBeamAngle(double manualBeamAngle)							{ setQuery<double>(__func__, manualBeamAngle); }
		/** \brief Gets the maximum allowable angle (in degrees) between the audio source and the Kinect.
		 *  \return The MaxBeamAngle of the KinectAudioSource */
		double getMaxBeamAngle(void) const										{ return getQuery<double>(__func__); }
		/** \brief Gets the maximum allowable angle (in degrees) between the audio source and the Kinect.
		 *  \return The MaxSoundSourceAngle of the KinectAudioSource */
		double getMaxSoundSourceAngle(void) const								{ return getQuery<double>(__func__); }
		/** \brief Gets the mimimum allowable angle (in degrees) between the audio source and the Kinect.
		 *  \return The MinBeamAngle of the KinectAudioSource */
		double getMinBeamAngle(void) const										{ return getQuery<double>(__func__); }
		/** \brief Gets the minimum allowable angle (in degrees) between the audio source and the Kinect.
		 *  \return The MinSoundSourceAngle of the KinectAudioSource */
		double getMinSoundSourceAngle(void) const								{ return getQuery<double>(__func__); }
		/** \brief Gets a Boolean value that determines whether the KinectAudio DMO performs noise suppression.
		 *  \return The NoiseSuppression of the KinectAudioSource */
		bool getNoiseSuppression(void) const									{ return (bool)getQuery<int>(__func__); }
		/** \brief Sets a Boolean value that determines whether the KinectAudio DMO performs noise suppression.
		 *  \param noiseSuppression The NoiseSuppression of the KinectAudioSource */
		void setNoiseSuppression(bool noiseSuppression)
		{
			int intValue = (int)noiseSuppression;
			setQuery<int>(__func__, intValue);
		}
		/** \brief Gets the audio source direction.
		 *  \return The SoundSourceAngle of the KinectAudioSource */
		double getSoundSourceAngle(void) const									{ return getQuery<double>(__func__); }
		/** \brief Gets the confidence associated with the audio source location estimate, which is a number ranging from 0.0 (no confidence) to 1.0 (total confidence).
		 *  \return The SoundSourceAngleConfidence of the KinectAudioSource */
		double getSoundSourceAngleConfidence(void) const						{ return getQuery<double>(__func__); }

		/* Methods */
		/** \brief Method for enabling the Kinect to stream out audio data. */
		void enable(void) const													{}

		/* Events */
		KEventHandler<BeamAngleChangedEventArgs&> beamAngleChangedCb(void) const				{ return _beamAngleChangedCb; }
		/** \brief Sets the callback that is called when the BeamAngle property changes, so that an application can be notified of the change.
		 *  \param cb The function to be called */
		void setBeamAngleChangedCb(KEventHandler<BeamAngleChangedEventArgs&> cb)
		{
			processQuery(buildQuery("BeamAngleChanged"));
			_beamAngleChangedCb = cb;
		}

		KEventHandler<SoundSourceAngleChangedEventArgs&> soundSourceAngleChangedCb(void) const	{ return _soundSourceAngleChangedCb; }
		/** \brief Sets the callback that is called when the SoundSourceAngle property changes, so that an application can be notified of the change.
		 *  \param cb The function to be called */
		void setSoundSourceAngleChangedCb(KEventHandler<SoundSourceAngleChangedEventArgs&> cb)
		{
			processQuery(buildQuery("SoundSourceAngleChanged"));
			_soundSourceAngleChangedCb = cb;
		}

	protected:
		KEventHandler<BeamAngleChangedEventArgs&> _beamAngleChangedCb;
		KEventHandler<SoundSourceAngleChangedEventArgs&> _soundSourceAngleChangedCb;
};

#endif
