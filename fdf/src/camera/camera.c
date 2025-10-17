/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:40:11 by ptison            #+#    #+#             */
/*   Updated: 2025/10/18 01:04:42 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/camera.h"

t_camera	init_camera_defaults(int width, int height)
{
	t_camera	camera;

	camera.alpha = 0.46373398 / 2;
	camera.beta = 0.46373398;
	camera.xrotate = 0;
	camera.yrotate = 0;
	camera.zrotate = 0;
	camera.x_offset = width / 2;
	camera.y_offset = height / 2;
	camera.zoom = 1;
	camera.zscale = 1;
	return (camera);
}

void	reset_camera(t_camera *cam, int width, int height)
{
	cam->alpha = 0.46373398 / 2;
	cam->beta = 0.46373398;
	cam->xrotate = 0;
	cam->yrotate = 0;
	cam->zrotate = 0;
	cam->x_offset = width / 2;
	cam->y_offset = height / 2;
	cam->zoom = 1;
	cam->zscale = 1;
}


void set_camera_isometric(t_camera *cam, int screen_w, int screen_h)
{
    cam->alpha   = M_PI / 4.0;                   // 45�
    cam->beta    = atan(1.0 / sqrt(2.0));        // \u22480.615479709 rad = 35.2643897�
    cam->xrotate = cam->yrotate = cam->zrotate = 0.0;
    cam->zoom    = 1.0;
    cam->zscale  = 1.0;
    cam->x_offset = screen_w  / 2;
    cam->y_offset = screen_h / 2;
}


// Projekce jednoho 3D bodu do 2D (ortho izometrie)
// Pořadí: Rz(alpha) -> Rx(beta) -> ortho projekce (zahodí z)
t_pt2 project_iso(const t_vec3 p_in, const t_camera *cam)
{
    // aplikuj případné převýšení na výšku
    double px = p_in.x;
    double py = p_in.y;
    double pz = p_in.z * cam->zscale;

    // + volitelné jemné rotace (sluč do základních úhlů)
    double A = cam->alpha + cam->zrotate; // kolem Z
    double B = cam->beta  + cam->xrotate; // kolem X
    // (pokud chceš mít i rotaci kolem Y, můžeš ji vložit mezi, ale pro izometrii není potřeba)

    double sA = sin(A), cA = cos(A);
    double sB = sin(B), cB = cos(B);

    // 1) rotace kolem Z
    double x1 =  cA*px - sA*py;
    double y1 =  sA*px + cA*py;
    double z1 =  pz;

    // 2) rotace kolem X
    double x2 =  x1;
    double y2 =  cB*y1 - sB*z1;
    double z2 =  sB*y1 + cB*z1;

    // 3) ortografická projekce (zahodíme z2)
    t_pt2 out;
    out.x = cam->x_offset + cam->zoom * x2;
    out.y = cam->y_offset - cam->zoom * y2; // mínus, ať roste nahoru
    (void)z2; // nevyužito v ortho režimu

    return out;
}
