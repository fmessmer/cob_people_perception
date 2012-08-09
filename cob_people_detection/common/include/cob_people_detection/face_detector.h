/*!
*****************************************************************
* \file
*
* \note
* Copyright (c) 2012 \n
* Fraunhofer Institute for Manufacturing Engineering
* and Automation (IPA) \n\n
*
*****************************************************************
*
* \note
* Project name: Care-O-bot
* \note
* ROS stack name: cob_people_perception
* \note
* ROS package name: cob_people_detection
*
* \author
* Author: Richard Bormann
* \author
* Supervised by:
*
* \date Date of creation: 07.08.2012
*
* \brief
* functions for detecting a face within a color image (patch)
* current approach: haar detector on color image
*
*****************************************************************
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* - Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer. \n
* - Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution. \n
* - Neither the name of the Fraunhofer Institute for Manufacturing
* Engineering and Automation (IPA) nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission. \n
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License LGPL as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License LGPL for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License LGPL along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************/

#ifndef __FACE_DETECTOR_H__
#define __FACE_DETECTOR_H__

#ifdef __LINUX__
#else
	#include "cob_vision/cob_vision_ipa_utils/common/include/cob_vision_ipa_utils/MathUtils.h"
	#include "cob_vision/cob_sensor_fusion/common/include/cob_sensor_fusion/ColoredPointCloud.h"	// todo: necessary?
#endif

#include <opencv/ml.h>
#include <opencv/cv.h>

namespace ipa_PeopleDetector {

/// Interface to Calibrate Head of Care-O-bot 3.
/// Long description
class FaceDetector
{
public:

	/// Constructor.
	FaceDetector(void); ///< Constructor
	~FaceDetector(void); ///< Destructor

	/// Initialization function.
	/// Creates an instance of a range imaging sensor (i.e. SwissRanger SR-3000) and an instance of
	/// @param directory The directory for data files
	/// @return Return code
	virtual unsigned long init(std::string directory, double faces_increase_search_scale, int faces_drop_groups, int faces_min_search_scale_x, int faces_min_search_scale_y);

	/// Function to detect the faces on color image
	/// The function detects the faces in an given image
	/// @param heads_color_images Color images of the regions that supposedly contain a head
	/// @param face_coordinates Vector of same size as heads_color_images, each entry becomes filled with another vector with the coordinates of detected faces in color image, i.e. outer index corresponds with index of heads_color_images
	/// @return Return code
	virtual unsigned long detectColorFaces(std::vector<cv::Mat>& heads_color_images, std::vector<std::vector<cv::Rect> >& face_coordinates);


private:
//	/// interpolates unassigned pixels in the depth image when using the kinect
//	/// @param img depth image
//	/// @return Return code
//	unsigned long InterpolateUnassignedPixels(cv::Mat& img);

	double m_faces_increase_search_scale;		///< The factor by which the search window is scaled between the subsequent scans
	int m_faces_drop_groups;					///< Minimum number (minus 1) of neighbor rectangles that makes up an object.
	int m_faces_min_search_scale_x;				///< Minimum search scale x
	int m_faces_min_search_scale_y;				///< Minimum search scale y

	CvMemStorage* m_storage;					///< Storage for face and eye detection
	CvHaarClassifierCascade* m_face_cascade;	///< Haar-Classifier for face-detection

	bool m_initialized;		///< indicates whether the class was already initialized
};

} // end namespace

#endif // __FACE_DETECTOR_H__