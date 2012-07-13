#ifndef BEAMANGLECHANGEDEVENTARGS_H
#define BEAMANGLECHANGEDEVENTARGS_H

class BeamAngleChangedEventArgs
{
	public:
		BeamAngleChangedEventArgs(double angle) :
			_angle(angle)
		{}

		/* Properties */
		double getAngle(void) const		{ return _angle; }
		void setAngle(double angle)		{ _angle = angle; }

	protected:
		double _angle;
};

#endif
