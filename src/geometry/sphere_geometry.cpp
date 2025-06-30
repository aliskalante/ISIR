#include "sphere_geometry.hpp"


namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{

		/// TODO !
		Vec3f oc = p_ray.getOrigin() - _center; 
		float a	 = glm::dot( p_ray.getDirection(), p_ray.getDirection() ); 
		float b	 = 2.0f * glm::dot( oc, p_ray.getDirection() );			 
		float c	 = glm::dot( oc,oc ) - _radius * _radius;			
		

		float discriminant = b * b - 4 * a * c;

		if ( discriminant < 0 )
		{
			
			return false;
		}
		else
		{
			discriminant = std::sqrt( discriminant );
			p_t1		 = ( -b - discriminant ) / ( 2.0f * a );
			p_t2		 = ( -b + discriminant ) / ( 2.0f * a );

			if ( p_t1 > p_t2 ) { std::swap( p_t1, p_t2 ); }

			p_t1 = -1.f;
			p_t2 = -1.f;

			return true;
		}
	}

} // namespace RT_ISICG
