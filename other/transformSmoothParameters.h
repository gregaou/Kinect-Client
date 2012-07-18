#ifndef TRANSFORMSMOOTHPARAMETERS_H
#define TRANSFORMSMOOTHPARAMETERS_H

class TransformSmoothParameters
{
	public:
		TransformSmoothParameters(float correction, float jitterRadius, float maxDeviationRadius, float prediction, float smoothing) :
			_correction(correction),
			_jitterRadius(jitterRadius),
			_maxDeviationRadius(maxDeviationRadius),
			_prediction(prediction),
			_smoothing(smoothing)
		{}

		/* Properties */
		float getCorrection(void) const							{ return _correction; }
		void setCorrection(float correction)					{ _correction = correction; }
		float getJitterRadius(void) const						{ return _jitterRadius; }
		void setJitterRadius(float jitterRadius)				{ _jitterRadius = jitterRadius; }
		float getMaxDeviationRadius(void) const					{ return _maxDeviationRadius; }
		void setMaxDeviationRadius(float maxDeviationRadius)	{ _maxDeviationRadius = maxDeviationRadius; }
		float getPrediction(void) const							{ return _prediction; }
		void setPrediction(float prediction)					{ _prediction = prediction; }
		float getSmoothing(void) const							{ return _smoothing; }
		void setSmoothing(float smoothing)						{ _smoothing = smoothing; }

		/* Methods */
		bool equals(const TransformSmoothParameters& smoothParameter)
		{
			return _correction == smoothParameter.getCorrection() &&
				   _jitterRadius == smoothParameter.getJitterRadius() &&
				   _maxDeviationRadius == smoothParameter.getMaxDeviationRadius() &&
				   _prediction == smoothParameter.getPrediction() &&
				   _smoothing == smoothParameter.getSmoothing();
		}

	protected:
		float _correction;
		float _jitterRadius;
		float _maxDeviationRadius;
		float _prediction;
		float _smoothing;
};

#endif
