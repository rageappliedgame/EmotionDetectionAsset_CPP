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

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <ctime>

#include <dlib/opencv.h>

//To capture the video from a camera
#include "C:\opencv-2.4.11\opencv\sources\modules\core\include\opencv2\highgui\highgui.hpp"

// #include "C:\Users\kbh\Desktop\FaceEmotionDetection&DatasetTraining\FaceEmotionDetection2016-March-01\src\lib\Tracker.h"
#include <dlib/image_transforms.h>
#include <dlib/image_processing/render_face_detections_lines.h>

using namespace dlib;
using namespace std;
//using namespace FACETRACKER;


// ----------------------------------------------------------------------------------------

// See http://stackoverflow.com/questions/876901/calculating-execution-time-in-c
#ifndef SYSOUT_F
#define SYSOUT_F(f, d) cout << f << std::setprecision (3) << (int)(d * 1000.0) << "ms" << endl // For Visual studio
#endif

#ifndef speedtest___             
#define speedtest___(data)   for (long blockTime = NULL; (blockTime == NULL ? (blockTime = clock()) != NULL : false); SYSOUT_F(data, (double) (clock() - blockTime) / CLOCKS_PER_SEC))
#endif
// ----------------------------------------------------------------------------------------
long double calculateEuclideanDistance(const short int x, const short int y, const short int a, const short int b) {
	//Solution: http://www.cut-the-knot.org/pythagoras/DistanceFormula.shtml
	//dist((x, y), (a, b)) = √(x - a)² + (y - b)²
	return (sqrt(pow(x - a, 2) + pow(y - b, 2)));
}
// -------------------------
long double * setPointsToCalculateEuclideanDistance(full_object_detection shape) {

	static long double EuclideanDistanceArray[54];

	//Left eyebrow to the left eye
	EuclideanDistanceArray[0] = calculateEuclideanDistance(shape.part(17).x(), shape.part(17).y(), shape.part(36).x(), shape.part(36).y());
	EuclideanDistanceArray[1] = calculateEuclideanDistance(shape.part(17).x(), shape.part(17).y(), shape.part(39).x(), shape.part(39).y());
	EuclideanDistanceArray[2] = calculateEuclideanDistance(shape.part(36).x(), shape.part(36).y(), shape.part(39).x(), shape.part(39).y());

	EuclideanDistanceArray[3] = calculateEuclideanDistance(shape.part(19).x(), shape.part(19).y(), shape.part(36).x(), shape.part(36).y());
	EuclideanDistanceArray[4] = calculateEuclideanDistance(shape.part(19).x(), shape.part(19).y(), shape.part(39).x(), shape.part(39).y());
	EuclideanDistanceArray[5] = EuclideanDistanceArray[2];

	EuclideanDistanceArray[6] = calculateEuclideanDistance(shape.part(21).x(), shape.part(21).y(), shape.part(36).x(), shape.part(36).y());
	EuclideanDistanceArray[7] = calculateEuclideanDistance(shape.part(21).x(), shape.part(21).y(), shape.part(39).x(), shape.part(39).y());
	EuclideanDistanceArray[8] = EuclideanDistanceArray[2];

	//Right eyebrow to the right eye
	EuclideanDistanceArray[9] = calculateEuclideanDistance(shape.part(22).x(), shape.part(22).y(), shape.part(42).x(), shape.part(42).y());
	EuclideanDistanceArray[10] = calculateEuclideanDistance(shape.part(22).x(), shape.part(22).y(), shape.part(45).x(), shape.part(45).y());
	EuclideanDistanceArray[11] = calculateEuclideanDistance(shape.part(42).x(), shape.part(42).y(), shape.part(45).x(), shape.part(45).y());

	EuclideanDistanceArray[12] = calculateEuclideanDistance(shape.part(24).x(), shape.part(24).y(), shape.part(42).x(), shape.part(42).y());
	EuclideanDistanceArray[13] = calculateEuclideanDistance(shape.part(24).x(), shape.part(24).y(), shape.part(45).x(), shape.part(45).y());
	EuclideanDistanceArray[14] = EuclideanDistanceArray[11];

	EuclideanDistanceArray[15] = calculateEuclideanDistance(shape.part(26).x(), shape.part(26).y(), shape.part(42).x(), shape.part(42).y());
	EuclideanDistanceArray[16] = calculateEuclideanDistance(shape.part(26).x(), shape.part(26).y(), shape.part(45).x(), shape.part(45).y());
	EuclideanDistanceArray[17] = EuclideanDistanceArray[11];

	//Left eye
	EuclideanDistanceArray[18] = calculateEuclideanDistance(shape.part(37).x(), shape.part(37).y(), shape.part(40).x(), shape.part(40).y());
	EuclideanDistanceArray[19] = calculateEuclideanDistance(shape.part(37).x(), shape.part(37).y(), shape.part(41).x(), shape.part(41).y());
	EuclideanDistanceArray[20] = calculateEuclideanDistance(shape.part(40).x(), shape.part(40).y(), shape.part(41).x(), shape.part(41).y());

	EuclideanDistanceArray[21] = calculateEuclideanDistance(shape.part(38).x(), shape.part(38).y(), shape.part(40).x(), shape.part(40).y());
	EuclideanDistanceArray[22] = calculateEuclideanDistance(shape.part(38).x(), shape.part(38).y(), shape.part(41).x(), shape.part(41).y());
	EuclideanDistanceArray[23] = EuclideanDistanceArray[20];

	EuclideanDistanceArray[24] = calculateEuclideanDistance(shape.part(43).x(), shape.part(43).y(), shape.part(46).x(), shape.part(46).y());
	EuclideanDistanceArray[25] = calculateEuclideanDistance(shape.part(43).x(), shape.part(43).y(), shape.part(47).x(), shape.part(47).y());
	EuclideanDistanceArray[26] = calculateEuclideanDistance(shape.part(46).x(), shape.part(46).y(), shape.part(47).x(), shape.part(47).y());

	EuclideanDistanceArray[27] = calculateEuclideanDistance(shape.part(44).x(), shape.part(44).y(), shape.part(46).x(), shape.part(46).y());
	EuclideanDistanceArray[28] = calculateEuclideanDistance(shape.part(44).x(), shape.part(44).y(), shape.part(47).x(), shape.part(47).y());
	EuclideanDistanceArray[29] = EuclideanDistanceArray[26];

	//Top of the mouth
	EuclideanDistanceArray[30] = calculateEuclideanDistance(shape.part(48).x(), shape.part(48).y(), shape.part(51).x(), shape.part(51).y());
	EuclideanDistanceArray[31] = calculateEuclideanDistance(shape.part(51).x(), shape.part(51).y(), shape.part(54).x(), shape.part(54).y());
	EuclideanDistanceArray[32] = calculateEuclideanDistance(shape.part(48).x(), shape.part(48).y(), shape.part(54).x(), shape.part(54).y());

	//Buttom of the mouth
	EuclideanDistanceArray[33] = calculateEuclideanDistance(shape.part(48).x(), shape.part(48).y(), shape.part(57).x(), shape.part(57).y());
	EuclideanDistanceArray[34] = calculateEuclideanDistance(shape.part(54).x(), shape.part(54).y(), shape.part(57).x(), shape.part(57).y());
	EuclideanDistanceArray[35] = EuclideanDistanceArray[32];

	//Left eyebrow
	EuclideanDistanceArray[36] = calculateEuclideanDistance(shape.part(17).x(), shape.part(17).y(), shape.part(19).x(), shape.part(19).y());
	EuclideanDistanceArray[37] = calculateEuclideanDistance(shape.part(19).x(), shape.part(19).y(), shape.part(21).x(), shape.part(21).y());
	EuclideanDistanceArray[38] = calculateEuclideanDistance(shape.part(17).x(), shape.part(17).y(), shape.part(21).x(), shape.part(21).y());

	//Right eyebrow
	EuclideanDistanceArray[39] = calculateEuclideanDistance(shape.part(22).x(), shape.part(22).y(), shape.part(24).x(), shape.part(24).y());
	EuclideanDistanceArray[40] = calculateEuclideanDistance(shape.part(24).x(), shape.part(24).y(), shape.part(26).x(), shape.part(26).y());
	EuclideanDistanceArray[41] = calculateEuclideanDistance(shape.part(22).x(), shape.part(22).y(), shape.part(26).x(), shape.part(26).y());

	//Eyebrows to the top nose
	EuclideanDistanceArray[42] = calculateEuclideanDistance(shape.part(21).x(), shape.part(21).y(), shape.part(27).x(), shape.part(27).y());
	EuclideanDistanceArray[43] = calculateEuclideanDistance(shape.part(22).x(), shape.part(22).y(), shape.part(27).x(), shape.part(27).y());
	EuclideanDistanceArray[44] = calculateEuclideanDistance(shape.part(21).x(), shape.part(21).y(), shape.part(22).x(), shape.part(22).y());

	//Left eye to the mouth
	EuclideanDistanceArray[45] = calculateEuclideanDistance(shape.part(36).x(), shape.part(36).y(), shape.part(60).x(), shape.part(60).y());
	EuclideanDistanceArray[46] = calculateEuclideanDistance(shape.part(48).x(), shape.part(48).y(), shape.part(60).x(), shape.part(60).y());
	EuclideanDistanceArray[47] = calculateEuclideanDistance(shape.part(36).x(), shape.part(36).y(), shape.part(48).x(), shape.part(48).y());

	//Right eye to the mouth
	EuclideanDistanceArray[48] = calculateEuclideanDistance(shape.part(45).x(), shape.part(45).y(), shape.part(64).x(), shape.part(64).y());
	EuclideanDistanceArray[49] = calculateEuclideanDistance(shape.part(54).x(), shape.part(54).y(), shape.part(64).x(), shape.part(64).y());
	EuclideanDistanceArray[50] = calculateEuclideanDistance(shape.part(45).x(), shape.part(45).y(), shape.part(54).x(), shape.part(54).y());

	//Mouth to eyes
	EuclideanDistanceArray[51] = calculateEuclideanDistance(shape.part(39).x(), shape.part(39).y(), shape.part(51).x(), shape.part(51).y());
	EuclideanDistanceArray[52] = calculateEuclideanDistance(shape.part(42).x(), shape.part(42).y(), shape.part(51).x(), shape.part(51).y());
	EuclideanDistanceArray[53] = calculateEuclideanDistance(shape.part(39).x(), shape.part(39).y(), shape.part(42).x(), shape.part(42).y());

	return EuclideanDistanceArray;
}
// -------------------------
long double calculateCosines(const long double a, const long double b, const long double c) {
	//General Solution: https://www.mathsisfun.com/algebra/trig-solving-triangles.html
	//Solution for this specific problem: https://www.mathsisfun.com/algebra/trig-solving-sss-triangles.html

	//To solve three sides of the triangle (called an SSS triangle) :

	//Use The Law of Cosines first to calculate one of the angles
	//then use The Law of Cosines again to find another angle
	//and finally use angles of a triangle add to 180° to find the last angle.

	//We use the "angle" version of the Law of Cosines :
	//cos(C) = (a² + b² − c²)/2ab
	//cos(A) = (b² + c² − a²)/2bc
	//cos(B) = (c² + a² − b²)/2ca

	return ((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a*b));
}

