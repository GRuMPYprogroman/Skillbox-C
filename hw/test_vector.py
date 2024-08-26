import unittest
import SmartPtr_hw

class TestVector3D(unittest.TestCase):

    def test_addition(self):
        vec1 = SmartPtr_hw.Vector3D(1.0, 2.0, 3.0)
        vec2 = SmartPtr_hw.Vector3D(4.0, 5.0, 6.0)
        vec3 = vec1.plus_product(vec2)
        self.assertEqual(vec3.get_coords(), (5.0, 7.0, 9.0))

    def test_subtraction(self):
        vec1 = SmartPtr_hw.Vector3D(1.0, 2.0, 3.0)
        vec2 = SmartPtr_hw.Vector3D(4.0, 5.0, 6.0)
        vec3 = vec1.minus_product(vec2)
        self.assertEqual(vec3.get_coords(), (-3.0, -3.0, -3.0))

    def test_dot_product(self):
        vec1 = SmartPtr_hw.Vector3D(1.0, 2.0, 3.0)
        vec2 = SmartPtr_hw.Vector3D(4.0, 5.0, 6.0)
        result = vec1.dot_product(vec2)
        self.assertEqual(result, 32.0)

    def test_length(self):
        vec = SmartPtr_hw.Vector3D(3.0, 4.0, 0.0)
        self.assertEqual(vec.length(), 5.0)

    def test_normalize(self):
        vec = SmartPtr_hw.Vector3D(3.0, 4.0, 0.0)
        vec.normalize()
        coords = vec.get_coords()
        self.assertAlmostEqual(coords[0], 0.6, places=7)
        self.assertAlmostEqual(coords[1], 0.8, places=7)
        self.assertAlmostEqual(coords[2], 0.0, places=7)

if __name__ == '__main__':
    unittest.main()