/*
* Facial Emotion Recognition in C++ versions 2.0 (Updated on Monday 11 June 2018).
*
* Emotion recognition is done based on facial expressions using image files and the webcam.
*
* Copyright 2017 Open University of the Netherlands (OUNL)
*
* Author: Kiavash Bahreini.
* Organization: Open University of the Netherlands (OUNL).
* Project: The RAGE project
* Project URL: http://rageproject.eu.
* Task: T2.3 of the RAGE project; Development of assets for emotion detection.
*
* For any questions please contact:
*
* Kiavash Bahreini via kiavash.bahreini [AT] ou [DOT] nl
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* This project has received funding from the European Union’s Horizon
* 2020 research and innovation programme under grant agreement No 644187.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/*
* This code is based on the dlib c++ library.
*
* URL: http://dlib.net/.
*/

/*
* In order to capture the video from a camera this code uses
* the Opencv version 2.4.11 and/or higher.
* URL: https://sourceforge.net/projects/opencvlibrary/files/opencv-win/
*/

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing.h>
#include<dlib/image_transforms.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

#ifndef DLIB_RENDER_FACE_DeTECTIONS_H_
#define DLIB_RENDER_FACE_DeTECTIONS_H_

#include "full_object_detection.h"
#include "../gui_widgets.h"
#include "render_face_detections_abstract.h"
#include <vector>

namespace dlib
{
    inline std::vector<image_window::overlay_circle> render_face_detections (
        const std::vector<full_object_detection>& dets,
        const rgb_pixel color = rgb_pixel(0,255,0)
    )
    {
        //std::vector<image_window::overlay_line> lines;

		std::vector<image_window::overlay_circle> circle;
		for (unsigned long i = 0; i < dets.size(); ++i)
		{
			DLIB_CASSERT(dets[i].num_parts() == 68,
				"\t std::vector<image_window::overlay_line> render_face_detections()"
				<< "\n\t Invalid inputs were given to this function. "
				<< "\n\t dets[" << i << "].num_parts():  " << dets[i].num_parts()
				);

			const full_object_detection& d = dets[i];

			for (unsigned long i = 0; i <= 67; ++i) {
				//lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
				circle.push_back(image_window::overlay_circle(d.part(i), 3, rgb_pixel(255, 0, 0)));			
			}

		return circle;
    }

// ----------------------------------------------------------------------------------------

    inline std::vector<image_window::overlay_circle> render_face_detections (
        const full_object_detection& det,
        const rgb_pixel color = rgb_pixel(0,255,0)
    )
    {
        std::vector<full_object_detection> dets;
        dets.push_back(det);
        return render_face_detections(dets, color);
    }

// ----------------------------------------------------------------------------------------

}

#endif // DLIB_RENDER_FACE_DeTECTIONS_H_

