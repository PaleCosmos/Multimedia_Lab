import cv2
import numpy as np
import math
from object_module import *
import sys
import aruco

A = [[1019.37187, 0, 618.709848], [0, 1024.2138, 327.280578], [0, 0, 1]]
A = np.array(A)

obj = three_d_object('data/3d_objects/a.obj', 'data/3d_objects/a.png')


def get_extended_RT(A, H):
	H = np.float64(H)
	A = np.float64(A)
	R_12_T = np.linalg.inv(A).dot(H)

	r1 = np.float64(R_12_T[:, 0])
	r2 = np.float64(R_12_T[:, 1])
	T = R_12_T[:, 2]

	norm = np.float64(math.sqrt(np.float64(np.linalg.norm(r1))
                             * np.float64(np.linalg.norm(r2))))

	r3 = np.cross(r1, r2)/(norm)
	R_T = np.zeros((3, 4))
	R_T[:, 0] = r1
	R_T[:, 1] = r2
	R_T[:, 2] = r3
	R_T[:, 3] = T
	return R_T


def main():
	marker_colored = cv2.imread('data/m1_flip_new.png')
	marker_colored = cv2.resize(
		marker_colored, (480, 480), interpolation=cv2.INTER_CUBIC)
	marker = cv2.cvtColor(marker_colored, cv2.COLOR_BGR2GRAY)

	cv2.namedWindow("webcam")
	vc = cv2.VideoCapture(0)

	h, w = marker.shape
	marker_sig1 = aruco.get_bit_sig(marker, np.array(
		[[0, 0], [0, w], [h, w], [h, 0]]).reshape(4, 1, 2))
	marker_sig2 = aruco.get_bit_sig(marker, np.array(
		[[0, w], [h, w], [h, 0], [0, 0]]).reshape(4, 1, 2))
	marker_sig3 = aruco.get_bit_sig(marker, np.array(
		[[h, w], [h, 0], [0, 0], [0, w]]).reshape(4, 1, 2))
	marker_sig4 = aruco.get_bit_sig(marker, np.array(
		[[h, 0], [0, 0], [0, w], [h, w]]).reshape(4, 1, 2))

	sigs = [marker_sig1, marker_sig2, marker_sig3, marker_sig4]

	rval, frame = vc.read()
	h2, w2,  _ = frame.shape

	h_canvas = max(h, h2)
	w_canvas = w + w2

	while rval:
		rval, frame = vc.read()
		key = cv2.waitKey(20)
		if key == 27:
			break

		canvas = np.zeros((h_canvas, w_canvas, 3), np.uint8)
		canvas[:h, :w, :] = marker_colored

		success, H = aruco.find_homography_aruco(frame, marker, sigs)
		if not success:
			canvas[:h2, w:, :] = np.flip(frame, axis=1)
			cv2.imshow("webcam", canvas)
			print("no")
			continue

		print("yes")
		R_T = get_extended_RT(A, H)
		transformation = A.dot(R_T)

		# flipped for better control
		augmented = np.flip(
			augment(frame, obj, transformation, marker, True), axis=1)
		canvas[:h2, w:, :] = augmented
		cv2.imshow("webcam", canvas)


if __name__ == '__main__':
	main()
