#pragma once
#include <DirectXMath.h>
#include "tnl_matrix.h"
namespace tnl {
	class Vector3;
	class Matrix;
	class Quaternion final : public DirectX::XMFLOAT4 {
	public:
		Quaternion() noexcept : DirectX::XMFLOAT4(0, 0, 0, 1) {}
		Quaternion(DirectX::XMVECTOR& v) noexcept { DirectX::XMStoreFloat4(this, v); }
		Quaternion(DirectX::XMFLOAT4& v) noexcept { this->x = v.x; this->y = v.y; this->z = v.z; this->w = v.w; }

		//-----------------------------------------------------------------------------------------------------
		//
		// operator
		//
		const Quaternion& operator = (DirectX::XMVECTOR& other) noexcept;
		const Quaternion operator * (const Quaternion& other) const noexcept;
		const Quaternion& operator *= (const Quaternion& other) noexcept;

		//-----------------------------------------------------------------------------------------------------
		//
		// inline function
		//
		inline Matrix getMatrix() const noexcept {
			DirectX::XMFLOAT4X4 m4x4;
			DirectX::XMStoreFloat4x4(&m4x4, DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(this)));
			return m4x4;
		}

		//-----------------------------------------------------------------------------------------------------
		//
		// static function
		//
		static Quaternion RotationAxis(const Vector3& axis, const float rotate) noexcept;
		static Quaternion Subtract(const Quaternion& q1, const Quaternion& q2) noexcept;

		//-----------------------------------------------------------------------------------------------------
		//
		// function
		//
		Vector3 getEuler() const noexcept;
	};


	//-----------------------------------------------------------------------------------------------------
	inline const Quaternion& Quaternion::operator = (DirectX::XMVECTOR& other) noexcept {
		DirectX::XMStoreFloat4(this, other);
		return *this;
	}
	//-----------------------------------------------------------------------------------------------------
	inline const Quaternion Quaternion::operator * (const Quaternion& other) const noexcept {
		DirectX::XMVECTOR l = DirectX::XMLoadFloat4(this);
		DirectX::XMVECTOR r = DirectX::XMLoadFloat4(&other);
		DirectX::XMVECTOR v = DirectX::XMQuaternionMultiply(l, r);
		DirectX::XMFLOAT4 f4;
		DirectX::XMStoreFloat4(&f4, v);
		return f4;
	}
	//-----------------------------------------------------------------------------------------------------
	inline const Quaternion& Quaternion::operator *= (const Quaternion& other) noexcept {
		*this = *this * other;
		return *this;
	}

} 
