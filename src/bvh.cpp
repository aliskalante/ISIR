// bvh.cpp
#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"
#include <iostream>
#include <stdexcept>

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_meshList )
	{
		std::cout << "Constructing BVH..." << std::endl;
		if ( p_meshList == nullptr || p_meshList->empty() )
		{
			throw std::runtime_error( "BVH::build error no triangles supplied" );
		}
		_triangles = p_meshList;

		Chrono timer;
		timer.start();

		/// TODO: réellement construire la hiérarchie ici

		timer.stop();
		std::cout << "Completed in " << timer.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRec ) const
	{
		/// TODO: descendre la hiérarchie et remplir p_hitRec
		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRec );
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO: intersection rapide, sans record
		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
	}

	void BVH::_buildRec( BVHNode *			node,
						 const unsigned int startIdx,
						 const unsigned int triCount,
						 const unsigned int depthLevel )
	{
		/// TODO: split ou leaf selon triCount et depthLevel
	}

	bool BVH::_intersectRec( const BVHNode * node,
							 const Ray &	 ray,
							 const float	 tMin,
							 const float	 tMax,
							 HitRecord &	 rec ) const
	{
		/// TODO: intersection récursive
		return false;
	}

	bool BVH::_intersectAnyRec( const BVHNode * node, const Ray & ray, const float tMin, const float tMax ) const
	{
		/// TODO: test d’intersection court-circuité
		return false;
	}
} // namespace RT_ISICG
