
#ifndef __RT_ISICG_SPOTLIGHT__
#define __RT_ISICG_SPOTLIGHT__

#include "lights/base_light.hpp"

namespace RT_ISICG
{
	class SpotLight : public BaseLight
	{
	  public:
		SpotLight()			 = delete;
		virtual ~SpotLight() = default;

		SpotLight( const Vec3f & pos, const Vec3f & col, float pow, float innerCutoffCos, float outerCutoffCos )
			: BaseLight( col, pow, true ), _pos( pos ), _innerCos( innerCutoffCos ), _outerCos( outerCutoffCos )
		{
		}

		virtual LightSample sample( const Vec3f & refPoint ) const override;

	  private:
		Vec3f _pos;
		float _innerCos;
		float _outerCos;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_SPOTLIGHT__
