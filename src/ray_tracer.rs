/*==============================================================================

    ray_tracer.rs
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

use crate::geometry::*;

fn alpha_beta_to_cartesian(a: Vertex, b: Vertex, percent: f64) -> (f64, f64) {
    let dist = a.dist_2d(b);
    let dist_seg = dist * percent;
    return (
        (b.x - a.x) * dist_seg / dist + a.x,
        (b.y - a.y) * dist_seg / dist + a.y
    );
}

/// Derived from C code available at [Lighthouse3d](http://www.lighthouse3d.com/tutorials/maths/ray-triangle-intersection/)
fn process_intersection(ray: VertexGroup, tri: Triangle) -> Option<f64> {
    let mut dist: f64 = 64.0;

    let e1: Vector3D = Vector3D::from_vertices(tri.v[1].position, tri.v[0].position);
    let e2: Vector3D = Vector3D::from_vertices(tri.v[2].position, tri.v[0].position);

    let h: Vector3D = Vector3D::cross_product(ray.normal, e2);
    let a: f64 = Vector3D::dot_product(e1, h);

    if a > -0.00001 && a < 0.00001 {
        return Option::None;
    }

    let f: f64 = 1.0 / a;
    let s: Vector3D = Vector3D::from_vertices(ray.position, tri.v[0].position);
    let u: f64 = f * Vector3D::dot_product(s, h);

    if u < 0.0 || u > 1.0 {
        return Option::None;
    }

    let q: Vector3D = Vector3D::cross_product(s, e1);
    let v: f64 = f * Vector3D::dot_product(ray.normal, q);

    if v < 0.0 || u + v > 1.0 {
        return Option::None;
    }

    // At this stage, we compute dist to find out where intersection point is
    // on a line.
    dist = f * Vector3D::dot_product(e2, q);

    // If the condition below is true, ray intersection; else, line
    // intersection.
    return if dist > 0.00001 { Option::Some(dist) } else { None };
}

pub fn get_intersection(ray: VertexGroup, tri: Triangle) -> Option<(Vertex, f64)> {
    let dist = match process_intersection(ray, tri) {
        Option::Some(d) => d,
        Option::None => return Option::None
    };
    return Option::Some((
        Vertex::new(
            ray.position.x + ray.normal.x * dist,
            ray.position.y + ray.normal.y * dist,
            ray.position.z + ray.normal.z * dist
        ),
        dist
    ));
}

pub fn transform_trace_to_uv(t: Triangle, hit: &mut Vertex) {
    let mut tri_len: [f64; 3] = [0.0; 3];
    let mut hit_len: [f64; 2] = [0.0; 2];

    // Calculate distances between triangle sides and hit positions. This
    // flattens the triangle to 2D space for textures.
    tri_len[0] = t.v[1].position.dist_3d(t.v[2].position);
    tri_len[1] = t.v[0].position.dist_3d(t.v[2].position);
    tri_len[2] = t.v[0].position.dist_3d(t.v[1].position);
    hit_len[0] = t.v[0].position.dist_3d(*hit);
    hit_len[1] = t.v[1].position.dist_3d(*hit);

    // Calculate alpha and beta.
    let aa: f64 = (
        (tri_len[2].powf(2.0) + hit_len[0].powf(2.0) - hit_len[1].powf(2.0))
        / (2.0 * tri_len[2] * hit_len[0])
    ).acos(); // angle in radians
    let ab: f64 = (
        (tri_len[0].powf(2.0) + tri_len[2].powf(2.0) - tri_len[1].powf(2.0))
        / (2.0 * tri_len[0] * tri_len[2])
    ).acos(); // angle in radians
    let ad: f64 = deg_to_rad(180.0 - rad_to_deg(aa) - rad_to_deg(ab)); // angle in radians
    let ida: f64 = (tri_len[2] * ab.sin()) / ad.sin();
    let ie: f64 = (tri_len[2] * aa.sin()) / ad.sin();
    let alpha: f64 = hit_len[0] / ida;
    let beta: f64 = ie / tri_len[0];

    // Convert alpha and beta to UV coordinates
    (hit.x, hit.y) = alpha_beta_to_cartesian(t.v[1].texture, t.v[2].texture, beta);
    (hit.x, hit.y) = alpha_beta_to_cartesian(t.v[0].texture, *hit, alpha);
}