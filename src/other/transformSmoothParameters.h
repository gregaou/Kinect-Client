#ifndef TRANSFORMSMOOTHPARAMETERS_H
#define TRANSFORMSMOOTHPARAMETERS_H

/**
 * \file transformSmoothParameters.h
 * \brief C++ version of C# TransformSmoothParameters
 * \author Gaëtan Champarnaud
 *
 * Contains transform smoothing parameters.
 */

class TransformSmoothParameters
{
	public:
		/**
		 * \param correction The amount of correction, in the range [0.0, 1.0] inclusive
		 * \param jitterRadius The jitter-reduction radius (in meters)
		 * \param maxDeviationRadius The maximum radius (in meters) that filtered positions can deviate from raw data
		 * \param prediction The number of frames to predict into the future, which is a number >= 0
		 * \param smoothing The smoothing parameter, which is in the range [0.0, 1.0] inclusive
		 */
		TransformSmoothParameters(float correction = 0.5, float jitterRadius = 0.05, float maxDeviationRadius = 0.04, float prediction = 0.5, float smoothing = 0.5) :
			_correction(correction),
			_jitterRadius(jitterRadius),
			_maxDeviationRadius(maxDeviationRadius),
			_prediction(prediction),
			_smoothing(smoothing)
		{}

		/* Properties */
		/**
		 * \brief Gets the amount of correction, in the range [0.0, 1.0] inclusive.
		 * \return The JitterRadius of the TransformSmoothParameters
		 *
		 * A higher value corrects toward the raw data more quickly, a lower value corrects more slowly and appears smoother.
		 */
		float getCorrection(void) const							{ return _correction; }
		/**
		 * \brief Sets the amount of correction, in the range [0.0, 1.0] inclusive.
		 * \param correction The JitterRadius of the TransformSmoothParameters
		 *
		 * A higher value corrects toward the raw data more quickly, a lower value corrects more slowly and appears smoother.
		 */
		void setCorrection(float correction)					{ _correction = correction; }
		/**
		 * \brief Gets the jitter-reduction radius, in meters, which determines how aggressively to remove jitter from the raw data.
		 * \return The JitterRadius of the TransformSmoothParameters
		 *
		 * It determines how aggressively to remove jitter from the raw data. The jitter radius is a number >= 0. Any jitter beyond this radius is clamped to the jitter reduction radius.
		 */
		float getJitterRadius(void) const						{ return _jitterRadius; }
		/**
		 * \brief Sets the jitter-reduction radius, in meters, which determines how aggressively to remove jitter from the raw data.
		 * \param jitterRadius The JitterRadius of the TransformSmoothParameters
		 *
		 * It determines how aggressively to remove jitter from the raw data. The jitter radius is a number >= 0. Any jitter beyond this radius is clamped to the jitter reduction radius.
		 */
		void setJitterRadius(float jitterRadius)				{ _jitterRadius = jitterRadius; }
		/**
		 * \brief Gets the maximum radius (in meters) that filtered positions can deviate from raw data.
		 * \return The MaxDeviationRadius of the TransformSmoothParameters
		 *
		 * The maximum deviation value is >= 0. A filtered value that would exceed this radius is clamped at the maximum radius in the direction of the filtered value.
		 */
		float getMaxDeviationRadius(void) const					{ return _maxDeviationRadius; }
		/**
		 * \brief Sets the maximum radius (in meters) that filtered positions can deviate from raw data.
		 * \param maxDeviationRadius The MaxDeviationRadius of the TransformSmoothParameters
		 *
		 * The maximum deviation value is >= 0. A filtered value that would exceed this radius is clamped at the maximum radius in the direction of the filtered value.
		 */
		void setMaxDeviationRadius(float maxDeviationRadius)	{ _maxDeviationRadius = maxDeviationRadius; }
		/**
		 * \brief Gets the number of frames to predict into the future, which is a number >= 0.
		 * \return The Prediction of the TransformSmoothParameters
		 *
		 * A value greater than 0.5 will likely lead to overshoot when the data changes quickly; dampen the overshoot effect by using a smaller value of MaxDeviationRadius.
		 */
		float getPrediction(void) const							{ return _prediction; }
		/**
		 * \brief Sets the number of frames to predict into the future, which is a number >= 0.
		 * \param prediction The Prediction of the TransformSmoothParameters
		 *
		 * A value greater than 0.5 will likely lead to overshoot when the data changes quickly; dampen the overshoot effect by using a smaller value of MaxDeviationRadius.
		 */
		void setPrediction(float prediction)					{ _prediction = prediction; }
		/**
		 * \brief Gets the smoothing parameter, which is in the range [0.0, 1.0] inclusive.
		 * \return The Smoothing of the TransformSmoothParameters
		 *
		 * A higher value corresponds to more smoothing. Passing 0 causes the raw data to be returned. As the smoothing value is increased responsiveness to the raw data decreases; therefore, increased smoothing leads to increased latency.
		 */
		float getSmoothing(void) const							{ return _smoothing; }
		/**
		 * \brief Sets the smoothing parameter, which is in the range [0.0, 1.0] inclusive.
		 * \param smoothing The Smoothing of the TransformSmoothParameters
		 *
		 * A higher value corresponds to more smoothing. Passing 0 causes the raw data to be returned. As the smoothing value is increased responsiveness to the raw data decreases; therefore, increased smoothing leads to increased latency.
		 */
		void setSmoothing(float smoothing)						{ _smoothing = smoothing; }

		/* Methods */
		/**
		 * \brief Compares two TransformSmoothParameters to see if they contain the same data.
		 * \param smoothParameter The second TransformSmoothParameters
		 * \return \e true if the second TransformSmoothParameters contains the same data as this instance; otherwise, \e false.
		 */
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