long double * callCalculateCosines(const long double * EuclideanDistanceArrayPointer) {

	static long double CalculateCosinesArray[54];

	for (int i = 0; i < 54; i += 3) {
		CalculateCosinesArray[i] = calculateCosines(*(EuclideanDistanceArrayPointer + i), *(EuclideanDistanceArrayPointer + i + 1), *(EuclideanDistanceArrayPointer + i + 2));
		CalculateCosinesArray[i + 1] = calculateCosines(*(EuclideanDistanceArrayPointer + i + 1), *(EuclideanDistanceArrayPointer + i + 2), *(EuclideanDistanceArrayPointer + i));
		CalculateCosinesArray[i + 2] = calculateCosines(*(EuclideanDistanceArrayPointer + i + 2), *(EuclideanDistanceArrayPointer + i), *(EuclideanDistanceArrayPointer + i + 1));
	}
	return CalculateCosinesArray;
}

long double calculateArcCosines(const long double a) {
	//General Solution: https://www.mathsisfun.com/algebra/trig-solving-triangles.html
	//Solution for this specific problem: https://www.mathsisfun.com/algebra/trig-solving-sss-triangles.html

	//To solve three sides of the triangle (called an SSS triangle) :

	//Use The Law of Cosines first to calculate one of the angles
	//then use The Law of Cosines again to find another angle
	//and finally use angles of a triangle add to 180° to find the last angle.

	//We use the "angle" version of the Law of Cosines :
	//cos(C) = (a² + b² − c²)/2ab
	//cos(A) = (b² + c² − a²)/2bc
	//cos(B) = (c² + a² − b²)/2ca

	return (acos(a) * 180.0 / 3.14159265);
}

