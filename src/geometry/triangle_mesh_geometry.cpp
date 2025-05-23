#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"
#include <glm/gtc/epsilon.hpp>

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( unsigned int   idx0,
												unsigned int   idx1,
												unsigned int   idx2,
												MeshTriangle * parentMesh )
		: _meshPtr( parentMesh ), _i0( idx0 ), _i1( idx1 ), _i2( idx2 )
	{
		// compute initial flat normal
		const auto & verts = _meshPtr->_vertexList;
		Vec3f		 e1	   = verts[ _i1 ] - verts[ _i0 ];
		Vec3f		 e2	   = verts[ _i2 ] - verts[ _i0 ];
		_normalFace		   = glm::normalize( glm::cross( e1, e2 ) );
	}

	bool TriangleMeshGeometry::intersect( const Ray & ray, float & outT ) const
	{
		const auto &  verts = _meshPtr->_vertexList;
		const Vec3f & v0	= verts[ _i0 ];
		const Vec3f & v1	= verts[ _i1 ];
		const Vec3f & v2	= verts[ _i2 ];

		constexpr float EPS	  = glm::epsilon<float>();
		Vec3f			edgeA = v1 - v0;
		Vec3f			edgeB = v2 - v0;
		Vec3f			pVec  = glm::cross( ray.getDirection(), edgeB );
		float			det	  = glm::dot( edgeA, pVec );
		if ( glm::abs( det ) < EPS ) return false;

		float invDet = 1.0f / det;
		Vec3f tVec	 = ray.getOrigin() - v0;
		float u		 = invDet * glm::dot( tVec, pVec );
		if ( u < 0.0f || u > 1.0f ) return false;

		Vec3f qVec = glm::cross( tVec, edgeA );
		float v	   = invDet * glm::dot( ray.getDirection(), qVec );
		if ( v < 0.0f || ( u + v ) > 1.0f ) return false;

		float tHit = invDet * glm::dot( edgeB, qVec );
		outT	   = tHit;
		if ( tHit > EPS ) { return true; }

		// update flat normal based on barycentric coords
		_normalFace = ( 1.0f - u - v ) * v0 + u * v1 + v * v2;
		return false;
	}
} // namespace RT_ISICG
