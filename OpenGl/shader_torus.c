/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_torus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:44:31 by fnieto            #+#    #+#             */
/*   Updated: 2016/05/02 23:42:59 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sp.a.x is radius;
** sp.a.y is thickness;
*/

float torus(s_cam cam, s_geo sp)
{
	vec3 ro = cam.pos - sp.pos;
	float odst = (length(ro) - sp.a.x - 1);
	ro += cam.ray * odst;
	vec3 rd = cam.ray;
	vec2 torus = sp.a.xy;
	float Ra2 = torus.x*torus.x;
	float ra2 = torus.y*torus.y;

	float m = dot(ro,ro);
	float n = dot(ro,rd);

	float k = (m - ra2 - Ra2)/2.0;
	float a = n;
	float b = n*n + Ra2*rd.z*rd.z + k;
	float c = k*n + Ra2*ro.z*rd.z;
	float d = k*k + Ra2*ro.z*ro.z - Ra2*ra2;
	//----------------------------------
	
	float p = -3.0*a*a     + 2.0*b;
	float q =  2.0*a*a*a   - 2.0*a*b   + 2.0*c;
	float r = -3.0*a*a*a*a + 4.0*a*a*b - 8.0*a*c + 4.0*d;
	p /= 3.0;
	r /= 3.0;
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
		float t1 = -d1 - h - a;
		float t2 = -d1 + h - a;
		if( t1>0.0 )
			result=t1;
		else if( t2>0.0 )
			result=t2;
	}
	h = d1*d1 - z - d2;
	if( h>0.0 )
	{
		h = sqrt(h);
		float t1 = d1 - h - a;
		float t2 = d1 + h - a;
		if(t1 > 0.0)
			result=min(result,t1);
		else if(t2 > 0.0)
			result=min(result,t2);
	}
	return (result + odst);
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
