/*
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

#ifndef DLIB_RENDER_FACE_DeTECTIONS_LINES_H_
#define DLIB_RENDER_FACE_DeTECTIONS_LINES_H_

#include "full_object_detection.h"
#include "../gui_widgets.h"
#include "render_face_detections_abstract.h"
#include <vector>

namespace dlib
{
	inline std::vector<image_window::overlay_line> render_face_detections_lines(
		const std::vector<full_object_detection>& dets,
		const rgb_pixel color = rgb_pixel(0, 255, 0)
		)
	{
		std::vector<image_window::overlay_line> lines;
		for (unsigned long i = 0; i < dets.size(); ++i)
		{
			DLIB_CASSERT(dets[i].num_parts() == 68,
				"\t std::vector<image_window::overlay_line> render_face_detections_lines()"
				<< "\n\t Invalid inputs were given to this function. "
				<< "\n\t dets[" << i << "].num_parts():  " << dets[i].num_parts()
				);

			const full_object_detection& d = dets[i];
			//for (unsigned long i = 1; i <= 16; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));

			//for (unsigned long i = 28; i <= 30; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));

			//for (unsigned long i = 18; i <= 21; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
			//for (unsigned long i = 23; i <= 26; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
			//for (unsigned long i = 31; i <= 35; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
			//
			//lines.push_back(image_window::overlay_line(d.part(30), d.part(35), color));

			//for (unsigned long i = 37; i <= 41; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
			//
			//lines.push_back(image_window::overlay_line(d.part(36), d.part(41), color));

			//for (unsigned long i = 43; i <= 47; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
			//
			//lines.push_back(image_window::overlay_line(d.part(42), d.part(47), color));

			//for (unsigned long i = 49; i <= 59; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
			//
			//lines.push_back(image_window::overlay_line(d.part(48), d.part(59), color));

			//for (unsigned long i = 61; i <= 67; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(i), d.part(i - 1), color));
			//
			//lines.push_back(image_window::overlay_line(d.part(60), d.part(67), color));

			
			//lines.push_back(image_window::overlay_line(d.part(0), d.part(17), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(0), d.part(36), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(1), d.part(36), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(1), d.part(41), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(2), d.part(29), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(2), d.part(40), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(2), d.part(41), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(3), d.part(29), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(3), d.part(31), rgb_pixel(0, 0, 255)));


			//for (unsigned long i = 56; i <= 58; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(8), d.part(i), rgb_pixel(0, 0, 255)));

			//for (unsigned long i = 58; i <= 59; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(7), d.part(i), rgb_pixel(0, 0, 255)));

			//for (unsigned long i = 55; i <= 56; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(9), d.part(i), rgb_pixel(0, 0, 255)));

			//for (unsigned long i = 54; i <= 55; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(10), d.part(i), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(10), d.part(64), rgb_pixel(0, 0, 255)));

			//for (unsigned long i = 59; i <= 60; ++i)
			//	lines.push_back(image_window::overlay_line(d.part(6), d.part(i), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(6), d.part(48), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(5), d.part(48), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(5), d.part(60), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(11), d.part(54), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(11), d.part(64), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(4), d.part(48), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(12), d.part(54), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(3), d.part(48), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(3), d.part(31), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(13), d.part(29), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(13), d.part(35), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(13), d.part(54), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(14), d.part(29), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(14), d.part(46), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(14), d.part(47), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(15), d.part(45), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(15), d.part(46), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(16), d.part(26), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(16), d.part(45), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(26), d.part(44), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(26), d.part(45), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(25), d.part(43), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(25), d.part(44), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(24), d.part(43), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(23), d.part(42), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(23), d.part(43), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(23), d.part(20), rgb_pixel(0, 0, 255)));

			//lines.push_back(image_window::overlay_line(d.part(22), d.part(21), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(22), d.part(27), rgb_pixel(0, 0, 255)));
			//lines.push_back(image_window::overlay_line(d.part(22), d.part(42), rgb_pixel(0, 0, 255)));

			lines.push_back(image_window::overlay_line(d.part(17), d.part(36), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(17), d.part(39), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(19), d.part(36), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(19), d.part(39), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(21), d.part(36), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(21), d.part(39), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(22), d.part(42), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(22), d.part(45), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(24), d.part(42), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(24), d.part(45), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(26), d.part(42), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(26), d.part(45), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(43), d.part(47), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(43), d.part(46), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(44), d.part(47), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(44), d.part(46), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(48), d.part(54), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(51), d.part(57), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(51), d.part(48), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(51), d.part(54), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(57), d.part(48), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(57), d.part(54), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(19), d.part(17), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(19), d.part(21), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(24), d.part(22), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(24), d.part(26), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(21), d.part(22), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(36), d.part(39), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(42), d.part(45), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(37), d.part(41), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(37), d.part(40), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(38), d.part(41), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(38), d.part(40), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(36), d.part(48), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(39), d.part(51), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(42), d.part(51), rgb_pixel(0, 0, 255)));
			lines.push_back(image_window::overlay_line(d.part(45), d.part(54), rgb_pixel(0, 0, 255)));

		}
		return lines;
	}

	// ----------------------------------------------------------------------------------------

	inline std::vector<image_window::overlay_line> render_face_detections_lines(
		const full_object_detection& det,
		const rgb_pixel color = rgb_pixel(0, 255, 0)
		)
	{
		std::vector<full_object_detection> dets;
		dets.push_back(det);
		return render_face_detections_lines(dets, color);
	}

	// ----------------------------------------------------------------------------------------
}

#endif // DLIB_RENDER_FACE_DeTECTIONS_LINES_H_

