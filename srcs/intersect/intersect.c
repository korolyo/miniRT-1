
#include "minirt.h"


void	print_vect(t_vec *vec, char *name)
{
	printf("%s : x== %f, y == %f, z == %f\n", name, vec->x, vec->y, vec->z);
}

float	plane_intersect(t_camera *cam, t_vec *ray, t_plane *plane)
{
	float	denom;
	float	dist;
	t_vec	*p0lo;

	denom = dot_product(ray, plane->nv_orientation);
	if (!denom)
		return (0);
	p0lo = vec_subtraction(cam->d_origin, plane->d_coordinates);
	dist = dot_product(p0lo, plane->d_coordinates) / denom;
	free(p0lo);
	return(dist);
}

float	sphere_intersect(t_camera *cam, t_vec *ray, t_sph *sphere)
{
	float	b;
	float	c;
	float	discr;
	float	dist1; // ближняя дистанция
	float	dist2; // дальняя точка пересечения
	t_vec	*cam_sphere;

	dist1 = 0;
	dist2 = 0;
	b = 0;
	c = 0;
	cam_sphere = vec_subtraction(cam->d_origin, sphere->center);
	b = 2 * (dot_product(cam_sphere, ray));
	c = dot_product(cam_sphere, cam_sphere) - (sphere->rad * sphere->rad);
	discr = (b * b) - (4 * c);
	free(cam_sphere);
	if (discr < 0)
		return (0);                           // No intersection
	dist1 = (((b * -1) - sqrt(discr)) / (2));   // видимая область
	dist2 = (((b * -1) + sqrt(discr)) / (2));		// на всякий случай.
//	 printf("dist1 == %f dist2 == %f\n", dist1, dist2);
	if (dist1 > 0)
		return (dist1);
//	t_vec	*hit_position = vect_multipl_on(ray, dist1); // точка
//	соприкосновения
	return (0.0);
}

// ray = D
// x = vec_subtraction(cam->d_origin, cyl->d_coordinates);
// v = cyl->nv_orientation

/*
   a   = D|D - (D|V)^2
   b/2 = D|X - (D|V)*(X|V)
   c   = X|X - (X|V)^2 - r*r
   P = O + D*t
*/

float cylinder_intersect(t_camera *cam, t_vec *ray, t_cyl *cyl)
{
	t_vect	*camera_cy;
	float	a;
	float	b;
	float	c;
	float	dist[2];
	float	discr;
	float	tmp;
	t_vec	*p;
	float	len;
	t_vec	*norm;
	t_vec	*p_on_axis;
	
	
	camera_cy = vec_subtraction(cam->d_origin, cyl->d_coordinates);
	// print_vect(cam->d_origin, "cam->d_origin");
	// print_vect(cyl->d_coordinates, "cyl->d_coordinates");
	// printf("co = %f\n", dot_product(camera_cy, camera_cy));
	tmp = dot_product(ray, cyl->nv_orientation);

	a = ((tmp * tmp) - 1);
	b = 2 * ((tmp * dot_product(camera_cy, cyl->nv_orientation)) - dot_product(ray, camera_cy));
	tmp = dot_product(cyl->nv_orientation, camera_cy);
	c = (tmp * tmp) + (powf(cyl->diam * 0.5, 2) - dot_product(camera_cy, camera_cy));

	free(camera_cy);
	discr = (b * b) - (4 * a * c);
	// printf("b = %f, a = %f, c = %f\n", b, a, c);
	// printf("discr = %f\n", discr);
	if (discr < 0)
		return (0);
	dist[0] = (((b * -1) - sqrt(discr)) / 2 * a);
	dist[1] = (((b * -1) + sqrt(discr)) / 2 * a);
	vec_mult(ray, dist[0]);
	p = vec_sum(cam->d_origin, ray);
	len = dot_product(cyl->nv_orientation, p);
	// printf("len == %f\n", len);
	if (len >= cyl->height / 2 || len  * -1 >= cyl->height / 2)
		return (0);
	p_on_axis = new_vector(cyl->d_coordinates->x, cyl->d_coordinates->y, cyl->d_coordinates->z);
	vec_mult(p_on_axis, len);
	p_on_axis = vec_sum(p_on_axis, cyl->d_coordinates);
	norm = vec_subtraction(p_on_axis, p);
	vect_normalize(norm);
	if(dist[0] > 0)
		return (dist[0]);
	return (0);
}
