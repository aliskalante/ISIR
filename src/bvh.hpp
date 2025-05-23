// bvh.hpp
#ifndef __RT_ISICG_BVH__
#define __RT_ISICG_BVH__

#include "aabb.hpp"
#include "hit_record.hpp"
#include <vector>

namespace RT_ISICG
{
	class TriangleMeshGeometry;

	struct BVHNode
	{
		BVHNode() = default;
		~BVHNode()
		{
			delete left;
			delete right;
		}

		bool isLeaf() const { return ( left == nullptr && right == nullptr ); }

		AABB		 bounds;
		BVHNode *	 left		   = nullptr;
		BVHNode *	 right		   = nullptr;
		unsigned int firstTriangle = 0;
		unsigned int lastTriangle  = 0;
	};

	class BVH
	{
	  public:
		BVH() = default;
		~BVH() { delete _root; }

		// Construire l’arbre à partir d’une liste de triangles
		void build( std::vector<TriangleMeshGeometry> * p_meshList );

		// Intersection la plus proche
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRec ) const;
		// Simple test d’intersection (any-hit)
		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const;

	  private:
		void _buildRec( BVHNode * node, unsigned int startIdx, unsigned int triCount, unsigned int depthLevel );
		bool _intersectRec( const BVHNode * node, const Ray & p_ray, float tMin, float tMax, HitRecord & rec ) const;
		bool _intersectAnyRec( const BVHNode * node, const Ray & p_ray, float tMin, float tMax ) const;

	  private:
		std::vector<TriangleMeshGeometry> * _triangles = nullptr;
		BVHNode *							_root	   = nullptr;

		const unsigned int maxLeafSize	 = 8;
		const unsigned int maxDepthLevel = 32;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BVH__
