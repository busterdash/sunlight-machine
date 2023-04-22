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

/// A point in 3D space
#[derive(Default, Copy, Clone)]
pub struct Vertex {
    /// X-position of the vertex in world space
    pub x: f64,
    /// Y-position of the vertex in world space
    pub y: f64,
    /// Z-position of the vertex in world space
    pub z: f64,
    /// X-direction of the vertex normal
    pub nx: f64,
    /// Y-direction of the vertex normal
    pub ny: f64,
    /// Z-direction of the vertex normal
    pub nz: f64,
    /// X-coordinate of the vertex's position on a texture
    pub u: f64,
    /// Y-coordinate of the vertex's position on a texture
    pub v: f64
}

impl Vertex {
    /// Creates a new [Vertex] with all coordinates set.
    pub fn new(x: f64, y: f64, z: f64, nx: f64, ny: f64, nz: f64, u: f64, v: f64) -> Self {
        Self { x, y, z, nx, ny, nz, u, v }
    }

    /// Creates a new [Vertex] with only positional coordinates set.
    pub fn new_pos(x: f64, y: f64, z: f64) -> Self {
        let mut v = Self::default();
        v.x = x;
        v.y = y;
        v.z = z;
        return v;
    }
}

/// A triangle in 3D space represented by three [Vertex] instances
pub struct Triangle {
    /// List of vertices comprising the triangle
    pub v: [Vertex; 3]
}

impl Triangle {
    /// Creates a new triangle using three [Vertex] instances
    pub fn new(v1: Vertex, v2: Vertex, v3: Vertex) -> Self {
        Self { v: [v1, v2, v3] }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn triangle_construction() {
        let v: [Vertex; 3] = [
            Vertex::new_pos(0.0, 1.0, 2.0),
            Vertex::new_pos(3.0, 4.0, 5.0),
            Vertex::new_pos(6.0, 7.0, 8.0)
        ];
        let t = Triangle::new(v[0], v[1], v[2]);
        for i in 0 .. 3 {
            assert_eq!(t.v[i].x, (i * 3 + 0) as f64);
            assert_eq!(t.v[i].y, (i * 3 + 1) as f64);
            assert_eq!(t.v[i].z, (i * 3 + 2) as f64);
        }
    }
}