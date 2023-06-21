#include "minirt.h"

t_vector bumprotateVector(t_vector normal, t_vector bump_vec)
{
	t_vector standard = {0, 0, 1};
	if (normal.x == standard.x && normal.y == standard.y && normal.z == standard.z)
		return (unit_vec(bump_vec));
	normal = unit_vec(normal);
	bump_vec = unit_vec(bump_vec);

	// Calculate rotation axis vector
	t_vector axis = vec_prod(standard, normal);
	axis = unit_vec(axis);

	// Calculate the angle between the two vectors
	double theta = acos(vec_dot(standard, normal));

	// Calculate the rotation matrix
	double rotationMatrix[3][3] = {
		{cos(theta) + axis.x * axis.x * (1 - cos(theta)), axis.x * axis.y * (1 - cos(theta)) - axis.z * sin(theta), axis.x * axis.z * (1 - cos(theta)) + axis.y * sin(theta)},
		{axis.y * axis.x * (1 - cos(theta)) + axis.z * sin(theta), cos(theta) + axis.y * axis.y * (1 - cos(theta)), axis.y * axis.z * (1 - cos(theta)) - axis.x * sin(theta)},
		{axis.z * axis.x * (1 - cos(theta)) - axis.y * sin(theta), axis.z * axis.y * (1 - cos(theta)) + axis.x * sin(theta), cos(theta) + axis.z * axis.z * (1 - cos(theta))}};

	// Calculate the rotated vector
	t_vector rotatedVector;
	rotatedVector.x = rotationMatrix[0][0] * bump_vec.x + rotationMatrix[0][1] * bump_vec.y + rotationMatrix[0][2] * bump_vec.z;
	rotatedVector.y = rotationMatrix[1][0] * bump_vec.x + rotationMatrix[1][1] * bump_vec.y + rotationMatrix[1][2] * bump_vec.z;
	rotatedVector.z = rotationMatrix[2][0] * bump_vec.x + rotationMatrix[2][1] * bump_vec.y + rotationMatrix[2][2] * bump_vec.z;

	return rotatedVector;
}

t_vector	shpere_bumpvec(t_vector p, t_hit_array *sp, t_hit_record* rec)
{
	double	u;
	double	v;

	u = (rec->normal.x + 1) * 0.5;
	v = (rec->normal.y + 1) * 0.5;
	int	x = (int)(sp->bump_w * u);
	int	y = (int)(sp->bump_h * v);
	int	index = (x + y * sp->bump_w) * 3;
	t_vector bump = new_vec(sp->bump_addr[index + 2] / 255.0, sp->bump_addr[index + 1] / 255.0, sp->bump_addr[index] / 255.0);
	bump = new_vec((bump.x - 0.5) * 2, (bump.y - 0.5) * 2, (bump.z - 0.5) * 2);
	rec->normal = bumprotateVector(rec->normal, bump);
	return (rec->normal);
}

t_vector	plane_bumpvec(t_vector p, t_hit_array *pl, t_hit_record* rec)
{
	double	u;
	double	v;

	u = fract(p.x * 0.2);
	v = fract(p.y * 0.2);
	int	x = (int)(pl->texture_w * u);
	int	y = (int)(pl->texture_h * v);
	int	index = (x + y * pl->texture_w) * 3;
	t_vector bump = new_vec(pl->bump_addr[index + 2] / 255.0, pl->bump_addr[index + 1] / 255.0, pl->bump_addr[index] / 255.0);
	bump = new_vec((bump.x - 0.5) * 2, (bump.y - 0.5) * 2, (bump.z - 0.5) * 2);
	rec->normal = bumprotateVector(rec->normal, bump);
	return (rec->normal);
}
