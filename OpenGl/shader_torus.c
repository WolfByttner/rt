/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_torus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:44:31 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/03 15:41:00 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sp.a.x is radius;
** sp.a.y is thickness;
*/

float torus(s_cam cam, s_geo sp)
{
	vec3	pos;
	vec4	p1;
	vec4	p2;
	vec4	p3;

	pos = cam.pos - sp.pos;
	float odst = (length(pos) - sp.a.x - 1);
	if (odst > sp.a.x - 1)
		pos += cam.ray * odst;
	vec3 rd = cam.ray;
	vec2 torus = sp.a.xy;
	p1.x = sp.a.x*sp.a.x;
	p1.y = sp.a.y*sp.a.y;

	p1.z = dot(pos,pos);
	p1.w = dot(pos,cam.ray);
	if (p1.w > 0 && p1.z > pow(sp.a.x, 2))
		return (-1);
	p2.x = (p1.z - p1.y - p1.x) * .5;
	p3.x = p1.w;
	p3.y = p1.w * p1.w + p1.x * rd.z * rd.z + p2.x;
	p3.z = p2.x * p1.w + p1.x * pos.z * rd.z;
	p3.w = p2.x * p2.x + p1.x * pos.z * pos.z - p1.x * p1.y;
	//----------------------------------
	
	float p = (-3 * pow(p3.x, 2) + 2 * p3.y) / 3;
	float q = 2 * pow(p3.x, 3) - 2 * p3.x * p3.y + 2.0 * p3.z;
	float r = (-3 * pow(p3.x, 4) + 4 * p3.x * p3.x * p3.y - 8.0*p3.x*p3.z + 4.0*p3.w) / 3;
	float Q = p*p + r;
	float R = 3.0*r*p - p*p*p - q*q;
	float h = R*R - Q*Q*Q;
	float z = 0.0;
	if( h < 0.0 )
	{
		float sQ = sqrt(Q);
		z = 2.0*sQ*cos( acos(R/(sQ*Q)) / 3.0 );
	}
	else
	{
		float sQ = pow( sqrt(h) + abs(R), 1.0/3.0 );
		z = sign(R)*abs( sQ + Q/sQ );
	}
	z = p - z;
	//----------------------------------
	float d1 = z - 3.0*p;
	float d2 = z*z - 3.0*r;
	if( abs(d1)<1.0e-4 )
	{
		if( d2<0.0 )
			return -1.0;
		d2 = sqrt(d2);
	}
	else
	{
		if( d1<0.0 )
			return -1.0;
		d1 = sqrt( d1/2.0 );
		d2 = q/d1;
	}
	//----------------------------------
	float result = 1e20;
	h = d1*d1 - z + d2;
	if( h>0.0 )
	{
		h = sqrt(h);
		float t1 = -d1 - h - p3.x;
		float t2 = -d1 + h - p3.x;
		if( t1>0.0 )
			result=t1;
		else if( t2>0.0 )
			result=t2;
	}
	h = d1*d1 - z - d2;
	if( h>0.0 )
	{
		h = sqrt(h);
		float t1 = d1 - h - p3.x;
		float t2 = d1 + h - p3.x;
		if(t1 > 0.0)
			result=min(result,t1);
		else if(t2 > 0.0)
			result=min(result,t2);
	}
	return (result + (odst > sp.a.x - 1 ? odst : 0));
}

vec3 ntorus(vec3 pos, vec2 tor)
{
	return normalize(pos*(dot(pos,pos)- tor.y*tor.y - tor.x*tor.x*vec3(1.0,1.0,-1.0)));
}

s_res		torus_dst(s_geo sp, s_cam cam, s_res prev)
{
	s_res ret;

	ret.dst = torus(cam, sp);
	if (ret.dst > 0 && (ret.dst <= prev.dst || prev.dst < 0))
	{
		ret.mat = sp.mat;
		ret.cam = cam;
		ret.normal = ntorus(cam.pos - sp.pos + ret.dst * cam.ray, sp.a.xy);
		return (ret);
	}
	return (prev);
}
