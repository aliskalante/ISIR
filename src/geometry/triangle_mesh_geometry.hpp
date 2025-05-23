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
		TriangleMeshGeometry()			= delete;
		virtual ~TriangleMeshGeometry() = default;

		// Initialise with three vertex indices and reference to mesh
		TriangleMeshGeometry( unsigned int idx0, unsigned int idx1, unsigned int idx2, MeshTriangle * parentMesh );

		// Möller–Trumbore intersection test
		bool intersect( const Ray & ray, float & outT ) const;

		inline const Vec3f & getFaceNormal() const { return _normalFace; }

	  private:
		MeshTriangle * _meshPtr;
		unsigned int   _i0;
		unsigned int   _i1;
		unsigned int   _i2;
		mutable Vec3f  _normalFace;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_MESH_GEOMETRY__