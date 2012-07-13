#ifndef SOUNDSOURCEANGLECHANGEDEVENTARGS_H
#define SOUNDSOURCEANGLECHANGEDEVENTARGS_H

class SoundSourceAngleChangedEventArgs
{
	public:
		SoundSourceAngleChangedEventArgs(double angle, double confidenceLevel) :
			_angle(angle),
			_confidenceLevel(confidenceLevel)
		{}

		/* Properties */
		double getAngle(void) const						{ return _angle; }
		double getConfidenceLevel(void) const			{ return _confidenceLevel; }
		void setConfidenceLevel(double confidenceLevel)	{ _confidenceLevel = confidenceLevel; }

	protected:
		double _angle;
		double _confidenceLevel;
};

#endif
