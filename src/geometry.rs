/*==============================================================================

    geometry.rs
    Copyright 2023 Buster Schrader

    This file is part of The Sunlight Machine.

    The Sunlight Machine is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    The Sunlight Machine is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with The Sunlight Machine.  If not, see
    <https://www.gnu.org/licenses/>.
    
==============================================================================*/

/// Converts angles represented as degrees to angles represented as radians.
pub fn deg_to_rad(degrees: f64) -> f64 {
    degrees * (std::f64::consts::PI / 180.0)
}

/// Converts angles represented as radians to angles represented as degrees.
pub fn rad_to_deg(radians: f64) -> f64 {
    (radians / std::f64::consts::PI) * 180.0
}

/// A point in 3D space
#[derive(Default, Copy, Clone)]
pub struct Vertex {
    /// X-position of the vertex
    pub x: f64,
    /// Y-position of the vertex
    pub y: f64,
    /// Z-position of the vertex
    pub z: f64
}

impl Vertex {
    /// Creates a new [Vertex] instance.
    pub fn new(x: f64, y: f64, z: f64) -> Self {
        Self { x, y, z }
    }

    /// Gets the three-dimensional distance between this vertex and another.
    pub fn dist_3d(&self, other: Vertex) -> f64 {
        ((self.x - other.x).powf(2.0) + (self.y - other.y).powf(2.0) + (self.z - other.z).powf(2.0)).sqrt()
    }

    /// Gets the two-dimensional (XY) distance between this vertex and another.
    pub fn dist_2d(&self, other: Vertex) -> f64 {
        ((self.x - other.x).powf(2.0) + (self.y - other.y).powf(2.0)).sqrt()
    }

    /// Rotates this vertex about the origin's Y-axis.
    pub fn rotate_y(&mut self, angle: f64) -> Self {
        let o: Vertex = self.clone();
        let rad: f64 = deg_to_rad(angle);
        let pc: f64 = rad.cos();
        let ps: f64 = rad.sin();
        self.x = (o.x * pc) + (o.z * ps);
        self.z = (o.x * -ps) + (o.z * pc);
        return *self;
    }

    /// Rotates this vertex about the origin's Z-axis.
    pub fn rotate_z(&mut self, angle: f64) -> Self{
        let o: Vertex = self.clone();
        let rad: f64 = deg_to_rad(angle);
        let pc: f64 = rad.cos();
        let ps: f64 = rad.sin();
        self.x = (o.x * pc) + (o.y * -ps);
        self.y = (o.x * ps) + (o.y * pc);
        return *self;
    }
}

/// An object with direction and magnitude.
///
/// In the case of surface normals; they are preferred normalized, indicating
/// their magnitude should always be 1.
#[derive(Default, Copy, Clone)]
pub struct Vector3D {
    /// Magnitude in the X-direction
    pub x: f64,
    /// Magnitude in the Y-direction
    pub y: f64,
    /// Magnitude in the Z-direction
    pub z: f64
}

impl Vector3D {
    /// Returns the cross product of two vectors.
    pub fn cross_product(a: Self, b: Self) -> Self {
        Self::new(
            a.y * b.z - b.y * a.z,
            a.z * b.x - b.z * a.x,
            a.x * b.y - b.x * a.y
        )
    }

    /// Returns the dot product of two vectors.
    pub fn dot_product(a: Self, b: Self) -> f64 {
        a.x * b.x + a.y * b.y + a.z * b.z
    }

    /// Creates a new [Vector3D] instance.
    pub fn new(x: f64, y: f64, z: f64) -> Self {
        Self { x, y, z }
    }

    /// Creates a new [Vector3D] instance derived from two [Vertex] instances.
    pub fn from_vertices(a: Vertex, b: Vertex) -> Self {
        Self::new(a.x - b.x, a.y - b.y, a.z - b.z)
    }
}

/// A relationship between vertices representing the same point but in different
/// dimensions.
#[derive(Copy, Clone)]
pub struct VertexGroup {
    pub position: Vertex,
    pub normal: Vector3D,
    pub texture: Vertex
}

