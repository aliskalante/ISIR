// triangle_mesh_geometry.hpp
#ifndef __RT_ISICG_TRIANGLE_MESH_GEOMETRY__
#define __RT_ISICG_TRIANGLE_MESH_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class MeshTriangle;

	class TriangleMeshGeometry : public BaseGeometry
	{
	  public:
		TriangleMeshGeometry( unsigned int p_v0, unsigned int p_v1, unsigned int p_v2, MeshTriangle * p_mesh );

		bool intersect( const Ray & p_ray, float & p_t ) const;

		inline const Vec3f & getFaceNormal() const { return _faceNormal; }

	  private:
		MeshTriangle * _meshPtr;
		unsigned int   _v0;
		unsigned int   _v1;
		unsigned int   _v2;
		mutable Vec3f  _faceNormal;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_MESH_GEOMETRY__

// triangle_mesh_geometry.cpp
#include "objects/mesh_triangle.hpp"
#include "triangle_mesh_geometry.hpp"
#include <glm/gtc/epsilon.hpp>

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( unsigned int   p_v0,
												unsigned int   p_v1,
												unsigned int   p_v2,
												MeshTriangle * p_mesh )
		: _meshPtr( p_mesh ), _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 )
	{
		const auto & verts = _meshPtr->_vertexList;
		Vec3f		 edge1 = verts[ _v1 ] - verts[ _v0 ];
		Vec3f		 edge2 = verts[ _v2 ] - verts[ _v0 ];
		_faceNormal		   = glm::normalize( glm::cross( edge1, edge2 ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const auto &  verts = _meshPtr->_vertexList;
		const Vec3f & v0	= verts[ _v0 ];
		const Vec3f & v1	= verts[ _v1 ];
		const Vec3f & v2	= verts[ _v2 ];

		constexpr float EPS	  = glm::epsilon<float>();
		Vec3f			edge1 = v1 - v0;
		Vec3f			edge2 = v2 - v0;
		Vec3f			pvec  = glm::cross( p_ray.getDirection(), edge2 );
		float			det	  = glm::dot( edge1, pvec );
		if ( glm::abs( det ) < EPS ) return false;

		float invDet = 1.0f / det;
		Vec3f tvec	 = p_ray.getOrigin() - v0;
		float u		 = invDet * glm::dot( tvec, pvec );
		if ( u < 0.0f || u > 1.0f ) return false;

		Vec3f qvec = glm::cross( tvec, edge1 );
		float v	   = invDet * glm::dot( p_ray.getDirection(), qvec );
		if ( v < 0.0f || ( u + v ) > 1.0f ) return false;

		float tt = invDet * glm::dot( edge2, qvec );
		if ( tt < EPS ) return false;

		p_t			= tt;
		_faceNormal = ( ( 1.0f - u - v ) * v0 + u * v1 + v * v2 );
		return true;
	}
} // namespace RT_ISICG
