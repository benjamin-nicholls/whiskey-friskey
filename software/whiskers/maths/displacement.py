import sys
import math

# TODO convert XYZ displacement into a linear value
# Which method to use-- unsure.


def convert_XYZ_to_linear_displacement(X, Y, Z):
    return


def euclidian_distance_from_origin(x2, y2=None, z2=None):
    x1, y1, z1 = 0  # Origin.
    # No given values.
    if x2==None and y2==None and z2==None:
        return None
    # 1d.
    if y2==None and z2==None:
        return abs(x2 - x1)
    # 2d.
    if z2==None:
        return math.sqrt((x2-x1)**2 + (y2-y1)**2)
    #3d.
    return math.sqrt((x2-x1)**2 + (y2-y1)**2 + (z2-z1)**2)


def main(argv):
    print(f'{argv[0]} has no implementation yet.')
    return


if __name__ == '__main__':
    main(sys.argv)