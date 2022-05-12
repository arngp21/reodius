#pragma once
#include "tnl_vector.h"

namespace tnl {

	class IRect {
	public:
		IRect() {}

		inline float cx(const float lx, const float rx) { return (lx + rx) * 0.5f; }
		inline float cy(const float ly, const float ry) { return (ly + ry) * 0.5f; }
		inline float ltx(const tnl::Vector3& ofs, const float w, const float h) { return ofs.x - w * 0.5f; }
		inline float lty(const tnl::Vector3& ofs, const float w, const float h) { return ofs.y - h * 0.5f; }
		inline float rbx(const tnl::Vector3& ofs, const float w, const float h) { return ofs.x + w * 0.5f; }
		inline float rby(const tnl::Vector3& ofs, const float w, const float h) { return ofs.y + h * 0.5f; }

	};

}