impl VertexGroup {
    /// Builds a [VertexGroup] from raw coordinate values.
    ///
    /// # Arguments:
    /// * `x`, `y`, `z` - World-space positional coordinates
    /// * `nx`, `ny`, `nz` - Surface normal vector magnitudes
    /// * `u`, `v` - Texture map coordinates
    pub fn new(x: f64, y: f64, z: f64, nx: f64, ny: f64, nz: f64, u: f64, v: f64) -> Self {
        Self {
            position: Vertex::new(x, y, z),
            normal: Vector3D::new(nx, ny, nz),
            texture: Vertex::new(u, v, 0.0)
        }
    }

    /// Builds a [VertexGroup] from existing elements.
    pub fn combine(position: Vertex, normal: Vector3D, texture: Vertex) -> Self {
        Self { position, normal, texture }
    }
}

// TODO: Replace with derived trait if this behaves this way by default.
impl Default for VertexGroup {
    fn default() -> Self {
        Self {
            position: Vertex::default(),
            normal: Vector3D::default(),
            texture: Vertex::default()
        }
    }
}

/// A triangle in 3D space represented by three [VertexGroup] instances
pub struct Triangle {
    /// List of vertices comprising the triangle.
    pub v: [VertexGroup; 3]
}

impl Triangle {
    /// Creates a new triangle using three [VertexGroup] instances.
    pub fn new(v1: VertexGroup, v2: VertexGroup, v3: VertexGroup) -> Self {
        Self { v: [v1, v2, v3] }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    const ACC: i8 = 8;

    fn epsilon(value: f64, accuracy: i8) -> f64 {
        (value * 10_f64.powf(accuracy as f64)).floor() * 10_f64.powf(-accuracy as f64)
    }

    #[test]
    fn triangle_construction() {
        let normal = Vector3D::new(0.0, 0.0, 0.0);
        let texture = Vertex::new(0.0, 0.0, 0.0);
        let v: [VertexGroup; 3] = [
            VertexGroup::combine(Vertex::new(0.0, 1.0, 2.0), normal, texture),
            VertexGroup::combine(Vertex::new(3.0, 4.0, 5.0), normal, texture),
            VertexGroup::combine(Vertex::new(6.0, 7.0, 8.0), normal, texture)
        ];
        let t = Triangle::new(v[0], v[1], v[2]);
        for i in 0 .. 3 {
            assert_eq!(t.v[i].position.x, (i * 3 + 0) as f64);
            assert_eq!(t.v[i].position.y, (i * 3 + 1) as f64);
            assert_eq!(t.v[i].position.z, (i * 3 + 2) as f64);
        }
    }

    #[test]
    fn degree_radian_conversion() {
        assert_eq!(rad_to_deg(deg_to_rad(180.0)), 180.0);
    }

    #[test]
    fn vertex_distance_formulas() {
        assert_eq!(
            epsilon(Vertex::new(18.0, -31.0, 93.0).dist_2d(Vertex::new(-77.0, -11.0, 55.0)), ACC),
            epsilon(97.082439195, ACC)
        );
        assert_eq!(
            epsilon(Vertex::new(8.0, 19.0, 12.0).dist_3d(Vertex::new(-52.0, 32.0, -92.0)), ACC),
            epsilon(120.768373343, ACC)
        );
    }

    #[test]
    fn vertex_rotation() {
        let mut v = Vertex::new(3.0, 4.0, 5.0);
        v.rotate_z(90.0);
        assert_eq!(epsilon(v.x, ACC), -4.0);
        assert_eq!(epsilon(v.y, ACC), 3.0);
        assert_eq!(epsilon(v.z, ACC), 5.0);
        v.rotate_y(90.0);
        assert_eq!(epsilon(v.x, ACC), 5.0);
        assert_eq!(epsilon(v.y, ACC), 3.0);
        assert_eq!(epsilon(v.z, ACC), 4.0);
    }

    #[test]
    fn vector_dot_product() {
        assert_eq!(
            epsilon(Vector3D::dot_product(
                Vector3D::new(-0.392725, 0.000000, 0.919656),
                Vector3D::new(0.653218, 0.655690, 0.378582)
            ), ACC),
            epsilon(0.091630169, ACC)
        );
    }

    #[test]
    fn vector_cross_product() {
        let v = Vector3D::cross_product(
            Vector3D::new(-1.0, 0.0, 0.0),
            Vector3D::new(0.0, -1.0, 0.0)
        );
        // right-hand rule
        assert_eq!(v.x, 0.0);
        assert_eq!(v.y, 0.0);
        assert_eq!(v.z, 1.0);
    }
}