#ifndef __RT_ISICG_MESH_TRIANGLE__
#define __RT_ISICG_MESH_TRIANGLE__

#include "aabb.hpp"
#include "base_object.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include <vector>

namespace RT_ISICG
{
	class MeshTriangle : public BaseObject
	{
		friend class TriangleMeshGeometry;

	  public:
		MeshTriangle() = delete;
		MeshTriangle( const std::string & name ) : BaseObject( name ) {}
		virtual ~MeshTriangle() = default;

		size_t getVertexCount() const { return _vertexList.size(); }
		size_t getTriangleCount() const { return _faceList.size(); }

		inline void addVertex( float x, float y, float z )
		{
			_vertexList.emplace_back( x, y, z );
			_bounds.extend( Vec3f( x, y, z ) );
		}

		inline void addNormal( float x, float y, float z ) { _normalList.emplace_back( x, y, z ); }

		inline void addUV( float u, float v ) { _uvList.emplace_back( u, v ); }

		// Ajoute un triangle via indices des sommets
		inline void addTriangle( unsigned int i0, unsigned int i1, unsigned int i2 )
		{
			_faceList.emplace_back( TriangleMeshGeometry( i0, i1, i2, this ) );
		}

		bool intersect( const Ray & ray, float tMin, float tMax, HitRecord & record ) const override;
		bool intersectAny( const Ray & ray, float tMin, float tMax ) const override;

	  private:
		std::vector<Vec3f>				  _vertexList;
		std::vector<Vec3f>				  _normalList;
		std::vector<Vec2f>				  _uvList;
		std::vector<TriangleMeshGeometry> _faceList;
		AABB							  _bounds;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_MESH_TRIANGLE__
