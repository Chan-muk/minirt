/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:50:27 by chajung           #+#    #+#             */
/*   Updated: 2023/05/26 10:50:28 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// typedef struct {
//     float x;
//     float y;
// } vec2;

// typedef struct {
//     float x;
//     float y;
//     float z;
// } vec3;

// vec3 checkerboard(vec2 p, float size) {
//     p.x *= size;
//     p.y *= size;
//     vec2 f = (vec2){fract(p.x), fract(p.y)} - (vec2){0.5, 0.5};
//     return (vec3){f.x * f.y > 0.0 ? 1.0 : 0.0};
// }

// vec3 objcolor(vec3 p) {
//     return checkerboard((vec2){p.x, p.z}, 0.4);
// }

// void mainImage(vec4* fragColor, vec2 fragCoord, vec2 iResolution) {
//     vec2 uv = (fragCoord - (vec2){iResolution.x / 2.0, iResolution.y / 2.0}) / iResolution.y;
//     uv.x *= iResolution.x / iResolution.y;

//     // Camera
//     vec3 lookat = (vec3){0.0, 0.0, 0.0};
//     vec3 cam = (vec3){0.0, 0.0, 1.0};
//     vec3 up = (vec3){0.0, 1.0, 0.0};

//     float camdist = 2.0;
//     float camsize = 2.0;
//     float maxdist = 50.0;
//     float preci = 0.001;

//     vec3 v = cam - lookat;
//     vec3 camx = normalize((vec3){up.y * v.z - up.z * v.y, up.z * v.x - up.x * v.z, up.x * v.y - up.y * v.x}) * camsize;
//     vec3 camy = normalize((vec3){v.y * camx.z - v.z * camx.y, v.z * camx.x - v.x * camx.z, v.x * camx.y - v.y * camx.x}) * camsize;

//     vec3 campoint = cam - normalize(v) * camdist + camx * uv.x + camy * uv.y;

//     vec3 ray = normalize(campoint - cam);

//     float s = (-2.0 - campoint.y) / ray.y;
//     if (s < 0.0)
//         s = (1.0 - campoint.y) / ray.y;
//     vec3 p = campoint + ray * s;

//     float fadeout = fmaxf(maxdist - s, 0.0) / maxdist;
//     *fragColor = (vec4){objcolor(p).x * fadeout, objcolor(p).y * fadeout, objcolor(p).z * fadeout, 1.0};
// }

// t_color	plane_checkerboard(t_vector p)
// {
// 	double	u;
// 	double	v;

// 	printf("x: %f, y: %f, z: %f\n", p.x, -p.y, p.z);

// 	u = (atan2(-p.z, p.x) + M_PI) / (2 * M_PI);
// 	v = acos(-p.y) / M_PI;

// 	double sines = sin(2*p.x)*sin(2*p.y)*sin(2*p.z);
// 	if (sines < 0)
// 		return (new_color(1, 1, 1));
// 	else
// 		return (new_color(0, 0, 0));
// }

double _fract(double x) {
    return x - floor(x);
}

t_color	plane_checkerboard(t_vector p)
{
	// double	u = _fract(p.x * 0.2) - 0.5;
	// double	v = _fract(p.y * 0.4) - 0.5;

	double	u = _fract(p.x * 0.2) - 0.5;
	double	v = _fract(p.y * 0.4) - 0.5;

	if (u * v > 0.0)
		return (new_vec(1.0, 1.0, 1.0));
	return (new_vec(0, 0, 0));
}

bool	hit_plane(t_hit_array* pl, t_ray *ray, t_hit_record *rec)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(ray->dir, pl->norm);
	if (fabs(denominator) < rec->tmin)
		return (false);
	numrator = vec_dot(vec_sub(pl->center, ray->org), pl->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (false);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->norm;
	set_face_normal(ray, rec);
	// rec->albedo = pl->albedo;
	rec->albedo = plane_checkerboard(rec->p);
	return (true);
}
