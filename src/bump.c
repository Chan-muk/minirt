#include "minirt.h"

t_vector	bumprotatevector(t_vector normal, t_vector bump)
{
	const t_vector	stdvec = {0, 0, 1};
	const double	theta = acos(vec_dot(stdvec, unit_vec(normal)));
	const t_vector	axis = unit_vec(vec_prod(stdvec, unit_vec(normal)));
	double			rot[3][3];
	t_vector		rotvec;

	if (normal.x == stdvec.x && normal.y == stdvec.y && normal.z == stdvec.z)
		return (unit_vec(bump));
	bump = unit_vec(bump);
	rot[0][0] = cos(theta) + axis.x * axis.x * (1 - cos(theta));
	rot[0][1] = axis.x * axis.y * (1 - cos(theta)) - axis.z * sin(theta);
	rot[0][2] = axis.x * axis.z * (1 - cos(theta)) + axis.y * sin(theta);
	rot[1][0] = axis.y * axis.x * (1 - cos(theta)) + axis.z * sin(theta);
	rot[1][1] = cos(theta) + axis.y * axis.y * (1 - cos(theta));
	rot[1][2] = axis.y * axis.z * (1 - cos(theta)) - axis.x * sin(theta);
	rot[2][0] = axis.z * axis.x * (1 - cos(theta)) - axis.y * sin(theta);
	rot[2][1] = axis.z * axis.y * (1 - cos(theta)) + axis.x * sin(theta);
	rot[2][2] = cos(theta) + axis.z * axis.z * (1 - cos(theta));
	rotvec.x = rot[0][0] * bump.x + rot[0][1] * bump.y + rot[0][2] * bump.z;
	rotvec.y = rot[1][0] * bump.x + rot[1][1] * bump.y + rot[1][2] * bump.z;
	rotvec.z = rot[2][0] * bump.x + rot[2][1] * bump.y + rot[2][2] * bump.z;
	return (rotvec);
}

t_vector	shpere_bump(t_vector p, t_hit_array *sp, t_hit_record *rec)
{
	double			u;
	double			v;
	int				i;
	unsigned char	*addr;
	t_vector		bump;

	u = (rec->normal.x + 1) * 0.5;
	v = (rec->normal.y + 1) * 0.5;
	i = ((int)(sp->bump_w * u) + (int)(sp->bump_h * v) * sp->bump_w) * 3;
	addr = sp->bump_addr;
	bump = new_vec(addr[i + 2] / 255.0, addr[i + 1] / 255.0, addr[i] / 255.0);
	bump = new_vec((bump.x - 0.5) * 2, (bump.y - 0.5) * 2, (bump.z - 0.5) * 2);
	rec->normal = bumprotatevector(rec->normal, bump);
	return (rec->normal);
}

t_vector	plane_bump(t_vector p, t_hit_array *pl, t_hit_record *rec)
{
	double			u;
	double			v;
	int				i;
	unsigned char	*addr;
	t_vector		bump;

	u = fract(p.x * 0.2);
	v = fract(p.y * 0.2);
	i = \
	((int)(pl->texture_w * u) + (int)(pl->texture_h * v) * pl->texture_w) * 3;
	addr = pl->bump_addr;
	bump = new_vec(addr[i + 2] / 255.0, addr[i + 1] / 255.0, addr[i] / 255.0);
	bump = new_vec((bump.x - 0.5) * 2, (bump.y - 0.5) * 2, (bump.z - 0.5) * 2);
	rec->normal = bumprotatevector(rec->normal, bump);
	return (rec->normal);
}
