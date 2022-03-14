#include "minirt.h"

t_inter	*cyl_intersect_value(t_inter *ret, t_flist *figure_lst, float dist, t_vec *ray_origin, t_vec *ray_dir)
{
	t_cyl *cyl;

	cyl = (t_cyl *)figure_lst->content;
	ret->type = CYLINDER;
	ret->point = get_point(ray_origin, dist, ray_dir);
	ret->norm = cyl_normal(ret->point, cyl);
	ret->dist = dist;
	ret->figure = figure_lst->content;
	return (ret);
}

t_inter	*pl_intersect_value(t_inter *ret, t_flist *figure_lst, float dist, t_vec *ray_origin, t_vec *ray_dir)
{
	t_plane *plane;

	plane = (t_plane *)figure_lst->content;
	ret->type = PLANE;
	ret->norm = plane->nv_orientation;
	ret->point = get_point(ray_origin, dist, ray_dir);
	ret->dist = dist;
	ret->figure = figure_lst->content;
	return (ret);
}

t_inter	*sph_intersect_value(t_inter *ret, t_flist *figure_lst, float dist, t_vec *ray_origin, t_vec *ray_dir)
{
	t_sph *sph;

	sph = (t_sph *)figure_lst->content;
	ret->type = SPHERE;
	ret->point = get_point(ray_origin, dist, ray_dir);
	ret->norm = sph_normal(ret->point, sph);
	ret->dist = dist;
	ret->figure = figure_lst->content;
	return (ret);
}

t_inter	*ret_intersect(t_flist *figure_lst, float dist, t_vec *ray_origin, t_vec *ray_dir)
{
	t_inter	*ret_inter;

	ret_intersect = malloc(sizeof(t_inter));
	if (figure_lst->type == PLANE)
		pl_intersect_value(ret_inter, figure_lst, dist);
	else if (figure_lst->type == SPHERE)
		sph_intersect_value(ret_inter, figure_lst, dist);
	else if (figure_lst->type == CYLINDER)
		cyl_intersect_value(ret_inter, figure_lst, dist);
	return (ret_intersect);
}

t_inter	*intersect(t_vars *vars, t_vec *ray, t_flist *figure_lst, t_vec *ray_origin)
{
	t_inter	*ret_inter;
	int		size_lst;
	t_flist	*start;
	float	*dist;
	int		min_nbr;
	int		i;

	i = 0;
	start = figure_lst;
	vec_normalize(ray);
	size_lst = ft_flstsize(figure_lst);
	dist = malloc(sizeof(t_inter) * size_lst);
	while (figure_lst)
	{
		if (figure_lst->type == PLANE)
			dist[i] = plane_intersect(ray_origin, ray, figure_lst->content);
		else if (figure_lst->type == SPHERE)
			dist[i] = sphere_intersect(ray_origin, ray, figure_lst->content);
		else if (figure_lst->type == CYLINDER)
			dist[i] = cylinder_intersect(ray_origin, ray, figure_lst->content);
		i++;
		figure_lst = figure_lst->next;
	}
	min_nbr = find_min_nbr(dist, size_lst);
	if (dist[min_nbr] == -1)
	{
		free(dist);
		return (NULL);
	}
	ret_intersect = ret_intersect(find_node_lst(start, min_nbr), dist[min_nbr], ray_origin, ray);
	free(dist);
	return (ret_intersect);
}
