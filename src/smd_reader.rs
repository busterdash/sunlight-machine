/*==============================================================================

    smd_reader.rs
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

use std::{fs::File, io::BufRead, io::BufReader};

use crate::geometry::*;

pub struct SMDReader {
    tri_list: Vec<Triangle>
}

impl SMDReader {
    /// Parses a single geometry line from a SMD file.
    fn parse_line(line: &str) -> VertexGroup {
        let mut data_position: usize = 0;
        let mut line_data: [f64; 10] = [0.0; 10];
        let mut buffer: String = String::new();
        let mut last_char_is_space: bool = false; // for double spaces
        let bytes = line.as_bytes();
        for i in 0 .. bytes.len() {
            if bytes[i] != b' ' && bytes[i] != b'\t' {
                buffer.push(bytes[i] as char);
                last_char_is_space = false;
            } else {
                if last_char_is_space {
                    continue;
                }
                line_data[data_position] = buffer.parse().unwrap();
                data_position += 1;
                last_char_is_space = true;
                buffer.clear();
            }
        }
        return VertexGroup::new(
            line_data[1],
            line_data[2],
            line_data[3],
            line_data[4],
            line_data[5],
            line_data[6],
            line_data[7],
            line_data[8]
        )
    }

    /// Creates a new instance of this ridiculous singleton.
    pub fn new(smd_path: &str) -> Self {
        let mut tri_list: Vec<Triangle> = Vec::new();

        let mut line: String;
        let mut triangles: bool = false;
        let mut counter: u32 = 0;
        let mut vertex_counter: usize = 0;
        let mut vbuffer: [VertexGroup; 3] = [VertexGroup::default(); 3];

        let file = File::open(smd_path).unwrap();
        let read = BufReader::new(file);

        for (_i, l) in read.lines().enumerate() {
            line = l.unwrap();
            if !triangles && line == "triangles" {
                triangles = true;
                continue;
            }

            if triangles {
                counter += 1;

                if counter == 1 { // skip the first material definition
                    continue;
                }

                if line.len() <= 2 { // ignore empty lines (CRLF or LF)
                    continue;
                }

                if line[0..2] == "0 ".to_string() {
                    vbuffer[vertex_counter] = Self::parse_line(line.as_str());
                    vertex_counter += 1;
                } else {
                    tri_list.push(Triangle::new(
                        vbuffer[0],
                        vbuffer[1],
                        vbuffer[2]
                    ));
                    vertex_counter = 0;
                }
            }
        }

        return Self { tri_list };
    }

    /// Returns a triangle at a specific index.
    pub fn get_triangle(&self, index: usize) -> Option<&Triangle> {
        if index >= self.tri_list.len() {
            Option::None
        } else {
            Option::Some(&self.tri_list[index])
        }
    }

    /// Returns a model's bounding radius.
    pub fn get_max_coordinate(&self) -> f64 {
        let mut max: f64 = -1.0;

        for i in 0 .. self.get_triangle_count() { 
            for j in 0 .. 3 {
                if self.tri_list[i].v[j].position.x > max {
                    max = self.tri_list[i].v[j].position.x;
                }
                
                if self.tri_list[i].v[j].position.y > max {
                    max = self.tri_list[i].v[j].position.y;
                }
                
                if self.tri_list[i].v[j].position.z > max {
                    max = self.tri_list[i].v[j].position.z;
                }
            }
        }

        return max;
    }

    /// Returns a model's triangle quantity.
    pub fn get_triangle_count(&self) -> usize {
        self.tri_list.len()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn line_parsing() {
        let v = SMDReader::parse_line(
            "0  -1.000000 -2.000000 -3.000000  -4.000000 -5.000000 -6.000000  -7.000000 -8.000000 0"
        );
        assert_eq!(v.position.x, -1.0);
        assert_eq!(v.position.y, -2.0);
        assert_eq!(v.position.z, -3.0);
        assert_eq!(v.normal.x, -4.0);
        assert_eq!(v.normal.y, -5.0);
        assert_eq!(v.normal.z, -6.0);
        assert_eq!(v.texture.x, -7.0);
        assert_eq!(v.texture.y, -8.0);
    }
}