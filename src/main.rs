/*==============================================================================

	main.rs
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

#![doc = include_str!("../README.md")]

mod geometry;
mod smd_reader;

use smd_reader::*;

fn main() {
    let smdr = SMDReader::new("assets/cube.smd");
    println!(
        "Max radius: {}, triangle count: {}",
        smdr.get_max_coordinate(),
        smdr.get_triangle_count()
    );
}
