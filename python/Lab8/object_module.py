import cv2
import numpy as np


def augment(img, obj, projection, template, color=False, scale=4):
    h, w = template.shape
    vertices = obj.vertices
    img = np.ascontiguousarray(img, dtype=np.uint8)

    a = np.array([[0, 0, 0], [w, 0, 0],  [w, h, 0],  [0, h, 0]], np.float64)
    imgpts = np.int32(cv2.perspectiveTransform(
        a.reshape(-1, 1, 3), projection))
    cv2.fillConvexPoly(img, imgpts, (0, 0, 0))

    for face in obj.faces:
        face_vertices = face[0]
        points = np.array([vertices[vertex - 1] for vertex in face_vertices])
        points = scale*points
        points = np.array([[p[2] + w/2, p[0] + h/2, p[1]] for p in points])
        dst = cv2.perspectiveTransform(points.reshape(-1, 1, 3), projection)
        imgpts = np.int32(dst)
        if color is False:
            cv2.fillConvexPoly(img, imgpts, (50, 50, 50))
        else:
            cv2.fillConvexPoly(img, imgpts, face[-1])

    return img


class three_d_object:
    def __init__(self, filename_obj, filename_texture, color_fixed=False):
        self.texture = cv2.imread(filename_texture)
        self.vertices = []
        self.faces = []
        self.texcoords = []

        for line in open(filename_obj, "r"):
            if line.startswith('#'):
                continue

            values = line.split()
            if not values:
                continue

            if values[0] == 'v':
                v = [float(a) for a in values[1:4]]
                self.vertices.append(v)

            elif values[0] == 'vt':
                self.texcoords.append([float(a) for a in values[1:3]])

            elif values[0] == 'f':
                face_vertices = []
                face_texcoords = []
                for v in values[1:]:
                    w = v.split('/')
                    face_vertices.append(int(w[0]))
                    if len(w) >= 2 and len(w[1]) > 0:
                        face_texcoords.append(int(w[1]))
                    else:
                        color_fixed = True
                        face_texcoords.append(0)
                self.faces.append([face_vertices, face_texcoords])

        for f in self.faces:
            if not color_fixed:
                f.append(three_d_object.decide_face_color(
                    f[-1], self.texture, self.texcoords))
            else:
                f.append((50, 50, 50))

    def decide_face_color(hex_color, texture, textures):
        h, w, _ = texture.shape
        col = np.zeros(3)
        coord = np.zeros(2)
        all_us = []
        all_vs = []

        for i in hex_color:
            t = textures[i - 1]
            coord = np.array([t[0], t[1]])
            u, v = int(w*(t[0]) - 0.0001), int(h*(1-t[1]) - 0.0001)
            all_us.append(u)
            all_vs.append(v)

        u = int(sum(all_us)/len(all_us))
        v = int(sum(all_vs)/len(all_vs))

        col = np.uint8(texture[v, u])
        col = [int(a) for a in col]
        col = tuple(col)
        return (col)