long double * callCalculateArcCosines(const long double * CosinesArrayPointer) {

	static long double CalculateArcCosinesArray[54];

	for (int i = 0; i < 54; i += 3) {
		CalculateArcCosinesArray[i] = calculateArcCosines(*(CosinesArrayPointer + i));
		CalculateArcCosinesArray[i + 1] = calculateArcCosines(*(CosinesArrayPointer + i + 1));
		//CalculateArcCosinesArray[i + 2] = 180 - CalculateArcCosinesArray[i] - CalculateArcCosinesArray[i + 1];
		CalculateArcCosinesArray[i + 2] = calculateArcCosines(*(CosinesArrayPointer + i + 2));
	}
	return CalculateArcCosinesArray;
}
int main(int argc, char** argv)
{
	try
	{
		// This example takes in a shape model file and then a list of images to
		// process.  We will take these filenames in as command line arguments.
		// Dlib comes with example images in the examples/faces folder so give
		// those as arguments to this program.
//		if (argc == 1)
//		{
//			std::cout << "Call this program like this:" << endl;
//			std::cout << "./face_landmark_detection_ex shape_predictor_68_face_landmarks.dat faces/*.jpg" << endl;
//			std::cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
//			std::cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
//			return 0;
//		}

		clock_t tStart = clock();

		// We need a face detector.  We will use this to get bounding boxes for
		// each face in an image.
		frontal_face_detector detector;
		speedtest___("get_frontal_face_detector: ")
		{
			detector = get_frontal_face_detector();
		}
		// And we also need a shape_predictor.  This is the tool that will predict face
		// landmark positions given an image and face bounding box.  Here we are just
		// loading the model from the shape_predictor_68_face_landmarks.dat file you gave
		// as a command line argument.
		shape_predictor sp;
		speedtest___("deserialize database: ")
		{
			//deserialize(argv[1]) >> sp;
			deserialize("C:\\Users\\kbh\\Desktop\\dlib-master\\examples\\build\\Debug\\shape_predictor_68_face_landmarks.dat") >> sp;
		}

		image_window win;//, win_faces;
		// Loop over all the images provided on the command line.
		for (int i = 2; i < 3; ++i)
		{
			std::cout << "processing image " << "C:\\Users\\kbh\\Desktop\\Emotion and CK+\\cohn-kanade-images\\S005\\001\\S005_001_00000011.png" << endl;
			array2d<rgb_pixel> img;

			//			std::ifstream file("C:\\Users\\kbh\\Desktop\\Emotion and CK+\\List of files sorted by emotions.txt");
			//			std::ifstream emotionFile("C:\\Users\\kbh\\Desktop\\Emotion and CK+\\List of emotions sorted by emotions.txt");
			std::ifstream file("C:\\Users\\kbh\\Desktop\\Emotion and CK+\\FILES.txt");
			std::ifstream emotionFile("C:\\Users\\kbh\\Desktop\\Emotion and CK+\\EMOTIONS.txt");
			/*	Happy=69+69=138
			/	Sad=27+27=54
			/	Surprise=83+83=166
			/	Fear=25+25=50
			/	Disgust=59+59=118
			/	Anger=45+45=90
			/	Neutral=123+123=246
			*/
			//			std::string matrix[862]; //Number of files
			//			std::string emotionMatrix[862]; //Number of emotions
			std::string matrix[2]; //Number of files
			std::string emotionMatrix[2]; //Number of emotions
			std::string line;
			std::string emotionLine;
			int row = 0;
			int emotionRow = 0;

			while (std::getline(file, line)) {
				std::istringstream stream(line);

				matrix[row] = line;
				row++;
			}
			while (std::getline(emotionFile, emotionLine)) {
				std::istringstream stream(emotionLine);

				emotionMatrix[emotionRow] = emotionLine;
				emotionRow++;
			}

			for (int i = 0; i < row; i++) {
				std::cout << matrix[i];
				std::cout << "\n";
			}
			for (int i = 0; i < emotionRow; i++) {
				std::cout << emotionMatrix[i];
				std::cout << "\n";
			}

			bool flag = 0;// make sure that the image is processed in flip and not flip modes

			for (int i = 0; i < row; i++) {

				load_image(img, matrix[i]);
				// Make the image larger so we can detect small faces.
				//pyramid_up(img);

				if (flag == 1) {

					//Rotate cimg to img
					dlib::array2d<unsigned char> imgTempGray;
					assign_image(imgTempGray, img);
					flip_image_left_right(imgTempGray, img);

					flag = 0;
				}
				else {
					//load_image(img, matrix[i]);
					// Make the image larger so we can detect small faces.
					//pyramid_up(img);
					flag = 1;
				}
				// Now tell the face detector to give us a list of bounding boxes
				// around all the faces in the image.
				std::vector<dlib::rectangle> dets;
				speedtest___("detect faces: ")
				{
					dets = detector(img);
				}
				std::cout << "Number of faces detected: " << dets.size() << endl;

				// Now we will go ask the shape_predictor to tell us the pose of
				// each face we detected.
				std::vector<full_object_detection> shapes;
				speedtest___("detect features: ")
				{
					for (unsigned long j = 0; j < dets.size(); ++j)
					{
						full_object_detection shape = sp(img, dets[j]);
						std::cout << "number of parts: " << shape.num_parts() << endl;
						std::cout << "pixel position of first part:  " << shape.part(0) << " " << shape.part(0).x() << " " << shape.part(0).y() << endl;
						std::cout << "pixel position of second part: " << shape.part(1) << endl;

						////////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////////
						std::ofstream fout("EmotionsDataset.txt", ofstream::app);
						if (!fout)
							throw dlib::error("ERROR: Unable to open image_metadata_stylesheet.xsl for writing.");

						ostringstream convert;
						convert << emotionMatrix[i];// << i;

						// A pointer to a long double to calculate the euclidean distance between the landmark points.
						const long double *EuclideanDistanceArrayPointer;
						EuclideanDistanceArrayPointer = setPointsToCalculateEuclideanDistance(shape);

						// A pointer to a long double to calculate the cosines between the three sides of the triangle.
						const long double *CosinesArrayPointer;
						CosinesArrayPointer = callCalculateCosines(EuclideanDistanceArrayPointer);

						// A pointer to a long double to calculate the arc cosines of the angles.
						const long double *ArcCosinesArrayPointer;
						ArcCosinesArrayPointer = callCalculateArcCosines(CosinesArrayPointer);


						for (int i = 0; i < 54; i++)
							fout << *(ArcCosinesArrayPointer + i) << ",";

						fout << convert.str().c_str() << endl;
						fout.close();
						std::cout << "Write Done." << endl;

						////////////////////////////////////////////////////////////////
						//*(ArcCosinesArrayPointer + i)
						const long double *R = ArcCosinesArrayPointer;
						//Happy
						//Rule 1
						if (
							((*(R + 30) >= 159.608 && *(R + 30) <= 160.424) || (*(R + 30) >= 160.424))
							&& (!(*(R + 30) >= 160.168 && *(R + 30) <= 160.675) || (!*(R + 30) <= 160.168))
							&& ((*(R + 35) >= 30.0655 && *(R + 35) <= 30.2536) || (*(R + 35) >= 30.2536
								&& (!(*(R + 35) > 30.2536 && *(R + 35) <= 32.685))))
							) {
							cout << "Emotions = Happy(CF = 0.97)" << endl;
						}
						//Rule 2
						 if (
							((*(R + 31) >= 9.85016 && *(R + 31) <= 9.96286) || (*(R + 31) <= 9.85016))
							&& ((*(R + 51) >= 35.5078 && *(R + 51) <= 35.5856) || (*(R + 31) >= 35.5856))
							&& ((*(R + 10) >= 22.9748 && *(R + 10) <= 23.0757) || (*(R + 10) <= 23.0757))
							&& ((*(R + 0) >= 24.8358 && *(R + 0) <= 24.9599) || (*(R + 0) <= 24.8358))
							) {
							cout << "Emotions = Happy(CF = 0.98)" << endl;
						}
						//Rule 3
						 if (
							((*(R + 32) >= 13.8022 && *(R + 32) <= 14.6793) || (*(R + 32) <= 13.8022))
							&& ((*(R + 34) >= 25.1647 && *(R + 34) <= 25.4542) || (*(R + 34) >= 25.4542))
							&& ((*(R + 50) >= 3.7724 && *(R + 50) <= 3.79234) || (*(R + 50) >= 3.79234))
							&& ((*(R + 48) >= 64.551 && *(R + 48) <= 66.8476) || (*(R + 48) >= 66.8476))
							) {
							cout << "Emotions = Happy(CF = 0.9)" << endl;
						}
						//Rule 4
						 if (
							((*(R + 31) >= 12.4074 && *(R + 31) <= 16.2636) || (*(R + 31) <= 12.4074))
							&& ((*(R + 35) >= 25.6426 && *(R + 35) <= 27.0878) || (*(R + 35) >= 25.0878))
							&& ((*(R + 37) >= 21.4168 && *(R + 37) <= 21.5797) || (*(R + 37) >= 21.5797))
							&& ((*(R + 0) >= 21.1748 && *(R + 0) <= 21.9187) || (*(R + 0) <= 21.1748))
							) {
							cout << "Emotions = Happy(CF = 0.95)" << endl;
						}
						//Rule 5
						 if (
							((*(R + 32) >= 5.15255 && *(R + 32) <= 5.16574) || (*(R + 32) <= 5.15255))
							&& ((*(R + 32) >= 4.97626 && *(R + 32) <= 5.05265) || (*(R + 32) >= 5.05265))
							) {
							cout << "Emotions = Happy(CF = 0.66)" << endl;
						}
						//Sad
						//Rule 6
						 if (
							((*(R + 34) >= 15.1591 && *(R + 34) <= 15.3646) || (*(R + 34) >= 15.1591))
							&& ((*(R + 42) >= 73.6283 && *(R + 42) <= 74.5163) || (*(R + 42) <= 73.6283))
							&& ((*(R + 32) >= 17.9646 && *(R + 32) <= 17.9917) || (*(R + 32) >= 17.9917))
							&& ((*(R + 13) >= 68.61 && *(R + 13) <= 70.3929) || (*(R + 13) >= 70.3929))
							&& ((*(R + 37) >= 22.5483 && *(R + 37) <= 22.8643) || (*(R + 37) <= 22.5483))
							) {
							cout << "Emotions = Sad(CF = 0.94)" << endl;
						}
						//Rule 7
						 if (
							((*(R + 33) >= 142.341 && *(R + 33) <= 142.606) || (*(R + 33) >= 142.606))
							&& ((*(R + 44) >= 51.9081 && *(R + 44) <= 52.9607) || (*(R + 44) >= 52.9607))
							&& ((*(R + 50) >= 3.15842 && *(R + 50) <= 3.18719) || (*(R + 50) <= 3.15842))
							&& ((*(R + 31) >= 14.1431 && *(R + 31) <= 14.4425) || (*(R + 31) >= 14.4425))
							) {
							cout << "Emotions = Sad(CF = 0.82)" << endl;
						}
						//Rule 8
						 if (
							((*(R + 46) >= 84.9609 && *(R + 46) <= 85.074) || (*(R + 46) <= 84.9609))
							&& ((*(R + 51) >= 36.248 && *(R + 51) <= 36.6846) || (*(R + 51) >= 36.6846))
							) {
							cout << "Emotions = Sad(CF = 0.81)" << endl;
						}
						//Rule 9
						 if (
							((*(R + 42) >= 54.362 && *(R + 42) <= 54.4623) || (*(R + 42) <= 54.362))
							&& ((*(R + 3) >= 49.4672 && *(R + 3) <= 53.9726) || (*(R + 3) >= 53.9726))
							&& ((*(R + 18) >= 48.7314 && *(R + 18) <= 48.7806) || (*(R + 18) >= 48.7806))
							) {
							cout << "Emotions = Sad(CF = 0.84)" << endl;
						}
						//Rule 10
						 if (
							((*(R + 1) >= 6.82602 && *(R + 1) <= 7.03498) || (*(R + 1) <= 6.82602))
							&& ((*(R + 15) >= 14.5889 && *(R + 15) <= 15.0512) || (*(R + 15) >= 15.0512))
							) {
							cout << "Emotions = Sad(CF = 0.53)" << endl;
						}
						//Surprise
						//Rule 11
						 if (
							((*(R + 30) >= 126.304 && *(R + 30) <= 149.554) || (*(R + 30) <= 126.304))
							&& ((*(R + 34) >= 33.9611 && *(R + 34) <= 34.0477) || (*(R + 34) >= 34.0477))
							) {
							cout << "Emotions = Surprise(CF = 0.99)" << endl;
						}
						//Rule 12
						 if (
							((*(R + 8) >= 40.2461 && *(R + 8) <= 40.3331) || (*(R + 8) >= 40.3331))
							&& ((*(R + 51) >= 45.1865 && *(R + 51) <= 45.2721) || (*(R + 30) <= 45.1865))
							) {
							cout << "Emotions = Surprise(CF = 0.98)" << endl;
						}
						//Rule 13
						 if (
							((*(R + 17) >= 17.0409 && *(R + 17) <= 17.0477) || (*(R + 17) >= 17.0477))
							&& ((*(R + 17) >= 17.1027 && *(R + 17) <= 17.1054) || (*(R + 17) <= 17.1027))
							) {
							cout << "Emotions = Surprise(CF = 0.68)" << endl;
						}
						//Rule 14
						 if (
							((*(R + 48) >= 42.3974 && *(R + 48) <= 43.2472) || (*(R + 48) <= 42.3974))
							) {
							cout << "Emotions = Surprise(CF = 0.60)" << endl;
						}
						//Fear
						//Rule 15
						 if (
							((*(R + 26) >= 38.6598 && *(R + 26) <= 40.2364) || (*(R + 26) >= 40.2364))
							&& ((*(R + 50) >= 3.61388 && *(R + 50) <= 3.62035) || (*(R + 50) >= 3.62035))
							&& ((*(R + 19) >= 86.8202 && *(R + 19) <= 87.1376) || (*(R + 19) >= 87.1376))
							&& ((*(R + 32) >= 22.3228 && *(R + 32) <= 22.4199) || (*(R + 32) <= 22.3228))
							&& ((*(R + 44) >= 48.7314 && *(R + 44) <= 48.8141) || (*(R + 44) >= 48.8141))
							) {
							cout << "Emotions = Fear(CF = 0.90)" << endl;
						}
						//Rule 16
						 if (
							((*(R + 49) >= 95.8395 && *(R + 49) <= 96.2791) || (*(R + 49) <= 95.8395))
							&& ((*(R + 49) >= 93.3419 && *(R + 49) <= 94.0108) || (*(R + 49) >= 94.0108))
							&& ((*(R + 8) >= 35.0195 && *(R + 8) <= 35.6748) || (*(R + 8) >= 35.6748))
							&& ((*(R + 30) >= 112.548 && *(R + 30) <= 127.911) || (*(R + 30) >= 127.911))
							) {
							cout << "Emotions = Fear(CF = 0.84)" << endl;
						}
						//Rule 17
						 if (
							((*(R + 33) >= 113.647 && *(R + 33) <= 120.77) || (*(R + 33) >= 120.77))
							&& ((*(R + 35) >= 19.8265 && *(R + 35) <= 20.2393) || (*(R + 35) >= 20.2393))
							&& ((*(R + 22) >= 41.6335 && *(R + 22) <= 41.8665) || (*(R + 22) >= 41.8665))
							&& ((*(R + 51) >= 34.8844 && *(R + 51) <= 35.0913) || (*(R + 51) >= 35.0913))
							&& ((*(R + 12) >= 56.658 && *(R + 12) <= 56.7193) || (*(R + 12) <= 56.658))
							) {
							cout << "Emotions = Fear(CF = 0.87)" << endl;
						}
						//Disgust
						//Rule 18
						 if (
							((*(R + 26) >= 26.9489 && *(R + 26) <= 27.5973) || (*(R + 26) <= 26.9489))
							&& ((*(R + 8) >= 25.3267 && *(R + 8) <= 26.1046) || (*(R + 8) <= 25.3267))
							&& ((*(R + 21) >= 59.7436 && *(R + 21) <= 60.0864) || (*(R + 21) >= 60.0864))
							) {
							cout << "Emotions = Disgust(CF = 0.96)" << endl;
						}
						//Rule 19
						 if (
							((*(R + 26) >= 35.8377 && *(R + 26) <= 36.2538) || (*(R + 26) <= 35.8377))
							&& ((*(R + 30) >= 151.318 && *(R + 30) <= 151.76) || (*(R + 30) <= 151.76))
							&& ((*(R + 35) >= 18.6981 && *(R + 35) <= 18.7149) || (*(R + 35) >= 18.7149))
							&& ((*(R + 8) >= 25.9913 && *(R + 8) <= 26.0754) || (*(R + 8) <= 25.9913))
							&& ((*(R + 50) >= 3.1012 && *(R + 50) <= 3.21448) || (*(R + 50) >= 3.21448))
							&& ((*(R + 51) >= 40.4826 && *(R + 51) <= 40.6054) || (*(R + 51) <= 40.4826))
							) {
							cout << "Emotions = Disgust(CF = 0.96)" << endl;
						}
						//Rule 20
						 if (
							((*(R + 26) >= 35.4509 && *(R + 26) <= 35.8195) || (*(R + 26) <= 35.4509))
							&& ((*(R + 30) >= 160.168 && *(R + 30) <= 160.675) || (*(R + 30) <= 160.168))
							&& ((*(R + 42) >= 91.4652 && *(R + 42) <= 91.8476) || (*(R + 42) >= 91.8476))
							&& ((*(R + 9) >= 28.8713 && *(R + 9) <= 31.4661) || (*(R + 9) >= 31.4661))
							&& ((*(R + 16) >= 151.557 && *(R + 16) <= 151.794) || (*(R + 16) <= 151.557))
							) {
							cout << "Emotions = Disgust(CF = 0.94)" << endl;
						}
						//Rule 21
						 if (
							((*(R + 28) >= 38.1572 && *(R + 28) <= 38.3107) || (*(R + 28) <= 38.1572))
							&& ((*(R + 31) >= 7.43669 && *(R + 31) <= 10.1433) || (*(R + 31) >= 10.1433))
							&& ((*(R + 26) >= 30.9638 && *(R + 26) <= 31.4521) || (*(R + 26) <= 30.9638))
							&& ((*(R + 4) >= 46.4321 && *(R + 4) <= 46.5831) || (*(R + 4) <= 46.4321))
							&& ((*(R + 45) >= 74.4759 && *(R + 45) <= 75.0686) || (*(R + 45) >= 75.0686))
							) {
							cout << "Emotions = Disgust(CF = 0.94)" << endl;
						}
						//Rule 22
						 if (
							((*(R + 28) >= 38.1572 && *(R + 28) <= 38.3782) || (*(R + 28) <= 38.1572))
							&& ((*(R + 32) >= 8.70181 && *(R + 32) <= 8.71473) || (*(R + 32) >= 8.71473))
							&& ((*(R + 9) >= 35.9909 && *(R + 9) <= 36.1861) || (*(R + 9) >= 36.1861))
							&& ((*(R + 8) >= 27.817 && *(R + 8) <= 27.929) || (*(R + 8) <= 27.817))
							&& ((*(R + 14) >= 46.8177 && *(R + 14) <= 47.5595) || (*(R + 14) <= 46.8177))
							&& ((*(R + 8) >= 17.2892 && *(R + 8) <= 18.9069) || (*(R + 8) >= 18.9069))
							) {
							cout << "Emotions = Disgust(CF = 0.93)" << endl;
						}
						//Rule 23
						 if (
							((*(R + 28) >= 38.1572 && *(R + 28) <= 39.6233) || (*(R + 28) <= 38.1572))
							&& ((*(R + 32) >= 15.3773 && *(R + 32) <= 15.6442) || (*(R + 32) >= 15.6442))
							&& ((*(R + 23) >= 90 && *(R + 23) <= 92.4002) || (*(R + 23) <= 90))
							&& ((*(R + 6) >= 34.6599 && *(R + 6) <= 35.2154) || (*(R + 6) >= 35.2154))
							&& ((*(R + 2) >= 144.482 && *(R + 2) <= 144.492) || (*(R + 2) >= 144.492))
							) {
							cout << "Emotions = Disgust(CF = 0.90)" << endl;
						}
						//Rule 24
						 if (
							((*(R + 10) >= 26.4547 && *(R + 10) <= 27.2133) || (*(R + 10) <= 26.4547))
							&& ((*(R + 17) >= 35.5078 && *(R + 17) <= 35.5856) || (*(R + 17) >= 35.5856))
							&& ((*(R + 11) >= 22.9748 && *(R + 11) <= 23.0757) || (*(R + 11) <= 22.9748))
							&& ((*(R + 7) >= 24.8358 && *(R + 7) <= 24.9599) || (*(R + 7) >= 24.9599))
							&& ((*(R + 0) >= 24.8358 && *(R + 0) <= 24.9599) || (*(R + 0) <= 24.8358))
							) {
							cout << "Emotions = Disgust(CF = 0.86)" << endl;
						}
						//Anger
						//Rule 25
						 if (
							((*(R + 7) >= 115.258 && *(R + 7) <= 117.446) || (*(R + 7) >= 117.446))
							&& ((*(R + 34) >= 17.2653 && *(R + 34) <= 19.2307) || (*(R + 34) <= 17.2653))
							&& ((*(R + 30) >= 152.184 && *(R + 30) <= 152.257) || (*(R + 30) >= 152.257))
							&& ((*(R + 36) >= 141.526 && *(R + 36) <= 141.77) || (*(R + 36) >= 141.77))
							) {
							cout << "Emotions = Anger(CF = 0.93)" << endl;
						}
						//Rule 26
						 if (
							((*(R + 11) >= 122.859 && *(R + 11) <= 124.442) || (*(R + 11) >= 124.442))
							&& ((*(R + 22) >= 33.0558 && *(R + 22) <= 33.6901) || (*(R + 22) >= 33.6901))
							&& ((*(R + 8) >= 21.139 && *(R + 8) <= 21.5363) || (*(R + 8) <= 21.139))
							) {
							cout << "Emotions = Anger(CF = 0.90)" << endl;
						}
						//Rule 27
						 if (
							((*(R + 11) >= 114.76 && *(R + 11) <= 115.918) || (*(R + 11) >= 115.918))
							&& ((*(R + 34) >= 17.0449 && *(R + 34) <= 17.049) || (*(R + 34) <= 17.0449))
							&& ((*(R + 39) >= 137.883 && *(R + 39) <= 138.125) || (*(R + 39) <= 137.883))
							&& ((*(R + 19) >= 86.0353 && *(R + 19) <= 86.1859) || (*(R + 19) >= 86.1859))
							) {
							cout << "Emotions = Anger(CF = 0.82)" << endl;
						}
						//Rule 28
						 if (
							((*(R + 11) >= 123.048 && *(R + 11) <= 124.509) || (*(R + 11) >= 124.509))
							&& ((*(R + 51) >= 33.6707 && *(R + 51) <= 33.6995) || (*(R + 51) <= 33.6707))
							&& ((*(R + 18) >= 52.6819 && *(R + 18) <= 53.231) || (*(R + 18) >= 53.231))
							) {
							cout << "Emotions = Anger(CF = 0.83)" << endl;
						}
						//Rule 29
						 if (
							((*(R + 34) >= 22.8636 && *(R + 34) <= 23.1986) || (*(R + 34) <= 22.8636))
							&& ((*(R + 31) >= 10.1964 && *(R + 31) <= 10.3628) || (*(R + 31) <= 10.1964))
							&& ((*(R + 46) >= 107.21 && *(R + 46) <= 107.447) || (*(R + 46) <= 107.21))
							&& ((*(R + 47) >= 3.29176 && *(R + 47) <= 3.4244) || (*(R + 47) <= 3.29176))
							) {
							cout << "Emotions = Anger(CF = 0.82)" << endl;
						}
						//Rule 30
						 if (
							((*(R + 5) >= 68.4986 && *(R + 5) <= 68.8774) || (*(R + 5) <= 68.4986))
							&& ((*(R + 35) >= 18.6981 && *(R + 35) <= 18.7149) || (*(R + 35) <= 18.6981))
							&& ((*(R + 13) >= 66.8664 && *(R + 13) <= 67.7345) || (*(R + 13) <= 66.8664))
							&& ((*(R + 51) >= 39.3543 && *(R + 51) <= 39.4115) || (*(R + 51) <= 39.3543))
							) {
							cout << "Emotions = Anger(CF = 0.92)" << endl;
						}
						//Neutral
						//Rule 31
						 if (
							((*(R + 34) >= 26.5651 && *(R + 34) <= 26.7055) || (*(R + 34) <= 26.5651))
							&& ((*(R + 20) >= 39.2894 && *(R + 20) <= 39.6233) || (*(R + 20) >= 39.6233))
							&& ((*(R + 45) >= 78.9618 && *(R + 45) <= 789745) || (*(R + 45) <= 78.9618))
							&& ((*(R + 38) >= 19.9831 && *(R + 38) <= 20.0674) || (*(R + 38) >= 20.0674))
							&& ((*(R + 8) >= 35.4327 && *(R + 8) <= 36.92) || (*(R + 8) <= 35.4327))
							&& ((*(R + 30) >= 156.633 && *(R + 30) <= 157.079) || (*(R + 30) <= 156.633))
							&& ((*(R + 44) >= 38.5527 && *(R + 44) <= 38.6598) || (*(R + 44) >= 38.6598))
							) {
							cout << "Emotions = Neutral(CF = 0.98)" << endl;
						}
						//Rule 32
						 if (
							((*(R + 35) >= 27.2363 && *(R + 35) <= 27.3464) || (*(R + 35) <= 27.2363))
							&& ((*(R + 28) >= 38.1572 && *(R + 28) <= 38.6598) || (*(R + 28) >= 38.6598))
							&& ((*(R + 6) >= 38.9806 && *(R + 6) <= 39.1219) || (*(R + 6) >= 39.1219))
							&& ((*(R + 50) >= 3.61388 && *(R + 50) <= 3.64164) || (*(R + 50) <= 3.61388))
							&& ((*(R + 45) >= 79.5199 && *(R + 45) <= 79.6952) || (*(R + 45) <= 79.5199))
							) {
							cout << "Emotions = Neutral(CF = 0.95)" << endl;
						}
						//Rule 33
						 if (
							((*(R + 34) >= 28.1313 && *(R + 34) <= 28.9551) || (*(R + 34) <= 28.1313))
							&& ((*(R + 28) >= 38.1572 && *(R + 28) <= 38.4537) || (*(R + 28) >= 38.4537))
							&& ((*(R + 9) >= 39.7376 && *(R + 9) <= 39.8419) || (*(R + 9) >= 39.8419))
							&& ((*(R + 19) >= 86.6335 && *(R + 19) <= 87.0364) || (*(R + 19) <= 86.6335))
							&& ((*(R + 50) >= 3.61207 && *(R + 50) <= 3.62575) || (*(R + 50) <= 3.61207))
							) {
							cout << "Emotions = Neutral(CF = 0.93)" << endl;
						}
						//Rule 34
						 if (
							((*(R + 34) >= 26.8913 && *(R + 34) <= 26.9486) || (*(R + 34) <= 26.8913))
							&& ((*(R + 20) >= 33.6901 && *(R + 20) <= 35.8195) || (*(R + 20) >= 35.8195))
							&& ((*(R + 12) >= 58.3317 && *(R + 12) <= 58.6666) || (*(R + 12) <= 58.3317))
							&& ((*(R + 22) >= 38.7933 && *(R + 22) <= 39.0939) || (*(R + 22) <= 38.7933))
							&& ((*(R + 33) >= 152.969 && *(R + 33) <= 152.971) || (*(R + 33) <= 152.969))
							&& ((*(R + 43) >= 50.7021 && *(R + 43) <= 50.8786) || (*(R + 43) >= 50.8786))
							) {
							cout << "Emotions = Neutral(CF = 0.94)" << endl;
						}
						//Rule 35
						 if (
							((*(R + 33) >= 88.1516 && *(R + 33) <= 121.909) || (*(R + 33) >= 121.909))
							&& ((*(R + 28) >= 38.1572 && *(R + 28) <= 38.6238) || (*(R + 28) >= 38.6238))
							&& ((*(R + 51) >= 35.422 && *(R + 51) <= 36.0181) || (*(R + 51) <= 35.422))
							&& ((*(R + 43) >= 51.481 && *(R + 43) <= 51.6839) || (*(R + 43) <= 51.481))
							&& ((*(R + 32) >= 13.4486 && *(R + 32) <= 13.6831) || (*(R + 32) >= 13.6831))
							&& ((*(R + 26) >= 43.2643 && *(R + 26) <= 43.3844) || (*(R + 26) <= 43.2643))
							&& ((*(R + 36) >= 146.691 && *(R + 36) <= 146.723) || (*(R + 36) <= 146.691))
							) {
							cout << "Emotions = Neutral(CF = 0.97)" << endl;
						}
						//Rule 36
						 if (
							((*(R + 35) >= 29.0332 && *(R + 35) <= 32.685) || (*(R + 35) <= 29.0332))
							&& ((*(R + 8) >= 26.5308 && *(R + 8) <= 26.5651) || (*(R + 8) >= 26.5651))
							&& ((*(R + 29) >= 85.6013 && *(R + 29) <= 85.9144) || (*(R + 29) <= 85.6013))
							&& ((*(R + 44) >= 51.953 && *(R + 44) <= 52.0023) || (*(R + 44) <= 51.953))
							&& ((*(R + 5) >= 75.7986 && *(R + 5) <= 76.0875) || (*(R + 5) <= 75.7986))
							&& ((*(R + 18) >= 61.0736 && *(R + 18) <= 64.9831) || (*(R + 18) <= 61.0736))
							) {
							cout << "Emotions = Neutral(CF = 0.95)" << endl;
						}
						//Rule 37
						 if (
							((*(R + 33) >= 118.764 && *(R + 33) <= 120.426) || (*(R + 33) >= 120.426))
							&& ((*(R + 27) >= 57.0948 && *(R + 27) <= 64.7327) || (*(R + 27) <= 57.0948))
							&& ((*(R + 49) >= 104.517 && *(R + 49) <= 104.534) || (*(R + 49) >= 104.534))
							&& ((*(R + 51) >= 33.918 && *(R + 51) <= 34.2595) || (*(R + 51) <= 33.918))
							&& ((*(R + 5) >= 73.3444 && *(R + 5) <= 73.7261) || (*(R + 5) >= 73.7261))
							&& ((*(R + 33) >= 136.4 && *(R + 33) <= 149.673) || (*(R + 33) <= 136.4))
							) {
							cout << "Emotions = Neutral(CF = 0.96)" << endl;
						}
						else {
							cout << "No emotions detected" << endl;
						}

						////////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////////
						////////////////////////////////////////////////////////////////
						// a pointer to an int.
//						double *EuclideanDistanceArrayPointer;
//						EuclideanDistanceArrayPointer = setPointsToCalculateEuclideanDistance(shape);
//						for (int i = 0; i < 54; i++)
//							std::cout << "*(Pointer + " << i << ") : " << *(EuclideanDistanceArrayPointer + i) << endl;

						// You get the idea, you can get all the face part locations if
						// you want them.  Here we just store them in shapes so we can
						// put them on the screen.
						shapes.push_back(shape);
					}
				}

				// Now let's view our face poses on the screen.
				win.clear_overlay();
				win.set_image(img);
				win.add_overlay(render_face_detections(shapes));
				win.add_overlay(render_face_detections_lines(shapes));

				//win.set_title("Emotions = Happy(CF = 0.97)");

				// We can also extract copies of each face that are cropped, rotated upright,
				// and scaled to a standard size as shown here:
			//	dlib::array<array2d<rgb_pixel> > face_chips;
			//	dlib::extract_image_chips(img, get_face_chip_details(shapes), face_chips);
			//	win_faces.set_image(tile_images(face_chips));

				std::cout << "Hit enter to process the next image..." << endl;
				//sleep(1000);
				std::cin.get();
			}
		}
	}
	catch (exception& e)
	{
		std::cout << "\nexception thrown!" << endl;
		std::cout << e.what() << endl;
	}
	getchar();
}

