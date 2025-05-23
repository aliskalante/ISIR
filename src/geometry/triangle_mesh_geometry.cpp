#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const uint	   p_v0,
												const uint	   p_v1,
												const uint	   p_v2,
												MeshTriangle * p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		_faceNormal = glm::normalize( glm::cross( _refMesh->_vertices[ p_v1 ] - _refMesh->_vertices[ p_v0 ],
												  _refMesh->_vertices[ p_v2 ] - _refMesh->_vertices[ p_v0 ] ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();
		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];
		const float	  E = 0.0000001;
		
		float a, f, u, v;
		Vec3f edge1 = v1 - v0;
		Vec3f edge2 = v2 - v0;
		Vec3f h		= glm::cross( d, edge2 );
		a			= glm::dot( edge1, h );
		if ( a > -E && a < E ) return false; 
		f		= 1.f / a;
		Vec3f s = o - v0;
		u		= f * ( glm::dot( s, h ) );
		if ( u < 0.0 || u > 1.0 ) return false;
		Vec3f q = glm::cross( s, edge1 );
		v		= f * glm::dot( d, q );
		if ( v < 0.0 || u + v > 1.0 ) return false;
		
		float t = f * glm::dot( edge2, q );
		p_t		= t;
		if ( t > E ) 
		{
			return true;
		}

		//const_cast<Vec3f &>(_faceNormal )= ( 1.f - u - v ) * v0 + u * v1 + v * v2;
		_faceNormal = ( 1.f - u - v ) * v0 + u * v1 + v * v2;
		
		return false;
	}

} // namespace RT_ISICG
		