// ----------------------------------------------------------------------------------------

// -------------------------
int main_Kiavash(int argc, char** argv)
{

	try
	{
		cv::VideoCapture webcam(0);
		if (!webcam.isOpened())
		{
			cerr << "Unable to connect to camera" << endl;
			return 1;
		}
		image_window win;

		// Load face detection and pose estimation models.
		frontal_face_detector detector = get_frontal_face_detector();
		shape_predictor pose_model;
		deserialize("C:\\Users\\kbh\\Desktop\\dlib-master\\examples\\build\\Debug\\shape_predictor_68_face_landmarks.dat") >> pose_model;

		// Grab and process frames until the main window is closed by the user.
		while (!win.is_closed())
		{
			// Grab a frame
			cv::Mat temp;
			webcam >> temp;
			// Turn OpenCV's Mat into something dlib can deal with.  Note that this just
			// wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
			// long as temp is valid.  Also don't do anything to temp that would cause it
			// to reallocate the memory which stores the image as that will make cimg
			// contain dangling pointers.  This basically means you shouldn't modify temp
			// while using cimg.
			cv_image<bgr_pixel> cimg(temp);

			//Rotate cimg to img
			array2d<rgb_pixel> img;
			assign_image(img, cimg);
			flip_image_left_right(cimg, img);

			//Use img insted of cimg to rotate the image

			// Detect faces
			std::vector<rectangle> faces = detector(img);
			// Find the pose of each face.
			std::vector<full_object_detection> shapes;
			for (unsigned long i = 0; i < faces.size(); ++i)
				shapes.push_back(pose_model(img, faces[i]));

			//cout << "" << faces[0];
			//unsigned long height1 = faces[0].height;
			// Display it all on the screen
			win.clear_overlay();
			win.set_image(img);
			win.add_overlay(render_face_detections(shapes));
			win.add_overlay(render_face_detections_lines(shapes));

			//win.get_display_size(width1,height1);


			//cv::Mat d;

			//char *inputModel="face2.tracker";
			//FACETRACKER::Tracker model(inputModel);
			//d = model._clm._pdm._M + model._clm._pdm._V * model._clm._plocal;

			const char *fn = "c:\\detected.jpg";
			dlib::array2d<dlib::rgb_pixel> img_rgb;
			dlib::load_image(img_rgb, "c:\\loaded.jpg");
			dlib::array2d<unsigned char> img_gray;
			//dlib::resize_image(img_rgb, img_gray);
			//array2d<rgb_pixel> img;
			//dlib::load_image(img, "c:\\loaded.jpg");
			//dlib::cv_image<bgr_pixel> cimg(array2d<rgb_pixel> img);
			dlib::assign_image(img_gray, img_rgb);
			//std::vector<dlib::full_object_detection> shapes;
			//dlib::extract_image_chips(cimg, dlib::get_face_chip_details(shapes), img_gray);
			//img_gray.set_size(600, 800);
			flip_image_left_right(img_rgb, img_gray);
			dlib::save_jpeg(img_gray, fn);
		}
	}
	catch (serialization_error& e)
	{
		cout << "You need dlib's default face landmarking model file to run this example." << endl;
		cout << "You can get it from the following URL: " << endl;
		cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
		cout << endl << e.what() << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	//try
	//{
	//	// This example takes in a shape model file and then a list of images to
	//	// process.  We will take these filenames in as command line arguments.
	//	// Dlib comes with example images in the examples/faces folder so give
	//	// those as arguments to this program.
	//	if (argc == 1)
	//	{
	//		std::cout << "Call this program like this:" << endl;
	//		std::cout << "./face_landmark_detection_ex shape_predictor_68_face_landmarks.dat faces/*.jpg" << endl;
	//		std::cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
	//		std::cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
	//		return 0;
	//	}

	//	clock_t tStart = clock();

	//	// We need a face detector.  We will use this to get bounding boxes for
	//	// each face in an image.
	//	frontal_face_detector detector;
	//	speedtest___("get_frontal_face_detector: ")
	//	{
	//		detector = get_frontal_face_detector();
	//	}
	//	// And we also need a shape_predictor.  This is the tool that will predict face
	//	// landmark positions given an image and face bounding box.  Here we are just
	//	// loading the model from the shape_predictor_68_face_landmarks.dat file you gave
	//	// as a command line argument.
	//	shape_predictor sp;
	//	speedtest___("deserialize database: ")
	//	{
	//		deserialize(argv[1]) >> sp;
	//	}

	//	image_window win, win_faces;
	//	// Loop over all the images provided on the command line.
	//	for (int i = 2; i < argc; ++i)
	//	{
	//		std::cout << "processing image " << argv[i] << endl;
	//		array2d<rgb_pixel> img;
	//		load_image(img, argv[i]);
	//		// Make the image larger so we can detect small faces.
	//		pyramid_up(img);

	//		// Now tell the face detector to give us a list of bounding boxes
	//		// around all the faces in the image.
	//		std::vector<dlib::rectangle> dets;
	//		speedtest___("detect faces: ")
	//		{
	//			dets = detector(img);
	//		}
	//		std::cout << "Number of faces detected: " << dets.size() << endl;

	//		// Now we will go ask the shape_predictor to tell us the pose of
	//		// each face we detected.
	//		std::vector<full_object_detection> shapes;
	//		speedtest___("detect features: ")
	//		{
	//			for (unsigned long j = 0; j < dets.size(); ++j)
	//			{
	//				full_object_detection shape = sp(img, dets[j]);
	//				std::cout << "number of parts: " << shape.num_parts() << endl;
	//				std::cout << "pixel position of first part:  " << shape.part(0) << endl;
	//				std::cout << "pixel position of second part: " << shape.part(1) << endl;
	//				// You get the idea, you can get all the face part locations if
	//				// you want them.  Here we just store them in shapes so we can
	//				// put them on the screen.
	//				shapes.push_back(shape);
	//			}
	//		}

	//		// Now let's view our face poses on the screen.
	//		win.clear_overlay();
	//		win.set_image(img);
	//		win.add_overlay(render_face_detections(shapes));

	//		// We can also extract copies of each face that are cropped, rotated upright,
	//		// and scaled to a standard size as shown here:
	//		dlib::array<array2d<rgb_pixel> > face_chips;
	//		dlib::extract_image_chips(img, get_face_chip_details(shapes), face_chips);
	//		win_faces.set_image(tile_images(face_chips));

	//		std::cout << "Hit enter to process the next image..." << endl;
	//		std::cin.get();
	//	}
	//}
	//catch (exception& e)
	//{
	//	std::cout << "\nexception thrown!" << endl;
	//	std::cout << e.what() << endl;
	//}
}

// ----------------------------------------------------------------------------------------
